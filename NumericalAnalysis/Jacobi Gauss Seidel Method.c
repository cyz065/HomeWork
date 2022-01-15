#include <stdio.h>
#include <math.h>

void Jacobi_Method(int n, double TOL) {
	double d[4][5] = {
		{4, 1, -1, 1, -2},
		{1, 4, -1, -1, -1},
		{-1, -1, 5, 1, 0},
		{1, -1, 1, 3, 1}
	};
	double e[5][6] = {
		{4, 1, 1, 0, 1, 6},
		{-1, -3, 1, 1, 0, 6},
		{2, 1, 5, -1, -1, 6},
		{-1, -1, -1, 4, 0, 6},
		{0, 2, -1, 1, 4, 6}
	};
	double f[6][7] = {
		{4, -1, 0, -1, 0, 0, 0},
		{-1, 4, -1, 0, -1, 0, 5},
		{0, -1, 4, 0, 0, -1, 0},
		{-1, 0, 0, 4, -1, 0, 6},
		{0, -1, 0, -1, 4, -1, -2},
		{0, 0, -1, 0, -1, 4, 6}
	};
	int i, j;
	double T[7][7], b[7];
	double tmp;
	double a0 = 0, b0 = 0, c0 = 0, 
		d0 = 0, e0 = 0, f0 = 0;
	double a1 = 0, b1 = 0, c1 = 0, 
		d1 = 0, e1 = 0, f1 = 0;
	int cnt = 1;
	double error;

	if (n == 4) {
		for (i = 0; i < n; i++) {
			b[i] = d[i][n];
		}
		for (i = 0; i < n; i++) {
			tmp = d[i][i];
			for (j = 0; j < n; j++) {
				if (i == j) {
					T[i][j] = 0;
					continue;
				}
				else {
					T[i][j] = d[i][j] / tmp * (-1);
				}
			}
			T[i][j] = b[i] / tmp;
		}

		while (1) {
			a1 = T[0][1] * b0 + T[0][2] * c0 + T[0][3] * d0 + T[0][4];
			b1 = T[1][0] * a0 + T[1][2] * c0 + T[1][3] * d0 + T[1][4];
			c1 = T[2][0] * a0 + T[2][1] * b0 + T[2][3] * d0 + T[2][4];
			d1 = T[3][0] * a0 + T[3][1] * b0 + T[3][2] * c0 + T[3][4];

			error = fmax(fabs(a1 - a0), fabs(b1 - b0), fabs(c1 - c0), fabs(d1 - d0));

			if (error < TOL) {
				break;
			}
			else {
				a0 = a1;
				b0 = b1;
				c0 = c1;
				d0 = d1;
			}
			cnt++;
		}
		printf("d\n");
		printf("x1: %.4f x2: %.4f x3: %.4f x4: %.4f\n", a1, b1, c1, d1);
		printf("iteration : %d\n", cnt);
	}

	else if (n == 5) {
		for (i = 0; i < n; i++) {
			b[i] = e[i][n];
		}
		for (i = 0; i < n; i++) {
			tmp = e[i][i];
			for (j = 0; j < n; j++) {
				if (i == j) {
					T[i][j] = 0;
					continue;
				}
				else {
					T[i][j] = e[i][j] / tmp * (-1);
				}
			}
			T[i][j] = b[i] / tmp;
		}

		while (1) {
			a1 = T[0][1] * b0 + T[0][2] * c0 + T[0][3] * d0 + T[0][4] * e0 + T[0][5];
			b1 = T[1][0] * a0 + T[1][2] * c0 + T[1][3] * d0 + T[1][4] * e0 + T[1][5];
			c1 = T[2][0] * a0 + T[2][1] * b0 + T[2][3] * d0 + T[2][4] * e0 + T[2][5];
			d1 = T[3][0] * a0 + T[3][1] * b0 + T[3][2] * c0 + T[3][4] * e0 + T[3][5];
			e1 = T[4][0] * a0 + T[4][1] * b0 + T[4][2] * c0 + T[4][3] * d0 + T[4][5];

			error = fmax(fabs(a1 - a0), fabs(b1 - b0), fabs(c1 - c0), fabs(d1 - d0), fabs(e1 - e0));

			if (error < TOL) {
				break;
			}
			else {
				a0 = a1;
				b0 = b1;
				c0 = c1;
				d0 = d1;
				e0 = e1;
			}
			cnt++;
		}
		printf("e\n");
		printf("x1: %.4f x2: %.4f x3: %.4f x4: %.4f x5: %.4f\n", a1, b1, c1, d1, e1);
		printf("iteration : %d\n", cnt);
	}

	else if (n == 6) {
		for (i = 0; i < n; i++) {
			b[i] = f[i][n];
		}
		for (i = 0; i < n; i++) {
			tmp = f[i][i];
			for (j = 0; j < n; j++) {
				if (i == j) {
					T[i][j] = 0;
					continue;
				}
				else {
					T[i][j] = f[i][j] / tmp * (-1);
				}
			}
			T[i][j] = b[i] / tmp;
		}
		
		while (1) {
			a1 = T[0][1] * b0 + T[0][2] * c0 + T[0][3] * d0 + T[0][4] * e0 + T[0][5] * f0 + T[0][6];
			b1 = T[1][0] * a0 + T[1][2] * c0 + T[1][3] * d0 + T[1][4] * e0 + T[1][5] * f0 + T[1][6];
			c1 = T[2][0] * a0 + T[2][1] * b0 + T[2][3] * d0 + T[2][4] * e0 + T[2][5] * f0 + T[2][6];
			d1 = T[3][0] * a0 + T[3][1] * b0 + T[3][2] * c0 + T[3][4] * e0 + T[3][5] * f0 + T[3][6];
			e1 = T[4][0] * a0 + T[4][1] * b0 + T[4][2] * c0 + T[4][3] * d0 + T[4][5] * f0 + T[4][6];
			f1 = T[5][0] * a0 + T[5][1] * b0 + T[5][2] * c0 + T[5][3] * d0 + T[5][4] * e0 + T[5][6];

			error = fmax(fabs(a1 - a0), fabs(b1 - b0), fabs(c1 - c0), fabs(d1 - d0), fabs(e1 - e0), fabs(f1 - f0));

			if (error < TOL) {
				break;
			}
			else {
				a0 = a1;
				b0 = b1;
				c0 = c1;
				d0 = d1;
				e0 = e1;
				f0 = f1;
			}
			cnt++;
		}
		printf("f\n");
		printf("x1: %.4f x2: %.4f x3: %.4f x4: %.4f x5: %.4f x6: %.4f\n", a1, b1, c1, d1, e1, f1);
		printf("iteration : %d\n", cnt);
	}

}


void Gauss_Seidel_Method(int n, double TOL) {
	double d[4][5] = {
		{4, 1, -1, 1, -2},
		{1, 4, -1, -1, -1},
		{-1, -1, 5, 1, 0},
		{1, -1, 1, 3, 1}
	};
	double e[5][6] = {
		{4, 1, 1, 0, 1, 6},
		{-1, -3, 1, 1, 0, 6},
		{2, 1, 5, -1, -1, 6},
		{-1, -1, -1, 4, 0, 6},
		{0, 2, -1, 1, 4, 6}
	};
	double f[6][7] = {
		{4, -1, 0, -1, 0, 0, 0},
		{-1, 4, -1, 0, -1, 0, 5},
		{0, -1, 4, 0, 0, -1, 0},
		{-1, 0, 0, 4, -1, 0, 6},
		{0, -1, 0, -1, 4, -1, -2},
		{0, 0, -1, 0, -1, 4, 6}
	};
	int i, j;
	double T[7][7], b[7];
	double tmp;
	double a0 = 0, b0 = 0, c0 = 0,
		d0 = 0, e0 = 0, f0 = 0;
	double a1 = 0, b1 = 0, c1 = 0,
		d1 = 0, e1 = 0, f1 = 0;
	int cnt = 1;
	double error;

	if (n == 4) {
		for (i = 0; i < n; i++) {
			b[i] = d[i][n];
		}
		for (i = 0; i < n; i++) {
			tmp = d[i][i];
			for (j = 0; j < n; j++) {
				if (i == j) {
					T[i][j] = 0;
					continue;
				}
				else {
					T[i][j] = d[i][j] / tmp * (-1);
				}
			}
			T[i][j] = b[i] / tmp;
		}

		while (1) {
			a1 = T[0][1] * b0 + T[0][2] * c0 + T[0][3] * d0 + T[0][4];
			b1 = T[1][0] * a1 + T[1][2] * c0 + T[1][3] * d0 + T[1][4];
			c1 = T[2][0] * a1 + T[2][1] * b1 + T[2][3] * d0 + T[2][4];
			d1 = T[3][0] * a1 + T[3][1] * b1 + T[3][2] * c1 + T[3][4];

			error = fmax(fabs(a1 - a0), fabs(b1 - b0), fabs(c1 - c0), fabs(d1 - d0));

			if (error < TOL) {
				break;
			}
			else {
				a0 = a1;
				b0 = b1;
				c0 = c1;
				d0 = d1;
			}
			cnt++;
		}
		printf("d\n");
		printf("x1: %.4f x2: %.4f x3: %.4f x4: %.4f\n", a1, b1, c1, d1);
		printf("iteration : %d\n", cnt);
	}
	else if (n == 5) {
		for (i = 0; i < n; i++) {
			b[i] = e[i][n];
		}
		for (i = 0; i < n; i++) {
			tmp = e[i][i];
			for (j = 0; j < n; j++) {
				if (i == j) {
					T[i][j] = 0;
					continue;
				}
				else {
					T[i][j] = e[i][j] / tmp * (-1);
				}
			}
			T[i][j] = b[i] / tmp;
		}

		while (1) {
			a1 = T[0][1] * b0 + T[0][2] * c0 + T[0][3] * d0 + T[0][4] * e0 + T[0][5];
			b1 = T[1][0] * a1 + T[1][2] * c0 + T[1][3] * d0 + T[1][4] * e0 + T[1][5];
			c1 = T[2][0] * a1 + T[2][1] * b1 + T[2][3] * d0 + T[2][4] * e0 + T[2][5];
			d1 = T[3][0] * a1 + T[3][1] * b1 + T[3][2] * c1 + T[3][4] * e0 + T[3][5];
			e1 = T[4][0] * a1 + T[4][1] * b1 + T[4][2] * c1 + T[4][3] * d1 + T[4][5];

			error = fmax(fabs(a1 - a0), fabs(b1 - b0), fabs(c1 - c0), fabs(d1 - d0), fabs(e1 - e0));

			if (error < TOL) {
				break;
			}
			else {
				a0 = a1;
				b0 = b1;
				c0 = c1;
				d0 = d1;
				e0 = e1;
			}
			cnt++;
		}
		printf("e\n");
		printf("x1: %.4f x2: %.4f x3: %.4f x4: %.4f x5: %.4f\n", a1, b1, c1, d1, e1);
		printf("iteration : %d\n", cnt);
	}
	else if (n == 6) {
		for (i = 0; i < n; i++) {
			b[i] = f[i][n];
		}
		for (i = 0; i < n; i++) {
			tmp = f[i][i];
			for (j = 0; j < n; j++) {
				if (i == j) {
					T[i][j] = 0;
					continue;
				}
				else {
					T[i][j] = f[i][j] / tmp * (-1);
				}
			}
			T[i][j] = b[i] / tmp;
		}

		while (1) {
			a1 = T[0][1] * b0 + T[0][2] * c0 + T[0][3] * d0 + T[0][4] * e0 + T[0][5] * f0 + T[0][6];
			b1 = T[1][0] * a1 + T[1][2] * c0 + T[1][3] * d0 + T[1][4] * e0 + T[1][5] * f0 + T[1][6];
			c1 = T[2][0] * a1 + T[2][1] * b1 + T[2][3] * d0 + T[2][4] * e0 + T[2][5] * f0 + T[2][6];
			d1 = T[3][0] * a1 + T[3][1] * b1 + T[3][2] * c1 + T[3][4] * e0 + T[3][5] * f0 + T[3][6];
			e1 = T[4][0] * a1 + T[4][1] * b1 + T[4][2] * c1 + T[4][3] * d1 + T[4][5] * f0 + T[4][6];
			f1 = T[5][0] * a1 + T[5][1] * b1 + T[5][2] * c1 + T[5][3] * d1 + T[5][4] * e1 + T[5][6];

			error = fmax(fabs(a1 - a0), fabs(b1 - b0), fabs(c1 - c0), fabs(d1 - d0), fabs(e1 - e0), fabs(f1 - f0));

			if (error < TOL) {
				break;
			}
			else {
				a0 = a1;
				b0 = b1;
				c0 = c1;
				d0 = d1;
				e0 = e1;
				f0 = f1;
			}
			cnt++;
		}
		printf("f\n");
		printf("x1: %.4f x2: %.4f x3: %.4f x4: %.4f x5: %.4f x6: %.4f\n", a1, b1, c1, d1, e1, f1);
		printf("iteration : %d", cnt);
	}
}
int main(void) {
	double TOL = 0.001;
	printf("---------- Jacobi Method ----------\n");
	Jacobi_Method(4, TOL);
	printf("\n");

	Jacobi_Method(5, TOL);
	printf("\n");

	Jacobi_Method(6, TOL);
	printf("\n");

	printf("---------- Gauss_Seidel Method ----------\n");
	Gauss_Seidel_Method(4, TOL);
	printf("\n");

	Gauss_Seidel_Method(5, TOL);
	printf("\n");

	Gauss_Seidel_Method(6, TOL);
}