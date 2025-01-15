//
// Created by Fuszenecker Zoltan on 14.01.2025.
//

#include <gmock/gmock.h>
#include <string>
#include "fpdfview.h"
#include "./src/mainJNILib.cpp"


class MockPDFLinkHandler : public PDFLinkHandlerInterface {
public:
    MOCK_METHOD(std::string, ExtractText, (FPDF_TEXTPAGE text_page, int char_index, int count), (override));
    MOCK_METHOD(std::string, UTF16ToUTF8, (const unsigned short* utf16, size_t length), (override));
};

//MockPDFLinkHandler* mockExtractTextInstance = nullptr;

//extern "C" std::string ExtractText(FPDF_TEXTPAGE text_page, int char_index, int count) {
//    return mockExtractTextInstance->ExtractText(text_page, char_index, count);
//}