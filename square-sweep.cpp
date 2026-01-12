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

        // Generate square wave using Fourier series
        float square = 0.0f;
        for (int n = 1; n <= numHarmonics; n += 2) { // Only odd harmonics
            square += (1.0f / n) * sin(phase * n);
        }

        // Normalize the amplitude
        square *= 4.0f / M_PI;

        // Output the wave, scaled by an amplitude factor
        mono(square * 0.707f);

        // Update the phase
        phase += 2.0f * M_PI * frequency / SAMPLE_RATE;
        if (phase > 2.0f * M_PI) {
            phase -= 2.0f * M_PI;
        }
    }

    return 0;
}