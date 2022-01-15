'''
import sys
string = list(sys.stdin.readline().strip())
s = list()
s.append(string.pop(0))

# pop해준 원소가 ( 인경우에는 stack에 추가, 만약 (가 존재하고 pop 해준 원소가 ) 인 경우 괄호 쌍이 존재 하므로 top에 있는 (를 pop
# 괄호 쌍이 존재할 때 까지 append 괄호 쌍이 생기는 경우에는 stack에서 top를 pop

while(len(string) > 0) :
    t = string.pop(0)  
    if t == "(" :
        s.append(t)
    elif len(s) == 0 :
        s.append(t)
    elif t == ")" and s[-1] == "(" :
        s.pop()
    else :
        s.append(t)
print(len(s))
'''

import sys
string = sys.stdin.readline().strip()
opened = 0; ans = 0

for i in string :
    # (가 나오는 경우, 괄호쌍을 이루기 위해서는 (의 수만큼 )가 존재해야 하므로 opened를 1씩 증가시켜준다.
    if i == "(" :
        opened += 1
    else :
        # )가 나오는 경우 만약 opened가 0보다 크다면 (가 존재함을 의미하기 때문에 opened를 1씩 감소시켜 준다.
        if opened > 0 :
            opened -= 1
        # 그렇지 않은 경우에는 괄호쌍을 이루지 못하기 때문에 ans를 1씩 증가
        else :
            ans += 1

# (가 4개, )가 3개인 경우 ( 1개는 괄호쌍을 이루지 못하므로 나머지 ans 와 opened를 더한 결과를 출력
print(ans + opened)
    
