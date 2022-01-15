import sys

# 희망 등수가 큰 사람부터 낮은 등수를 주면 차이를 최소화 할 수 있다.
N = int(sys.stdin.readline())
rank = N; result = 0
student = [int(sys.stdin.readline()) for x in range(N)]

# rank를 큰 수 부터 결정하기 위해 역순 정렬
student = sorted(student, reverse = True)

# 절댓값 구하기
for i in student :
    if rank - i < 0 :
        result += i - rank
    else :
        result += rank - i
    rank -= 1
print(result)


        
        






        
   


