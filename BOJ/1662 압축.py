import sys
S = sys.stdin.readline().strip()
stack = list(); idx = 0; K = 0
Q = ""; length = 0

while(idx < len(S)) :
    # 닫는 괄호가 나오면 여는 괄호가 나올 때 까지 스택에서 pop
    if S[idx] == ')' :
        while(stack[-1] != '(') :
            # 스택에 있는 정수형 숫자는 K(Q)의 압축을 해제한 문자열의 길이를 의미한다.
            if type(stack[-1]) == int :
                K += stack.pop()
            # 스택에 있는 str형 숫자는 Q를 의미한다.
            else :
                Q += stack.pop()
        # 압축을 해제한 문자열의 길이와 스택에 있는 Q를 합하면 다시 새로운 Q의 길이가 된다.
        length = len(Q) + K
        # '(' 괄호 제거
        stack.pop()
        # 새로운 K를 pop
        num = stack.pop()
        # K(Q)의 압축을 해제한 문자열의 길이를 다시 stack에 추가해준다.
        stack.append(length * int(num))
        Q = ""
        K = 0
    # 닫는 괄호가 나올때 까지 스택에 push
    else :
        stack.append(S[idx])
    idx += 1

length = 0
# 스택에 있는 정수형 숫자는 문자열의 길이, str형 숫자는 Q를 의미한다.
# 따라서 정수형 숫자를 모두 더해주고, str형 숫자의 길이를 더해주면 압축을 해제한 문자열의 길이가 나온다.
for i in stack :
    if type(i) == int :
        length += i
    else :
        tmp = len(i)
        length += tmp
print(length)

# Solution
# 1) 문자열 S를 입력받는다.
# 2) 입력받은 문자열 S를 차례대로 읽어준다.
# 3) 만약 읽은 문자가 ')'가 아닌 경우에는 읽은 순서대로 stack에 push해주고,
#    그렇지 않은 경우에는 스택의 top이 '('가 나올때 까지 pop해준다.
# 4) top이 '('가 될때까지 나온 문자열의 길이를 구해주고 괄호 앞에 있는 숫자와 곱해서 압축을 해제한 문자열의 길이를 구한다음,
#    스택에 추가한다.
#    2) ~ 4) 과정을 반복한다.

# pop해주는 과정에 int형 정수가 나오면 이는 K(Q)압축을 해제한 문자열의 길이가 되고,
# str형 정수는 압축을 해제해야 하는 문자열 Q가 된다.

# T1. 33(562(71(9)))
# stack = ['3', 18]
# 18 -> 압축을 해제한 문자열의 길이
# '3' -> Q
# 18 + 1 = 19
