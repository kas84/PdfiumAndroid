//
// Created by Fuszenecker Zoltan on 15.01.2025.
//

#ifndef PDFIUMANDROID_MOCK_LIBRARY_H
#define PDFIUMANDROID_MOCK_LIBRARY_H

#include <gmock/gmock.h>
#include <string>
#include "fpdfview.h"
#include "./src/mainJNILib.cpp"


class MockPDFLinkHandler : public PDFLinkHandlerInterface {
public:
    MOCK_METHOD(std::string, ExtractText, (FPDF_TEXTPAGE text_page, int char_index, int count), (override));
    MOCK_METHOD(std::string, UTF16ToUTF8, (const unsigned short* utf16, size_t length), (override));
};

#endif //PDFIUMANDROID_MOCK_LIBRARY_H
