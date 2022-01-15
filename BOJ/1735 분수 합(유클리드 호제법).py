'''
import sys

A, a = map(int, sys.stdin.readline().split())
B, b = map(int, sys.stdin.readline().split())

x = 0; y = 0; tmp = a; temp = b;

if tmp < temp :
    tmp, temp = temp, tmp

while(temp) :
    tmp, temp = temp, tmp % temp

y = a * b // tmp
x = A * y // a + B * y // b
tmp = x; temp = y;

if tmp < temp :
    tmp, temp = temp, tmp

while(temp) :
    tmp, temp = temp, tmp % temp

x //= tmp
y //= tmp
print(x, y)
'''
import sys
import math

A, a = map(int, sys.stdin.readline().split())
B, b = map(int, sys.stdin.readline().split())
y = a * b // math.gcd(a, b)
x = A * y // a + B * y // b
A = math.gcd(x, y)
y //= A; x //= A;
print(x, y)


# 유클리드 호제
# 최대공약수를 구하는 함수를 gcd(x, y)라 가정
# 1) x % y = 0 이면 gcd(x, y) = y가 성립
# 2) x % y != 0 이면 gcd(x, y) = gcd(x, x % y)가 성립
# 3) 2가 될때 까지 2 ~ 3을 반복
# 최소공배수
# lcm(x,y)는 두 수 x, y의 곱을 최대공약수 gcd(x, y)로 나누면 구할수 있따.
# lcm(x, y) = x * y // gcd(x, y)
# ref) https://brownbears.tistory.com/454
