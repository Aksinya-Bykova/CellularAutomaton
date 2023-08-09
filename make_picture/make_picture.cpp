#include "make_picture.h"

namespace mpicture_space {
typedef sand_space::ImSize ImSize;
typedef sand_space::SandSize SandSize;

// основная функция
void generate_bmp(int argc, char **argv) {
  params p = parse(argc, argv);

  const std::string TXT_OUT = p.o + "/test_out.txt";
  const std::string FILE_NAME = p.o + "/test_out";
  const std::string ITER_FILE_NAME = p.o + "/test_";
  const std::string BMP = std::string(".bmp");

  // по ТЗ если 0, то сохраняется только последнее состояние
  if (p.f == 0) {
    from_txt(p, p.i, TXT_OUT);

    for (auto iter = 1; iter != p.m; ++iter) {
      // как меняется картинка, если развалить песчинки
      make_iteration(p, TXT_OUT, TXT_OUT);

      // нужно ещё поменять сам песок для кода
      sand_space::Sand s;
      open_picture(p, TXT_OUT, s);

      // сохраняем bmp
      std::string picture_file = FILE_NAME + BMP;
      save_picture(picture_file, s);
    }
  } else { // если не 0, то p.f - частота сохранения картинки
    for (auto iter = 0; iter != p.m; ++iter) {
      make_iteration(p, TXT_OUT, TXT_OUT);
      if ((iter % p.f == 0) && (iter != 0)) {
        sand_space::Sand s;
        open_picture(p, TXT_OUT, s);
        save_picture(ITER_FILE_NAME + std::to_string(iter) + BMP, s);
      }
    }
  }
}

void make_iteration(params &p, const std::string &path_in, const std::string &path_out) {
  sand_space::Sand s;

  open_picture(p, path_in, s);

  play_iter(s); // работа с песком

  std::ofstream oFile(path_out);
  std::ofstream out(path_out);

  for (auto i = 0; i != s.str; ++i) {
    for (auto j = 0; j != s.col; ++j) {
      out << s.net[i][j] << " ";
    }
    out << std::endl;
  }

  out.close();

  p.l = s.str;
  p.w = s.col;
}

// txt нужен, чтобы сделать первый песок - не рисовать же мне самой кучу из 4 песчинок

void from_txt(params &p, const std::string& path_in, const std::string& path_out) {
  sand_space::Sand s;
  s.net.resize(p.l, sand_space::Str(p.w));
  s.str = p.l;
  s.col = p.w;

  std::ifstream inp;
  inp.open(path_in);

  for (auto i = 0; i != s.str * s.col; ++i) {
    ImSize x, y;
    SandSize k;
    inp >> x >> y >> k;
    s.net[x][y] = k;
  }

  inp.close();

  play_iter(s);

  std::ofstream oFile(path_out);
  std::ofstream out(path_out);

  for (auto i = 0; i != s.str; ++i) {
    for (auto j = 0; j != s.col; ++j) {
      out << s.net[i][j] << " ";
    }
    out << std::endl;
  }

  out.close();

  p.l = s.str;
  p.w = s.col;
}

// когда нужно записать картинку в песок

void open_picture(const params &p, const std::string &path_in, sand_space::Sand &s) {
  s.net.resize(p.l, sand_space::Str(p.w));
  s.str = p.l;
  s.col = p.w;

  std::ifstream inp;
  inp.open(path_in);

  for (auto i = 0; i != s.str; ++i) {
    for (auto j = 0; j != s.col; ++j) {
      inp >> s.net[i][j];
    }
  }

  inp.close();
}

// сохранение bmp

void save_picture(const std::string &out_file, sand_space::Sand s) {
  std::ofstream oFile(out_file);
  std::ofstream out(out_file);

  Image image{s.str, s.col};

  for (auto i = 0; i != s.str; ++i) {
    for (auto j = 0; j != s.col; ++j) {
      image.set_color(s.net[i][j], i, j);
    }
  }

  image.export_to_file(out_file);
}
}// namespace