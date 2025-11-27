#include "parser.hpp"

#include <frozen/string.h>
#include <frozen/unordered_map.h>

using Func = void (*)(ParseResult &);

static constexpr frozen::unordered_map<frozen::string, Func, 2> olaf = {
    {"fg", nullptr},
    {"bg", nullptr},
};

// static constexpr auto builtins = []() {
//   constexpr frozen::string str("");
//   std::pair<frozen::string, std::function<void()>> pair{str, {}};
//   std::array<std::pair<frozen::string, std::function<void()>>, 1>
//   pairs{{pair}}; return frozen::make_unordered_map(pairs);
// }();
