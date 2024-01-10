#include "joystickapplication.h"
#include "xf/xfevent.h"
#include <iostream>

using app::JoystickApplication;

JoystickApplication::JoystickApplication():evDataBuffer(1){ ////SharedBuffer(sizeType length) 1bytes length
}

void JoystickApplication::start()
{
    board::Joystick::instance().start();   // start fsm of Joystick
    startBehavior();// send initial event for this fsm
}

void JoystickApplication::initialize()
{
    board::Joystick::instance().initialize();          // initialize Joystick
    board::Joystick::instance().setObserver(this);     // set observer of Joystick
    state = lastState = STATE_INIT;
}

EventStatus JoystickApplication::processEvent() // an SM is used so the ISR onPositionchange is the minimum size. We handle pubication of event in the SM.
{
    // will we handle the event ?
    EventStatus result = EventStatus::Unknown;
    // save the current state
    smState lastState = state;
    // get the actual event
    const IXFEvent* ev = this->getCurrentEvent();

    // transition switch
    switch (state) {
    case STATE_INIT:
        if (ev->getEventType() == IXFEvent::Initial)
        {
            state = STATE_WAIT;
        }
        break;
    case STATE_WAIT:
        if (ev->getEventType() == IXFEvent::Event && ev->getId() == 5)
        {
            state = STATE_SENDPOS;
        }
        break;
    case STATE_SENDPOS:
        if (ev->getEventType() == IXFEvent::NullTransition)
        {
            state = STATE_WAIT;
        }
        break;
    default:
        assert(true);
    }

    // action switch
    if (lastState != state)
    {
        switch (state) {
        case STATE_INIT:

            break;
        case STATE_WAIT:

            break;
        case STATE_SENDPOS:

            sensor::AbstractApplication::evPublishRequest(EVID_JOYSTICK, evDataBuffer);//hier wird das event auf die Liste appended
            GEN(XFNullTransition());
            break;
        }
    }
    else
    {
        result = EventStatus::NotConsumed;
    }
    return result;

}


void JoystickApplication::onPositionChange(IJoystick::Position position){

    std::cout << "onPosition Called";
    std::cout << std::endl;
    memcpy(evDataBuffer.data(), &position.position,sizeof(position.position));//void *memcpy(void *dest, const void *src, size_t n);
    //sensor::AbstractApplication::evPublishRequest(EVID_JOYSTICK, evDataBuffer);//hier wird das event auf die Liste appended
    GEN(XFEvent(5)); //generate an event of ID = 5, i chose this id for the joystick event.
}
