#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double t, double y) {
	return 5 * exp(5 * t) * (y - t) * (y - t) + 1;
}

double fx(double t) {
	return t - exp(-5 * t);
}

double fy(double t, double y) {
	10 * exp(5 * t) * (y - t) + 1;
}

double* Runge_Kutta_Order4(int N, double h, double w0) {
	double k1, k2, k3, k4;
	double t = 0.0;
	double* w = malloc(sizeof(double) * (N + 1));
	w[0] = w0;

	for (int i = 1; i < N + 1; i++) {
		k1 = h * f(t, w[i - 1]);
		k2 = h * f(t + h / 2, w[i - 1] + k1 / 2);
		k3 = h * f(t + h / 2, w[i - 1] + k2 / 2);
		k4 = h * f(t + h, w[i - 1] + k3);
		w[i] = w[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		t += h;
	}

	for (int i = 0; i < N + 1; i++) {
		if (w[i] < 10)
			printf("%.7f\n", w[i]);
		else
			printf("%.5e\n", w[i]);
	}
}

double* Trapezoidal_Method(int N, double TOL, double h, double w0) {
	double* result = malloc(sizeof(double) * N);
	double t0 = 0.0;
	double t = t0;
	double alpha = w0;
	double w = alpha;
	result[0] = w0;
	double w1 = w - (w - alpha - (h / 2) * (f(t0, alpha) + f(t + h, w)) / (1 - (h / 2) * fy(t + h, w)));

	while (fabs(w1 - w0) > TOL) {

	}
}
int main(void) {
	Runge_Kutta_Order4(4, 0.25, -1);
	printf("\n");
	Runge_Kutta_Order4(5, 0.20, -1);
	printf("\n");

}