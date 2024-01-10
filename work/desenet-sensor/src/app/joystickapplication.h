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
        /**
         * @brief Constructor for the JoystickApplication class.
         *
         * Initializes the evDataBuffer with a length of 1 byte.
         */
        JoystickApplication();
        /**
         * @brief Initializes the JoystickApplication.
         *
         * This involves initializing the joystick, setting the observer of the joystick, and setting the initial state.
         */
        void initialize();
        /**
         * @brief Starts the JoystickApplication.
         *
         * This involves starting the joystick's finite state machine (FSM) and sending an initial event for this FSM.
         */
        void start();

        SharedByteBuffer evDataBuffer;
        const desenet::EvId ID = EVID_JOYSTICK;
        IJoystick::Position pos;
        // XFReactive implementation
    protected:
    private:
        /**
         * @brief Callback function that is called whenever the joystick changes position.
         *
         * This function is an implementation from the IJoystick interface. It is responsible for handling changes in the joystick's position.
         *
         * @param position The new position of the joystick.
         */
        void onPositionChange(IJoystick::Position position);

        /**
         * @brief Processes an event.
         *
         * This method is part of the state machine implementation. It checks the current state and event type, and changes the state accordingly.
         *
         * @return The status of the event processing, either handled or unknown.
         */
        EventStatus processEvent();
        enum smState
        {
            STATE_INIT,
            STATE_WAIT,
            STATE_SENDPOS
        };
        smState state, lastState;
    };
} // namespace app end

#endif // JOYSTICKAPPLICATION_H
