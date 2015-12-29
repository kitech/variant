// Copyright Michael Park 2015
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef EXPERIMENTAL_VARIANT_REL_HPP
#define EXPERIMENTAL_VARIANT_REL_HPP

#include <cstddef>
#include <cstdlib>

#include <experimental/detail/variant/index_visitor.hpp>
#include <experimental/variant/unsafe/visit.hpp>

namespace std {
namespace experimental {

namespace detail {
namespace variant {

struct equal {
  template <typename T>
  constexpr bool operator()(const T &lhs, const T &rhs) const {
    return lhs == rhs;
  }

  template <typename T, typename U>
  constexpr bool operator()(const T &, const U &) const {
    assert(false);
    return false;
  }
};  // equal

struct less {
  template <typename T>
  constexpr bool operator()(const T &lhs, const T &rhs) const {
    return lhs < rhs;
  }

  template <typename T, typename U>
  constexpr bool operator()(const T &, const U &) const {
    assert(false);
    return false;
  }
};  // less

}  // namespace variant
}  // namespace detail

//- 20.N.8 relational operators:

template <typename... Ts>
constexpr bool operator==(const variant<Ts...> &lhs,
                          const variant<Ts...> &rhs) {
  using namespace detail::variant;
  return lhs.index() == rhs.index() && unsafe::visit(equal{}, lhs, rhs);
}

template <typename... Ts>
constexpr bool operator!=(const variant<Ts...> &lhs,
                          const variant<Ts...> &rhs) {
  return !(lhs == rhs);
}

template <typename... Ts>
constexpr bool operator<(const variant<Ts...> &lhs,
                         const variant<Ts...> &rhs) {
  using namespace detail::variant;
  return lhs.index() < rhs.index() ||
         (lhs.index() == rhs.index() && unsafe::visit(less{}, lhs, rhs));
}

template <typename... Ts>
constexpr bool operator>(const variant<Ts...> &lhs,
                         const variant<Ts...> &rhs) {
  return rhs < lhs;
}

template <typename... Ts>
constexpr bool operator<=(const variant<Ts...> &lhs,
                          const variant<Ts...> &rhs) {
  return !(lhs > rhs);
}

template <typename... Ts>
constexpr bool operator>=(const variant<Ts...> &lhs,
                          const variant<Ts...> &rhs) {
  return !(lhs < rhs);
}

}  // namespace experimental
}  // namespace std

#endif  // EXPERIMENTAL_VARIANT_REL_HPP
