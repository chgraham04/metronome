#include "metronome.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>
#include <iostream>

Metronome::Metronome(int bpm, int beatsPerMeasure, int noteValue, bool accentEnabled)
    : bpm(bpm), beatsPerMeasure(beatsPerMeasure), noteValue(noteValue), accentEnabled(accentEnabled) {}

Metronome::~Metronome() {
    Mix_CloseAudio();
    SDL_Quit();
}

void Metronome::start() {
    Uint32 interval = static_cast<Uint32>((60.0 / bpm) * 1000); // ms per beat
    std::cout << "[DEBUG] Interval per beat: " << interval << "ms\n";

    bool running = true;
    int beat = 1;

    while (running) {
        if (beat == 1 && accent) {
            Mix_PlayChannel(-1, click1, 0);
        } else {
            Mix_PlayChannel(-1, click2, 0);
        }

        SDL_Delay(interval);
        beat = (beat % beatsPerMeasure) + 1;

        SDL_PumpEvents();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
    }
}

