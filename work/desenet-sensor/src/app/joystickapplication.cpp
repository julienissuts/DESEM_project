#include "joystickapplication.h"
#include "xf/xfevent.h"

using app::JoystickApplication;

JoystickApplication::JoystickApplication():evDataBuffer(1){ ////SharedBuffer(sizeType length) 1bytes length
}


void JoystickApplication::onPositionChange(IJoystick::Position position){
    memcpy(evDataBuffer.data(), &position.position,sizeof(position.position));//void *memcpy(void *dest, const void *src, size_t n);
    sensor::AbstractApplication::evPublishRequest(EVID_JOYSTICK, evDataBuffer);
}
