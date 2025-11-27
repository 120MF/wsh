#include <csignal>
#include <print>
#include <signal.h>

#include "loop.hpp"

int main() {
  struct sigaction act{};
  act.sa_handler = SIG_IGN;
  sigaction(SIGINT, &act, nullptr);
  sigaction(SIGTSTP, &act, nullptr);
  std::print("wsh");
  loop();
  return 0;
}
