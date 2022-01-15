import sys;
import json;

N = int(sys.stdin.readline());
result = 0;

A = [num for num in map(int, sys.stdin.readline().split())];
B = [num for num in map(int, sys.stdin.readline().split())];

#A = list(map(int, sys.stdin.readline().split()));
#B = list(map(int, sys.stdin.readline().split()));


A.sort();
B = sorted(B, reverse = True);

'''
for i in range(N - 1) :
    for j in range(i + 1, N) :
        if(A[i] > A[j]) :
            A[i], A[j] = A[j], A[i];

for i in range(N - 1) :
    for j in range(i + 1, N) :
        if(B[i] < B[j]) :
            B[i], B[j] = B[j], B[i];
'''
for i in range(N) :
    temp = A[i] * B[i];
    result += temp;

print(result);

