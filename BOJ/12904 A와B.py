import sys
from collections import deque

S = deque(sys.stdin.readline().strip())
T = deque(sys.stdin.readline().strip())
reverse = 0

# S와 T에 공통된 알파벳이 1개도 없는 경우
if('A' in S and 'A' not in T) :
    print(0);
elif('B' in S and 'B' not in T) :
    print(0);

else :
    while(len(T) > len(S)) :
        # 가장 뒤 알파벳이 B인경우 오른쪽에서 pop해주고 reverse를 1로 해서 문자열 뒤집기를 해야 됨을 나타냄
        if(reverse == 0 and T[-1] == 'B') :
            T.pop();
            reverse = 1;
        # reverse가 1인 경우 뒤가 아닌 앞에서 문자열 제거
        elif(reverse == 1 and T[0] == 'B') :
            T.popleft()
            reverse = 0
        # A도 B와 마찬가지로 시행
        elif(reverse == 0 and T[-1] == 'A') :
            T.pop()
        elif(reverse == 1 and T[0] == 'A') :
            T.popleft()
    # reverse가 1 즉, 문자열을 뒤집어야 하는 경우에는 문자열을 뒤집어 준다.
    if(reverse == 1) :
        T.reverse()
    # 가능 여부 출력
    if(T == S) :
        print(1)
    else :
        print(0)
