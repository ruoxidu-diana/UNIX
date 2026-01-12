#include "everything.h"

int main() {
    // Sampling rate and duration
    const double sampleRate = 48000.0; // 48 kHz
    const double duration = 5.0;      // 5 seconds
    const int numSamples = sampleRate * duration;

    for (int i = 0; i < numSamples; ++i) {
        double t = static_cast<double>(i) / sampleRate;

        // Frequency of the impulse train (e.g., periodicity of impulses)
        double frequency = 440.0; // Example: A4 note

        // Calculate the number of harmonics below Nyquist
        int numHarmonics = static_cast<int>(sampleRate / (2.0 * frequency));

        // Generate impulse train using Fourier series
        double impulse = 0.0;
        for (int n = 1; n <= numHarmonics; ++n) { // Include all harmonics
            impulse += sin(2.0 * M_PI * n * frequency * t);
        }

        // Normalize the amplitude
        impulse /= numHarmonics;

        // Output the impulse train
        mono(impulse);
    }

    return 0;
}
