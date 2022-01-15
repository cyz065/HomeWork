import sys
import math

A, B = map(int, sys.stdin.readline().split())

print(math.gcd(A, B))
print(math.lcd(A, B))

