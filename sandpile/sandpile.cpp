#include "sandpile.h"

/* Эта функция занимается только песком */

namespace sand_space {
void play_iter(Sand &s) {
  VecCords big_sands;

  // найти клетки с >=4
  detect_big(s, big_sands);

  // проверить, есть ли такие клетки на границах. если да, то на каких
  Border bor = detect_border(s, big_sands);

  // увеличить те границы, где такие клетки нашлись
  resize_border(s, bor);

  // узнать их новые адреса в поле
  VecCords new_big_sands;
  detect_big(s, new_big_sands);

  // развалить эти большие песчинки
  ruin_all(s, new_big_sands);
}

void detect_big(Sand &s, VecCords &big_sands) {
  for (auto str = 0; str != s.str; ++str) {
    for (auto col = 0; col != s.col; ++col) {
      if (s.net[str][col] >= 4) {
        big_sands.push_back(std::make_pair(str, col));
      }
    }
  }
}

Border detect_border(Sand &s, VecCords &big_sands) {
  Border ans = {false, false, false, false};

  for (const auto &elem : big_sands) {
    if (elem.first == 0) {
      ans.up = true;
    }
    if (elem.first == s.str - 1) {
      ans.down = true;
    }
    if (elem.second == 0) {
      ans.left = true;
    }
    if (elem.second == s.col - 1) {
      ans.right = true;
    }
  }

  return ans;
}

void resize_down(Sand &s) {
  assert(s.str < IM_MAX);
  ++s.str;

  Str help(s.col, 0);
  s.net.insert(s.net.end(), help);
}

void resize_up(Sand &s) {
  assert(s.str < IM_MAX);
  ++s.str;

  Str help(s.col, 0);
  s.net.insert(s.net.begin(), help);
}

void resize_right(Sand &s) {
  assert(s.col < IM_MAX);
  ++s.col;

  for (auto it = 0; it != s.str; ++it) {
    s.net[it].insert(s.net[it].end(), 0);
  }
}

void resize_left(Sand &s) {
  assert(s.col < IM_MAX);
  ++s.col;

  for (auto it = 0; it != s.str; ++it) {
    s.net[it].insert(s.net[it].begin(), 0);
  }
}

void resize_border(Sand &s, Border bor) {
  if (bor.up) {
    resize_up(s);
  }
  if (bor.down) {
    resize_down(s);
  }
  if (bor.right) {
    resize_right(s);
  }
  if (bor.left) {
    resize_left(s);
  }
}

void ruin_sandpile(Sand &s, ImSize i, ImSize j) {
  s.net[i][j] -= 4;
  s.net[i - 1][j] += 1;
  s.net[i][j - 1] += 1;
  s.net[i + 1][j] += 1;
  s.net[i][j + 1] += 1;
}

void ruin_all(Sand &s, VecCords &new_big_sands) {
  for (const auto &elem : new_big_sands) {
    ruin_sandpile(s, elem.first, elem.second);
  }
}
} // namespace