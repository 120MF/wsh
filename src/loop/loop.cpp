#include "loop.h"
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
    std::println("{}", line);
  }
}
