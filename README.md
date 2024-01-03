# Monads

Concepts are a fairly recent feature,
so I made a maybe monad in CPP to show just how cool they are.


# Building

You do need a cpp compiler that supports c++20 (gcc, clang and MSVC all currently do that)
and cmake for this


```bash
cmake -B build
cd build && make
./monads_demo
```


# The Monad concept and Maybe code.

Just look at how cool this looks!
```cpp
#include <concepts>
#include <functional>

template <class A_B, class FA, class FB> FB fmap(A_B, FA const &);

template <class A_B, class FA, class FB>
concept Functor = requires(A_B fmap_fn, FA &lhs) {
    { fmap<A_B, FA, FB>(fmap_fn, lhs) } -> std::convertible_to<FB>;
    // This is hiow you declate a requirement for the concept:
    // The value in the brackets is what the opeartion would
    // look like, and the value on the right is the type of the result
};

template <class A, class MA, class MB>
concept no_functor_monad =
    requires(A obj_a, MA mon_a, std::function<MB(A)> func, MB mon_b) {
        { func >>= mon_a } -> std::convertible_to<MB>;
        { mon_a >> mon_b } -> std::convertible_to<MB>;
        { MA{obj_a} } -> std::convertible_to<MA>;
        
        // You can declare multiple requirements for the concept
    };

template <class A, class MA, class MB>
concept Monad = Functor<std::function<MB(A const &)>, MA, MB> &&
                no_functor_monad<A, MA, MB>;
// You could compose concepts like this.
```

And here's the Maybe
```cpp
#include "fmap.hpp"
#include "functor.hpp"
#include "monad.hpp"
#include <iostream>
#include <ostream>

template <class T> struct Maybe {

    // ... 
    // Constructors and assignment operators...
    // ...

    T value;
    bool has_value = false;
};

// The implemenation of the >>= operator required for the monad
template <class A, class B>
constexpr auto operator>>=(std::function<Maybe<B>(A)> const func,
                           Maybe<A> const &maybe) {
    return maybe ? func(maybe) : Maybe<B>{};
}

// The implemenation of the >> operator required for the monad
template <class A, class B>
Maybe<B> operator>>(Maybe<A> const &maybe_a, Maybe<B> const &maybe_b) {
    return maybe_a ? Maybe<B>(maybe_b) : Maybe<B>();
}

// Peiople usually do the >>= throught fmap,
// But this works too
template <class A, class B>
Maybe<B> fmap(std::function<B(A)> const func, Maybe<A> const &maybe) {
    return maybe ? Maybe<B>{func(maybe)} : Maybe<B>{};
}
```

And now you could do stuff like this!
```cpp
#include "maybe.hpp"

template <class T> Maybe<double> multiply_by_ten(T &&val) {
    constexpr float ten = 10.0F;
    return {ten * val};
}

template <class T> Maybe<double> add_five(T &&val) {
    constexpr float five = 5.0F;
    return {five + val};
}

template <class T> Maybe<double> add_five_for_fmap(T &&val) {
    constexpr float five = 5.0F;
    return {five + val};
}

// You do have to cast functions like this, since
// std::function<B(A)> != std::function<B(A const &)>
// so I a currently searching for some better fix.
const std::function<Maybe<double>(int)> mul_ten =
    std::function{multiply_by_ten<int>};
const std::function<Maybe<double>(double)> addFive =
    std::function{add_five<int>};
const std::function<Maybe<double>(double)> addFive_fmap =
    std::function{add_five_for_fmap<int>};

// This only prints monads)
template <class A, class B = A>
    requires Monad<A, Maybe<B>, Maybe<A>>
void print_maybe(Maybe<A> &mon) {
    std::cout << mon << std::endl;
}

int main() {
    Maybe<int> m1 = 12;
    Maybe<int> m2;
    Maybe<double> a = mul_ten >>= m1;
    Maybe<double> b = addFive >>= mul_ten >>= m1;

    std::cout << "A = " << a << std::endl;
    std::cout << "B = " << b << std::endl;
    std::cout << "M1 = " << m1 << std::endl;

    std::cout << "M2 = ";
    print_maybe(m2);

    m2 = 115;

    std::cout << "M2 = ";
    print_maybe(m2);

    a = mul_ten >>= m2;

    std::cout << "A = ";
    print_maybe(a);

    auto res = fmap(addFive_fmap, a);
    std::cout << "RES = " << res << std::endl;
}
```
