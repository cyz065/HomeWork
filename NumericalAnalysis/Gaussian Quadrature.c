#include <stdio.h>
#include <math.h>
double f1(double x) {
	return x * x * log(x);
}
double f2(double x) {
	return x * x * exp(-x);
}
double gaussian_quadrature_f1(double a, double b, int n) {
	double* roots = 0; double* coefficients = 0;
	if (n == 2) {
		double roots_2[2] = { -0.5773502692, 0.5773502692 };
		double coefficients_2[2] = { 1.0000000000, 1.0000000000 };
		roots = roots_2; coefficients = coefficients_2;
	}
	else if (n == 3) {
		double roots_3[3] = { -0.7745966692, 0.0000000000, 0.7745966692 };
		double coefficients_3[3] = { 0.5555555556, 0.8888888889, 0.5555555556 };
		roots = roots_3; coefficients = coefficients_3;
	}
	else if (n == 4) {
		double roots_4[4] = { -0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116 };
		double coefficients_4[4] = { 0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451 };
		roots = roots_4; coefficients = coefficients_4;
	}
	else if (n == 5) {
		double roots_5[5] = { -0.9061798459, -0.5384693101, 0.0000000000, 0.5384693101, 0.9061798459 };
		double coefficients_5[5] = { 0.2369268850, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268850 };
		roots = roots_5; coefficients = coefficients_5;
	}
	double result = 0;
	for (int i = 0; i < n; i++) {
		result += coefficients[i] *f1(((b - a) * roots[i] + b + a) / 2);
	}
	return result * (b - a) / 2;
}
double gaussian_quadrature_f2(double a, double b, int n) {
	double* roots = 0; double* coefficients = 0;
	if (n == 2) {
		double roots_2[2] = { -0.5773502692, 0.5773502692 };
		double coefficients_2[2] = { 1.0000000000, 1.0000000000 };
		roots = roots_2; coefficients = coefficients_2;
	}
	else if (n == 3) {
		double roots_3[3] = { -0.7745966692, 0.0000000000, 0.7745966692 };
		double coefficients_3[3] = { 0.5555555556, 0.8888888889, 0.5555555556 };
		roots = roots_3; coefficients = coefficients_3;
	}
	else if (n == 4) {
		double roots_4[4] = { -0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116 };
		double coefficients_4[4] = { 0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451 };
		roots = roots_4; coefficients = coefficients_4;
	}
	else if (n == 5) {
		double roots_5[5] = { -0.9061798459, -0.5384693101, 0.0000000000, 0.5384693101, 0.9061798459 };
		double coefficients_5[5] = { 0.2369268850, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268850 };
		roots = roots_5; coefficients = coefficients_5;
	}

	double result = 0;
	for (int i = 0; i < n; i++) {
		result += coefficients[i] * f2(((b - a) * roots[i] + b+ a) / 2);
	}
	return result * (b - a) / 2;
}
int main(void) {
	double result1 = 0; double result2 = 0; int n = 2;
	printf("           a            b\n");
	for (int i = 2; i < 6; i++) {
		result1 = gaussian_quadrature_f1(1, 1.5, i);
		result2 = gaussian_quadrature_f2(0, 1, i);
		printf("n = %d %.7f     %.7f\n", i, result1, result2);
	}
}