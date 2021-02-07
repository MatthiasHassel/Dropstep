#include "Input.h"

Input::Input() :    TempoPot        {TempoPotPin, true},
                    VolumePot       {VolumePotPin, true},
                    AttackPot       {AttackPotPin, true},
                    ReleasePot      {ReleasePotPin, true},
                    BitcrusherPot   {BitcrusherPotPin, true},
                    DelayPot        {DelayPotPin, true},
                    ReverbPot       {ReverbPotPin, true},
                    LowpassPot      {LowpassPotPin, true}
{
    pinMode (TempoPotPin, INPUT);
    pinMode (VolumePotPin, INPUT);
    pinMode (AttackPotPin, INPUT);
    pinMode (ReleasePotPin, INPUT);
    pinMode (BitcrusherPotPin, INPUT);
    pinMode (DelayPotPin, INPUT);
    pinMode (ReverbPotPin, INPUT);
    pinMode (LowpassPotPin, INPUT);
    pinMode (Enc1ButtonPin, INPUT);
    pinMode (Enc2ButtonPin, INPUT);
    pinMode (Enc3ButtonPin, INPUT);

    Enc1Button.attach(Enc1ButtonPin);
    Enc2Button.attach(Enc2ButtonPin);
    Enc3Button.attach(Enc3ButtonPin);

    EncVal.fill(0);
    PotVal.fill(0);
    ButtonState.fill(false);
}

void Input::testIO()
{
    //read analog Inputs
    TempoPot.update();
    PotVal[0] = TempoPot.getValue();

    VolumePot.update();
    PotVal[1] = VolumePot.getValue();

    AttackPot.update();
    PotVal[2] = AttackPot.getValue();

    ReleasePot.update();
    PotVal[3] = ReleasePot.getValue();

    BitcrusherPot.update();
    PotVal[4] = BitcrusherPot.getValue();

    DelayPot.update();
    PotVal[5] = DelayPot.getValue();

    ReverbPot.update();
    PotVal[6] = ReverbPot.getValue();

    LowpassPot.update();
    PotVal[7] = LowpassPot.getValue();

    //read Encoder
    EncVal[0] = Enc1.read();
    EncVal[1] = Enc2.read();
    EncVal[2] = Enc3.read();

    //read Buttons
    if(Enc1Button.fallingEdge()) ButtonState[0] = !ButtonState[0];
    if(Enc2Button.fallingEdge()) ButtonState[1] = !ButtonState[1];
    if(Enc3Button.fallingEdge()) ButtonState[2] = !ButtonState[2];
    
    Serial.print("Potis:\t");
    for(unsigned int i{0}; i < PotVal.size(); ++i)
    {
        Serial.print(PotVal[i]);
        Serial.print("\t");
    }
    Serial.print("Encoder:\t");
    for(unsigned int i{0}; i < EncVal.size(); ++i)
    {
        Serial.print(EncVal[i]);
        Serial.print("\t");
    }
    Serial.print("Buttons:\t");
    for(unsigned int i{0}; i < ButtonState.size(); ++i)
    {
        Serial.print(ButtonState[i]);
        Serial.print("\t");
    }
    Serial.println();
}