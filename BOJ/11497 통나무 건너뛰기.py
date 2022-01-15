'''
import sys

T = int(sys.stdin.readline())
game = list()

# 가장 작은 수 부터 왼쪽, 오른쪽 번갈아 가면서 삽입하면 최솟값을 구할수 있다.
# ex) 2 4 5 7 9 -> 2 5 9 7 4
for i in range(T) :
    N = int(sys.stdin.readline())
    wood = list(map(int, sys.stdin.readline().split()))
    wood.sort()
    difference = list()
    i = 0; j = i + 1
    # 짝수 인덱스 값 먼저 차례로 append한 후, 인덱스가 큰 값부터 작은 값으로 오면서 append
    # ex) 2 4 5 7 9 -> 2 5 9 먼저 append해주고, 7 4 순서로 append
    if len(wood) % 2 == 0 :
        while(j < len(wood)) :
            game.append(wood[i])
            i = j + 1
            j = i + 1
        j -= 2
        i = j - 1
        while(i >= 0) :
            game.append(wood[j])
            j -= 2
            i = j - 1
    else :
        while(j <= len(wood)) :
            game.append(wood[i])
            i = j + 1
            j = i + 1
        j -= 4
        i = j + 1
        while(i >= 0) :
            game.append(wood[j])
            j -= 2
            i = j - 1
    # list에서 인접한 원소끼리 차이를 구해서 최솟값을 출력
    for i in range(len(game) - 1) :
        difference.append(abs(game[i] - game[i + 1]))
    difference.append(abs(game[0] - game[-1]))
    print(max(difference))
    game.clear()
    difference.clear()
'''

import sys
from collections import deque

T = int(sys.stdin.readline())
game = deque(); check = 0;

for i in range(T) :
    N = int(sys.stdin.readline())
    wood = list(map(int, sys.stdin.readline().split()))
    wood.sort()
    difference = list()
    # wood에서 최댓값을 pop해서 append해 준 후, 반복해서 그 다음 최댓값을 오른쪽 왼쪽 순서대로 append해준다.
    # 그럼 정규분포 형태의 리스트가 만들어지고 이 배열이 최솟값이 된다.
    # 가장 큰 값을 추가
    game.append(wood.pop())
    while(len(wood) > 0) :
        # 그다음 최댓값을 오른쪽에 추가
        if(check == 0) :
            game.append(wood.pop())
            check = 1
        # 오른쪽 추가 후에 왼쪽에 추가
        else :
            game.appendleft(wood.pop())
            check = 0
        
    for i in range(len(game) - 1) :
        difference.append(abs(game[i] - game[i + 1]))
    difference.append(abs(game[i] - game[i + 1]))
    print(max(difference))
    game.clear()
        
            
