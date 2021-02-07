#ifndef Sequencer_h
#define Sequencer_h

#include <array>
#include <Arduino.h>
#include <ResponsiveAnalogRead.h>

class Sequencer
{
public:
    Sequencer();
    bool changed();
    int getPattern();
    int getTempo();
    std::pair<float, int> getChanges();
    std::pair<int, bool> step();
    void setStep(int, bool);
    void setStepnum(int);

    std::array<bool, 48> stepState;

private:
    bool m_change {false};
    int m_step {0};
    int m_STEPNUM {8};
    int tempo_poti {A13};
    unsigned long m_interval {200};
    unsigned long m_lastMillis {0};

    ResponsiveAnalogRead TempoPoti;

};
#endif