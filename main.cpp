#include "metronome.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./metronome_engine <bpm> <beats-per-measure>\n";
        return 1;
    }

    int bpm = std::atoi(argv[1]);
    int beatsPerMeasure = std::atoi(argv[2]);

    // Infer note value from time signature
    int noteValue = 4;
    if (beatsPerMeasure == 6) noteValue = 8; // Handle 6/8

    Metronome metro(bpm, beatsPerMeasure, noteValue);
    metro.start();

    return 0;
}
