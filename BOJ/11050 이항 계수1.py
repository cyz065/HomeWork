import sys

N, K = map(int, sys.stdin.readline().split())
tmp = 1; t = 1

for i in range(K) :
    tmp *= N
    N -= 1;

for i in range(K) :
    t *= K;
    K -= 1
result = tmp // t
print(result)
