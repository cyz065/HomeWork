import sys

N = int(sys.stdin.readline())
n = list(map(int, sys.stdin.readline().split()))
M = int(sys.stdin.readline())
m = list(map(int, sys.stdin.readline().split()))

ans = list(); idx = 0;

l = 0; r = N - 1; mid = (l + r) // 2
n.sort()


while(idx < M) :
    while(True) :
        mid = (l + r) // 2
        if l > r :
            ans.append(0)
            l = 0; r = N - 1
            break
        if n[mid] < m[idx] :
            l = mid + 1
        elif n[mid] > m[idx] :
            r = mid - 1
        else :
            ans.append(1)
            l = 0; r = N - 1
            break
    idx += 1
'''
while(idx < M) :
    mid = (l + r) // 2
    if l > r :
        ans.append(0)
        idx += 1
        l = 0; r = N - 1
    elif n[mid] < m[idx] :
        l = mid + 1
    elif n[mid] > m[idx] :
        r = mid - 1
    else:
        ans.append(1)
        l = 0; r = N - 1
        idx += 1
'''
print(' '.join(map(str, ans)))


        
    
