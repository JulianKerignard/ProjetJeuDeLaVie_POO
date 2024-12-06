#include "gtest/gtest.h"
#include "FileHandler.h"

TEST(FileHandlerTest, ValidateFileFormat_ValidContent) {
    FileHandler fileHandler;
    std::string validContent = "5 5\n0 1 0 0 0\n0 0 0 0 0\n0 0 2 0 0\n0 0 0 0 0\n0 0 0 0 0\n";
    EXPECT_TRUE(fileHandler.validateFileFormat(validContent));
}

TEST(FileHandlerTest, ValidateFileFormat_InvalidContent) {
    FileHandler fileHandler;
    std::string invalidContent = "5 5\n0 1 0 0\n0 0 0 0 0\n0 0 2 0 0\n0 0 0 0 0\n0 0 0 0 0\n";
    EXPECT_FALSE(fileHandler.validateFileFormat(invalidContent));
}