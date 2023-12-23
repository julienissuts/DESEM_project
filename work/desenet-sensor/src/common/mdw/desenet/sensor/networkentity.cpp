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
using std::list;
using std::map;
using std::make_pair;
using std::bind;
using std::pair;
using std::vector;

using desenet::sensor::NetworkEntity;

NetworkEntity * NetworkEntity::_pInstance(nullptr);		// Instantiation of static attribute

NetworkEntity::NetworkEntity()
 : _pTimeSlotManager(nullptr),
   _pTransceiver(nullptr)
{
    assert(!_pInstance);		// Only one instance allowed
    _pInstance = this;
}

NetworkEntity::~NetworkEntity()
{
}

void NetworkEntity::initialize()
{
}

void NetworkEntity::initializeRelations(ITimeSlotManager & timeSlotManager, NetworkInterfaceDriver & transceiver)
{
    _pTimeSlotManager = &timeSlotManager;
    _pTransceiver = &transceiver;

    // TODO: Add additional initialization code here
    _pTimeSlotManager->setObserver(*this);
     // Set the receive callback between transceiver and network. Bind this pointer to member function
    transceiver.setReceptionHandler(std::bind(&NetworkEntity::onReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

/**
 * This method does not automatically create an instance if there is none created so far.
 * It is up the the developer to create an instance of this class prior to access the instance() method.
 */
//static
NetworkEntity & NetworkEntity::instance()
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
    //remember: a list is non-contagious and each element has a ptr to next & previous
    //push_back concats a new element to the list.
}

bool NetworkEntity::svPublishRequest(AbstractApplication *app, SvGroup group)
{
    //the Sensor app calls the publishRequest giving its group, what is the ptr to "app"???
    if(publishers_Arr[group] == nullptr){ //if no app is in the slot of this group...
        publishers_Arr[group] = app;//... we store the ptr to the app into the group list
        return true;
    }
    else{
        return false;//if we have already a ptr to an app, we get an error
    }

}

void NetworkEntity::onTimeSlotSignal(const ITimeSlotManager &timeSlotManager, const ITimeSlotManager::SIG &signal)
{

}

/**
 * Called by the NetworkInterfaceDriver (layer below) after reception of a new frame
 */
void NetworkEntity::onReceive(NetworkInterfaceDriver & driver, const uint32_t receptionTime, const uint8_t * const buffer, size_t length)
{
    (void)(driver);
    (void)(receptionTime);
    Frame frame = Frame::useBuffer(buffer, length);

    // TODO: Add your code here

    if(frame.type() == FrameType::Beacon){ //kontrolle ob unser frame ein beacon ist
        ledController().flashLed(0);//param = 0 damit led geflasht wird

        //mach tram to beacon mit beacon klasse
        Beacon b(frame);
        // _pTimeSlotManager->onBeaconReceived(b.slotDuration())


        for(auto& p : syncList)
        {
            if(p != nullptr){
                p->svSyncIndication(b.networkTime()); //svSyncIndication(NetworkTime)
            //we send a syncIndication to each registered app
            }
        }

        MPDU _mpdu;
        SharedByteBuffer buff;

        for(desenet::SvGroup svgroup = 0; svgroup< 16; svgroup++){

            desenet::SharedByteBuffer::sizeType dataSize=0;
            buff = _mpdu.proxy2mpdu();

            if(publishers_Arr[svgroup]!=nullptr){

                _mpdu.printMPDU();

                dataSize = publishers_Arr[svgroup]->svPublishIndication(svgroup,buff);
                _mpdu.printMPDU();

                if(dataSize > 0)
                {
                    _mpdu.printMPDU();
                    _mpdu.writePDUHeader(1,svgroup,dataSize);
                    _mpdu.printMPDU();
                }
            }
        }

    }

}
//die init von ledController ist im factory.cpp gemacht
//diese funktion könnte auch durch board::LedController::instance(); ersetzt werden
board::LedController & NetworkEntity::ledController() const
{
    return board::LedController::instance();
}
