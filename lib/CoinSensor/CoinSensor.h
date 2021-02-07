#ifndef Chips_einlesen_h
#define Chips_einlesen_h

#include <Arduino.h>
#include <array>

class CoinSensor
{
public:
    CoinSensor();
    bool changed();
    int getStepnum();
    std::array<bool, 48> step_state;
    void read();

private:
    bool m_changed {false};
    int m_STEPNUM {8};
    std::array<int, 8> m_multiplyer;
    std::array<int, 8> m_pins{{A14, A15, A16, A17, A18, A19, A20, A21}};
    std::array<bool, 8> m_sensor_state;
    unsigned long m_interval {500};
    unsigned long m_lastMillis {0};
};
#endif
