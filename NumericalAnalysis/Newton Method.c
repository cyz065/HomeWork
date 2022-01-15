#include <stdio.h>
#include <math.h>
#define SIZE 1000000000

double f(double x) {
	return x - pow(3.0, -x);
}

double derivative_f(double x) {
	return 1.0 + pow(3.0, -x) * log(3.0);
}

int main(void) {
	double TOL = 0.00000001;
	int n = 0;
	double p0 = 0.5;
	double p = p0 - f(p0) / derivative_f(p0);
	printf("n         pn        |pn - p(n-1)|\n");
	printf("%d    %.9f\n", n, p0);
	while (fabs(p - p0) > TOL) {
		double a = round(p0 * SIZE) / SIZE;
		double b = round(p * SIZE) / SIZE;
		double difference = fabs(b - a);
		p0 = p;
		p = p0 - f(p0) / derivative_f(p0);
		n++;
		printf("%d    %.9f     %.9f\n", n, p0, difference);
	}

}