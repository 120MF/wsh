#include "loop.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <print>
#include <string>
#include <string_view>

#include <fcntl.h>
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
      child_process(res.processes);
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

void child_process(ParseResult::Process &pro) {
  // Parse exe
  auto &path = pro.words.front();
  auto size = pro.words.size();
  std::vector<char *> argv(size + 1);
  for (size_t i = 0; i < size; ++i) {
    argv[i] = pro.words[i].data();
  }
  argv[size] = nullptr;
  // Parse redirection
  if (!pro.redirects.empty()) {
    std::string_view out_file{}, in_file{};
    int out_flag{};
    for (auto &arr : pro.redirects) {
      if (arr[0] == ">") {
        out_file = arr[1];
        out_flag = O_CREAT;
      } else if (arr[0] == ">>") {
        out_file = arr[1];
        out_flag = O_APPEND;
      } else if (arr[0] == "<") {
        in_file = arr[1];
      }
    }
    if (!out_file.empty()) {
      int fd = open(out_file.data(), out_flag | O_RDWR);
      if (fd == -1) {
        perror("open");
        std::exit(EXIT_FAILURE);
      }
      dup2(fd, STDOUT_FILENO);
    }
    if (!in_file.empty()) {
      int fd = open(in_file.data(), O_RDONLY);
      if (fd == -1) {
        perror("open");
        std::exit(EXIT_FAILURE);
      }
      dup2(fd, STDIN_FILENO);
    }
  }

  // Execute
  auto ret = execvp(path.c_str(), argv.data());
  if (ret == -1) {
    perror("execvp");
    std::exit(EXIT_FAILURE);
  }
  std::exit(EXIT_SUCCESS);
}
