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
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "[SDL ERROR] Failed to initialize SDL: " << SDL_GetError() << "\n";
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "[SDL ERROR] Failed to open audio: " << Mix_GetError() << "\n";
        return;
    }

    Mix_Chunk* click1 = Mix_LoadWAV("click_1.wav");
    Mix_Chunk* click2 = Mix_LoadWAV("click_2.wav");

    if (!click1 || !click2) {
        std::cerr << "[SDL ERROR] Failed to load click sounds.\n";
        if (!click1) std::cerr << " - click_1.wav not loaded.\n";
        if (!click2) std::cerr << " - click_2.wav not loaded.\n";
        return;
    }

    int intervalMs = static_cast<int>((60000.0 / bpm) * (4.0 / noteValue));
    std::cout << "[DEBUG] Interval per beat: " << intervalMs << "ms\n";

    int beatCount = 0;
    while (true) {
        if (accentEnabled && (beatCount % beatsPerMeasure == 0)) {
            Mix_PlayChannel(-1, click1, 0);
        } else {
            Mix_PlayChannel(-1, click2, 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        beatCount++;
    }

    // NOTE: This loop runs until externally terminated (e.g., by Python GUI).
}
