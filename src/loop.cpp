#include "loop.h"
#include "parser.h"
#include <iostream>
#include <print>
#include <string>

void loop() {
  std::string line;
  while (true) {
    std::print("> ");
    if (!std::getline(std::cin, line)) {
      break;
    }
    std::print("| ");
    for (auto s : parse_line(line)) {
      std::print("{} | ", s);
    }
    std::println();
  }
}
