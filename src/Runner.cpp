#include "Runner.hpp"
#include <tuple>
#include <algorithm>
#include <iostream>

Runner::Runner() {
    _audio = new RtAudio();
}

Runner::~Runner() {
    delete _audio;
}

std::string Runner::getRtAudioVersion(void) const {
    return RtAudio::getVersion();
}

std::vector<Runner::ApiDefinition> Runner::getAvailableApis(void) const {
    std::vector<RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);

    std::vector<Runner::ApiDefinition> result;
    for (RtAudio::Api api : apis) {
        result.emplace_back(
            Runner::ApiDefinition{
                api,
                RtAudio::getApiName(api),
                RtAudio::getApiDisplayName(api),
            }
        );
    }

    return result;
}

std::vector<Runner::DeviceDefinition> Runner::getAvailableDevices(void) {
    std::vector<Runner::DeviceDefinition> result;
    for (unsigned int deviceId : _audio->getDeviceIds()) {
        RtAudio::DeviceInfo deviceInfo = _audio->getDeviceInfo(deviceId);
        result.emplace_back(
            DeviceDefinition{
                deviceId,
                deviceInfo.name,
                std::make_tuple(deviceInfo.inputChannels, deviceInfo.outputChannels, deviceInfo.duplexChannels),
                std::make_pair(deviceInfo.isDefaultInput, deviceInfo.isDefaultOutput),
                deviceInfo.sampleRates,
                deviceInfo.currentSampleRate,
                deviceInfo.preferredSampleRate,
                deviceInfo.nativeFormats
            }
        );
    }
    return result;
}

Runner::DeviceDefinition Runner::getDefaultDevice(void) {
    std::vector<Runner::DeviceDefinition> devices = getAvailableDevices();
    auto it = std::find_if(devices.begin(), devices.end(), [this](DeviceDefinition &device) {
        return device.rtAudioId == _audio->getDefaultOutputDevice();
    });

    if (it == devices.end()) {
        throw std::runtime_error("No default device found");
    } else {
        return *it;
    }
}

struct CallbackData {
    AbstractSample* sample;
    unsigned int sampleRate;
};

// Static callback function that can be converted to RtAudioCallback
int audioCallback(void *outputBuffer, void*, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus, void *userData) {
    CallbackData* data = static_cast<CallbackData*>(userData);
    AbstractSample* sample = data->sample;
    unsigned int sampleRate = data->sampleRate;
    
    float *buffer = static_cast<float *>(outputBuffer);
    std::cout << "[audioCallback] streamTime: " << streamTime << ", nBufferFrames: " << nBufferFrames << ", sampleRate: " << sampleRate << std::endl;
    for (unsigned int i = 0; i < nBufferFrames; ++i) {
        const double additionalTime = static_cast<double>(i) / sampleRate;
        std::cout << "i: " << i << ", additionalTime: " << additionalTime << std::endl;
        buffer[i] = sample->getFrame(streamTime + additionalTime).RTAUDIO_FLOAT32;
    }
    return 0;
}

void Runner::playSample(AbstractSample &sample) {
    std::cout << "Play sample " << sample << std::endl;

    Runner::DeviceDefinition defaultDevice = getDefaultDevice();

    RtAudio::StreamParameters params;
    params.deviceId = defaultDevice.rtAudioId;
    params.nChannels = 1;

    const unsigned int sampleRate = defaultDevice.currentSampleRate;
    unsigned int bufferFrames = 256;

    CallbackData callbackData = {&sample, sampleRate};

    RtAudioErrorType result = _audio->openStream(
        &params,
        nullptr, // input params
        RTAUDIO_FLOAT32,
        sampleRate,
        &bufferFrames,
        audioCallback,
        &callbackData
    );
    
    if (result != RTAUDIO_NO_ERROR) {
        std::cerr << "Failed to open audio stream: " << _audio->getErrorText() << std::endl;
        return;
    }
    
    std::cout << "Audio stream opened successfully" << std::endl;
}


std::ostream &operator<<(std::ostream& os, const Runner::DeviceDefinition &device) {
    os << device.displayName << " (id: " << device.rtAudioId << ")" << std::endl;
    os << "Max Channels (in, out, duplex): " << std::get<0>(device.channels) << ", " << std::get<1>(device.channels) << ", " << std::get<2>(device.channels) << std::endl;
    if (device.defaultDevice.first) {
        os << "Default In ";
    }
    if (device.defaultDevice.second) {
        os << "Default Out ";
    }
    if (device.defaultDevice.first || device.defaultDevice.second) {
        os << std::endl;
    }
    os << "Sample Rates: ";
    for (unsigned int rate : device.sampleRates) {
        os << rate << " ";
    }
    os << std::endl;
    os << "Current Sample Rate: " << device.currentSampleRate << std::endl;
    os << "Preferred Sample Rate: " << device.preferredSampleRate << std::endl;

    os << "Native Formats: ";
    if (device.nativeFormats ^ RTAUDIO_SINT8) {
        os << "SINT8 ";
    }
    if (device.nativeFormats ^ RTAUDIO_SINT16) {
        os << "SINT16 ";
    }
    if (device.nativeFormats ^ RTAUDIO_SINT24) {
        os << "SINT24 ";
    }
    if (device.nativeFormats ^ RTAUDIO_SINT32) {
        os << "SINT32 ";
    }
    if (device.nativeFormats ^ RTAUDIO_FLOAT32) {
        os << "FLOAT32 ";
    }
    if (device.nativeFormats ^ RTAUDIO_FLOAT64) {
        os << "FLOAT64 ";
    }
    os << std::endl;

    return os;
}
