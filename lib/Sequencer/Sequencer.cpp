#include <Arduino.h>
#include "Sequencer.h"

Sequencer::Sequencer() : TempoPoti(tempo_poti, true)
{
    stepState.fill(false);
    TempoPoti.enableEdgeSnap();
    TempoPoti.setActivityThreshold(5.0);
}

bool Sequencer::changed()
{
    bool ch = m_change;
    m_change = false;
    return ch;
}

int Sequencer::getPattern()
{
    return m_step;
}

int Sequencer::getTempo()
{
    return m_interval;
}

std::pair<int, bool> Sequencer::step()
{
    TempoPoti.update();
    m_interval = map(TempoPoti.getValue(), 1023, 0, 125, 500);
    

    if ((millis() - m_lastMillis) > m_interval) //Timer is compared to m_interval --> next Step, Timer restarts
    {
        if (m_step == m_STEPNUM)
        {
            m_step = 0;
        }
        m_step++;
        m_lastMillis = millis();
    }
    return std::make_pair(m_step, stepState[m_step - 1]);
}

std::pair<float, int> Sequencer::getChanges()
{
    if (TempoPoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_interval, 9);
    }
    
    return std::make_pair(0,0);
}

void Sequencer::setStep(int step, bool onoff) //changes the StepState if a Chip is detected in CoinsSensor
{
    stepState[step] = onoff;
}

void Sequencer::setStepnum(int stepnum) //gets Stepnum from CoinSensor, default is 8, if a chip lands in the second row Stepnum is 16 and so on
{
    m_STEPNUM = stepnum;
}