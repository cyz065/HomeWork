import sys
N = int(sys.stdin.readline())
score = 0; stack = list(); top = -1

for i in range(N) :
    tmp = list(map(int, sys.stdin.readline().split()))
    # 과제가 주어지는 경우 stack에 push
    if tmp[0] == 1 :
        assignment = [tmp[1], tmp[2]]
        stack.append(assignment)
        top += 1
        stack[top][1] -= 1
        # 과제가 끝나는 경우 점수를 추가해 주고 stack에서 pop
        if stack[top][1] == 0 :
            score += stack[top][0]
            stack.pop()
            top -= 1
    else :
        # 과제가 주어지지 않은 경우 기존 과제를 수행
        if len(stack) != 0 :
            stack[top][1] -= 1
            if stack[top][1] == 0 :
                score += stack[top][0]
                stack.pop()
                top -= 1
print(score)
        
