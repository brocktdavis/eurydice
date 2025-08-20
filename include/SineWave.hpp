#ifndef SINE_WAVE_H
#define SINE_WAVE_H

#include "AbstractSample.hpp"

class SineWave : public AbstractSample {
private:
    double _frequency;
public:
    /** frequency: Hz */
    explicit SineWave(double frequency, RtAudioFormat format = RTAUDIO_FLOAT64) 
        : AbstractSample(format), _frequency(frequency) {}

    RtAudioFormat supportedFormatsBitVector(void) override;
    AbstractSample::SAMPLE_T getFrame(double seconds) override;

    // Override the stream operator for more detailed output
     friend std::ostream& operator<<(std::ostream& os, const SineWave& sineWave);
};

#endif // SINE_WAVE_H
