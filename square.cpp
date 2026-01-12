#include "everything.h"  // Include the provided header file

int main() {
    // 1. Initialization
    const double sampleRate = 48000.0;  // Sampling rate in Hz
    const double frequency = 440.0;    // Fundamental frequency (A4)
    const double duration = 5.0;       // Duration in seconds
    const int numSamples = sampleRate * duration;

    // Calculate the number of odd harmonics below Nyquist frequency
    const int numHarmonics = static_cast<int>(sampleRate / (2.0 * frequency));

    // 2. Generate the waveform
    for (int i = 0; i < numSamples; ++i) {
        double t = static_cast<double>(i) / sampleRate;  // Time in seconds
        double squareWave = 0.0;

        // Sum the odd harmonics
        for (int n = 1; n <= numHarmonics; n += 2) {  // Only odd harmonics: 1, 3, 5, ...
            squareWave += (1.0 / n) * sin(2.0 * M_PI * n * frequency * t);
        }

        // Normalize the amplitude
        squareWave *= 4.0 / M_PI;

        // 3. Output the waveform
        mono(squareWave);
    }

    return 0;
}