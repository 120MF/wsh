#include "parser.h"
#include <sstream>

std::vector<std::string> parse_line(std::string str) {
  std::vector<std::string> res;
  std::stringstream s(str);
  std::string word;
  while (s >> word) {
    res.push_back(word);
  }
  return std::move(res);
}
