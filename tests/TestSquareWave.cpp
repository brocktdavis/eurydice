#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

#include <rtaudio/RtAudio.h>

#include "SquareWave.hpp"

#define ERROR 1e-12

TEST(SquareWaveFixture, testConstructor) {
    SquareWave wave(1.0);
    ASSERT_NO_THROW();
}

TEST(SquareWaveFixture, testFloat64Supported) {
    SquareWave wave(1.0);
    ASSERT_NO_THROW();

    EXPECT_TRUE(wave.supportedFormatsBitVector() & RTAUDIO_FLOAT64);
}

TEST(SquareWaveFixture, test1Hz) {
    SquareWave wave(1.0);
    ASSERT_NO_THROW();

    EXPECT_DOUBLE_EQ(wave.getFrame(0.0001).RTAUDIO_FLOAT64, 1.0);
    EXPECT_DOUBLE_EQ(wave.getFrame(0.4999).RTAUDIO_FLOAT64, 1.0);
    
    EXPECT_DOUBLE_EQ(wave.getFrame(0.5001).RTAUDIO_FLOAT64, -1.0);
    EXPECT_DOUBLE_EQ(wave.getFrame(0.9999).RTAUDIO_FLOAT64, -1.0);
}

TEST(SquareWaveFixture, test440Hz) {
    SquareWave wave(440.0);
    ASSERT_NO_THROW();

    EXPECT_DOUBLE_EQ(wave.getFrame(0.0001 / 440.0).RTAUDIO_FLOAT64, 1.0);
    EXPECT_DOUBLE_EQ(wave.getFrame(0.4999 / 440.0).RTAUDIO_FLOAT64, 1.0);
    
    EXPECT_DOUBLE_EQ(wave.getFrame(0.5001 / 440.0).RTAUDIO_FLOAT64, -1.0);
    EXPECT_DOUBLE_EQ(wave.getFrame(0.9999 / 440.0).RTAUDIO_FLOAT64, -1.0);
}

TEST(SquareWaveFixture, testRepr) {
    SquareWave wave1(440.0);
    SquareWave wave2(440.5);
    SquareWave wave3(440.3);
    SquareWave wave4(0.0);

    std::stringstream ss;
    ss << wave1 << "-" << wave2 << "-" << wave3 << "-" << wave4;

    EXPECT_EQ(ss.str(), "SquareWave 440Hz-SquareWave 440.5Hz-SquareWave 440.3Hz-SquareWave 0Hz");
}
