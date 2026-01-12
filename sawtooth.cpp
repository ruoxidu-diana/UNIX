#include "everything.h"  

int main() {
    const double sampleRate = 48000.0;  
    const double frequency = 440.0;    
    const double duration = 5.0;      
    const int numSamples = sampleRate * duration;

    // Calculate the number of harmonics below Nyquist frequency
    const int numHarmonics = static_cast<int>(sampleRate / (2.0 * frequency));

    for (int i = 0; i < numSamples; ++i) {
        double t = static_cast<double>(i) / sampleRate;  // Time in seconds
        double sawtooth = 0.0;

        // Sum the harmonics
        for (int n = 1; n <= numHarmonics; ++n) {
            sawtooth += (1.0 / n) * sin(2.0 * M_PI * n * frequency * t);
        }

        // Normalize the amplitude
        sawtooth *= 0.5;

        // Output the waveform
        mono(sawtooth);
    }

    return 0;
}