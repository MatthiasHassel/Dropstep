#ifndef Display_h
#define Display_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

class Display
{
public:
    Display();
    Adafruit_SSD1306 display;
    void clear();
    void logoanimation();
    void ShowData(int selStep, int pitch, int amplitude);
    void ShowEffectChange(std::pair<float, int> state);

private:
    bool timerflag {false};
    unsigned int oldMillis {0};
    unsigned int m_interval {1000};
    int volume {0};
    int tempo {80};
    //int screen_width {128}; // OLED display width, in pixels
    //int screen_height {32}; // OLED display height, in pixels
    //int oled_reset {4}; // Reset pin # (or -1 if sharing Arduino reset pin)
};
#endif