from collections import deque;
import sys;

queue = deque();
rotation = list();
N, K = map(int, sys.stdin.readline().split());

'''
for i in range(1, N + 1) :
    queue.append(i);
'''   
queue = deque(range(1, N + 1));

for i in range(len(queue)) :
    queue.rotate(-K + 1);
    rotation.append(queue.popleft());

print('<' + ', '.join(map(str, rotation)) + '>');

#print(''.join(map(str, rotation)));

#a = [1, 2, 3, 4, 5];
#print('<'.join(map(str, a)));
# 새로운 type의 출력
# join 함수 -> list를 문자열의 형태로 출력하기 위해 사용하는 함수
# list를 출력할 때 join함수 앞에 있는 문자를 삽입해서 출력해 준다.
# ex) a = [1, 2, 3, 4, 5] print('<'.join(map(str, a)));
# -> 1<2<3<4<5
'''
print("<", end = "");
for i in range(len(sequence) - 1) :
    print(sequence[i], end = ", ");
print(sequence[-1], end = "");
print(">");
'''
