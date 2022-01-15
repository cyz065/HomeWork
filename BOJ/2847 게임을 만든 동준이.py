import sys
N = int(sys.stdin.readline())
score = list()
cnt = 0
score = [int(sys.stdin.readline()) for x in range(N)];

# list에서 값을 2개씩 비교
for i in range(1, len(score)) :
	second = score[len(score) - i]
	first = score[len(score) - i - 1]
	# list의 elements가 증가하도록 하기 위해서 1씩 감소시키고 값을 변경
	if(first >= second) :
		cnt += first - second + 1
		first = second - 1
		score[len(score) - i - 1] = first
	else :
		continue
print(cnt)
