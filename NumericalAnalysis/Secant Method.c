#include <stdio.h>
#include <math.h>

double f(double x) {
	return x * x * x + 4 * x * x - 10;
}

void compute() {
	double p0 = 1;
	double p1 = 2;
	double TOL = 0.0005;
	int n = 2;
	
	printf("n         pn                f(pn)\n");

	while (fabs(p1 - p0) > TOL) {
		double pn = p1 - f(p1) * (p1 - p0) / (f(p1) - f(p0));
		printf("%d     %.10f      ", n, pn);
		if (f(pn) > 0)
			printf(" ");
		printf("%.10f \n", f(pn));
		p0 = p1;
		p1 = pn;
		n++;
	}
}
int main(void) {
	compute();
}