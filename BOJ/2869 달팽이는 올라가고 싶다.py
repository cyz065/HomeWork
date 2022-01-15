# Sol 1)
A, B, V = input().split();
A, B, V = int(A), int(B), int(V);

day = (B - V) // (B - A);
day1 = (B - V) % (B - A);

if(day1 == 0) :
    print(day);
else :
    print(day + 1);

# Sol 2)
'''
import math;
A, B, V = input().split();
A, B, V = int(A), int(B), int(V);

day = (B - V) / (B - A);
print(math.ceil(day));
'''

# math 모듈
# ceil 올림함수
# 수식설계...
