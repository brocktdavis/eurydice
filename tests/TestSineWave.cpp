#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

#include <rtaudio/RtAudio.h>

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
    EXPECT_NEAR(wave.getFrame(0.5).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.5).RTAUDIO_FLOAT64, 0.0, ERROR);

    EXPECT_NEAR(wave.getFrame(0.25).RTAUDIO_FLOAT64, 1.0, ERROR);
    EXPECT_NEAR(wave.getFrame(0.75).RTAUDIO_FLOAT64, -1.0, ERROR);
}

TEST(SineWaveFixture, test440Hz) {
    SineWave wave(440.0);
    ASSERT_NO_THROW();

    EXPECT_NEAR(wave.getFrame(0.0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.0).RTAUDIO_FLOAT64, 0.0, ERROR);
    EXPECT_NEAR(wave.getFrame(1.0/440.0).RTAUDIO_FLOAT64, 0.0, ERROR);

    EXPECT_NEAR(wave.getFrame(0.25/440.0).RTAUDIO_FLOAT64, 1.0, ERROR);
    EXPECT_NEAR(wave.getFrame(0.75/440.0).RTAUDIO_FLOAT64, -1.0, ERROR);
}

TEST(SineWaveFixture, testRepr) {
    SineWave wave1(440.0);
    SineWave wave2(440.5);
    SineWave wave3(440.3);
    SineWave wave4(0.0);

    std::stringstream ss;
    ss << wave1 << "-" << wave2 << "-" << wave3 << "-" << wave4;

    EXPECT_EQ(ss.str(), "SineWave 440Hz-SineWave 440.5Hz-SineWave 440.3Hz-SineWave 0Hz");
}
