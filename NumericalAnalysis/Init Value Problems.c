#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double t, double y) {
	return y - t * t + 1;
}

double fx(double t) {
	return t * t + 2 * t + 1 - 0.5 * exp(t);
}

double* Exact(double t0) {
	double* w = malloc(sizeof(double) * 6);
	double t = t0;
	for (int i = 0; t <= 0.5; i++) {
		w[i] = fx(t);
		t += 0.1;
	}
	return w;
}

double* Runge_Kutta_Order4(double t0, double h, double w0) {
	double k1, k2, k3, k4;
	double t = t0;
	double* w = malloc(sizeof(double) * 6);
	w[0] = w0;

	for (int i = 1; t < 0.5; i++) {
		k1 = h * f(t, w[i - 1]);
		k2 = h * f(t + h / 2, w[i - 1] + k1/ 2);
		k3 = h * f(t + h / 2, w[i - 1] + k2 / 2);
		k4 = h * f(t + h, w[i - 1] + k3);
		w[i] = w[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		t += h;
	}
	return w;
}

double* Modified_Euler_Method(double t0, double h, double w0) {
	double w[12];
	double* result = malloc(sizeof(double) * 6);
	w[0] = w0;
	double t = t0;
	int idx = 0;

	for (int i = 1; t < 0.5; i++) {
		w[i] = w[i - 1] + h / 2 * (f(t, w[i - 1]) + f(t + h, w[i - 1] + h * f(t, w[i - 1])));
		t += h;
	}

	for (int i = 0; i < 12; i += 2) {
		result[idx] = w[i];
		idx++;
	}
	return result;
}

double* Euler(double t0, double h, double w0) {
	double w[22];
	double t = t0;
	w[0] = w0;
	double* result = malloc(sizeof(double) * 6);
	double N = 0.5 / h + 1;
	int idx = 0;

	for (int i = 1; i <= (int)N; i++) {
		w[i] = w[i - 1] + h * f(t, w[i - 1]);
		t += h;
	}

	for (int i = 0; i <= 20; i += 4) {
		result[idx] = w[i];
		idx++;
	}
	return result;
}

int main(void) {
	double t0 = 0.0;
	double alpha = 0.5;

	double* original = Exact(t0);
	double * runge_kutta = Runge_Kutta_Order4(t0, 0.1, alpha);
	double * modified_euler = Modified_Euler_Method(t0, 0.05, alpha);
	double * euler = Euler(t0, 0.025, alpha);

	printf("ti\tExact\t\tEuler\t\tModifeid-Euler\tRunge-Kutta-Order4\n");
	printf("\t\t\th=0.025\t\th=0.05\t\th=0.1\n");
	for (int i = 0; i < 6; i++) {
		printf("%.1f\t%.7f\t%.7f\t%.7f\t%.7f\n", t0, original[i], euler[i], modified_euler[i], runge_kutta[i]);
		t0 += 0.1;
	}
}