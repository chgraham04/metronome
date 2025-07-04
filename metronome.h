#ifndef METRONOME_H
#define METRONOME_H

#include <SDL.h>
#include <SDL_mixer.h>

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

    Mix_Chunk* click1;
    Mix_Chunk* click2;
};

#endif
