#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "eurydice.hpp"

class EurydiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code that will be called before each test
    }
    
    void TearDown() override {
        // Cleanup code that will be called after each test
    }
};

TEST_F(EurydiceTest, ConstructorTest) {
    Eurydice app;
    EXPECT_NO_THROW();
}

TEST_F(EurydiceTest, GetStatusTest) {
    Eurydice app;
    std::string status = app.getStatus();
    EXPECT_EQ(status, "Eurydice is operational");
}

TEST_F(EurydiceTest, ProcessDataTest) {
    Eurydice app;
    std::string testData = "test data";
    EXPECT_NO_THROW(app.processData(testData));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 