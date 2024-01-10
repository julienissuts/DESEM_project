#include "joystickapplication.h"
#include "xf/xfevent.h"
#include <iostream>

using app::JoystickApplication;

JoystickApplication::JoystickApplication() : evDataBuffer(1)
{ ////SharedBuffer(sizeType length) 1bytes length
}

void JoystickApplication::start()
{
    board::Joystick::instance().start(); // start fsm of Joystick
    startBehavior();                     // send initial event for this fsm
}

void JoystickApplication::initialize()
{
    board::Joystick::instance().initialize();      // initialize Joystick
    board::Joystick::instance().setObserver(this); // set observer
    state = lastState = STATE_INIT;                // set initial state of the fsm
}

EventStatus JoystickApplication::processEvent()
{

    EventStatus result = EventStatus::Unknown;    // initial status of the event
    smState lastState = state;                    // save last state
    const IXFEvent *ev = this->getCurrentEvent(); // get current event

    // transition switch
    switch (state)
    {
    case STATE_INIT:
        if (ev->getEventType() == IXFEvent::Initial) // if the event is initial
        {
            state = STATE_WAIT; // set state to wait
        }
        break;
    case STATE_WAIT:
        if (ev->getEventType() == IXFEvent::Event && ev->getId() == 5) // if the event is an event and the id is 5
        {
            state = STATE_SENDPOS; // set state to sendpos
        }
        break;
    case STATE_SENDPOS:
        if (ev->getEventType() == IXFEvent::NullTransition) // if the event is a null transition
        {
            state = STATE_WAIT; // set state to wait
        }
        break;
    default:
        assert(true); // if the state is not one of the above, assert
    }

    // action switch
    if (lastState != state)
    {
        switch (state)
        {
        case STATE_INIT:

            break;
        case STATE_WAIT:

            break;
        case STATE_SENDPOS:
            sensor::AbstractApplication::evPublishRequest(EVID_JOYSTICK, evDataBuffer); // hier wird das event auf die Liste appended
            GEN(XFNullTransition());                                                    // generate a null transition
            break;
        }
    }
    else
    {
        result = EventStatus::NotConsumed; // if the event is not consumed, return not consumed
    }
    return result;
}

void JoystickApplication::onPositionChange(IJoystick::Position position)
{
    std::cout << "onPosition Called";
    std::cout << std::endl;
    memcpy(evDataBuffer.data(), &position.position, sizeof(position.position)); // void *memcpy(void *dest, const void *src, size_t n);
    GEN(XFEvent(5));                                                            // generate an event of ID = 5, i chose this id for the joystick event.
}
