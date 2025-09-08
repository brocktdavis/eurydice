#include "SquareWave.hpp"

#include <cassert>
#include <cmath>
#include <sstream>

RtAudioFormat SquareWave::supportedFormatsBitVector() {
    return RTAUDIO_SINT8 | RTAUDIO_SINT16 | RTAUDIO_SINT24 | RTAUDIO_SINT32 | RTAUDIO_FLOAT32 | RTAUDIO_FLOAT64;
}

AbstractSample::SAMPLE_T SquareWave::getFrame(double seconds) {
    int phase = static_cast<long int>(2 * seconds * _frequency);
    double sample = phase % 2 == 0 ? 1.0 : -1.0;

    AbstractSample::SAMPLE_T result{};
    
    switch (_format) {
        case RTAUDIO_SINT8:   result.RTAUDIO_SINT8 = static_cast<int8_t>(sample * 127.0); break;
        case RTAUDIO_SINT16:  result.RTAUDIO_SINT16 = static_cast<int16_t>(sample * 32767.0); break;
        case RTAUDIO_SINT24:  result.RTAUDIO_SINT24 = static_cast<int32_t>(sample * 8388607.0); break;
        case RTAUDIO_SINT32:  result.RTAUDIO_SINT32 = static_cast<int32_t>(sample * 2147483647.0); break;
        case RTAUDIO_FLOAT32: result.RTAUDIO_FLOAT32 = static_cast<float>(sample); break;
        case RTAUDIO_FLOAT64: result.RTAUDIO_FLOAT64 = sample; break;
        default: assert(false && "Unsupported format");
    }
    
    return result;
}

std::string SquareWave::describe() const {
    std::ostringstream strs;
    strs << "SquareWave " << _frequency << "Hz";
    return strs.str();
}
