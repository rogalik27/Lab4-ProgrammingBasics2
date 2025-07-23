#include <iostream>
#include <cmath>
#include "1.3derivatives.h"

double myFunction(double x) {
    return x * x * std::sin(x);
}

int main() {
    std::cout << "Testing myFunction:\n";

    double xRoot = findSmallestSecondDerivativeRoot(myFunction, 1, 5);
    std::cout << "Approximate root of second derivative: x = " << xRoot << "\n";
    std::cout << "Second derivative at x = " << xRoot << ": " << secondDerivative(myFunction, xRoot) << "\n";

    return 0;
}

