#ifndef METRONOME_H
#define METRONOME_H

class Metronome {
public:
    Metronome(int bpm, int beatsPerMeasure, int noteValue, bool accentEnabled);
    ~Metronome();
    void start();

private:
    int bpm;
    int beatsPerMeasure;
    int noteValue;
    bool accentEnabled;
};

#endif // METRONOME_H
