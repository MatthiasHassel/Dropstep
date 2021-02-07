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

    TempoPot.enableEdgeSnap();
    VolumePot.enableEdgeSnap();
    AttackPot.enableEdgeSnap();
    ReleasePot.enableEdgeSnap();
    BitcrusherPot.enableEdgeSnap();
    DelayPot.enableEdgeSnap();
    ReverbPot.enableEdgeSnap();
    LowpassPot.enableEdgeSnap();
    
    Enc1Button.attach(Enc1ButtonPin);
    Enc2Button.attach(Enc2ButtonPin);
    Enc3Button.attach(Enc3ButtonPin);

    m_EncVal.fill(0);
    m_PotVal.fill(0);
    m_ButtonState.fill(false);
}

void Input::updateAll()
{
   updatePots();
   updateEnc();
   updateButtons();
}

void Input::testIO()
{
    updateAll();
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
    for(unsigned int i{0}; i < m_ButtonState.size(); ++i)
    {
    Serial.print(m_ButtonState[i]);
        Serial.print("\t");
    }
    Serial.println();
}

void Input::updatePots()
{
     //read analog Inputs
    TempoPot.update();
    m_PotVal[0] = TempoPot.getValue();

    VolumePot.update();
    m_PotVal[1] = VolumePot.getValue();

    AttackPot.update();
    m_PotVal[2] = AttackPot.getValue();

    ReleasePot.update();
    m_PotVal[3] = ReleasePot.getValue();

    BitcrusherPot.update();
    m_PotVal[4] = BitcrusherPot.getValue();

    DelayPot.update();
    m_PotVal[5] = DelayPot.getValue();

    ReverbPot.update();
    m_PotVal[6] = ReverbPot.getValue();

    LowpassPot.update();
    m_PotVal[7] = LowpassPot.getValue();
}

void Input::updateEnc()
{
    //read Encoder
    m_EncVal[0] = Enc1.read();
    if(m_EncVal[0] < 0) Enc1.write(0);
    m_EncVal[1] = Enc2.read();
    if(m_EncVal[1] < 0) Enc2.write(0);
    m_EncVal[2] = Enc3.read();
    if(m_EncVal[2] < 0) Enc3.write(0);
}

void Input::updateButtons()
{
    //read Buttons
    Enc1Button.update();
    Enc2Button.update();
    Enc3Button.update();
    if(Enc1Button.fallingEdge()) m_ButtonState[0] = !m_ButtonState[0];
    if(Enc2Button.fallingEdge()) m_ButtonState[1] = !m_ButtonState[1];
    if(Enc3Button.fallingEdge()) m_ButtonState[2] = !m_ButtonState[2];
}

std::array<int, 8> Input::getPotVal()
{
    updatePots();
    return m_PotVal;
}

std::array<int, 3> Input::getEncVal()
{
    updateEnc();
    return m_EncVal;
}

std::array<bool, 3> Input::getButtonState()
{
    updateButtons();
    return m_ButtonState;
}