#include "metronome.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <thread>

Metronome::Metronome(int bpm, int beatsPerMeasure, int noteValue, bool accentEnabled)
    : bpm(bpm), beatsPerMeasure(beatsPerMeasure), noteValue(noteValue), accentEnabled(accentEnabled) {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    click1 = Mix_LoadWAV("click_2.wav");
    click2 = Mix_LoadWAV("click_1.wav");

    if (!click1 || !click2) {
        std::cerr << "[SDL ERROR] Failed to load click sounds.\n";
        if (!click1) std::cerr << " - click_1.wav not loaded.\n";
        if (!click2) std::cerr << " - click_2.wav not loaded.\n";
    }
}

Metronome::~Metronome() {
    Mix_FreeChunk(click1);
    Mix_FreeChunk(click2);
    Mix_CloseAudio();
    SDL_Quit();
}

void Metronome::start() {
    Uint32 interval = static_cast<Uint32>((60.0 / bpm) * 1000); // milliseconds per beat
    std::cout << "[DEBUG] Interval per beat: " << interval << "ms\n";

    int beat = 1;
    while (true) {
        if (beat == 1 && accentEnabled) {
            Mix_PlayChannel(-1, click1, 0);
        } else {
            Mix_PlayChannel(-1, click2, 0);
        }

        SDL_Delay(interval);
        beat = (beat % beatsPerMeasure) + 1;
        SDL_PumpEvents(); // Keep SDL responsive
    }
}
