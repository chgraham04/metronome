#define SDL_MAIN_HANDLED
#include "metronome.h"
#include <cstdlib>
#include <iostream>

// int main(int argc, char* argv[]) {
//     std::cout << "[DEBUG] Program started with " << argc << " arguments.\n";
//
//     if (argc < 3) {
//         std::cerr << "Usage: ./metronome_engine <bpm> <beats-per-measure>\n";
//         return 1;
//     }
//
//     int bpm = std::atoi(argv[1]);
//     int beatsPerMeasure = std::atoi(argv[2]);
//
//     std::cout << "[DEBUG] BPM: " << bpm << ", Beats per Measure: " << beatsPerMeasure << "\n";
//
//     int noteValue = 4;
//     if (beatsPerMeasure == 6) noteValue = 8;
//
//     Metronome metro(bpm, beatsPerMeasure, noteValue);
//
//     std::cout << "[DEBUG] Created Metronome instance. Starting now...\n";
//     metro.start();
//
//     std::cout << "[DEBUG] Exiting program.\n";
//     return 0;
// }
int main() {
    std::cout << "[DEBUG] Hello world from metronome_engine.exe\n";
    return 0;
}
