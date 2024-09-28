// #ifndef BMPREADER_H
// #define BMPREADER_H

// #include <cstdint>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <iostream>

// struct BMPFileHeader {
//     uint16_t bfType;
//     uint32_t bfSize;
//     uint16_t bfReserved1;
//     uint16_t bfReserved2;
//     uint32_t bfOffBits;
// };

// struct BMPInfoHeader {
//     uint32_t biSize;
//     int32_t biWidth;
//     int32_t biHeight;
//     uint16_t biPlanes;
//     uint16_t biBitCount;
//     uint32_t biCompression;
//     uint32_t biSizeImage;
//     int32_t biXPelsPerMeter;
//     int32_t biYPelsPerMeter;
//     uint32_t biClrUsed;
//     uint32_t biClrImportant;
// };

// class BMPReader {
// public:
//     BMPReader();
//     ~BMPReader();

//     bool openBMP(const std::string &fileName);
//     void displayBMP() const;
//     void closeBMP();

// private:
//     BMPFileHeader bmpFileHeader;
//     BMPInfoHeader bmpInfoHeader;
//     std::vector<uint8_t> pixelData;
//     int width;
//     int height;
//     std::ifstream file;

//     bool readBMPFile(const std::string &fileName);
//     void readHeaders();
//     void readPixelData();
// };

// #endif // BMPREADER_H