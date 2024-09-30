#include "BMPReader.h"

#include <fstream>
#include <iostream>
// #include <ostream>

namespace draw_bmp {

BMPReader::BMPReader() : height_(0), width_(0) {}
BMPReader::~BMPReader() { closeBMP(); }

bool BMPReader::openBMP(const std::string &fileName) {
  closeBMP();
  loadBMP(fileName, 0, 0);
  return true;
}

void BMPReader::displayBMP() { printBitMapInfo(header_); }

void BMPReader::closeBMP() {
  if (file_.is_open()) {
    file_.close();
  }
  pixelData_.clear();
}

int *BMPReader::loadBMP(const std::string &fileName, int &mx, int &my) {
  mx = my = -1;
  file_.open(fileName, std::ios::binary | std::ios::in);
  if (!file_) {
    std::cerr << "Failed to open file: " << fileName << std::endl;
    return nullptr;
  }

  BMPheader bh;  // File header sizeof(BMPheader) = 56

  // читаем заголовок
  file_.read(reinterpret_cast<char *>(&bh), sizeof(BMPheader));
  if (!file_) {
    std::cerr << "Failed to read file header: " << fileName << std::endl;
    return nullptr;
  }

  // проверяем сигнатуру
  if (bh.bfType != 0x4d42 && bh.bfType != 0x4349 && bh.bfType != 0x5450) {
    file_.close();
    return nullptr;
  }

  // проверка размера файла
  fseek(f, 0, SEEK_END);
  int filesize = ftell(f);
  // восстановим указатель в файле:
  fseek(f, sizeof(BMPheader), SEEK_SET);
  // проверим условия
  if (bh.bfSize != filesize || bh.bfReserved != 0 || bh.biPlanes != 1 ||
      (bh.biSize != 40 && bh.biSize != 108 && bh.biSize != 124) ||
      bh.bfOffBits != 14 + bh.biSize ||

      bh.biWidth < 1 || bh.biWidth > 10000 || bh.biHeight < 1 ||
      bh.biHeight > 10000 ||
      bh.biBitCount !=
          24 ||  // пока рассматриваем только полноцветные изображения
      bh.biCompression != 0  // пока рассматриваем только несжатие изображения
  ) {
    fclose(f);
    return NULL;
  }
  // Заголовок прочитан и проверен, тип - верный (BGR-24), размеры (mx,my)
  // найдены
  int mx = bh.biWidth;
  int my = bh.biHeight;
  int mx3 =
      (3 * mx + 3) &
      (-4);  // Compute row width in file, including padding to 4-byte boundary
  unsigned char *tmp_buf = new unsigned char[mx3 * my];  // читаем данные
  res = fread(tmp_buf, 1, mx3 * my, f);
  if ((int)res != mx3 * my) {
    delete[] tmp_buf;
    fclose(f);
    return NULL;
  }
  // данные прочитаны
  fclose(f);

  // выделим память для результата
  v = new int[mx * my];

  // Перенос данных (не забудем про BGR->RGB)
  unsigned char *ptr = (unsigned char *)v;
  for (int y = my - 1; y >= 0; y--) {
    unsigned char *pRow = tmp_buf + mx3 * y;
    for (int x = 0; x < mx; x++) {
      *ptr++ = *(pRow + 2);
      *ptr++ = *(pRow + 1);
      *ptr++ = *pRow;
      pRow += 3;
      ptr++;
    }
  }
  delete[] tmp_buf;
  return v;  // OK
}

void BMPReader::printBitMapInfo(const BMPheader &header) {
  std::cout << "BitMapFileHeader:" << std::endl;
  std::cout << "  bfType: " << std::hex << header.bfType << std::dec
            << std::endl;
  std::cout << "  bfSize: " << header.bfSize << std::endl;
  std::cout << "  bfReserved1: " << header.bfReserved << std::endl;
  std::cout << "  bfOffBits: " << header.bfOffBits << std::endl;
  std::cout << "BitMapInfo:" << std::endl;
  std::cout << "  bcSize: " << header.biSize << std::endl;
  std::cout << "  bcWidth: " << header.biWidth << std::endl;
  std::cout << "  bcHeight: " << header.biHeight << std::endl;
  std::cout << "  bcPlanes: " << header.biPlanes << std::endl;
  std::cout << "  bcBitCount: " << header.biBitCount << std::endl;
  std::cout << "  biSize: " << header.biCompression << std::endl;
}
}  // namespace draw_bmp