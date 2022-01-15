import sys
T = int(sys.stdin.readline())

for i in range(T) :
    N = int(sys.stdin.readline())
    note1 = set(map(int, sys.stdin.readline().split()))
    M = int(sys.stdin.readline())
    note2 = list(map(int, sys.stdin.readline().split()))

    note1.sort()
    for i in note2 :
        if i in note1 :
            print(1)
        else :
            print(0)

# list와 set의 time complexity
# set 자료형은 해시 테이블로 실행되기 때문에 in 연산에서
# 평균적으로 O(1)의 시간 복잡도를 가지고, 최악의 상황에서는 O(n)
# 시간 복잡도를 가진다.
# 반면 list는 평균적으로 O(n)의 시간 복잡도를 가지기 때문에
# 중복이 필요없고 빠른 in연산을 위해서는 set자료형을 사용하는 것이 좋다.
