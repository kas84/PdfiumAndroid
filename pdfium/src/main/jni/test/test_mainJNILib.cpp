#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "fpdfview.h"
#include "mock_library.h"

extern "C" bool IsCharacterSpace(FPDF_TEXTPAGE text_page, int char_index, PDFLinkHandlerInterface *pdfLinkHandler);


class IsCharacterSpaceTest : public ::testing::Test {
public:
    MockPDFLinkHandler mockPdfLinkHandler;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test when the character is a space
TEST_F(IsCharacterSpaceTest, ReturnsTrueForSpace) {
    // Set up the mock to return a space
    FPDF_TEXTPAGE mockTextPage = nullptr; // Use a dummy value for the tes
    EXPECT_CALL(mockPdfLinkHandler, ExtractText(mockTextPage, 0, 1))
            .WillOnce(::testing::Return(" "));

    EXPECT_TRUE(IsCharacterSpace(mockTextPage, 0, &mockPdfLinkHandler));
}

// Test when the character is not a space
TEST_F(IsCharacterSpaceTest, ReturnsFalseForNonSpace) {
    // Set up the mock to return a non-space character
    EXPECT_CALL(mockPdfLinkHandler, ExtractText(::testing::_, ::testing::_, ::testing::_))
            .WillOnce(::testing::Return("a"));

    FPDF_TEXTPAGE mockTextPage = nullptr; // Use a dummy value for the test
    EXPECT_FALSE(IsCharacterSpace(mockTextPage, 1, &mockPdfLinkHandler));
}

// Test for edge case (empty character)
TEST_F(IsCharacterSpaceTest, ReturnsFalseForEmptyCharacter) {
    // Set up the mock to return an empty string
    EXPECT_CALL(mockPdfLinkHandler, ExtractText(::testing::_, ::testing::_, ::testing::_))
            .WillOnce(::testing::Return(""));

    FPDF_TEXTPAGE mockTextPage = nullptr; // Use a dummy value for the test
    EXPECT_FALSE(IsCharacterSpace(mockTextPage, 2, &mockPdfLinkHandler));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}