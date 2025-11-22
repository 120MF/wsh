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
    // Get user input
    if (!std::getline(std::cin, line)) {
      break;
    }
    int wstatus{};
    // Parse user input
    auto res = parse_line(line);
    // Start new process
    auto pid = fork();
    switch (pid) {
    case -1:
      // On fork error
      perror("fork");
      std::exit(EXIT_FAILURE);
    case 0: {
      // Child process
      auto &path = res.words.front();
      auto size = res.words.size();
      std::vector<char *> argv(size + 1);
      for (size_t i = 0; i < size; ++i) {
        argv[i] = res.words[i].data();
      }
      argv[size] = nullptr;
      // Execute
      auto ret = execvp(path.c_str(), argv.data());
      if (ret == -1) {
        perror("execvp");
        std::exit(EXIT_FAILURE);
      }
      std::exit(EXIT_SUCCESS);
    }
    default: {
      // Parent process
      // Block wait child
      auto ret = waitpid(pid, &wstatus, 0);
      if (ret == -1) {
        perror("waitpid");
        std::exit(EXIT_FAILURE);
      }
    }
    }
  }
}
