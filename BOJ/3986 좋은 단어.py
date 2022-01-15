import sys
N = int(sys.stdin.readline())
word = [sys.stdin.readline().strip() for x in range(N)]
stack = list(); cnt = 0

# 아치형 곡선을 그어 선 끼리 교차하지 않는다.
# -> 스택의 top과 같은 값이 나오고, stack의 길이가 0이 되면 가능
for i in word :
    for j in i :
        if len(stack) == 0 or stack[-1] != j :
            stack.append(j)
        else :
            stack.pop()
    if len(stack) == 0 :
        cnt += 1
    stack.clear()
print(cnt)
