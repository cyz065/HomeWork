import sys
N = int(sys.stdin.readline())
schedule = list(); idx = 0
T = 0;

for i in range(N) :
    tmp = tuple(map(int, sys.stdin.readline().split()))
    schedule.append(tmp)
    T += schedule[i][0]

# 해야하는 일들을 끝나는 시간(S)순서대로 정렬
schedule = sorted(schedule, key = lambda x : x[1])
S = schedule[N - 1][1]

# 해야하는 일의 합 T가 마지막 일이 끝나는 시간보다 크면 0시 이전에
# 일을 해도 불가능 하기 때문에 -1
if T > S :
    print(-1)
# 해야하는 일 시간의 합 T와 마지막 일이 끝나는 시간이 같으면, 0시에 일을 시작하면 가능
elif T == S :
    print(0)
# T가 S보다 작은 경우에는 S의 합을 구해서 T를 빼준 후에, T를 더해 가면서 S를 초과하는지 확인한다.
# 만일 초과하는 경우에는 time을 1씩 빼주고, 그렇지 않은 경우에는 time이 답이 된다.
else :
    time = S - T
    tmp = time
    while(idx < N and time >= 0) :
        tmp += schedule[idx][0]
        if tmp > schedule[idx][1] :
            idx = 0
            time -= 1
            tmp = time
            continue
        else :
            idx += 1
    print(time)
        

# clu
# 1) 일찍 끝나는 순서대로 오름차순 정렬
# 2) 모든 T의 합을 구하기
# 2-1) 만일 T의 합이 S보다 크다면 -1
# 2-2) T의 합이 S와 같다면 0\
# 3) T의합이 S보다 작으면 S-T를 초기 시간으로 설정한 후에, T를 점점 더하면서, S(i)보다 커지는지 확인
# 3-1) T가 S(i)보다 커지는 경우에는 time을 1 감소 시키고, 처음부터 다시 3) 과정을 수행
# 3-2) T가 S(i)보다 작은 경우 S까지 반복
# 4) T가 S보다 작아지는 경우의 time을 출력
