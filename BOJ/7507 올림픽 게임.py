import sys
n = int(sys.stdin.readline())
games = list()

for i in range(n) :
    m = int(sys.stdin.readline())
    cnt = 1
    for j in range(m) :
        d, s, e = map(int, sys.stdin.readline().split())
        games.append((d, s, e))
    # 경기를 날짜, 끝나는 시간 오름차순으로 정렬
    games = sorted(games, key = lambda x : (x[0], x[2]))
    end = games[0][2]

    for k in range(len(games) - 1) :
        # 다음 경기의 시작 시간이 현재 관람중인 경기의 끝나는 시간보다 크거나 같으면
        # 경기 관람이 가능하기 때문에 cnt 1 증가
        if games[k][0] == games[k + 1][0] and end <= games[k + 1][1] :
            cnt += 1
            end = games[k + 1][2]
        # 다음 경기의 날짜가 다른 경우에는 무조건 관람이 가능하기 때문에 cnt 1증가
        elif games[k][0] != games[k + 1][0] :
            cnt += 1
            end = games[k + 1][2]
    print("Scenario #%d" %(i + 1))
    print(cnt, '\n')
    games.clear()
