#include <iostream>
#include <cassert>
#include <cinttypes>
#include <utility>
#include <vector>

namespace sand_space {
typedef uint16_t ImSize;
typedef std::vector<std::pair<ImSize, ImSize>> VecCords;
const uint16_t IM_MAX = UINT16_MAX;

typedef uint64_t SandSize;
typedef std::vector<SandSize> Str;

class Sand {
 public:
  std::vector<Str> net;
  ImSize str;
  ImSize col;
  // TODO test constructor
  //Sand(std::vector<Str> net, ImSize str, ImSize col) : net(std::move(net)), str(str), col(col){}
};

struct Border {
  bool up;
  bool down;
  bool left;
  bool right;
};

void play_iter(Sand &s);

void detect_big(Sand &s, VecCords &big_sands);

Border detect_border(Sand &s, VecCords &big_sands);

void resize_down(Sand &s);
void resize_up(Sand &s);
void resize_right(Sand &s);
void resize_left(Sand &s);
void resize_border(Sand &s, Border bor);

void ruin_sandpile(Sand &s, ImSize i, ImSize j);
void ruin_all(Sand &s, VecCords &new_big_sands);
} // namespace
