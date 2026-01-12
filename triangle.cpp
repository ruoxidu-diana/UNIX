#include "everything.h"
#include <cmath>

int main() {
    // Sampling rate and duration
    const double sampleRate = 48000.0; // 48 kHz
    const double duration = 5.0;      // 5 seconds
    const int numSamples = sampleRate * duration;

    for (int i = 0; i < numSamples; ++i) {
        double t = static_cast<double>(i) / sampleRate;

        // Fundamental frequency of the triangle wave
        double frequency = 440.0; // Example: A4 note

        // Calculate the number of harmonics below Nyquist
        int numHarmonics = static_cast<int>(sampleRate / (2.0 * frequency));
        if (numHarmonics % 2 == 0) --numHarmonics; // Ensure odd number of harmonics

        // Generate the triangle wave using Fourier series
        double triangle = 0.0;
        for (int n = 1; n <= numHarmonics; n += 2) { // Sum only odd harmonics
            triangle += pow(-1.0, (n - 1) / 2) * (1.0 / (n * n)) * sin(2.0 * M_PI * n * frequency * t);
        }

        // Normalize the amplitude
        triangle *= 8.0 / (M_PI * M_PI);

        // Output the triangle wave
        mono(triangle);
    }

    return 0;
}