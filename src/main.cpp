#include <Arduino.h>
#include "Input.h"

Input input;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  input.updateAll();
}




/*#include "Sequencer.h"
#include "CoinSensor.h"
#include "Leds.h"
#include "Synth.h"
#include "Display.h"

bool timerflag {false};
unsigned int oldMillis {0};
unsigned int interval {500};

Sequencer seq;
Leds leds;
Synth synth1;
CoinSensor chips;
Display display;

int STEPNUM {8};

void setup()
{
  Serial.begin(9600);
  display.clear();
  synth1.getChanges(); //get start Poti values
  synth1.effectchanged(); //discard change flag
  leds.logoanimation();
  display.logoanimation();
  leds.clear();
  Serial.print("Setup Done");
}

void loop()
{
  chips.read();
  if (chips.changed())
  {
    for (unsigned int i {0}; i < chips.step_state.size(); ++i)
    {
      seq.setStep(i, chips.step_state[i]);
    }
    leds.changeColor(seq.stepState);
    STEPNUM = chips.getStepnum(); //default is 8, if a chip lands in row 2 or higher the stepnum increases
    leds.setStepnum(STEPNUM);
    seq.setStepnum(STEPNUM);
    synth1.setStepnum(STEPNUM);
  }


  leds.brightness(synth1.getSelectedStep(), synth1.getSelectedAmplitude());
  leds.set(seq.step(), synth1.getSelectedStep()); //activates the green LED (runs through the steps)


  synth1.setTempo(seq.getTempo());
  synth1.play(seq.step());        //plays the music
  synth1.getChanges();
  if (synth1.effectchanged())
  {
    display.ShowEffectChange(synth1.getChanges());
    timerflag = true;
    oldMillis = millis();
  }

  seq.getChanges();
  if (seq.changed())
  {
    display.ShowEffectChange(seq.getChanges());
    timerflag = true;
    oldMillis = millis();
  }

  if (!timerflag)
  {
    display.ShowData(synth1.getSelectedStep(), synth1.getSelectedSemitone(), synth1.getSelectedAmplitude() * 100);
  }

  if (timerflag)
  {
    if (millis() - oldMillis > interval)
    {
      timerflag = false;
    }
  }

  
  synth1.serialmonitor();
}
*/