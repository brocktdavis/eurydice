# Eurydice

A modern C++ project with CMake build system.

## Features

- **Modern C++17** with CMake build system
- **Unit testing** with Google Test framework
- **Standard development tools** for code quality
- **Cross-platform** compatibility

## Prerequisites

- **CMake** 3.16 or higher
- **GCC** 11 or higher (or compatible compiler)
- **Make** (for convenience commands)
- **vcpkg** (for package management)
- **RtAudio** (installed via vcpkg)

## Quick Start

1. **Setup vcpkg and install dependencies**
   ```bash
   make setup
   ```

2. **Build the project**
   ```bash
   make build
   ```

3. **Run the application**
   ```bash
   make run
   ```

4. **Run tests**
   ```bash
   make test
   ```

## Build Commands

```bash
make build        # Build the project
make run          # Build and run
make test         # Run tests
make clean        # Clean build artifacts
make help         # Show all available commands
```

## Development

### Testing

Tests are built using Google Test framework:

```bash
make test       # Run all tests
cd build && ctest --verbose  # Run tests with verbose output
```

### Adding New Features

1. Add header files to `include/`
2. Add implementation files to `src/`
3. Update `src/CMakeLists.txt` with new source files
4. Add tests to `tests/`
5. Update `tests/CMakeLists.txt` if needed

## Configuration

### Environment Variables

- `CMAKE_BUILD_TYPE`: Set to `Debug` or `Release`
- `CMAKE_CXX_STANDARD=17`: C++17 standard

### Build Options

- **C++17**: Modern C++ standard
- **CMake 3.16+**: Modern build system
- **Google Test**: Unit testing framework
- **RtAudio**: Cross-platform real-time audio I/O library

### Audio Support

This project includes RtAudio for real-time audio functionality:

- **Cross-platform**: Works on Windows, macOS, and Linux
- **Multiple APIs**: Supports ALSA, PulseAudio, JACK, Core Audio, WASAPI, ASIO
- **Real-time**: Low-latency audio input/output
- **Device enumeration**: Lists available audio devices and their capabilities

## Troubleshooting

### Debug Mode

To build in debug mode:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release Mode

To build in release mode:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## License

[Add your license information here]

## Version

Current version: 1.0.0
