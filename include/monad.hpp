#pragma once

#include "functor.hpp"
#include <concepts>
#include <functional>

#ifndef MONAD_HPP
#define MONAD_HPP

template <class A, class MA, class MB>
concept no_functor_monad =
    requires(A obj_a, MA mon_a, std::function<MB(A)> func, MB mon_b) {
        { func >>= mon_a } -> std::convertible_to<MB>;
        { mon_a >> mon_b } -> std::convertible_to<MB>;
        { MA{obj_a} } -> std::convertible_to<MA>;
    };

template <class A, class MA, class MB>
concept Monad = Functor<std::function<MB(A const &)>, MA, MB> &&
                no_functor_monad<A, MA, MB>;

#endif
