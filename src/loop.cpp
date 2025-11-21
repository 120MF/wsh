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
    auto pid = fork();
    switch (pid) {
    case -1:
      perror("fork");
      std::exit(EXIT_FAILURE);
    case 0: {
      auto &path = s.front();
      char *argv[s.size()];
      for (int i = 0; i < s.size() - 1; i++) {
        argv[i] = s[i + 1].data();
      }
      argv[s.size()] = nullptr;
      auto ret = execvp(path.c_str(), argv);
      if (ret == -1) {
        perror("execvp");
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
