#include <iostream>
#include "1.2function.h"

class SinFunction : public Functions{
public:
    double evaluate(double x) const override {
        return std::sin(x);
    }
};

class CustomFunction : public Functions{
public:
    double evaluate(double x) const override {
        return x * x * x - 3 * x;
    }
};

int main() {
    SinFunction sinFunc;
    CustomFunction customFunc;

    double start = -10.0;
    double end = 10.0;
    double step = 0.01;

    std::cout << "Sin(x): Найменший корінь другої похідної: "
              << sinFunc.findSmallestSecondDerivativeRoot(start, end, step)
              << std::endl;

    std::cout << "x^3 - 3x: Найменший корінь другої похідної: "
              << customFunc.findSmallestSecondDerivativeRoot(start, end, step)
              << std::endl;

    return 0;
}
