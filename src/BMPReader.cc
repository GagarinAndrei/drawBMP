#include "BMPReader.h"

#include <fstream>
#include <iostream>
// #include <ostream>

namespace draw_bmp {

BMPReader::BMPReader() : height_(0), width_(0) {}
BMPReader::~BMPReader() { closeBMP(); }

bool BMPReader::openBMP(const std::string &fileName) {
  closeBMP();
  file_.open(fileName, std::ios::binary | std::ios::in);
  if (!file_) {
    std::cerr << "Failed to open file: " << fileName << std::endl;
    return false;
  }
  return readBMPFile();
}

void BMPReader::displayBMP() {
  printBitMapFileHeader(header_);
  printBitMapInfo(info_);
}

void BMPReader::closeBMP() {
  if (file_.is_open()) {
    file_.close();
  }
  pixelData_.clear();
}

bool BMPReader::readBMPFile() {
  readHeaders();
  if (info_.biBitCount != 24 && info_.biBitCount != 32) {
    std::cerr << "Unsupported BMP format. Only 24-bit and 32-bit BMP files are "
                 "supported."
              << std::endl;
    closeBMP();
    return false;
  }
  readPixelData();

  return true;
}

void BMPReader::readHeaders() {
  file_.read(reinterpret_cast<char *>(&header_), sizeof(BitMapFileHeader));
  if (!file_) {
    std::cerr << "Failed to read BitMapFileHeader" << std::endl;
    closeBMP();
    return;
  }
  file_.read(reinterpret_cast<char *>(&info_), sizeof(BitMapInfo));
  if (!file_) {
    std::cerr << "Failed to read BitMapInfo" << std::endl;
    closeBMP();
    return;
  }

  width_ = info_.biWidth;
  height_ = info_.biHeight;
}

void BMPReader::readPixelData() {}

void BMPReader::printBitMapFileHeader(const BitMapFileHeader &header) {
  std::cout << "BitMapFileHeader:" << std::endl;
  std::cout << "  bfType: " << header.bfType << std::endl;
  std::cout << "  bfSize: " << header.bfSize << std::endl;
  std::cout << "  bfReserved1: " << header.bfReserved1 << std::endl;
  std::cout << "  bfReserved2: " << header.bfReserved2 << std::endl;
  std::cout << "  bfOffBits: " << header.bfOffBits << std::endl;
}

void BMPReader::printBitMapInfo(const BitMapInfo &info) {
  std::cout << "BitMapInfo:" << std::endl;
  std::cout << "  bcSize: " << info.biSize << std::endl;
  std::cout << "  bcWidth: " << info.biWidth << std::endl;
  std::cout << "  bcHeight: " << info.biHeight << std::endl;
  std::cout << "  bcPlanes: " << info.biPlanes << std::endl;
  std::cout << "  bcBitCount: " << info.biBitCount << std::endl;
  std::cout << "  biCompression: " << info.biCompression << std::endl;
  std::cout << "  biSizeImage: " << info.biSizeImage << std::endl;
  std::cout << "  biXPelsPerMeter: " << info.biXPelsPerMeter << std::endl;
  std::cout << "  biYPelsPerMeter: " << info.biYPelsPerMeter << std::endl;
  std::cout << "  biClrUsed: " << info.biClrUsed << std::endl;
  std::cout << "  biClrImportant: " << info.biClrImportant << std::endl;
}
}  // namespace draw_bmp