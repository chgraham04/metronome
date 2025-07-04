#ifndef METRONOME_H
#define METRONOME_H

#include <SDL.h>
#include <SDL_mixer.h>

class Metronome {
public:
    Metronome(int bpm, int beatsPerMeasure, int noteValue);
    ~Metronome();
    void start();

private:
    int bpm;
    int beatsPerMeasure;
    int noteValue;

    Mix_Chunk* click1 = nullptr;
    Mix_Chunk* click2 = nullptr;

    bool initializeAudio();
    void playTick(bool isAccent);
    void cleanUpAudio();
};

#endif // METRONOME_H
