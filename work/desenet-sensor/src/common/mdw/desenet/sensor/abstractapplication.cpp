#include "desenet/sensor/net.h"
#include "abstractapplication.h"

using desenet::sensor::AbstractApplication;

/*********************************************************************************************************
* TODO: Implement the protected methods of the AbstractApplication class here. From these you have to    *
* call the different methods on your DESENET Controller Entity implementation...                         *
*********************************************************************************************************/

// Default implementations.

void AbstractApplication::svSyncRequest()
{
    // TODO: Register application using the network entity
    NetworkEntity::instance().svSyncRequest(this);
    //in the abstractApplication we call the svSyncRequest method from networkEntity
}

bool AbstractApplication::svPublishRequest(SvGroup group)
{
    // TODO: Register application for the provided group using the network entity

    return NetworkEntity::instance().svPublishRequest(this, group);
    // we call the svPublishRequest method in NetworkEntity
}

void AbstractApplication::evPublishRequest(EvId id, const SharedByteBuffer & evData)
{
    // TODO: Publish event data

    NetworkEntity::instance().evPublishRequest(id, evData);// calls evPublishRequest of NetworkEntity
}

/**
 * Default callback method for syncs
 */
void AbstractApplication::svSyncIndication(desenet::NetworkTime)
{
}

/**
 * Default callback method for SV publishes
 */
SharedByteBuffer::sizeType AbstractApplication::svPublishIndication(SvGroup, SharedByteBuffer &)
{
    return 0;
}
