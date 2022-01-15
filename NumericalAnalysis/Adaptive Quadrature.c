#include <stdio.h>
#include <math.h>

double function_a(double x) {
    return exp(2 * x) * sin(3 * x);
}
double function_b(double x) {
    return exp(3 * x) * sin(2 * x);
}
double function_c(double x) {
    return 2 * x * cos(2 * x) - pow(x - 2, 2);
}
double function_d(double x) {
    return 4 * x * cos(2 * x) - pow(x - 2, 2);
}

double adaptive_quadrature(double (*f)(double), double a, double b, double S, double TOL) {
    double mid = (a + b) / 2; double h = (b - a) / 2;
    double m1 = (a + mid) / 2; double m2 = (mid + b) / 2;
    // ���Ӱ� ������ ������ ���� Simpson's Rule ����
    double Sleft = h / 6 * (f(a) + 4 * f(m1) + f(mid));
    double Sright = h / 6 * (f(mid) + 4 * f(m2) + f(b));
    double S2 = Sleft + Sright;
    // �ٻ簪�� ������ 15 * TOL���� �۾� �� ������ ������ �������� ������ ������ �����Ѵ�.
    // �ٻ簪�� ������ 15 * TOL���� �۾����� ���, �� ���� ��ȯ�Ѵ�.
    if (fabs(S2 - S) <= 15 * TOL)
        return S2 + (S2 - S) / 15;
    return adaptive_quadrature(f, a, mid, Sleft, TOL / 2) + adaptive_quadrature(f, mid, b, Sright, TOL / 2);
}
double simpson_rule(double (*f)(double), double a, double b) {
    double TOL = 0.00001;
    double mid = (a + b) / 2;
    double h = (b - a) / 2;
    double S = (h / 3) * (f(a) + 4 * f(mid) + f(b));
    return adaptive_quadrature(f, a, b, S, TOL);
}
int main(void) {
    printf("a : %lf\n", simpson_rule(function_a, 1, 3));
    printf("b : %lf\n", simpson_rule(function_b, 1, 3));
    printf("c : %lf\n", simpson_rule(function_c, 0, 5));
    printf("d : %lf\n", simpson_rule(function_d, 0, 5));
}