#include <fstream>
#include <vector>
#include <string>
#include "../parser/parser.h"
#include "../sandpile/sandpile.h"
#include "../bmp/bmp.h"

namespace mpicture_space {
void generate_bmp(int argc, char **argv);

void make_iteration(params &p, const std::string &path_in, const std::string &path_out);

void from_txt(params &p, const std::string& path_in, const std::string& path_out);

void open_picture(const params &p, const std::string &path_in, sand_space::Sand &s);

void save_picture(const std::string &out_file, sand_space::Sand s);
} // namespace