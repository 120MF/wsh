#ifndef INCLUDE_BUILTIN_FOREGROUND_HPP_
#define INCLUDE_BUILTIN_FOREGROUND_HPP_

#include "parser.hpp"
#include <frozen/string.h>
#include <print>
struct Foreground {
  static void execute(ParseResult &res) { std::println("Howdy!"); };
  static constexpr frozen::string name = "fg";
};

#endif // INCLUDE_BUILTIN_FOREGROUND_HPP_
