# Source files for the library
set(LIB_SOURCES
    AbstractSample.cpp
    Runner.cpp
    SineWave.cpp
    SquareWave.cpp
)

# Source files for the main executable
set(MAIN_SOURCES
    main.cpp
)

# Create library
add_library(eurydice_lib ${LIB_SOURCES})

# Set compiler flags for library
target_compile_options(eurydice_lib PRIVATE -Wall -Wextra -Wpedantic)

# Link RtAudio to library (required via vcpkg)
target_link_libraries(eurydice_lib RtAudio::rtaudio)

# Create executable
add_executable(eurydice ${MAIN_SOURCES})

# Link executable with library
target_link_libraries(eurydice eurydice_lib)

# Link RtAudio to executable (required via vcpkg)
target_link_libraries(eurydice RtAudio::rtaudio)

# Set compiler flags for executable
target_compile_options(eurydice PRIVATE -Wall -Wextra -Wpedantic)
