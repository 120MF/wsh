#include <csignal>
#include <print>
#include <signal.h>

void main_handler(int signo, siginfo_t *info, void *context) {
  do {
  } while (0);
}

#include "loop.h"
int main() {
  struct sigaction act{};
  act.sa_handler = SIG_IGN;
  sigaction(SIGINT, &act, nullptr);
  sigaction(SIGTSTP, &act, nullptr);
  std::print("wsh");
  loop();
  return 0;
}
