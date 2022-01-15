# 1) 시간 초과
'''
import sys
from collections import deque

N = int(sys.stdin.readline())
number = deque(map(int, sys.stdin.readline().split()))
NGE = list(); cnt = 1; tmp = 0; i = 1;

while(len(number) > 0) :
    tmp = number.popleft()
    while(len(number) > 0) :
        if(tmp > number[0]) :
            number.popleft()
            cnt += 1
        else :
            break
    for i in range(cnt) :
        NGE.append(number[0]);
    cnt = 1
print(NGE);
'''
# 2)
import sys
N = int(sys.stdin.readline())
stack = list(); top = -1
A = list(map(int, sys.stdin.readline().split()));
NGE = [-1] * N

stack.append(0);
top += 1;

for i in range(1, N) :
    # A[i]가 stack의 top이 가리키는 값보다 큰 경우, stack의 top이 가리키는 값보다
    # 큰 수가 나올때까지 pop해준다. 그리고 pop해준 index에 해당하는 오큰수는 A[i]이므로 -1을 A[i]값으로 치환
    # A[i]값을 스택에 추가하여 그 다음 오큰수를 찾는다.
    if A[i] > A[stack[top]] :
        while(top >= 0 and A[stack[top]] < A[i]) :
            tmp = stack.pop()
            top -= 1
            NGE[tmp] = A[i]
        stack.append(i)
        top += 1
    # A[i]보다 stack의 top이 가리키는 수가 큰 경우, 오큰수가 아니기 때문에 stack에 추가해주고 다음 큰 수를 찾는다.
    else :
        stack.append(i)
        top += 1
print(*NGE);

# 오큰수
# 1) 스택에 값을 넣을 때 스택에 가장 위에있는 값이 현재의 값보다 작거나 스택이 빌 때 까지 pop연산을 해준다.
# 2) 현재의 값이 크다면 그 수가 오큰수가 되므로 해당하는 NGE수열의 -1을 현재의 값으로 변경해준다.
# 3) 현재의 값보다 큰 값을 스택에서 만나거나 스택이 비게 되면,
#    그 다음 오큰수를 찾기위해서 현재의 값을 스택에 push해주고 1)의 과정을 반복한다.
# 참고) https://hooongs.tistory.com/329        
    


