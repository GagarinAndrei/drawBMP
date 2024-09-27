#ifndef DRAWBMP_SRC_DRAWBMP_H
#define DRAWBMP_SRC_DRAWBMP_H
#include <fstream>
// #include <windows.h>

class drawBMP {
 public:
  drawBMP();
  ~drawBMP();

  
  void openBMP(const std::string &fileName);
  void displayBMP();
  void closeBMP();
};

#endif  // DRAWBMP_SRC_DRAWBMP_H