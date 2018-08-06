#ifndef BlinkerTimingTimer_H
#define BlinkerTimingTimer_H

#if defined(ESP8266) || defined(ESP32)
#include <Blinker/BlinkerConfig.h>
#include <utility/BlinkerUtility.h>

class BlinkerTimingTimer
{
    public :
        BlinkerTimingTimer()
            : timerState(false)
            , isLoopTask(false)
        {}

        BlinkerTimingTimer(uint32_t _timerData, String _action, String _text)
            : timerState(false)
            , isLoopTask(false)
        {
            timerData = _timerData;
            actionData = _action;
            timerText = _text;

            isLoopTask = timerData >> 31;
            timerState = timerData >> 23 & 0x01;
            timingDay = timerData >> 11 & 0x7F;
            times = timerData & 0x7FF;
        }

        BlinkerTimingTimer(bool _state, uint8_t _timingDay, uint16_t _times, String _action, String _text, bool _isLoop)
            : timerState(false)
            , isLoopTask(false)
        {
            timerState = _state;
            timingDay = timingDay;
            times = _times;
            actionData = _action;
            timerText = _text;
            isLoopTask = _isLoop;

            timerData = isLoopTask << 31 | timerState << 23 | timingDay << 11 | times;
        }

        void freshTimer(uint32_t _timerData, String _action, String _text) {
            timerData = _timerData;
            actionData = _action;
            timerText = _text;

            isLoopTask = timerData >> 31;
            timerState = timerData >> 23 & 0x01;
            timingDay = timerData >> 11 & 0x7F;
            times = timerData & 0x7FF;
        }

        bool isTimingDay(uint8_t _day) {
            if (timingDay & (0x01 << _day)) return true;
            else return false;
        }

        uint8_t getTimingday() { return timingDay; }

        String getAction() { return actionData; }

        String getText() { return timerText; }

        uint32_t getTimerData() { return timerData; }

        uint16_t getTime() { return times; }

        bool state() { return timerState; }

		bool isLoop() { return isLoopTask; }

        void disableTask() {
            timerState = false;

            timerData = isLoopTask << 31 | timerState << 23 | timingDay << 11 | times;
        }

    private :
        // - - - - - - - - | - - - - - - - - | - - - - - - - - | - - - - - - - -
        // |                 |           |               | 11 0-0x7FF times
        // |                 |           | 18 timingDay
        // |                 | 24 timerState
        // | 32 isLoopTask
        uint32_t timerData;
        uint8_t  timingDay;
        String   actionData;
        String   timerText;
        uint16_t times;
        bool     timerState;
        bool     isLoopTask;
};

#endif

#endif