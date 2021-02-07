#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include "Display.h"

Display::Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
}

void Display::clear()
{
  display.clearDisplay();
  display.display();
}

void Display::logoanimation()
{

  display.clearDisplay();
  for (int16_t i {0}; i < max(display.width(), display.height()) / 2; i += 2)
  {
    display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(500);

  display.clearDisplay();

  for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3)
  {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(500);

  display.fillRect(8, 6, display.width() - 15, display.height() - 10, SSD1306_BLACK);
  display.display(); // Update screen with each newly-drawn rectangle
  delay(1);

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 10);
  display.println(F("DropStep4"));
  display.display(); // Show initial text
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
}

void Display::ShowData(int selStep, int pitch, int amplitude)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Pitch: "));
  display.print(pitch);
  display.setCursor(0, 19);
  display.print(F("Vol:   "));
  display.print(amplitude);
  display.display();
}

void Display::ShowEffectChange(std::pair<float, int> state)
{
  switch (state.second)
  {
  case 1:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Attack:"));
    display.setCursor(0, 19);
    display.print(state.first);
    display.display();
    break;

  case 2:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Release:"));
    display.setCursor(0, 19);
    display.print(state.first);
    display.display();
    break;

  case 3:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Bitdepth:"));
    display.setCursor(0, 19);
    display.print(state.first);
    display.display();
    break;
  case 4:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Delaylevel:"));
    display.setCursor(0, 19);
    display.print(state.first);
    display.display();
    break;

  case 5:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Reverbtime:"));
    display.setCursor(0, 19);
    display.print(state.first);
    display.display();
    break;

  case 6:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Cutoff:"));
    display.setCursor(0, 19);
    display.print(state.first);
    display.display();
    break;

  case 7:
    volume = state.first * 100;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Main Vol:"));
    display.setCursor(0, 19);
    display.print(volume);
    display.display();
    break;

  case 8:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Synthmode:"));
    display.setCursor(0, 19);
    if (state.first == 1)
    {
      display.print("Drums");
    }

    else if (state.first == 2)
    {
      display.print("Strings");
    }

    else if (state.first == 3)
    {
      display.print("Sawtooth");
    }

    else if (state.first == 4)
    {
      display.print("Sine");
    }
    display.display();
    break;

    case 9:
      tempo = map(state.first, 500, 80, 80, 220);
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print(F("Tempo:"));
      display.setCursor(0, 19);
      display.print(tempo);
      display.display();
      break;
  }
}