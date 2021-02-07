#include <Arduino.h>
#include <array>
#include <WS2812Serial.h>
#include "Leds.h"
#include "Sequencer.h"

const int pin = 1;
const int numled = 48;

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

Leds::Leds(): pixels(numled, displayMemory, drawingMemory, pin, WS2812_GRB)
{
    pixels.begin(); // This initializes the NeoPixel library.
    m_redValue.fill(0);
    m_blueValue.fill(0);

    m_ledSequence = {   //LEDs are connectet vertical, Sequence moves horizontal --> LED Sequence is needed
                        0,6,12,18,24,30,36,42,
                        1,7,13,19,25,31,37,43,
                        2,8,14,20,26,32,38,44,
                        3,9,15,21,27,33,39,45,
                        4,10,16,22,28,34,40,46,
                        5,11,17,23,29,35,41,47
                    };
}

void Leds::setStepnum(int stepnum)
{
    m_STEPNUM = stepnum;
}

void Leds::changeColor(std::array<bool, 48> m_stepState)
{
    for (unsigned int i {0}; i < m_stepState.size(); ++i)
    {
        if (m_stepState[i]) //checks if a step is active
        {
            if ((m_redValue[m_ledSequence[i]] != 0) || (m_blueValue[m_ledSequence[i]] != 0)) //if the LED already shines blue or red the code moves on without changing anything
            {
                continue;
            }
            if (m_color) //checks if it's player1's or player2's turn
            {   
                m_redValue[m_ledSequence[i]] = 255;
                m_blueValue[m_ledSequence[i]] = 0;
                m_color = false;
            }
            else
            {
                m_redValue[m_ledSequence[i]] = 0;
                m_blueValue[m_ledSequence[i]] = 255;
                m_color = true;
            }
        }
        else
        {
            m_redValue[m_ledSequence[i]] = 0;
            m_blueValue[m_ledSequence[i]] = 0;
        }

        pixels.setPixelColor(m_ledSequence[i], pixels.Color(m_redValue[m_ledSequence[i]], 0, m_blueValue[m_ledSequence[i]]));
        pixels.show();
    }
}

void Leds::brightness(int m_step, float ampl)
{
    m_brightness = int (ampl*255);

            if (m_brightness > 0)
            {
                if (m_redValue[m_ledSequence[m_step]] != 0)
                {
                m_redValue[m_ledSequence[m_step]] = m_brightness;
                }

                if (m_blueValue[m_ledSequence[m_step]] != 0)
                {
                m_blueValue[m_ledSequence[m_step]] = m_brightness;
                }
            }
}

void Leds::set(std::pair<int, bool> state, int m_selectedStep) 
{
    
    for (int i {0}; i < m_STEPNUM; ++i)
    {
        if ((i + 1) == state.first) //state first: 1-8 --> i+1 (Arrays begin with 0)
        {
            pixels.setPixelColor(m_ledSequence[i], pixels.Color(m_redValue[m_ledSequence[i]], 150, m_blueValue[m_ledSequence[i]]));
            pixels.show(); // This sends the updated pixel color to the hardware.
        }
        else if (i == m_selectedStep)
        {
            if(m_selectedStep != m_oldSelectedStep || digitalRead(6)==LOW)
            {
                pixels.setPixelColor(m_ledSequence[m_selectedStep], pixels.Color(255, 255, 255));
                pixels.show(); 
                m_oldSelectedStep = m_selectedStep;
                timerflag = true;
                oldMillis = millis();
            }

            if (timerflag)
            {
                pixels.setPixelColor(m_ledSequence[m_oldSelectedStep], pixels.Color(255, 255, 255));
                pixels.show();
                if(millis() - oldMillis > m_interval)
                {
                    timerflag = false;
                }
            }

            if(!timerflag)
            {
            pixels.setPixelColor(m_ledSequence[i], pixels.Color(m_redValue[m_ledSequence[i]], 0, m_blueValue[m_ledSequence[i]]));
            pixels.show(); // This sends the updated pixel color to the hardware.
            }                     
        }

        else
        {
            pixels.setPixelColor(m_ledSequence[i], pixels.Color(m_redValue[m_ledSequence[i]], 0, m_blueValue[m_ledSequence[i]]));
            pixels.show(); // This sends the updated pixel color to the hardware.
        }

        
    }
}

void Leds::logoanimation()
{
    
    for (int i {17}; i > 11; --i) 
    {
    pixels.setPixel(i, ledRED);
    pixels.setPixel(i+18, ledRED);
    pixels.show();
    delayMicroseconds(1500000/48);
    }

    for (int i {23}; i > 17; --i) 
    {
    pixels.setPixel(i, ledBLUE);
    pixels.setPixel(i+6, ledBLUE);
    pixels.show();
    delayMicroseconds(1500000/48);
    }

    for (int i {17}; i > 11; --i) 
    {
    pixels.setPixel(i, 0);
    pixels.setPixel(i+18, 0);
    pixels.show();
    delayMicroseconds(1500000/48);
    }

    for (int i {5}; i > -1; --i) 
    {
    pixels.setPixel(i, ledGREEN);
    pixels.setPixel(i+42, ledGREEN);
    pixels.show();
    delayMicroseconds(1500000/48);
    }

    for (int i {23}; i > 17; --i) 
    {
    pixels.setPixel(i, 0);
    pixels.setPixel(i+6, 0);
    pixels.show();
    delayMicroseconds(1500000/48);
    }

    for (int i {5}; i > -1; --i) 
    {
    pixels.setPixel(i, 0);
    pixels.setPixel(i+42, 0);
    pixels.show();
    delayMicroseconds(1500000/48);
    }

    pixels.setPixel(13, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(14, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(15, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(16, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);   
    pixels.setPixel(18, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(23, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(24, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(29, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(31, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(32, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(33, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48);
    pixels.setPixel(34, ledWHITE);
    pixels.show();
    delayMicroseconds(1500000/48); 

}

void Leds::clear()
    {
        pixels.clear();
        pixels.show();
    }