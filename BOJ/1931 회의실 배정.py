import sys

N = int(sys.stdin.readline());
meeting = list();
end_time = 0; cnt = 0;

for i in range(N) :
    start, end = map(int, sys.stdin.readline().split());
    meeting.append((start, end));

meeting = sorted(meeting, key = lambda x : (x[1], x[0]));

for i in range(len(meeting)) :
    # end_time이 회의 시작시간보다 작다면 회의가 가능
    if(end_time <= meeting[i][0]) :
        # end_time을 회의가 끝나는 시간으로 change
        end_time = meeting[i][1];
        cnt += 1;
print(cnt);
