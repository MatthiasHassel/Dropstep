#ifndef Input_H
#define Input_H

#include <Arduino.h>
#include <array>
#include "Bounce2.h"
#include "Encoder.h"
#include "ResponsiveAnalogRead.h"

class Input
{
    public:
        Input();
        
        std::array<int, 8> getPotVal();
        std::array<int, 3> getEncVal();
        std::array<bool, 3> getButtonVal();
        std::array<bool, 48> getStepState();
        int getStepnum();
        bool changed();

        void updateAll();
        void testIO();
        void setEncVal(int index, int val);
    
    private:
        void updatePots();
        void updateEnc();
        void updateButtons();
        void updateSensors();
        void updateStepnum(int);
        std::array<int, 8> m_PotVal;
        std::array<int, 3> m_EncVal;
        std::array<int, 3> m_oldEncVal;
        std::array<bool, 3> m_ButtonVal;
        std::array<bool, 48> m_StepState;
        std::array<int, 8> m_multiplyer;
        std::array<int, 8> SensorPins{{A14, A15, A16, A17, A18, A19, A20, A21}};
        std::array<bool, 8> m_sensor_state;

        bool m_changed {false};
    
        //PotiPins: 0MainVol, 1Tempo, 2Attack, 3Release, 4Bitcrusher, 5Delay, 6Reverb, 7Lowpass
        std::array<const int, 8> PotPins {{A1, A13, A7, A2, A3, A22, A6, A12}};
        ResponsiveAnalogRead *Potis[8];
       

        const int Enc1ButtonPin     {6};
        const int Enc2ButtonPin     {2};
        const int Enc3ButtonPin     {30};
        std::array<const int, 3> EncButtonPins  {{Enc1ButtonPin, Enc2ButtonPin, Enc3ButtonPin}};

        Bounce Enc1Button;
        Bounce Enc2Button;
        Bounce Enc3Button;
        std::array<Bounce, 3> EncButtons {{Enc1Button, Enc2Button, Enc3Button}};

        const uint8_t Enc1A {25};
        const uint8_t Enc1B {24};
        const uint8_t Enc2A {26};
        const uint8_t Enc2B {27};
        const uint8_t Enc3A {29};
        const uint8_t Enc3B {28};
        std::array<const uint8_t, 3> EncAPins {{Enc1A, Enc2A, Enc3A}};
        std::array<const uint8_t, 3> EncBPins {{Enc1B, Enc2B, Enc3B}}; 
        Encoder *Enc[3];

        int m_STEPNUM {8};

};
#endif
