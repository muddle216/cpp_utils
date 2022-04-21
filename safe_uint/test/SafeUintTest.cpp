//
// Created by LC on 2022/4/19.
//

#include "SafeUInt.h"

class Logger {
public:
    static void log(const char *func, uint64_t a, uint64_t b, uint64_t result, uint64_t operatorResult) {
        if (result != operatorResult) {
            std::cout << func << "(" << a << ", " << b << ") = " << result << "|overflow|" << operatorResult << std::endl;
        }
    }
};

class Creator {
public:
    template<class A, class B>
    static auto create32(A a, B b) -> decltype(SafeUIntHelper::create32<A, B, INT_MAX, 0U, true, Logger>(a, b)) {
        return SafeUIntHelper::create32<A, B, INT_MAX, 0U, true, Logger>(a, b);
    }

    template<class A, class B>
    static auto create64(A a, B b) -> decltype(SafeUIntHelper::create64<A, B, LLONG_MAX, 0U, true, Logger>(a, b)) {
        return SafeUIntHelper::create64<A, B, LLONG_MAX, 0U, true, Logger>(a, b);
    }
};

template<class A, class B>
bool comp(A a, B b) {
    return a == b;
};

int main() {
    comp(INT_MAX - 1U + 2U, Creator::create32(INT_MAX - 1U, 2U).add());
    comp(1U - 2U, Creator::create32(1U, 2U).sub());
    comp(INT_MAX - 1U + 2, Creator::create32(INT_MAX - 1U, 2).addOrSub());
    comp(1U + -2, Creator::create32(1U, -2).addOrSub());

//    Creator::create32(1, 2);

    return 0;
}