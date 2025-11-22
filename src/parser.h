#ifndef INCLUDE_SRC_PARSER_H_
#define INCLUDE_SRC_PARSER_H_

#include <array>
#include <string>
#include <vector>

using Redirects = std::vector<std::array<std::string, 2>>;

struct ParseResult {
  std::vector<std::string> words;
  Redirects redirects;
};

ParseResult parse_line(std::string str);

#endif // INCLUDE_SRC_PARSER_H_
