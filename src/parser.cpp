#include "parser.h"
#include <array>
#include <sstream>
#include <string>

ParseResult parse_line(std::string str) {
  ParseResult res;
  ParseResult::Process process{};
  std::stringstream s(str);
  std::string word;
  // TODO: unwrap quotation mark ""
  while (s >> word) {
    if (word == "|") {
      res.processes.push_back(std::move(process));
      process = ParseResult::Process{};
    } else if (word == ">" || word == "<" || word == ">>") {
      std::array<std::string, 2> tmp;
      tmp[0] = word;
      s >> tmp[1];
      process.redirects.push_back(std::move(tmp));
    } else {
      process.words.push_back(word);
    }
  }
  if (!process.words.empty() || !process.redirects.empty()) {
    res.processes.push_back(process);
  }
  return std::move(res);
}
