#pragma once

#include "fmap.hpp"
#include "functor.hpp"
#include "monad.hpp"
#include <iostream>
#include <ostream>

#ifndef MAYBE_HPP
#define MAYBE_HPP

template <class T> struct Maybe {
    Maybe() = default;
    Maybe(T const &val) : value{val}, has_value{true} {};
    Maybe(Maybe const &rhs) : value{rhs.value}, has_value{rhs.has_value} {};
    Maybe(Maybe &&rhs) noexcept : value{rhs.value}, has_value{rhs.has_value} {};
    ~Maybe() = default;

    Maybe &operator=(T &&rhs) noexcept {
        this->value = rhs;
        this->has_value = true;
        return *this;
    }

    Maybe &operator=(Maybe const &rhs) {
        this->value = rhs.value;
        this->has_value = rhs.has_value;
        return *this;
    }

    Maybe &operator=(Maybe &&rhs) noexcept {
        this->value = rhs.value;
        this->has_value = rhs.has_value;
        return *this;
    }

    operator bool() const { return has_value; }
    operator T() const { return value; }

  private:
    T value;
    bool has_value = false;
};

template <class A, class B>
Maybe<B> fmap(std::function<B(A)> const func, Maybe<A> const &maybe) {
    return maybe ? Maybe<B>{func(maybe)} : Maybe<B>{};
}

template <class A, class B>
constexpr auto operator>>=(std::function<Maybe<B>(A)> const func,
                           Maybe<A> const &maybe) {
    return maybe ? func(maybe) : Maybe<B>{};
}

template <class A, class B>
Maybe<B> operator>>(Maybe<A> const &maybe_a, Maybe<B> const &maybe_b) {
    return maybe_a ? Maybe<B>(maybe_b) : Maybe<B>();
}

template <class A>
std::ostream &operator<<(std::ostream &stream, Maybe<A> const &maybe) {
    if (maybe) {
        stream << static_cast<A>(maybe);
    }

    return stream;
}

#endif
