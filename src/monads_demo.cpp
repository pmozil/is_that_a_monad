#include "maybe.hpp"

Maybe<double> multiply_by_ten(int const &val) {
    constexpr float ten = 10.0F;
    return {ten * val};
}

Maybe<double> add_five(double const &val) {
    constexpr float five = 5.0F;
    return {five + val};
}

const std::function<Maybe<double>(int)> mul_ten =
    std::function{multiply_by_ten};
const std::function<Maybe<double>(double)> addFive =
    std::function{multiply_by_ten};

template <class A>
    requires Monad<A, Maybe<A>, Maybe<A>>
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
}
