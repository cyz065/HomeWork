#include <stdio.h>

double f(double x) {
	if (x == 1.8)
		return 3.12014;
	else if (x == 2.0)
		return 4.42569;
	else if (x == 2.2)
		return 6.04241;
	else if (x == 2.4)
		return 8.03014;
	else if (x == 2.6)
		return 10.46675;
	else
		return -1;
}
double Midpoint_Rule(double a, double b) {
	return (b - a) * f((a + b) / 2);
}
double Trapezoidal_Rule(double a, double b) {
	return (b - a) * (f(a) + f(b)) / 2;
}
double Simpsons_Rule(double a, double b) {
	return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
}
int main(void) {
	double a = 1.8;
	double b = 2.6;

	printf("(i) the Midpoint rule     (ii) the Trapezoidal rule     (iii) Simpson's rule\n");
	printf("       %.5f         ", Midpoint_Rule(a, b));
	printf("           %.5f         ", Trapezoidal_Rule(a, b));
	printf("              %.5f         ", Simpsons_Rule(a, b));
}