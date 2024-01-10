#ifndef JOYSTICKAPPLICATION_H
#define JOYSTICKAPPLICATION_H

#include "board/interfaces/ijoystickobserver.h"
#include "desenet/sensor/abstractapplication.h"
#include "joystick.h"

namespace app
{

class JoystickApplication : public IJoystickObserver,
                            public desenet::sensor::AbstractApplication,
                            public XFReactive

{
public:
    JoystickApplication();
    //virtual ~JoystickApplication();
    void initialize();
    void start();                                    //CHANGED
    SharedByteBuffer evDataBuffer;
    const desenet::EvId ID = EVID_JOYSTICK;
    IJoystick::Position pos;
    // XFReactive implementation
protected:
//    virtual EventStatus processEvent();		///< Implements the state machine.

private:
    // this is a callback that is called whenever the joystick change values
    //implementation from iJoystick
    void onPositionChange(IJoystick::Position position);

    EventStatus processEvent();
    enum smState {STATE_INIT, STATE_WAIT, STATE_SENDPOS};
    smState state, lastState;

};
} //namespace app end

#endif // JOYSTICKAPPLICATION_H
