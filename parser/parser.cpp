#include "parser.h"
#include <iostream>

params parse(int argc, char** argv) {
  params p;

  std::vector<std::string> args;

  for (int i = 1; i < argc; ++i) {
    std::string s = argv[i];
    args.push_back(s);
  }

  for (int i = 1; i < args.size(); ++i) {
    if (args[i][0] != '-') {
      if (args[i - 1] == "-l") {
        p.l = std::stoi(args[i]);
      } else if (args[i - 1] == "-w") {
        p.w = std::stoi(args[i]);
      } else if (args[i - 1] == "-i") {
        p.i = args[i];
      } else if (args[i - 1] == "-o") {
        p.o = args[i];
      } else if (args[i - 1] == "-m") {
        p.m = std::stoi(args[i]);
      } else if (args[i - 1] == "-f") {
        p.f = std::stoi(args[i]);
      }
    }
  }

  /*p.l = 1;
  p.w = 1;
  p.i = R"(C:\Users\User\CLionProjects\new_labwork-3-Aksinya-Bykova\pictures\test_inp.txt)";
  p.o = R"(..\pictures)";
  p.m = 10000;
  p.f = 0;*/

  return p;
}
