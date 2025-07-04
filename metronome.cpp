#include "metronome.h"
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

    click1 = Mix_LoadWAV("click_1.wav");
    if (!click1) {
        std::cerr << "Failed to load click_1.wav: " << Mix_GetError() << std::endl;
        return false;
    }

    click2 = Mix_LoadWAV("click_2.wav");
    if (!click2) {
        std::cerr << "Failed to load click_2.wav: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void Metronome::cleanUpAudio() {
    if (click1) Mix_FreeChunk(click1);
    if (click2) Mix_FreeChunk(click2);
    Mix_CloseAudio();
    SDL_Quit();
}

void Metronome::playTick(bool isAccent) {
    Mix_Chunk* sound = isAccent ? click1 : click2;
    if (!sound) return;

    Mix_PlayChannel(-1, sound, 0);
    SDL_Delay(50);  // short delay to ensure click plays before sleep
}

void Metronome::start() {
    if (!initializeAudio()) return;

    double beatsPerSecond = bpm / 60.0;
    double baseNoteDuration = 1000.0 / beatsPerSecond; // milliseconds
    double adjustedNoteDuration = baseNoteDuration * (4.0 / noteValue);

    while (true) {
        for (int beat = 1; beat <= beatsPerMeasure; ++beat) {
            playTick(beat == 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(adjustedNoteDuration)));
        }
    }
}
