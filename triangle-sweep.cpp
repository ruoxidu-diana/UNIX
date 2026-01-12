#include "everything.h"

int main(int argc, char* argv[]) {
    float phase = 0.0f;

    // Start from the highest MIDI note (127) and sweep down to the lowest (0)
    for (float note = 127.0f; note > 0.0f; note -= 0.001f) {
        // Convert MIDI note to frequency
        float frequency = mtof(note);

        // Calculate the number of harmonics below the Nyquist frequency
        int numHarmonics = static_cast<int>(SAMPLE_RATE / (2.0f * frequency));
        numHarmonics = numHarmonics - (numHarmonics % 2 == 0); // Ensure odd harmonics only

        // Generate triangle wave using Fourier series
        float triangle = 0.0f;
        for (int n = 1; n <= numHarmonics; n += 2) { // Only odd harmonics
            triangle += pow(-1.0f, (n - 1) / 2.0f) * (1.0f / (n * n)) * sin(phase * n);
        }

        // Normalize the amplitude
        triangle *= 8.0f / (M_PI * M_PI);

        // Output the wave, scaled by an amplitude factor
        mono(triangle * 0.707f);

        // Update the phase
        phase += 2.0f * M_PI * frequency / SAMPLE_RATE;
        if (phase > 2.0f * M_PI) {
            phase -= 2.0f * M_PI;
        }
    }

    return 0;
}