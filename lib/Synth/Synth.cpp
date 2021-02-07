#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce2.h>
#include <Encoder.h>
#include <array>
#include "Synth.h"
#include "Sequencer.h"


Synth::Synth() :
AttackPoti(attack_poti, true),
ReleasePoti(release_poti, true),
BitcrusherPoti(bitcrusher_poti, true),
DelayPoti(delay_poti, true),
ReverbPoti(reverb_poti, true),
LowpassPoti(lowpass_poti, true),
VolumePoti(volume_poti, true),
patchCord1(waveform1, 0, mixerWaveform, 2),
patchCord2(waveform2, 0, mixerWaveform, 3),
patchCord3(string1, 0, mixerWaveform, 1),
patchCord4(drum1, drum_amp),
patchCord5(drum_amp, 0, mixerWaveform, 0),
patchCord6(mixerWaveform, envelope1),
patchCord7(envelope1, bitcrusher1),
patchCord8(bitcrusher1, delay1),
patchCord9(delay1, 0, mixerDelay, 0),
patchCord10(delay1, 1, mixerDelay, 1),
patchCord11(delay1, 2, mixerDelay, 2),
patchCord12(delay1, 3, mixerDelay, 3),
patchCord13(mixerDelay, rev_amp),
patchCord14(mixerDelay, 0, mixerReverb, 0),
patchCord15(rev_amp, reverb1),
patchCord16(reverb1, 0, mixerReverb, 1),
patchCord17(mixerReverb, biquad1),
patchCord18(biquad1, 0, mainmix, 0),
patchCord19(mainmix, 0, audio_out, 0),
patchCord20(mainmix, 0, audio_out, 1)

{   
    audioShield.enable();
    audioShield.volume(0.7);
    audioShield.lineOutLevel(13);
    AudioMemory(200);
    
    mixerWaveform.gain(0, 1);
    mixerWaveform.gain(1, 0);
    mixerWaveform.gain(2, 0);
    mixerWaveform.gain(3, 0);

    debButton1.attach(m_buttonPin1);
    debButton2.attach(m_buttonPin2);
    debButton3.attach(m_buttonPin3);


    m_semiTone.fill(6);
    m_pitch.fill(185);
    m_amplitude.fill(1);

    myEnc2.write(m_semiTone[m_selected_step]*2);
    myEnc3.write(m_amplitude[m_selected_step]*100);

    AttackPoti.enableEdgeSnap();
    ReleasePoti.enableEdgeSnap();
    BitcrusherPoti.enableEdgeSnap();
    DelayPoti.enableEdgeSnap();
    ReverbPoti.enableEdgeSnap();
    LowpassPoti.enableEdgeSnap();
    VolumePoti.enableEdgeSnap();

    AttackPoti.setActivityThreshold(6.0);
    ReleasePoti.setActivityThreshold(5.0);
    ReverbPoti.setActivityThreshold(13.0);

    pinMode(m_buttonPin1, INPUT);
    pinMode(m_buttonPin2, INPUT);
    pinMode(m_buttonPin3, INPUT);
    pinMode(bitcrusher_poti, INPUT);
    pinMode(delay_poti, INPUT);
    pinMode(reverb_poti, INPUT);
    pinMode(lowpass_poti, INPUT);
    pinMode(attack_poti, INPUT);
    pinMode(release_poti, INPUT);
    pinMode(volume_poti, INPUT);

    drum1.frequency(m_pitch[0]);
    drum1.pitchMod(0.55);
    drum_amp.gain(1);

    waveform1.begin(0.1,m_pitch[0],WAVEFORM_SAWTOOTH);
    waveform2.begin(0.2,m_pitch[0],WAVEFORM_TRIANGLE);

    bitcrusher1.bits(16);

    delay1.delay(0,0);
    delay1.delay(1,150);
    delay1.delay(2,300);
    delay1.delay(3,450);

    mixerDelay.gain(0,1);
    mixerDelay.gain(1,0);
    mixerDelay.gain(2,0);
    mixerDelay.gain(3,0);

    envelope1.attack(9.2);
    envelope1.hold(2.1);
    envelope1.decay(31.4);
    envelope1.sustain(0.6);
    envelope1.release(84.5);

    rev_amp.gain(0.4);
    reverb1.reverbTime(0);
    mixerReverb.gain(0,0);
    mixerReverb.gain(1,1);
    mixerReverb.gain(2,0);
    mixerReverb.gain(3,0);

    biquad1.setLowpass(0, 20000, 0.707);

    mainmix.gain(0, 1);    
}

void Synth::setStepnum(int stepnum)
{
    m_STEPNUM = stepnum;
}

void Synth::m_changeMode()
{
    debButton3.update();

    if (debButton3.fell())
    {
        m_synthMode++;
        if (m_synthMode == 5)
        {
            m_synthMode = 1;
        }
    }

    switch (m_synthMode)
    {
    case 1:
        mixerWaveform.gain(0, 1);
        mixerWaveform.gain(1, 0);
        mixerWaveform.gain(2, 0);
        mixerWaveform.gain(3, 0);
        //Serial.print("Drum1");
        break;

    case 2:
        mixerWaveform.gain(0, 0);
        mixerWaveform.gain(1, 1);
        mixerWaveform.gain(2, 0);
        mixerWaveform.gain(3, 0);
        //Serial.print("String");
        break;

    case 3:
        mixerWaveform.gain(0, 0);
        mixerWaveform.gain(1, 0);
        mixerWaveform.gain(2, 1);
        mixerWaveform.gain(3, 0);
        //Serial.print("Sine");
        break;

    case 4:
        mixerWaveform.gain(0, 0);
        mixerWaveform.gain(1, 0);
        mixerWaveform.gain(2, 0);
        mixerWaveform.gain(3, 1);
        //Serial.print("Sawtooth");
        break;

    default:
        mixerWaveform.gain(0, 1);
        mixerWaveform.gain(1, 0);
        mixerWaveform.gain(2, 0);
        mixerWaveform.gain(3, 0);
        //Serial.print("Default --> Drum1");
        break;
    }
}

void Synth::m_getSelectedStep()
{
    if (myEnc1.read() > (m_STEPNUM-1)*2)     //upper and lower limit of Encoder 1
    {
        myEnc1.write((m_STEPNUM-1)*2);  
    }

    if (myEnc1.read() < 0)
    {
        myEnc1.write(0);
    }
    
    m_selected_step = myEnc1.read()/2;  //Encoder 1 adds 2 with every turn, so step 48 suits to Encoder 1 96

    if(m_selected_step != m_old_selected_step)  //if selected step changes, encoder2 and encoder3 are set to the former pitch/amplitude of the new selected step
    {
        myEnc2.write(m_semiTone[m_selected_step]*2);
        myEnc3.write(m_amplitude[m_selected_step]*100);
        m_old_selected_step = m_selected_step;
    }
}

void Synth::m_getPitch()
{
    
    if (myEnc2.read() > 48)
    {
        myEnc2.write(48);
    }

    if (myEnc2.read() < 2)
    {
        myEnc2.write(2);
    }
    m_semiTone[m_selected_step] = myEnc2.read() / 2; //Encoder 2 adds 2 with every turn, so Semitone 24 suits to Encoder 2 48


    

    for (int n = 0; n <= 24; ++n)
    {
        if (n == m_semiTone[m_selected_step])
        {
            m_pitch[m_selected_step] = m_note[n];  //pitch array contains the frequencies of a 24 diatonic scale
        }
    }
}

void Synth::m_getAmplitude()
{
    
    if (myEnc3.read() > 100)
    {
        myEnc3.write(100);
    }

    if (myEnc3.read() < 0)
    {
        myEnc3.write(0);
    }
    m_amplitude[m_selected_step]= myEnc3.read()*0.01; //scales the amplitude to value between 0.00 and 1.00
    
}

void Synth::play(std::pair<int, bool> state)
{
    m_changeMode();
    m_getSelectedStep();
    m_getPitch();
    m_getAmplitude();
    m_getEffects();
    
    VolumePoti.update();
    analog_volume = VolumePoti.getValue();
    
    
    if (VolumePoti.hasChanged())
    {
        global_volume = map(analog_volume, 0, 1023, 0.0, 1.0);
        mainmix.gain(0, global_volume);
    }

    m_step = state.first;
    if (m_step != m_oldStep)    //note off
    {
        envelope1.noteOff();
        m_notePlayed = false;
        m_oldStep = m_step;
    }

    for (int i {0}; i <= m_STEPNUM; ++i)
    {
        if ((i + 1) == state.first)
        {
            if (state.second && (m_notePlayed == false))    //pitch update and note on
            {   
                drum1.frequency(m_pitch[i]);
                drum_amp.gain(m_amplitude[i]);
                drum1.noteOn();    
                string1.noteOn(m_pitch[i],0.2*m_amplitude[i]);
                waveform1.frequency(m_pitch[i]);
                waveform1.amplitude(0.1*m_amplitude[i]);
                waveform2.frequency(m_pitch[i]);
                waveform2.amplitude(0.3*m_amplitude[i]);
                envelope1.noteOn();
                m_notePlayed = true;
                
            }
        }
    }
}

void Synth::serialmonitor()
{
    unsigned long currentMillis = millis();
 
    if(currentMillis - previousMillis > interval) 
    {  
        Serial.print("Attack: ");
        Serial.print(m_attacktime);
        Serial.print("  Release: ");
        Serial.print(m_releasetime);
        Serial.print("  Bits: ");
        Serial.print(m_bitdepth);
        Serial.print("  Delay: ");
        Serial.print(m_delayGain1);
        Serial.print("  Reverb: ");
        Serial.print(m_reverbtime);
        Serial.print("  Filter: ");
        Serial.print(m_lowpassfrequency);
        Serial.print("  Poti: ");
        Serial.print(LowpassPoti.getValue());
        Serial.print("  Vol:");
        Serial.println(myEnc3.read());

        previousMillis = currentMillis;
    }
}

void Synth::m_getEffects()
{
    m_interval = m_tempo;

    BitcrusherPoti.update();
    m_bitdepth = map(BitcrusherPoti.getValue(), 1023, 10, 5, 16);
    bitcrusher1.bits(m_bitdepth);

    DelayPoti.update();
    m_delayGain1 = map(DelayPoti.getValue(), 0, 1023, 0, 100) * 0.004;  
    m_delayGain2 = map(DelayPoti.getValue(), 0, 1023, 0, 100) * 0.003;
    m_delayGain3 = map(DelayPoti.getValue(), 0, 1023, 0, 100) * 0.002;;
    m_delayGain0 = 1;

    mixerDelay.gain(0, m_delayGain0); //mixerDelay 0 --> undelayed Signal
    mixerDelay.gain(1, m_delayGain1);
    mixerDelay.gain(2, m_delayGain2);
    mixerDelay.gain(3, m_delayGain3);

    ReverbPoti.update();
    m_reverbtime = map(ReverbPoti.getValue(), 1023, 1, 55, 0)*0.1;
    reverb1.reverbTime(m_reverbtime);
    mixerReverb.gain(0, 0.5); // makes sure that gain is never higher than 1 //"Dry Signal"
    mixerReverb.gain(1, 0.5); //"Wet Signal"

    AttackPoti.update();
    m_attacktime = map(AttackPoti.getValue(), 0, 1023, 0, m_interval);

    ReleasePoti.update();
    m_releasetime = map(ReleasePoti.getValue(), 0, 1023, 0, m_interval*2);

    envelope1.attack(m_attacktime);
    envelope1.release(m_releasetime);
    envelope1.hold(m_interval-m_attacktime);

    LowpassPoti.update();
    m_lowpassfrequency = map(LowpassPoti.getValue(), 1023, 0, 40, 20000);
    biquad1.setLowpass(0, m_lowpassfrequency, 0.707);
} 

std::pair<float, int> Synth::getChanges()
{
    if (AttackPoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_attacktime,1);
    }


    if (ReleasePoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_releasetime, 2);
    }

    if (BitcrusherPoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_bitdepth, 3);
    }

    if (DelayPoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_delayGain1, 4);
    }
/*
    if (ReverbPoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_reverbtime, 5);
    }
*/
    if (LowpassPoti.hasChanged())
    {
        m_change = true;
        return std::make_pair(m_lowpassfrequency, 6);
    }

     if (VolumePoti.hasChanged())
   {
       m_change = true;
       return std::make_pair(global_volume, 7);
   }
   
   if (debButton3.fell())
   {
       m_change = true;
       return std::make_pair(m_synthMode, 8);
   }

    return std::make_pair(0, 0);
}

int Synth::getSelectedStep()
{
    return m_selected_step;
}

int Synth::getSelectedSemitone()
{
    return m_semiTone[m_selected_step];
}

float Synth::getSelectedAmplitude()
{
    return m_amplitude[m_selected_step];
}

bool Synth::effectchanged()
{
    bool ch = m_change;
    m_change = false;
    return ch;
}

void Synth::setTempo(int tempo)
{
    m_tempo = tempo;
}