#include "bmp.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
  this->r = r;
  this->g = g;
  this->b = b;
}


void Image::export_to_file(const std::string& path) const {
  std::ofstream out(path, std::ios::binary);

  if (!out) {
    throw std::runtime_error("Failed to open: test.bmp");
  }

  uint32_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + image_width * image_height + CHANNEL_AMOUNT * (COLOR_SIZE + 1);

  unsigned char file_header[FILE_HEADER_SIZE];
  // file type
  file_header[0] = 'B';
  file_header[1] = 'M';
  // file size
  file_header[2] = (file_size >> BYTE * 0);
  file_header[3] = (file_size >> BYTE * 1);
  file_header[4] = (file_size >> BYTE * 2);
  file_header[5] = (file_size >> BYTE * 3);
  // reserved 1
  file_header[6] = 0;
  file_header[7] = 0;
  // reserved 2
  file_header[8] = 0;
  file_header[9] = 0;
  // pixel data offset
  file_header[10] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + (COLOR_SIZE + 1) * CHANNEL_AMOUNT;
  file_header[11] = 0;
  file_header[12] = 0;
  file_header[13] = 0;

  unsigned char info_header[INFORMATION_HEADER_SIZE];
  // header size
  info_header[0] = INFORMATION_HEADER_SIZE;
  info_header[1] = 0;
  info_header[2] = 0;
  info_header[3] = 0;
  // image width
  info_header[4] = image_width >> BYTE * 0;
  info_header[5] = image_width >> BYTE * 1;
  info_header[6] = image_width >> BYTE * 2;
  info_header[7] = image_width >> BYTE * 3;
  // image height
  info_header[8] = image_height >> BYTE * 0;
  info_header[9] = image_height >> BYTE * 1;
  info_header[10] = image_height >> BYTE * 2;
  info_header[11] = image_height >> BYTE * 3;
  // planes
  info_header[12] = 1;
  info_header[13] = 0;
  // bits per pixel
  info_header[14] = BYTE / 2;
  info_header[15] = 0;

  info_header[16] = 0;
  info_header[17] = 0;
  info_header[18] = 0;
  info_header[19] = 0;
  info_header[20] = 0;
  info_header[21] = 0;
  info_header[22] = 0;
  info_header[23] = 0;
  info_header[24] = 0;
  info_header[25] = 0;
  info_header[26] = 0;
  info_header[27] = 0;
  info_header[28] = 0;
  info_header[29] = 0;
  info_header[30] = 0;
  info_header[31] = 0;

  info_header[32] = COLOR_SIZE + 1;
  info_header[36] = COLOR_SIZE + 1;

  out.write(reinterpret_cast<const char*>(file_header), FILE_HEADER_SIZE);
  out.write(reinterpret_cast<const char*>(info_header), INFORMATION_HEADER_SIZE);

  for (auto color : COLORS) {
    out << color.b << color.g << color.r << static_cast<unsigned char>(0);
  }

  int count = 0;
  bool write = false;
  unsigned char last = 0;
  int padding_amount = 0;

  for (auto color: color_array) {
    if (write) {
      unsigned char out_colors = ((last << (BYTE / 2)) + color);
      out << out_colors;
      padding_amount = (padding_amount + 1) % MAX_PADDING;
      write = false;
    } else {
      write = true;
    }

    if (++count == image_width) {
      if (write) {
        unsigned char out_colors = (color << (BYTE / 2));
        out << out_colors;
        padding_amount = (padding_amount + 1) % MAX_PADDING;
      }

      for (int k = 0; k < (MAX_PADDING - padding_amount) % MAX_PADDING; k++) {
        out << static_cast<unsigned char>(0);
      }

      write = false;
      padding_amount = 0;
      count = 0;
    }
    last = color;
  }
}

Image::Image(uint16_t height, uint16_t width) {
  this->image_height = height;
  this->image_width = width;
  this->color_array.resize(width * height);
}

void Image::set_color(uint64_t color, int x, int y) {
  if (color > COLOR_SIZE) {
    color = COLOR_SIZE;
  }
  color_array[x + y * image_width] = color;
}