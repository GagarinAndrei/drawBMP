#ifndef BMP_READER_H
#define BMP_READER_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace draw_bmp {

// #pragma pack(push, 4)

typedef struct {
  uint16_t bfType;
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
} BitMapFileHeader;

typedef struct {
  uint32_t biSize;
  int32_t biWidth;
  int32_t biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;

} BitMapInfo;

// #pragma pack(pop)

class BMPReader {
 public:
  BMPReader();
  ~BMPReader();

  bool openBMP(const std::string &fileName);
  void displayBMP();
  void closeBMP();

 private:
  BitMapFileHeader header_;
  BitMapInfo info_;
  std::vector<uint16_t> pixelData_;
  std::fstream file_;
  uint16_t height_;
  uint16_t width_;

  bool readBMPFile();
  void readHeaders();
  void readPixelData();

  void printBitMapInfo(const BitMapInfo &info);
  void printBitMapFileHeader(const BitMapFileHeader &header);
};
};  // namespace draw_bmp

#endif  // BMP_READER_H