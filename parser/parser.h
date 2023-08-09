#include <vector>
#include <string>

// сначала params приходят из командной строки, но в ходе выполнения программы мы их меняем

struct params{
  uint16_t l; // -l, --length - длина сетки (гарантированно влезет в uint16_t)
  uint16_t w; // -w, --width - ширина сетки (гарантированно влезет в uint16_t)
  std::string i; // -i, --input - tsv-файл (tab-separated values) c начальными данными
  std::string o; // -o, --output - путь к директории, для сохранения картинок
  uint16_t m; // -m, --max-iter - максимальное количество итераций модели
  uint16_t f; // -f, --freq - частота с которой должны сохранятся картинки
  // (если 0, то сохраняется только последнее состояние)
};

params parse(int argc, char** argv);
