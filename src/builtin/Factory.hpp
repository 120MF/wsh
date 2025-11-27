#ifndef INCLUDE_BUILTIN_FACTORY_HPP_
#define INCLUDE_BUILTIN_FACTORY_HPP_

#include "Foreground.hpp"
#include <frozen/string.h>
#include <frozen/unordered_map.h>

using FuncPtr = void (*)(ParseResult &);

using Registry = std::tuple<Foreground>;

template <typename Tuple> struct MapBuilder;

template <typename... Ts> struct MapBuilder<std::tuple<Ts...>> {
  static constexpr auto map = []() {
    std::array<std::pair<frozen::string, FuncPtr>, sizeof...(Ts)> entries = {
        {{Ts::name, &Ts::execute}...}};
    return frozen::make_unordered_map(entries);
  }();
};

static constexpr auto &builtin_map = MapBuilder<Registry>::map;

#endif // INCLUDE_BUILTIN_FACTORY_HPP_
