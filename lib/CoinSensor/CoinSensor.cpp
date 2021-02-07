#include <Arduino.h>
#include <Bounce2.h>
#include "CoinSensor.h"

CoinSensor::CoinSensor()
{
    for (unsigned int i {0}; i < m_pins.size(); ++i)
    {
        pinMode(m_pins[i], INPUT);
    }
    step_state.fill(false);
}

bool CoinSensor::changed()
{
    bool ch = m_changed;
    m_changed = false;
    return ch;
}

int CoinSensor::getStepnum()  //activates the higher rows if a chip is in it
{
    for (unsigned int n {0}; n < m_multiplyer.size(); n++)
    {
        if (m_multiplyer[n] > 1 && m_STEPNUM < 16)
        {
            m_STEPNUM = 16;
        }

        if (m_multiplyer[n] > 2 && m_STEPNUM < 24)
        {
            m_STEPNUM = 24;
        }

        if (m_multiplyer[n] > 3 && m_STEPNUM < 32)
        {
            m_STEPNUM = 32;
        }

        if (m_multiplyer[n] > 4 && m_STEPNUM < 40)
        {
            m_STEPNUM = 40;
        }

        if (m_multiplyer[n] > 5 && m_STEPNUM < 48)
        {
            m_STEPNUM = 48;
        }
    }
    return m_STEPNUM;
}

void CoinSensor::read()
{
    for (unsigned int i {0}; i < m_pins.size(); ++i)
    {
        if ((analogRead(m_pins[i]) < 700) && (!m_sensor_state[i]))
        {
            step_state[i + (m_multiplyer[i] * 8)] = !step_state[i + (m_multiplyer[i] * 8)];
            m_changed = true;
            m_multiplyer[i]++; //next time a chip is recognized it is in the next higher row than the last
            m_sensor_state[i] = true; //indicates that chip is still in the light sensor, prevents m_changed to return true multiple times
        }

        if ((analogRead(m_pins[i]) > 800) && (m_sensor_state[i]))
        {
            m_sensor_state[i] = false; //chip passed the sensor
        }
    }
}



