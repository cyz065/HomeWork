#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 3

void swap_row(double m[SIZE][SIZE + 1], int i, int j) {
	for (int k = 0; k <= SIZE; k++) {
		double temp = m[i][k];
		m[i][k] = m[j][k];
		m[j][k] = temp;
	}
}

void backward_substitution(double m[SIZE][SIZE + 1]) {
	double result[SIZE];
	int i, k;

	result[2] = m[2][3] / m[2][2];
	for (i = 1; i >= 0; i--) {
		result[i] = m[i][3];
		for (k = i + 1; k < SIZE; k++) {
			result[i] = result[i] - m[i][k] * result[k];
		}
		result[i] = result[i] / m[i][i];
	}
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		printf("x%d: %f ", i + 1, result[i]);
	}
	printf("\n");
}

void Gaussian(double m[SIZE][SIZE + 1]) {
	int i, j;
	double ratio;

	for (i = 0; i < SIZE - 1; i++) {
		for (j = i + 1; j < SIZE; j++) {
			if (m[i][i] != 0) {
				ratio = m[j][i] / m[i][i];
				for (int k = 0; k < SIZE + 1; k++) {
					m[j][k] = m[j][k] - ratio * m[i][k];
				}
			}
			else {
				swap_row(m, i, j);
			}
		}
	}
	backward_substitution(m);
};

void Gaussian_partial_pivoting(double m[SIZE][SIZE + 1]) {
	int i, j;
	double ratio;

	for (i = 0; i < SIZE - 1; i++) {
		for (j = i + 1; j < SIZE; j++) {
			if (m[i][i] == 0 || (fabs(m[i][i]) < fabs(m[j][i]))) {
				swap_row(m, i, j);
			}
			else {
				ratio = m[j][i] / m[i][i];
				for (int k = 0; k < SIZE + 1; k++) {
					m[j][k] = m[j][k] - ratio * m[i][k];
				}
			}
		}
	}
	backward_substitution(m);
}

void Gaussian_scaled_partial_pivoting(double m[SIZE][SIZE + 1]) {
	double ratio;
	int i, j, max_rows_num;
	double s[SIZE];

	s[0] = m[0][0]; s[1] = m[1][0]; s[2] = m[2][0];

	for (i = 0; i < SIZE; i++) {
		for (j = 1; j < SIZE; j++) {
			if (fabs(m[i][j]) > fabs(s[i])) {
				s[i] = m[i][j];
			}
		}
	}

	for (i = 0; i < 2; i++) {
		max_rows_num = i;
		for (j = i + 1; j < 3; j++) {
			if (fabs(m[j][i] / s[j]) > fabs(m[max_rows_num][i] / s[max_rows_num])) {
				max_rows_num = j;
			}
		}
		swap_row(m, i, max_rows_num);
		double tmp = s[i];
		s[i] = s[max_rows_num];
		s[max_rows_num] = tmp;
	}

	for (i = 0; i < 2; i++) {
		for (j = i + 1; j < 3; j++) {
			ratio = m[j][i] / m[i][i];
			for (int k = 0; k < 4; k++) {
				m[j][k] = m[j][k] - ratio * m[i][k];
			}
		}
	}
	backward_substitution(m);
}

int main(void) {
	double a[3][4] = {
		{1, -5, 1, 7},
		{10, 0, 20, 6},
		{5, 0, -1, 4}
	};

	double b[3][4] = {
		{1, 1, -1, 1},
		{1, 1, 4, 2},
		{2, -1, 2, 3}
	};

	double c[3][4] = {
		{2, -3, 2, 5},
		{-4, 2, -6, 14},
		{2, 2, 4, 8}
	};

	double d[3][4] = {
		{0, 1, 1, 6},
		{1, -2, -1, 4},
		{1, -1, 1, 5}
	};

	printf("------------------Gaussian------------------\n");
	Gaussian(a);
	Gaussian(b);
	Gaussian(c);
	Gaussian(d);
	printf("\n");

	printf("-------Gaussian Partial Pivoting-------\n");
	Gaussian_partial_pivoting(a);
	Gaussian_partial_pivoting(b);
	Gaussian_partial_pivoting(c);
	Gaussian_partial_pivoting(d);
	printf("\n");

	printf("-----Gaussian Scaled Partial Pivoting-----\n");
	Gaussian_scaled_partial_pivoting(a);
	Gaussian_scaled_partial_pivoting(b);
	Gaussian_scaled_partial_pivoting(c);
	Gaussian_scaled_partial_pivoting(d);
}