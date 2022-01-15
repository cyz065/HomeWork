# 5397 키로거 참고
import sys

string = list(sys.stdin.readline().strip())
M = int(sys.stdin.readline())
tmp = list()
cmd = [sys.stdin.readline().strip() for x in range(M)]

# 커서를 실제로 옮기는 것이 아니라, 문자를 pop하고 append해서 커서의 위치를 표현해준다.

for i in cmd :
    # 명령어가 L인 경우 커서를 옮기는 효과를 위해 string배열에서 문자 1개를 pop
    # 임시로 tmp배열에 추가
    # 만약 string배열이 비어있는 경우에는 커서가 가장 왼쪽을 가리키고 있으므로 무시
    if i == 'L' and string != [] :
        tmp.append(string.pop())
    # 명령어가 B인 경우 가장 끝에 있는 문자를 제거
    elif i == 'B' and string != [] :
        string.pop()
    # 명렁어가 D인 경우 커서를 오른쪽으로 옮기는 효과를 위해 tmp배열에 있는 문자를 string배열에 추가
    # tmp배열이 비어있는 경우에는 커서가 가장 오른쪽을 가리키고 있으므로 무시
    elif i == 'D' and tmp != [] :
         string.append(tmp.pop())
    # 명령어가 P인 경우, P명령어는 'P $' 형식을 되어 있으므로, 2번 인덱스의 값이 추가해줄 값이된다.
    # 이 값을 string배열 끝에 추가해준다.
    elif i[0] == 'P' :
        c = i[2]
        string.append(c)
# 커서가 중간에 위치하는 경우, tmp배열에 값이 존재하게 된다. 이 경우에는 모든 값을 reverse해주면 string 배열에 있는 원래의 순서가 된다.
if tmp != [] :
    tmp = tmp[::-1]
    tmp = ''.join(map(str, tmp))
    string.append(tmp)
string = ''.join(map(str, string))
print(string)
