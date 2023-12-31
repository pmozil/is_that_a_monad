#pragma once

#include "fmap.hpp"
#include <concepts>

#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

template <class A_B, class FA, class FB>
concept Functor = requires(A_B fmap_fn, FA &lhs) {
    { fmap<A_B, FA, FB>{}(fmap_fn, lhs) } -> std::convertible_to<FB>;
};

#endif
