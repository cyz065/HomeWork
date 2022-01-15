import sys
from collections import deque

N = int(sys.stdin.readline())
student = deque(map(int, sys.stdin.readline().split()))
stack = list(); rank = 1

# rank와 head가 일치하면 student에서 pop 해주고 rank를 1 올려준다
while(len(student) > 0) :
    if(student[0] == rank) :
        student.popleft()
        rank += 1
        # stack에 있는 다음 학생과 rank가 일치하면 stack에서 pop
        while(True) :
            if(len(stack) > 0 and stack[-1] == rank) :
                stack.pop()
                rank += 1
            else :
                break
    # rank와 head가 다른 경우 stack에 학생을 추가
    else :
        stack.append(student.popleft())

# 배부가 가능한 경우 stack의 길이가 0이 된다
if len(stack) == 0 :
    print("Nice")
else :
    print("Sad")

