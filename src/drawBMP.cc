// #include "drawBMP.h"

// BMPReader::BMPReader() : width(0), height(0) {}

// BMPReader::~BMPReader() {
//     closeBMP();
// }

// bool BMPReader::openBMP(const std::string &fileName) {
//     closeBMP();
//     return readBMPFile(fileName);
// }

// void BMPReader::displayBMP() const {
//     if (pixelData.empty()) {
//         std::cerr << "No BMP file loaded." << std::endl;
//         return;
//     }

//     for (int y = height - 1; y >= 0; --y) {
//         for (int x = 0; x < width; ++x) {
//             int index = (y * width + x) * (bmpInfoHeader.biBitCount / 8);
//             uint8_t r = pixelData[index + 2];
//             uint8_t g = pixelData[index + 1];
//             uint8_t b = pixelData[index];

//             if (r == 0 && g == 0 && b == 0) {
//                 std::cout << "#"; // Черный цвет
//             } else if (r == 255 && g == 255 && b == 255) {
//                 std::cout << " "; // Белый цвет (фон)
//             } else {
//                 std::cout << "?"; // Неизвестный цвет
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// void BMPReader::closeBMP() {
//     if (file.is_open()) {
//         file.close();
//     }
//     pixelData.clear();
// }

// bool BMPReader::readBMPFile(const std::string &fileName) {
//     file.open(fileName, std::ios::binary);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file: " << fileName << std::endl;
//         return false;
//     }

//     readHeaders();
//     readPixelData();
//     return true;
// }

// void BMPReader::readHeaders() {
//     file.read(reinterpret_cast<char*>(&bmpFileHeader),
//     sizeof(BMPFileHeader));
//     file.read(reinterpret_cast<char*>(&bmpInfoHeader),
//     sizeof(BMPInfoHeader));

//     if (bmpFileHeader.bfType != 0x4D42 || (bmpInfoHeader.biBitCount != 24 &&
//     bmpInfoHeader.biBitCount != 32)) {
//         std::cerr << "Unsupported BMP format." << std::endl;
//         closeBMP();
//         return;
//     }

//     width = bmpInfoHeader.biWidth;
//     height = bmpInfoHeader.biHeight;
// }

// void BMPReader::readPixelData() {
//     int rowSize = ((bmpInfoHeader.biBitCount * width + 31) / 32) * 4;
//     int pixelDataSize = rowSize * height;
//     pixelData.resize(pixelDataSize);

//     file.seekg(bmpFileHeader.bfOffBits, std::ios::beg);
//     file.read(reinterpret_cast<char*>(pixelData.data()), pixelDataSize);
// }