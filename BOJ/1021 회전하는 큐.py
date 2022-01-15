import sys
from collections import deque

N, M = map(int, sys.stdin.readline().split())
num = deque(); mid = 0; cnt = 0

# 1 ~ N까지 원소의 위치를 append
for i in range(1, N + 1) :
    num.append(i)

# pop해줄 index를 기록하고 있는 arr
arr = list(map(int, sys.stdin.readline().split()))


if len(num) % 2 == 0 :
    mid = len(num) // 2 - 1
else :
    mid = len(num) // 2

# num의 가운데 index mid보다 큰 경우에는 오른쪽으로 회전, mid보다 작은 경우에는 왼쪽으로 회전 시키고, 첫 요소가 같은 경우에는 pop
while(len(arr) > 0) :
    if arr[0] == num[0] :
        num.popleft()
        arr.pop(0)
        if len(arr) == 0 :
            break
        elif len(num) % 2 == 0 :
            mid -= 1
    else :
        if num.index(arr[0]) <= mid :
            while(arr[0] != num[0]) :
                num.rotate(-1)
                cnt += 1
        else :
            while(arr[0] != num[0]) :
                num.rotate(1)
                cnt += 1
print(cnt)
