#pragma once
#include <cmath>
#include <limits>

typedef double (*FuncPointer)(double);

class Functions {
public:
    virtual double evaluate(double x) const = 0;

    double firstDerivative(double x, double dx = 1e-7);

    double secondDerivative(double x, double dx = 1e-7);

    double findSmallestSecondDerivativeRoot(double start, double end, double step, double epsilon = 1e-6);
};
