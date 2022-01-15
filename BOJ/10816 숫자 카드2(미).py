import sys

N = int(sys.stdin.readline())
card = list(map(int, sys.stdin.readline().split()))
M = int(sys.stdin.readline())
m = list(map(int, sys.stdin.readline().split()))
answer = list();

card.sort()
m.sort()
l = 0; r = M - 1; cnt = 0;

while(idx < len(m)) :
    mid = (l + r) // 2
    if card[mid] < m[idx] :
        l = mid + r
    elif card[mid] > m[idx] :
        r = mid - 1
    else :
        idx += 1
        l = 0; r = M - 1;
        idx += 1
        
    
