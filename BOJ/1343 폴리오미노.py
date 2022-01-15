import sys
from collections import deque
X = deque(sys.stdin.readline().strip())
count_a = 0; count_b = 0; count_x = 0
string = ""; A = "AAAA"; B = "BB";
arr = sorted(X, reverse = True);

while(len(X) > 0) :
    # 전체 X의 개수가 홀수 이면 조건에 부합X break
    for i in arr :
        if(i == "X") :
            count_x += 1;
    if(count_x % 2 != 0) :
        break;
    
    # '.'이 나오기 전까지 X의 개수 count
    count_x = 0;
    while(len(X) > 0 and X[0] != '.') :
        X.popleft()
        count_x += 1
        
    #  X의 개수가 홀수이면 조건에 부합하지 않으므로 break
    if(count_x % 2 != 0) :
        break
    
    # X의 개수에 따라서 A와 B의 개수 count
    else :
        count_a = count_x // 4
        tmp = count_x % 4
        count_b = tmp // 2
        for i in range(count_a) :
            string += A
        for j in range(count_b) :
            string += B
            
    # '.' 이어 붙이기
    while(len(X) > 0 and X[0] != 'X') :
        tmp = X.popleft()
        string+= tmp
    
if(count_x % 2 == 0) :
    print(string);
else :
    print(-1)

