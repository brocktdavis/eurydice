#include <iostream>
#include <string>

#include "eurydice.hpp"
#include "runner.hpp"

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
}

int main(int argc, char* argv[]) {
    std::cout << "=== Eurydice C++ Application ===" << std::endl;
    
    Eurydice app;
    
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--version" || arg == "-v") {
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
        app.run();
        test_runner();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 