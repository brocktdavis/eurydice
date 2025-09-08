#include <iostream>
#include <string>

#include "Runner.hpp"
#include "SineWave.hpp"
#include "SquareWave.hpp"

void test_sine(Runner &runner) {
    std::vector<std::unique_ptr<AbstractSample>> samples1;

    samples1.push_back(std::make_unique<SineWave>(440.0)); // A4
    samples1.push_back(std::make_unique<SineWave>(554.37)); // C#5
    samples1.push_back(std::make_unique<SineWave>(659.255)); // E5

    std::cout << "Playing AMaj (Note frequencies)" << std::endl;
    runner.playSamples(samples1);


    std::vector<std::unique_ptr<AbstractSample>> samples2;

    samples2.push_back(std::make_unique<SineWave>(440.0)); // A4
    samples2.push_back(std::make_unique<SineWave>(550.0)); // ~C#5
    samples2.push_back(std::make_unique<SineWave>(660.0)); // ~E5

    std::cout << "Playing AMaj (Perfect harmonies)" << std::endl;
    runner.playSamples(std::move(samples2));
}

void test_square(Runner &runner) {
    std::vector<std::unique_ptr<AbstractSample>> samples1;

    samples1.push_back(std::make_unique<SquareWave>(440.0)); // A4
    samples1.push_back(std::make_unique<SquareWave>(554.37)); // C#5
    samples1.push_back(std::make_unique<SquareWave>(659.255)); // E5

    std::cout << "Playing AMaj (Square note frequencies)" << std::endl;
    runner.playSamples(samples1);
}

void test_runner() {
    Runner runner;

    std::cout << "RtAudio version: " << runner.getRtAudioVersion() << std::endl << std::endl;

    std::cout << "Available apis: ";
    for (Runner::ApiDefinition apiDef : runner.getAvailableApis()) {
        std::cout << apiDef.displayName << " (" << apiDef.identifyingName << ") ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Devices: ";
    for (Runner::DeviceDefinition device : runner.getAvailableDevices()) {
        std::cout << device << std::endl;
    }

    std::cout << "--------------------------------" << std::endl << std::endl;

    try {
        const Runner::DeviceDefinition defaultDevice = runner.getDefaultDevice();
        std::cout << "Default device: " << defaultDevice << std::endl << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl << std::endl;
    }

    std::cout << "--------------------------------" << std::endl << std::endl;

    test_sine(runner);
    test_square(runner);
}

int main(int argc, char* argv[]) {
    std::cout << "=== Eurydice C++ Application ===" << std::endl;
    
    
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--version" || arg == "-v") {
            // TODO: use manifest/Cmake/other place to get this version
            std::cout << "Eurydice version 1.0.0" << std::endl;
            return 0;
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -h, --help     Show this help message" << std::endl;
            std::cout << "  -v, --version  Show version information" << std::endl;
            return 0;
        }
    }
    
    try {
        test_runner();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 