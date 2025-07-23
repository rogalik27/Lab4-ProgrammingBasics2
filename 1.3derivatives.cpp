#include "1.3derivatives.h"
#include <cmath>

double firstDerivative(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double secondDerivative(double (*f)(double), double x, double h) {
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

double findSmallestSecondDerivativeRoot(double (*f)(double), double a, double b, double step, double eps) {
    double minX = a;
    double minVal = std::abs(secondDerivative(f, a));

    for (double x = a; x <= b; x += step) {
        double val = std::abs(secondDerivative(f, x));
        if (val < minVal) {
            minVal = val;
            minX = x;
        }
    }

    return minX;
}
