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

    // Used in << operator
    std::string describe() const override;
};

#endif // SINE_WAVE_H
