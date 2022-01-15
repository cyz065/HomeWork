import sys
D, K = map(int, sys.stdin.readline().split())
first = 0; second = 1; tmp = 0;

# first, second에서 second가 1씩 증가할 때마다 D일에 해당하는 값은
# 피보나치 수열의 D - 1번째 수 만큼 증가한다. [1, 1, 2, 3, 5, 8 ...]

#                        +0     +1     +1     +2     +3     +5
# ex) first   second    D = 1, D = 2, D = 3, D = 4, D = 5, D = 6
#      1        1        1       1      2      3      5      8
#      1        2        1       2      3      5      8      13

# 따라서 tmp는 D일에 second가 1 증가하는 경우 증가하게 되는 떡의 갯수가 된다.
for i in range(D - 1) :
    first = second
    second = tmp
    tmp = first + second

first = 1; second = 1; idx = 2;
f = first; s = second
temp = f + s

# first, second를 1, 1 부터 시작해서 D일에 해당하는 떡의 갯수를
# temp와, t에 기록한다.
for j in range(D - 3) :
    f = s
    s = temp
    temp = f + s
t = temp

# first, second에서 second가 1씩 증가할 때마다 D - 1번째 수 만큼 증가하고, D - 1번째 수는 tmp이므로,
# temp가 K보다 작은 경우에는 temp에 tmp값을 더해준다.
# temp가 K보다 커지는 경우에는 first를 1 증가시키고, second를 first값으로 초기화 한 후, 위와 같이 tmp만큼 계속해서
# 증가시켜 주고, temp가 K와 같아지는 경우의 first, second가 답이 된다.
while(temp != K) :
    if temp < K :
        temp += tmp
        second += 1
    elif temp > K :
        first += 1
        second = first
        temp = t * idx
        idx += 1
print(first)
print(second)


