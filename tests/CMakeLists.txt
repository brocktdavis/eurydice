# Find Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    # Download and build Google Test if not found
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Test source files
set(TEST_SOURCES
    test_eurydice.cpp
    TestSineWave.cpp
)

# Create test executable
add_executable(unit_tests ${TEST_SOURCES})

# Link libraries
target_link_libraries(unit_tests 
    gtest_main 
    gmock
)

# Link with main library
target_link_libraries(unit_tests eurydice_lib)

# Add tests
include(GoogleTest)
gtest_discover_tests(unit_tests) 