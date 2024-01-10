#include <assert.h>
#include <array>
#include <list>
#include <map>
#include <vector>
#include <utility>
#include "platform-config.h"
#include "board/ledcontroller.h"
#include "desenet/frame.h"
#include "desenet/beacon.h"
#include "desenet/timeslotmanager.h"
#include "abstractapplication.h"
#include "networkentity.h"

using std::array;
using std::bind;
using std::list;
using std::make_pair;
using std::map;
using std::pair;
using std::vector;

using desenet::sensor::NetworkEntity;

NetworkEntity *NetworkEntity::_pInstance(nullptr); // Instantiation of static attribute

NetworkEntity::NetworkEntity()
    : _pTimeSlotManager(nullptr),
      _pTransceiver(nullptr)
{
    assert(!_pInstance); // Only one instance allowed
    _pInstance = this;
}

NetworkEntity::~NetworkEntity()
{
}

void NetworkEntity::initialize()
{
}

void NetworkEntity::initializeRelations(ITimeSlotManager &timeSlotManager, NetworkInterfaceDriver &transceiver)
{
    _pTimeSlotManager = &timeSlotManager;
    _pTransceiver = &transceiver;

    // TODO: Add additional initialization code here
    _pTimeSlotManager->setObserver(*this); // Set the observer of the time slot manager to this instance
                                           // Set the receive callback between transceiver and network. Bind this pointer to member function
    transceiver.setReceptionHandler(std::bind(&NetworkEntity::onReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

/**
 * This method does not automatically create an instance if there is none created so far.
 * It is up the the developer to create an instance of this class prior to access the instance() method.
 */
// static
NetworkEntity &NetworkEntity::instance()
{
    assert(_pInstance);
    return *_pInstance;
}

SlotNumber NetworkEntity::slotNumber() const
{
    return timeSlotManager().slotNumber();
}

void NetworkEntity::svSyncRequest(AbstractApplication *app)
{
    syncList.push_back(app); // makes new element in list,
    // remember: a list is non-contagious and each element has a ptr to next & previous
    // push_back concats a new element to the list.
}

bool NetworkEntity::svPublishRequest(AbstractApplication *app, SvGroup group)
{
    // the Sensor app calls the publishRequest giving its group and a ptr to the app
    if (publishers_Arr[group] == nullptr)
    {                                // if no app is in the slot of this group...
        publishers_Arr[group] = app; //... we store the ptr to the app into the group list
        return true;
    }
    else
    {
        return false; // if we have already a ptr to an app, we get an error
    }
}

void NetworkEntity::evPublishRequest(EvId evid, const SharedByteBuffer &evdata)
{
    // if the joystick creates an event the event is pushed into the eList

    EventElement event(evid, evdata); // create an event element with the event id and the event data

    eList.push_back(event); // push the event into the list
}

void NetworkEntity::onTimeSlotSignal(const ITimeSlotManager &timeSlotManager, const ITimeSlotManager::SIG &signal)
{
    //  if correct signal comes then send mpdu
    if (signal == timeSlotManager.OWN_SLOT_START)// if the signal is the start of our slot
    {
        *_pTransceiver << _mpdu;// send the mpdu, << is an overload operator... the mpdu is sent to what _pTransceiver points to

        _mpdu.clear();// reset the mpdu
    }
}

/**
 * Called by the NetworkInterfaceDriver (layer below) after reception of a new frame
 */
void NetworkEntity::onReceive(NetworkInterfaceDriver &driver, const uint32_t receptionTime, const uint8_t *const buffer, size_t length)
{
    (void)(driver);// unused parameter
    (void)(receptionTime);// unused parameter
    Frame frame = Frame::useBuffer(buffer, length);// create a frame with the buffer and the length

    // TODO: Add your code here

    if (frame.type() == FrameType::Beacon)// if the frame is a beacon
        ledController().flashLed(0); // param = 0 damit led geflasht wird

        // mach tram to beacon mit beacon klasse
        Beacon b(frame);

        // send timeslot to timeslotmanager 
        _pTimeSlotManager->onBeaconReceived(b.slotDuration());

        SharedByteBuffer buff;// create a SharedByteBuffer object

        for (desenet::SvGroup svgroup = 0; svgroup < 16; svgroup++)// for each svgroup
        {
            desenet::SharedByteBuffer::sizeType dataSize = 0;
            buff = _mpdu.proxy2mpdu();

            if (publishers_Arr[svgroup] != nullptr)// if there is an app in the slot of this group
            {
                //_mpdu.printMPDU();
                dataSize = publishers_Arr[svgroup]->svPublishIndication(svgroup, buff);// we call the svPublishIndication of the app
                //_mpdu.printMPDU();
                if (dataSize > 0)// if there is data to send
                {
                    //_mpdu.printMPDU();
                    _mpdu.writePDUHeader(0, svgroup, dataSize); // 0 for SV,
                    //_mpdu.printMPDU();
                }
            }
        }

        while (!eList.empty())// while the list of events is not empty
        {
            buff = _mpdu.proxy2mpdu();// create a SharedByteBuffer object tied to the mpdu frame
            memcpy(buff.data(), eList.front().data.data(), eList.front().data.length()); // data is written into PDU
            // front() returns a reference to first object
            // begin() returns an iterator to first object
            _mpdu.writePDUHeader(1, eList.front().id, eList.front().data.length()); // Header of added data is created
            eList.erase(eList.begin());// erase the first element of the list
            //_mpdu.printMPDU();
        }

        for (auto &p : syncList) // put syncIndication after read of sampled values 
        {
            if (p != nullptr)// if there is an app in this element of the list
            {
                p->svSyncIndication(b.networkTime()); // svSyncIndication(NetworkTime)
                // we send a syncIndication to each registered app
            }
        }
    }
}
// die init von ledController ist im factory.cpp gemacht
// diese funktion könnte auch durch board::LedController::instance(); ersetzt werden
board::LedController &NetworkEntity::ledController() const
{
    return board::LedController::instance();
}
