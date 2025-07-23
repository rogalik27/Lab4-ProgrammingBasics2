#include "1.2function.h"

double Functions::firstDerivative(double x, double dx){
    return (evaluate(x + dx) - evaluate(x)) / dx;
}

double Functions::secondDerivative(double x, double dx){
    return (firstDerivative(x + dx) - firstDerivative(x)) / dx;
}

double Functions::findSmallestSecondDerivativeRoot(double start, double end, double step, double epsilon){
    double minRoot = std::numeric_limits<double>::quiet_NaN();

    for (double x = start; x <= end; x += step) {
        double y1 = secondDerivative(x);
        double y2 = secondDerivative(x + step);

        if (y1 * y2 <= 0 && std::abs(y1 - y2) > epsilon){
            double rootCandidate = x;

            if (std::isnan(minRoot) || rootCandidate < minRoot)
                minRoot = rootCandidate;
        }
    }

    return minRoot;
}
