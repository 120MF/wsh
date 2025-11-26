#include "loop.h"
#include "parser.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <print>
#include <string>
#include <string_view>

#include <fcntl.h>
#include <sys/types.h>
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
    // Parse user input
    auto res = parse_line(line);
    std::vector<pid_t> pids;
    for (auto &process : res.processes) {
      // Start new process
      auto pid = fork();
      switch (pid) {
      case -1:
        // On fork error
        perror("fork");
        std::exit(EXIT_FAILURE);
      case 0:
        // Child process
        child_process(res, process);
      default:

        auto [in, out] = process.pipe;
        if (in.has_value())
          close(in.value());
        if (out.has_value())
          close(out.value());
        pids.push_back(pid);
      }
    }
    for (auto pid : pids) {
      auto ret = waitpid(pid, nullptr, 0);
      if (ret == -1) {
        perror("waitpid");
        std::exit(EXIT_FAILURE);
      }
    }
  }
}

void child_process(ParseResult &res, ParseResult::Process &pro) {
  // Parse exe
  auto &path = pro.words.front();
  auto size = pro.words.size();
  std::vector<char *> argv(size + 1);
  for (size_t i = 0; i < size; ++i) {
    argv[i] = pro.words[i].data();
  }
  argv[size] = nullptr;
  // Parse pipe
  apply_pipe(res, pro);
  // Parse redirection
  apply_redirect(pro);

  // Execute
  auto ret = execvp(path.c_str(), argv.data());
  if (ret == -1) {
    perror("execvp");
    std::exit(EXIT_FAILURE);
  }

  std::exit(EXIT_SUCCESS);
}

void apply_redirect(ParseResult::Process &pro) {
  if (!pro.redirects.empty()) {
    std::string_view out_file{}, in_file{};
    int out_flag{};
    for (auto &arr : pro.redirects) {
      if (arr[0] == ">") {
        out_file = arr[1];
        out_flag = O_TRUNC;
      } else if (arr[0] == ">>") {
        out_file = arr[1];
        out_flag = O_APPEND;
      } else if (arr[0] == "<") {
        in_file = arr[1];
      }
    }
    std::vector<int> fds;
    if (!out_file.empty()) {
      int fd = open(out_file.data(), out_flag | O_CREAT | O_WRONLY, 0644);
      if (fd == -1) {
        perror("open");
        std::exit(EXIT_FAILURE);
      }
      int ret = dup2(fd, STDOUT_FILENO);
      if (ret == -1) {
        perror("dup2");
        std::exit(EXIT_FAILURE);
      }
      fds.push_back(fd);
    }
    if (!in_file.empty()) {
      int fd = open(in_file.data(), O_RDONLY);
      if (fd == -1) {
        perror("open");
        std::exit(EXIT_FAILURE);
      }
      int ret = dup2(fd, STDIN_FILENO);
      if (ret == -1) {
        perror("dup2");
        std::exit(EXIT_FAILURE);
      }
      fds.push_back(fd);
    }
    for (auto fd : fds) {
      close(fd);
    }
  }
}

void apply_pipe(ParseResult &res, ParseResult::Process &pro) {
  if (pro.pipe.first) {
    auto value = pro.pipe.first.value();
    dup2(value, STDIN_FILENO);
  }
  if (pro.pipe.second) {
    auto value = pro.pipe.second.value();
    dup2(value, STDOUT_FILENO);
  }
  for (auto &process : res.processes) {
    process.pipe.first.has_value() ? close(process.pipe.first.value()) : 0;
    process.pipe.second.has_value() ? close(process.pipe.second.value()) : 0;
  }
}
