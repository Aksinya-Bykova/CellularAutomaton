#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Color {
  uint8_t r{};
  uint8_t g{};
  uint8_t b{};

  Color(uint8_t r, uint8_t g, uint8_t b);
};

const int COLOR_SIZE = 4;
const int CHANNEL_AMOUNT = 4;
const Color COLORS[] = {
    {255, 255, 255}, // white
    {0, 255, 0}, // green
    {105, 0, 198}, // purple
    {255, 255, 0}, // yellow
    {0, 0, 0} // black
};

const int FILE_HEADER_SIZE = 14;
const int INFORMATION_HEADER_SIZE = 40;
const int BYTE = 8;
const int MAX_PADDING = 4;

class Image {
 public:
  Image(uint16_t height, uint16_t width);
  void set_color(uint64_t color, int x, int y);
  void export_to_file(const std::string& path) const;

 private:
  std::vector<uint8_t> color_array;
  uint16_t image_width;
  uint16_t image_height;
};