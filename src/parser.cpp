#include "parser.h"
#include <array>
#include <cstdio>
#include <sstream>
#include <string>
#include <unistd.h>

ParseResult parse_line(std::string str) {
  ParseResult res;
  ParseResult::Process process{};
  std::stringstream s(str);
  std::string word;
  // TODO: unwrap quotation mark ""
  while (s >> word) {
    if (word == "|") {
      int pipefd[2];
      if (pipe(pipefd) == -1) {
        perror("pipe");
        return {};
      }

      process.pipe.second = pipefd[1];
      res.processes.push_back(std::move(process));
      process = ParseResult::Process{};
      process.pipe.first = pipefd[0];
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
