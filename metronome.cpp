#include "metronome.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <thread>
#include <chrono>
#include <iostream>

Metronome::Metronome(int bpm, int beatsPerMeasure, int noteValue)
    : bpm(bpm), beatsPerMeasure(beatsPerMeasure), noteValue(noteValue) {}

Metronome::~Metronome() {
    cleanUpAudio();
}

bool Metronome::initializeAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void Metronome::cleanUpAudio() {
    Mix_CloseAudio();
    SDL_Quit();
}

void Metronome::playTick(bool isAccent) {
    const char* soundFile = isAccent ? "click_1.wav" : "click_2.wav";
    Mix_Chunk* sound = Mix_LoadWAV(soundFile);
    if (!sound) {
        std::cerr << "Failed to load " << soundFile << ": " << Mix_GetError() << std::endl;
        return;
    }

    Mix_PlayChannel(-1, sound, 0);
    SDL_Delay(100);  // Let the sound start playing
    Mix_FreeChunk(sound);
}

void Metronome::start() {
    if (!initializeAudio()) return;

    double beatsPerSecond = bpm / 60.0;
    double baseNoteDuration = 1000.0 / beatsPerSecond; // in ms
    double adjustedNoteDuration = baseNoteDuration * (4.0 / noteValue);

    while (true) {
        for (int beat = 1; beat <= beatsPerMeasure; ++beat) {
            playTick(beat == 1);
            std::this_thread::sleep_for(std::chrono::milliseconds((int)adjustedNoteDuration));
        }
    }
}
