import sys

# 편차가 작을수록 곱의 결과가 커진다.
# 12 7 -> 2 2 2 2 2 1 1 : 32
S, K = map(int, sys.stdin.readline().split())
# a = 몫, b = 나머지
a = S // K; b = S % K; result = 1

# K - b만큼 몫을 가지고, b개수 만큼 1씩 분배해준다.
# ex) 12 7 -> K = 7, b = 5에서 7개에 몫(a)을 분배 해주고, 나머지(b)개수 만큼 1씩 더해준다
# 2 2 2 2 2 1 1
tmp = K - b
for i in range(tmp) :
    result *= a

for i in range(b) :
    result *= (a + 1)
print(result)
        

# clu
# 편차가 작을수록 곱의 결과가 커진다.
# K개 만큼 몫을 분배해주고 나머지(b)를 K개중 b개에 1씩 분배해준다.
