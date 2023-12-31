#ifndef SENSOR_NETWORK_ENTITY_H
#define SENSOR_NETWORK_ENTITY_H

#include <assert.h>
#include <list>
#include <array>
#include "platform-config.h"
#include "desenet/desenet.h"
#include "desenet/networkinterfacedriver.h"
#include "desenet/itimeslotmanager.h"
#include "../mpdu.h"

// Forward declaration of class(es) in namespace board
namespace board {
    class LedController;
}

using desenet::NetworkInterfaceDriver;
using namespace desenet;

namespace desenet {
namespace sensor {

class AbstractApplication;
class Net;

/**
 * @brief Implements the desenet protocol on the network layer.
 */
class NetworkEntity : public ITimeSlotManager::Observer
{
    friend class AbstractApplication;
    friend class Net;

public:
    NetworkEntity();
    virtual ~NetworkEntity();

    void initialize();																						///< Initializes the instance.
    void initializeRelations(ITimeSlotManager & timeSlotManager, NetworkInterfaceDriver & transceiver);		///< Initializes all relations needed by the instance.

    static NetworkEntity & instance();																		///< Returns reference to single instance.

    desenet::SlotNumber slotNumber() const;     ///< Returns the actual slot number.


protected:
    /**
     * @brief Holds event information.
     */
    struct EventElement
    {
        EventElement(EvId id, const SharedByteBuffer & data)
         : id(id), data(data)
        {}

        EvId id;						///< Event identifier (ex. EVID_JOYSTICK).
        const SharedByteBuffer data;	///< Data that goes together with the event.
    };

    // desenet::NetworkInterfaceDriver::Callback callback
protected:
    /**
     * @brief Called by the lower layer after reception of a new frame
     */
    void onReceive(NetworkInterfaceDriver & driver, const uint32_t receptionTime, const uint8_t * const buffer, size_t length);

protected:
    inline ITimeSlotManager & timeSlotManager() const { assert(_pTimeSlotManager); return *_pTimeSlotManager; }	///< Internal access to TimeSlotManager
    inline NetworkInterfaceDriver & transceiver() const { assert(_pTransceiver); return *_pTransceiver; }		///< Internal access to Transceiver
    board::LedController & ledController() const;																///< Internal access to	LedController

protected:
    typedef std::list<AbstractApplication *> ApplicationSyncList; // is a dynamic list of AbstractApplication, die Elemente sind nicht zusammenhängend, jedes Element hat einen ptr zum nächsten Element.
    typedef std::array<AbstractApplication *, 16> ApplicationPublishersArray;
    typedef std::list<EventElement> EventElementList;

protected:
    static NetworkEntity * _pInstance;				///< Pointer to single instance.
    ITimeSlotManager * _pTimeSlotManager;			///< Pointer to TimeSlotManager.
    NetworkInterfaceDriver * _pTransceiver;			///< Pointer to transceiver.

private:
    MPDU _mpdu;
    EventElementList eList; //stores all the events in a list
    ApplicationSyncList syncList; // list for all apps which want to receive svSyncIndications() if beacon arrives
    ApplicationPublishersArray publishers_Arr;

    void evPublishRequest(EvId evid, const SharedByteBuffer &evdata);
    void svSyncRequest(AbstractApplication *app);
    bool svPublishRequest(AbstractApplication *app, SvGroup group);

    void onTimeSlotSignal(const ITimeSlotManager & timeSlotManager, const ITimeSlotManager::SIG & signal)override;
};

} // sensor
} // desenet
#endif // SENSOR_NETWORK_ENTITY_H
