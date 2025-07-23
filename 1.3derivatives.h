#ifndef DERIVATIVES_H
#define DERIVATIVES_H

double firstDerivative(double (*f)(double), double x, double h = 1e-5);
double secondDerivative(double (*f)(double), double x, double h = 1e-5);
double findSmallestSecondDerivativeRoot(double (*f)(double), double a, double b, double step = 1e-2, double eps = 1e-5);

#endif
