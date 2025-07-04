#define SDL_MAIN_HANDLED
#include "metronome.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: ./metronome_engine <bpm> <beats-per-measure> <noteValue> <accentEnabled>\n";
        return 1;
    }

    int bpm = std::atoi(argv[1]);
    int beatsPerMeasure = std::atoi(argv[2]);
    int noteValue = std::atoi(argv[3]);
    bool accentEnabled = std::atoi(argv[4]);

    Metronome metro(bpm, beatsPerMeasure, noteValue);
    metro.setAccentEnabled(accentEnabled);
    metro.start();

    return 0;
}
