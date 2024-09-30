#include <iostream>

#include "BMPReader.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <BMP file path>" << std::endl;
    return 1;
  }

  draw_bmp::BMPReader bmpReader;
  if (!bmpReader.openBMP(argv[1])) {
    return 1;
  }

  bmpReader.displayBMP();
  bmpReader.closeBMP();

  return 0;
}
