#ifndef Leds_h
#define Leds_h

#include <Arduino.h>
#include <array>
#include "WS2812Serial.h"





class Leds
{
public:
    Leds();
    void brightness(int m_step, float ampl);
    void clear();
    void changeColor(std::array<bool, 48>);
    void logoanimation();
    void set(std::pair<int, bool>, int);
    void setStepnum(int);

private:
    
    WS2812Serial pixels;
    
    bool m_color {false}; //toggles everytime a step ist set to change color between red and blue
    bool timerflag {false};
    
    int m_STEPNUM {8};
    int m_oldSelectedStep {0};
    int m_brightness {255};
    int ledRED {0xFF0000};
    int ledGREEN  {0x00FF00};
    int ledBLUE   {0x0000FF};
    int ledYELLOW {0xFFFF00};
    int ledPINK   {0xFF1088};
    int ledORANGE {0xE05800};
    int ledWHITE  {0xFFFFFF};


    
    std::array<int, 48> m_redValue; //stores the red value for each individual Step
    std::array<int, 48> m_blueValue; //stores the blue value for each individual Step
    std::array<bool, 48> m_stepState;
    std::array<int, 48> m_ledSequence; //LEDs are connectet vertical, Sequence moves horizontal --> LED Sequence is needed
    unsigned int oldMillis {0};
    unsigned int m_interval {1000};
    
};
#endif