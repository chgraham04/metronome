#define SDL_MAIN_HANDLED
#include "metronome.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "[DEBUG] Program started with " << argc << " arguments.\n";

    if (argc < 5) {
        std::cerr << "Usage: ./metronome_engine <bpm> <beatsPerMeasure> <noteValue> <accentEnabled>\n";
        return 1;
    }

    int bpm = std::atoi(argv[1]);
    int beatsPerMeasure = std::atoi(argv[2]);
    int noteValue = std::atoi(argv[3]);
    bool accentEnabled = std::atoi(argv[4]) != 0;

    std::cout << "[DEBUG] BPM: " << bpm << ", BeatsPerMeasure: " << beatsPerMeasure
              << ", NoteValue: " << noteValue << ", AccentEnabled: " << accentEnabled << "\n";

    Metronome metro(bpm, beatsPerMeasure, noteValue, accentEnabled);
    metro.start();

    std::cout << "[DEBUG] Exiting program.\n";
    return 0;
}
