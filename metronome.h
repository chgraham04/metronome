#ifndef METRONOME_H
#define METRONOME_H

class Metronome {
public:
    Metronome(int bpm, int beatsPerMeasure, int noteValue);
    ~Metronome();
    void start();

private:
    int bpm;
    int beatsPerMeasure;
    int noteValue;
    bool initializeAudio();
    void playTick(bool isAccent);
    void cleanUpAudio();
};

#endif
