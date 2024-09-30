#ifndef BMP_READER_H
#define BMP_READER_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace draw_bmp {

using BYTE = uint8_t;
using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = int32_t;

typedef struct {
  WORD bfType;
  DWORD bfSize;
  DWORD bfReserved;
  DWORD bfOffBits;
  DWORD biSize;
  LONG biWidth;
  LONG biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BMPheader;

class BMPReader {
 public:
  BMPReader();
  ~BMPReader();

  bool openBMP(const std::string &fileName);
  void displayBMP();
  void closeBMP();

 private:
  BMPheader header_;
  std::vector<uint16_t> pixelData_;
  std::fstream file_;
  uint16_t height_;
  uint16_t width_;

  int* loadBMP(const std::string &fileName, int &mx, int &my);

  void printBitMapInfo(const BMPheader &header_);
};
};  // namespace draw_bmp

#endif  // BMP_READER_H