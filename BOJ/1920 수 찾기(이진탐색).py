import sys
N = int(sys.stdin.readline())
A = list(set(map(int, sys.stdin.readline().split())))
M = int(sys.stdin.readline())
m = list(map(int, sys.stdin.readline().split()))

l = 0; r = len(A) - 1; mid = (l + r) // 2
i = 0

A.sort()

while(i < M) :
    mid = (l + r) // 2
    if l > r :
        print(0)
        i += 1
        l = 0; r = len(A) - 1
    elif A[mid] > m[i] :
        r = mid - 1
    elif A[mid] < m[i] :
        l = mid + 1
    else :
        print(1)
        i += 1
        l = 0; r = len(A) - 1


            
