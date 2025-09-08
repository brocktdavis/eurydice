#ifndef RUNNER_H
#define RUNNER_H

#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

#include <rtaudio/RtAudio.h>

#include "AbstractSample.hpp"

class Runner {
private:
    RtAudio* _audio;
public:
    Runner();
    ~Runner();

    /** Defines information about an audio API (e.g. Linux PulseAudio) */
    struct ApiDefinition {
        RtAudio::Api enumValue;
        std::string identifyingName;
        std::string displayName;
    };

    /** Defines information about an audio device. */
    struct DeviceDefinition {
        unsigned int rtAudioId{};
        std::string displayName;
        std::tuple<unsigned int, unsigned int, unsigned int> channels; // in, out, duplex channels
        std::pair<bool, bool> defaultDevice; // in, out
        std::vector<unsigned int> sampleRates;
        unsigned int currentSampleRate{};   /*!< Current sample rate, system sample rate as currently configured. */
        unsigned int preferredSampleRate{}; /*!< Preferred sample rate, e.g. for WASAPI the system sample rate. */
        RtAudioFormat nativeFormats{}; // bitmask of supported audio formats
    };

    std::string getRtAudioVersion(void) const;
    std::vector<ApiDefinition> getAvailableApis(void) const;
    std::vector<DeviceDefinition> getAvailableDevices(void); // TODO: const?
    DeviceDefinition getDefaultDevice(void); // TODO: const?
    void playSamples(const std::vector<std::unique_ptr<AbstractSample>>& samples);
};

std::ostream& operator<<(std::ostream& os, const Runner::DeviceDefinition& device);

#endif // RUNNER_H
