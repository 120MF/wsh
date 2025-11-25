#ifndef INCLUDE_SRC_PARSER_H_
#define INCLUDE_SRC_PARSER_H_

#include <array>
#include <string>
#include <vector>

using Words = std::vector<std::string>;
using Redirects = std::vector<std::array<std::string, 2>>;

struct ParseResult {
  struct Process {
    Words words;
    Redirects redirects;
  };
  std::vector<Process> processes;
};

ParseResult parse_line(std::string str);

#endif // INCLUDE_SRC_PARSER_H_
