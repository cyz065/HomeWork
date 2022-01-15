'''
def printArray(List) :
    for line in List :
        print(line);

board = list();
m, n = map(int, input().split());
count = 0;
chess_board = list();
tmp_board = list();
start = 0; end = 8;

for i in range(m) :
    tmp = list(input()); 
    board.append(tmp);
    
for i in range(m - 7) :
    tmp_board = board[start:end];
    for j in range(n - 7) :
        
'''

import sys
N, M = map(int, sys.stdin.readline().split())
# 체스판 초기화
board = [[0] * M] * N
idx = 0 # 가로
index = 0 # 세로
cnt = 0 # 새로 칠해야 하는 칸의 개수
colors = ['W', 'B'];
l = 0 # colors의 인덱스
count = list() # cnt값을 저장하기 위한 배열

# 체스판을 입력 받기
for i in range(N) :
    board[i] = list(sys.stdin.readline().strip())

while(True) :
    # color값은 체스판의 가장 첫 번째 칸의 색상
    color = board[index][idx]
    l = colors.index(color)
    
    # 먼저 가로로 8개 씩 색상을 확인하고 이후에 1줄 내려가서 8줄의 색상을 확인한다.
    for j in range(index, index + 8) :
        for k in range(idx, idx + 8) :
            
            # 체스판의 색상이 번갈아 나타나지 않는 경우 cnt를 1 증가
            # 그 다음 색상이 아래 코드를 통해 변경되므로 계속해서 확인 가능
            if colors[l] != board[j][k] :
                cnt += 1
                
            # 색상이 B, W가 번갈아 나와야 하므로 l을 0, 1 계속해서 변경
            l = (l + 1) % 2
            
        # 다음 줄은 윗 줄의 색상과 달라야 하기 때문에 색상을 변경 (줄 변경 시에만)
        l = (l + 1) % 2
        
    # 가장 첫번째 칸의 색을 바꾸어야 하는 경우를 위한 코드,
    # 64와 64 - cnt값 중 최솟값으로도 가능하지 않을까...?????
    tmp = 64 - cnt
    cnt = min(tmp, cnt)
    
    # 새로 칠해야 하는 칸의 개수를 저장
    count.append(cnt)
    cnt = 0
    index += 1 # 다음 줄로 넘어간다.

    # 만약 가능한 아랫줄 까지 모두 내려온 경우에는 다시 처음 줄로 올라가고, idx번째칸 부터가 아닌 idx + 1칸부터 다시 점검한다.
    # ex) [0][0] ~ [7][7]까지 한 후, [0][1] ~ [7][8]까지 다시 수행
    if index > N - 8 and idx < M - 8 :
        index = 0
        idx += 1
    # 모든 경우를 다 살펴 본 경우, 탈출
    elif index > N - 8 and idx >= M - 8 :
        break
#print(count)
print(min(count))
        
    
        

        




        
'''
for i in range(m-7) :
    for j in range(n-7) :
        print("--추출--");
        #chess_board = [m[j:j+n] for m in board[i:i+m]];
        printArray([m[j:j+n] for m in board[i:i+m]])
'''
'''
for i in range(m-8) :
    for j in range(n-8) :
        chess_board = board[0:9][0:9];
print(chess_board);
'''
'''
for j in range(m) :
    for k in range(n-1) :
        if(board[j][k] == 'B' or 'W') :
            if(board[j][k+1] == board[j][k]) :
                print("Index : borad[", j, "]", "[", k, "]");
                count += 1;

print(count);
'''           

                
                
        
                       

        
        






        
   


