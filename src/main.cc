#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Using: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    // std::ifstream file(filename);

    // // Проверяем, удалось ли открыть файл
    // if (!file.is_open()) {
    //     std::cerr << "Не удалось открыть файл: " << filename << std::endl;
    //     return 1;
    // }

    // // Читаем и выводим содержимое файла
    // std::string line;
    // while (std::getline(file, line)) {
    //     std::cout << line << std::endl;
    // }

    // Закрываем файл
    // file.close();

  return 0;
}