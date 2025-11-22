#include "parser.h"
#include <array>
#include <sstream>
#include <string>

ParseResult parse_line(std::string str) {
  ParseResult res;
  auto &words = res.words;
  std::stringstream s(str);
  std::string word;
  // TODO: unwrap quotation mark ""
  while (s >> word) {
    if (word == ">" || word == "<" || word == ">>") {
      std::array<std::string, 2> tmp;
      tmp[0] = word;
      s >> tmp[1];
      res.redirects.push_back(std::move(tmp));
    } else {
      words.push_back(word);
    }
  }
  return std::move(res);
}
