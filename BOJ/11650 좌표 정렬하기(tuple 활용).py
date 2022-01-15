import sys;

N = int(sys.stdin.readline());
point = list();

for i in range(N) :
    x, y = map(int, sys.stdin.readline().split());
    point.append((x, y)); # (x, y) 튜플이 list에 append

ordered_point = sorted(point, key = lambda x : (x[0], x[1]));

for i in ordered_point :
    print(i[0], i[1], sep = ' ');
    
    

# list안에 list를 추가하는 경우 list자료형대신 tuple자료형을 append하자.
# tuple이 list보다 메모리를 적게 차지한다.
# 참고 : https://www.educative.io/edpresso/tuples-vs-list-in-python
