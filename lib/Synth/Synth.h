#ifndef Synth_h
#define Synth_h

#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce2.h>
#include <Encoder.h>
#include <ResponsiveAnalogRead.h>
#include <array>

class Synth
{

public:
    Synth();
    bool effectchanged();
    float getSelectedAmplitude();
    int getSelectedStep();
    int getSelectedSemitone();
    int getSynthMode();
    std::pair<float, int> getChanges();
    void play(std::pair<int, bool>);
    void serialmonitor();
    void setStepnum(int);
    void setTempo(int);

private:
    void m_changeMode();
    void m_getSelectedStep();
    void m_getPitch();
    void m_getAmplitude();
    void m_getEffects();

    int m_tempo;
    int m_note[25] = {131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523};
    int m_synthMode {1};
    bool m_change {false};

    std::array<int, 48> m_semiTone;
    int m_selected_step {0};
    int m_old_selected_step {0};

    int m_buttonPin1 {6};
    int m_buttonPin2 {2};
    int m_buttonPin3 {30};

    Bounce debButton1;
    Bounce debButton2;
    Bounce debButton3;

    Encoder myEnc1{25, 24};
    Encoder myEnc2{26,27};
    Encoder myEnc3{29,28};

    int attack_poti {A7};
    int release_poti {A2};
    int bitcrusher_poti {A3};
    int delay_poti {A22}; 
    int reverb_poti {A6};
    int lowpass_poti {A12};
    int volume_poti {A1};

    ResponsiveAnalogRead AttackPoti;
    ResponsiveAnalogRead ReleasePoti;
    ResponsiveAnalogRead BitcrusherPoti;
    ResponsiveAnalogRead DelayPoti;
    ResponsiveAnalogRead ReverbPoti;
    ResponsiveAnalogRead LowpassPoti;
    ResponsiveAnalogRead VolumePoti;

    
    bool m_notePlayed {false};
    float m_volume {0.7};
    int m_step {1};
    int m_oldStep = 0;
    int m_STEPNUM = 8;
    unsigned long lastMillis = millis();

    std::array<int, 48> m_pitch;
    std::array<float, 48> m_amplitude;

    int m_interval {0};
    int m_bitdepth {16};
    float m_delayGain0 {1};
    float m_delayGain1 {0};
    float m_delayGain2 {0};
    float m_delayGain3 {0};
    float m_reverbtime {0};
    float m_attacktime {9.2};
    float m_releasetime {84.5};
    int m_lowpassfrequency {200000};

    float global_volume {1.0};
    float analog_volume;
    float old_analog_volume;

    unsigned long previousMillis {0};
    unsigned long interval {500};
    
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=62,181
AudioSynthWaveform       waveform2;      //xy=64,214
AudioSynthKarplusStrong  string1;        //xy=69,146
AudioSynthSimpleDrum     drum1;          //xy=71,109
AudioAmplifier           drum_amp;
AudioMixer4              mixerWaveform;         //xy=313,168
AudioEffectEnvelope      envelope1;      //xy=483,168
AudioEffectBitcrusher    bitcrusher1;    //xy=636,169
AudioEffectDelay         delay1;         //xy=645,272
AudioMixer4              mixerDelay;         //xy=797,243
AudioAmplifier           rev_amp;           //xy=855,169
AudioEffectReverb        reverb1;        //xy=981,170
AudioMixer4              mixerReverb;         //xy=1073,245
AudioFilterBiquad        biquad1;        //xy=1199,24
AudioMixer4              mainmix;
AudioOutputI2S           audio_out;           //xy=1356,243
AudioControlSGTL5000     audioShield;     //xy=326,20
AudioConnection          patchCord1;
AudioConnection          patchCord2;
AudioConnection          patchCord3;
AudioConnection          patchCord4;
AudioConnection          patchCord5;
AudioConnection          patchCord6;
AudioConnection          patchCord7;
AudioConnection          patchCord8;
AudioConnection          patchCord9;
AudioConnection          patchCord10;
AudioConnection          patchCord11;
AudioConnection          patchCord12;
AudioConnection          patchCord13;
AudioConnection          patchCord14;
AudioConnection          patchCord15;
AudioConnection          patchCord16;
AudioConnection          patchCord17;
AudioConnection          patchCord18;
AudioConnection          patchCord19;
AudioConnection          patchCord20;
// GUItool: end automatically generated code

};
#endif