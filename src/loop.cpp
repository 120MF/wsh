#include "loop.h"
#include "parser.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <print>
#include <string>
#include <sys/wait.h>

#include <unistd.h>

void loop() {
  std::string line;
  while (true) {
    std::print("> ");
    if (!std::getline(std::cin, line)) {
      break;
    }
    int wstatus{};
    auto s = parse_line(line);
    for (auto &str : s) {
      std::println("{}", str);
    }
    auto pid = fork();
    switch (pid) {
    case -1:
      perror("fork");
      std::exit(EXIT_FAILURE);
    case 0: {
      auto &path = s.front();
      std::vector<char *> argv(s.size() + 1);
      for (size_t i = 0; i < s.size(); ++i) {
        argv[i] = s[i].data();
      }
      argv[s.size()] = nullptr;
      auto ret = execvp(path.c_str(), argv.data());
      if (ret == -1) {
        perror("execvp");
        std::exit(EXIT_FAILURE);
      }
      std::exit(EXIT_SUCCESS);
    }
    default: {
      auto ret = waitpid(pid, &wstatus, 0);
      if (ret == -1) {
        perror("waitpid");
        std::exit(EXIT_FAILURE);
      }
    }
    }
  }
}
