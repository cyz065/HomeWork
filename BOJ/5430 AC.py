import sys
from collections import deque

T = int(sys.stdin.readline())
reverse = False; error = False;

for i in range(T) :
    p = deque(sys.stdin.readline().strip())
    n = int(sys.stdin.readline())
    # 입력에서 대괄호 [] 제거
    arr = sys.stdin.readline().strip('[]\n')
    # , 제거
    arr = deque(arr.split(','))
    
    if '' in arr :
        arr.remove('');

    for i in p :
        # R이 홀수개이면 reverse가 True 짝수개이면 False
        if i == "R" :
            if reverse == False :
                reverse = True
            else :
                reverse = False
        # R이 홀수개이면 오른쪽부터 pop R이 짝수개이면 왼쪽에서 pop
        elif i == "D" :
            if reverse == False :
                # arr원소의 개수보다 D명령어가 더 많은 경우 error
                if len(arr) == 0 :
                    print("error")
                    error = True
                    break
                else :
                    arr.popleft()
            elif reverse == True :
                if len(arr) == 0 :
                    print("error")
                    error = True
                    break
                else :
                    arr.pop()
                    
    # 남아있는 arr 원소가 있고, R이 짝수개인 경우 그대로 출력
    if len(arr) > 0 and reverse == False :
        result = ','.join(map(str,arr))
        print('[' + result + ']')
    # 남아있는 arr원소가 있고, R이 홀수개인 경우 뒤집어서 출력
    elif len(arr) > 0 and reverse == True  :
        arr.reverse()
        result = ','.join(map(str,arr))
        print('[' + result + ']')
    # 남아있는 arr원소가 없고, error가 발생하지 않는 경우
    elif len(arr) == 0 and error == False :
        print(list(arr))
    reverse = False
    error = False
