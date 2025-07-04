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
    std::cout << "[DEBUG] Initializing SDL audio...\n";

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "[ERROR] SDL_Init error: " << SDL_GetError() << "\n";
        return false;
    }

    std::cout << "[DEBUG] SDL_Init successful.\n";

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "[ERROR] Mix_OpenAudio error: " << Mix_GetError() << "\n";
        return false;
    }

    std::cout << "[DEBUG] Mix_OpenAudio successful.\n";

    click1 = Mix_LoadWAV("click_1.wav");
    if (!click1) {
        std::cerr << "[ERROR] Failed to load click_1.wav: " << Mix_GetError() << "\n";
        return false;
    } else {
        std::cout << "[DEBUG] click_1.wav loaded successfully.\n";
    }

    click2 = Mix_LoadWAV("click_2.wav");
    if (!click2) {
        std::cerr << "[ERROR] Failed to load click_2.wav: " << Mix_GetError() << "\n";
        return false;
    } else {
        std::cout << "[DEBUG] click_2.wav loaded successfully.\n";
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
    std::cout << "[DEBUG] Playing " << (isAccent ? "click_1.wav" : "click_2.wav") << "\n";

    if (sound) {
        int channel = Mix_PlayChannel(-1, sound, 0);
        if (channel == -1) {
            std::cerr << "[ERROR] Mix_PlayChannel failed: " << Mix_GetError() << "\n";
        } else {
            std::cout << "[DEBUG] Sound playing on channel " << channel << "\n";
        }
    } else {
        std::cerr << "[ERROR] Sound chunk is null!\n";
    }
}


void Metronome::start() {
    std::cout << "[DEBUG] Starting metronome...\n";

    if (!initializeAudio()) {
        std::cerr << "[ERROR] Failed to initialize audio.\n";
        return;
    }

    const int interval_ms = static_cast<int>(60000.0 / bpm);
    std::cout << "[DEBUG] BPM = " << bpm << ", interval = " << interval_ms << " ms\n";

    for (int beat = 0;; ++beat) {
        bool isAccent = (beat % beatsPerMeasure == 0);
        std::cout << "[DEBUG] Beat " << beat << " (" << (isAccent ? "accent" : "regular") << ")\n";
        playTick(isAccent);
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

