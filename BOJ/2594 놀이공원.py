import sys
N = int(sys.stdin.readline())
# rest : 휴식 가능한 시간의 최댓값
rest = 0; idx = 1
# s, e : 이전 일정의 시작과 끝나는 시간
s = 0; e = 0;
schedule = list()

for i in range(N) :
    start, end = sys.stdin.readline().split()
    schedule.append((start, end))
# 운영 일정을 끝나는 시간의 오름차순으로 정렬해준다.
schedule = sorted(schedule, key = lambda x : int(x[1]))

tmp = schedule[0][0]; temp = schedule[0][1]
# s : 시작 시간을 분단위로 표현 ex) 10:30 -> 630
s = int(tmp[:2]) * 60 + int(tmp[2:])
# e : 끝나는 시간을 분단위로 표현 ex)13:00 -> 780
e = int(temp[:2]) * 60 + int(temp[2:])

# 놀이기구 1 운영전 쉴수 있는 시간을 구함
rest = s - 10 - 600
# 음수면 쉴시간이 zero, 양수인 경우에는 휴식 시간이 존재함
if rest < 0 :
    rest = 0
if len(schedule) > 1 :
    while(idx < N) :
        tmp = schedule[idx][0]
        temp = schedule[idx][1]
        # start는 그다음 놀이기구 운영 시작 시간
        start = int(tmp[:2]) * 60 + int(tmp[2:])
        # end는 그 다음 놀이기구의 운영이 끝나는 시간
        end = int(temp[:2]) * 60 + int(temp[2:])

        # 놀이기구 N이 끝나고 놀이기구 N + 1이 시작되기 전에 남는 시간이 있는 경우
        # 쉴 수 있는 시간을 구해서 기존의 값과 비교해서 최대값을 저장
        if e + 10 <= start - 10 :
            r = start - 10 - (e + 10)
            rest = max(rest, r)
        # s, e는 이전 일정을 나타내는 변수이므로 s, e를 N + 1의 시작, 끝나는 시간으로 변경해주고
        # 다음 loop에서 start, end는 N + 2의 시작과 끝으로 변경 
        s, e = start, end
        idx += 1
    # 가장 마지막에 22시 이전에 끝나는 경우에도 쉴 수 있는 시간이 존재하므로, 휴식 시간을 계산해서 최대값을 출력
    r = 22 * 60 - (end + 10)
    rest = max(rest, r)
    print(rest)
# 일정이 단 하나만 존재하는 경우
else :
    rest = 60 * 22 - (e + 10)
    print(rest)

