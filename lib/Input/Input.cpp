#include "Input.h"

Input::Input()
{
    for(unsigned int i {0}; i < PotPins.size(); ++i)
    {
        pinMode (PotPins[i], INPUT);
        Potis[i] = new ResponsiveAnalogRead {PotPins[i], true};
        Potis[i]->enableEdgeSnap();
    }
    
    for(unsigned int i {0}; i < EncButtonPins.size(); ++i)
    {
        pinMode (EncButtonPins[i], INPUT);
        EncButtons[i].attach(EncButtonPins[i]);
    }

    for(unsigned int i {0}; i < EncAPins.size(); ++i)
    {
        pinMode (EncAPins[i], INPUT);
        pinMode (EncBPins[i], INPUT);
        Enc[i] = new Encoder {EncAPins[i], EncBPins[i]};
    }

    for (unsigned int i {0}; i < SensorPins.size(); ++i)
    {
        pinMode(SensorPins[i], INPUT);
    }
    m_EncVal.fill(0);
    m_oldEncVal.fill(0);
    m_PotVal.fill(0);
    m_StepState.fill(false);
    m_ButtonVal.fill(true);
}

void Input::updateAll()
{
   updatePots();
   updateEnc();
   updateButtons();
   updateSensors();
}

void Input::testIO()
{
    //updateAll();
    
    Serial.print("Potis:\t");
    for(unsigned int i{0}; i < m_PotVal.size(); ++i)
    {
        Serial.print(m_PotVal[i]);
        Serial.print("\t");
    }
    
    Serial.print("Encoder:\t");
    for(unsigned int i{0}; i < m_EncVal.size(); ++i)
    {
        Serial.print(m_EncVal[i]);
        Serial.print("\t");
    }
    Serial.print("Buttons:\t");
    for(unsigned int i{0}; i < m_ButtonVal.size(); ++i)
    {
    Serial.print(m_ButtonVal[i]);
        Serial.print("\t");
    }
    Serial.print("StepNum:\t");
    Serial.print(getStepnum());
    Serial.println();
}

void Input::updatePots()
{
     //read analog Inputs
    for (unsigned int i {0}; i < PotPins.size(); ++i)
    {
        m_PotVal[i] = Potis[i]->getValue();
        if (Potis[i]->hasChanged()) m_changed = true;
    }
}

void Input::updateEnc()
{
    //read Encoder
    for(unsigned int i {0}; i < EncAPins.size(); ++i)
    {
        if(Enc[i]->read() < 0) Enc[i]->write(0);
        if(Enc[0]->read() > 48*2) Enc[0]->write(48*2);
        m_EncVal[i] = Enc[i]->read()/2;
        if(m_EncVal[i] != m_oldEncVal[i])
        {
            m_changed = true;
            m_oldEncVal[i] = m_EncVal[i];
        }
    }
}

void Input::updateButtons()
{
    //read Buttons
    for (unsigned int i {0}; i < EncButtons.size(); ++i)
    {
        EncButtons[i].update();
        m_ButtonVal[i] = EncButtons[i].read();
        if(EncButtons[i].fallingEdge()) 
        {
            if (i == 0) 
            {
                m_StepState[m_EncVal[0]] = !m_StepState[m_EncVal[0]];
                updateStepnum(m_EncVal[0]);
            }
            m_changed = true;
        }
    }
}

void Input::updateSensors()
{
    //read Sensors on top of the synth
    for (unsigned int i {0}; i < SensorPins.size(); ++i)
    {
        if ((analogRead(SensorPins[i]) < 700) && (!m_sensor_state[i]))
        {
            m_StepState[i + (m_multiplyer[i] * 8)] = true;
            m_changed = true;
            m_multiplyer[i]++; //next time a chip is recognized it is in the next higher row than the last
            updateStepnum(0);
            m_sensor_state[i] = true; //indicates that chip is still in the light sensor, prevents m_changed to return true multiple times
        }

        if ((analogRead(SensorPins[i]) > 800) && (m_sensor_state[i]))
        {
            m_sensor_state[i] = false; //chip passed the sensor
        }
    }
}

void Input::updateStepnum(int i)
{
 while(i > m_STEPNUM)
 {
     m_STEPNUM = m_STEPNUM + 8;
 }

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
}

bool Input::changed()
{
    bool ch = m_changed;
    m_changed = false;
    return ch;
}

std::array<int, 8> Input::getPotVal()
{
    return m_PotVal;
}

std::array<int, 3> Input::getEncVal()
{
    return m_EncVal;
}

std::array<bool, 3> Input::getButtonVal()
{
    return m_ButtonVal;
}

std::array<bool, 48> Input::getStepState()
{
    return m_StepState;
}

int Input::getStepnum()
{
    return m_STEPNUM;
}

void Input::setEncVal(int index,int val)
{
    m_EncVal[index] = val;
    Enc[index]->write(val);
}