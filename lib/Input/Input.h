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
        
        std::array<int, 8> PotVal;
        std::array<int, 3> EncVal;
        std::array<bool, 3> ButtonState;
        void testIO();
    
    private:
        

        const int TempoPotPin       {A13};
        const int VolumePotPin      {A15};
        const int AttackPotPin      {A7};
        const int ReleasePotPin     {A6};
        const int BitcrusherPotPin  {A12};
        const int DelayPotPin       {A22};
        const int ReverbPotPin      {A2};
        const int LowpassPotPin     {A3};

        const int Enc1ButtonPin {6};
        const int Enc2ButtonPin {2};
        const int Enc3ButtonPin {30};

        const uint8_t Enc1A {25};
        const uint8_t Enc1B {24};
        const uint8_t Enc2A {26};
        const uint8_t Enc2B {27};
        const uint8_t Enc3A {29};
        const uint8_t Enc3B {28};

        ResponsiveAnalogRead TempoPot;
        ResponsiveAnalogRead VolumePot;
        ResponsiveAnalogRead AttackPot;
        ResponsiveAnalogRead ReleasePot;
        ResponsiveAnalogRead BitcrusherPot;
        ResponsiveAnalogRead DelayPot;
        ResponsiveAnalogRead ReverbPot;
        ResponsiveAnalogRead LowpassPot;

        Bounce Enc1Button;
        Bounce Enc2Button;
        Bounce Enc3Button;

        Encoder Enc1 {Enc1A, Enc1B};
        Encoder Enc2 {Enc2A, Enc2B};
        Encoder Enc3 {Enc3A, Enc3B};

        
};
#endif
