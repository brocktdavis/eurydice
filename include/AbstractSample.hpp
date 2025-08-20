#ifndef ABSTRACT_SAMPLE_H
#define ABSTRACT_SAMPLE_H

#include <RtAudio/RtAudio.h>
#include <iostream>
#include <string>

class AbstractSample {
protected:
    RtAudioFormat _format = RTAUDIO_FLOAT64;
public:
    // Constructor to allow format specification
    explicit AbstractSample(RtAudioFormat format = RTAUDIO_FLOAT64) : _format(format) {}
    
    // Virtual destructor for proper cleanup
    virtual ~AbstractSample() = default;

    union SAMPLE_T {
        int8_t RTAUDIO_SINT8;
        int16_t RTAUDIO_SINT16;
        int32_t RTAUDIO_SINT24;
        int32_t RTAUDIO_SINT32;
        float RTAUDIO_FLOAT32;
        double RTAUDIO_FLOAT64;
    };

    virtual RtAudioFormat supportedFormatsBitVector(void) = 0;
    virtual SAMPLE_T getFrame(double seconds) = 0;

    // Pure virtual method for string representation
    virtual std::string describe() const = 0;

    // Friend declaration for stream operator that uses the virtual method
    friend std::ostream& operator<<(std::ostream& os, const AbstractSample& sample);
};

// Stream operator for AbstractSample that uses the virtual describe() method
std::ostream& operator<<(std::ostream& os, const AbstractSample& sample);

#endif // ABSTRACT_SAMPLE_H
