#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <RtAudio.h>

#include "SineWave.hpp"

#define ERROR 1e-12

TEST(SineWaveFixture, testConstructor) {
    SineWave wave(1.0);
    ASSERT_NO_THROW();
}

TEST(SineWaveFixture, testFloat64Supported) {
    SineWave wave(1.0);
    ASSERT_NO_THROW();

    EXPECT_TRUE(wave.supportedFormatsBitVector() & RTAUDIO_FLOAT64);
}

TEST(SineWaveFixture, test1Hz) {
    SineWave wave(1.0);
    ASSERT_NO_THROW();

    EXPECT_NEAR(wave.getFrame(0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(0.0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.0).RTAUDIO_FLOAT64, 0.0, ERROR);

    EXPECT_NEAR(wave.getFrame(0.5).RTAUDIO_FLOAT64, 1.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.5).RTAUDIO_FLOAT64, -1.0, ERROR);
}

TEST(SineWaveFixture, test440Hz) {
    SineWave wave(440.0);
    ASSERT_NO_THROW();

    EXPECT_NEAR(wave.getFrame(0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(0.0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.0).RTAUDIO_FLOAT64, 0.0, ERROR);

    EXPECT_NEAR(wave.getFrame(1.0/440.0).RTAUDIO_FLOAT64, 0.0, ERROR);

    EXPECT_NEAR(wave.getFrame(0.5/440.0).RTAUDIO_FLOAT64, 1.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.5/440.0).RTAUDIO_FLOAT64, -1.0, ERROR);
}
