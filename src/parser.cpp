#include "parser.h"

std::vector<std::string> parse_line(std::string_view str) {
  std::vector<std::string> res;
  auto pos_next = str.find(' ');
  for (auto pos_next = str.find(' '); pos_next != str.npos;
       str = str.substr(pos_next + 1), pos_next = str.find(' ')) {
    res.push_back(std::string(str.substr(0, pos_next)));
  }
  if (!str.empty()) {
    res.push_back(std::string(str));
  }
  return res;
}
