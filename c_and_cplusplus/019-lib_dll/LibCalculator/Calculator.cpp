#include "Calculator.h"

namespace z {
    Calculator::Calculator(){}
    Calculator::~Calculator(){}

    int Calculator::add(int a, int b) {
        return a + b + m_ + test(3) + 10000;
    }

    int Calculator::m_ = 2;

    int test(int i) {
        return i;
    }
}