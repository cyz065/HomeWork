A, B, C = input().split();
A, B, C = int(A), int(B), int(C);

if(B >= C) :
    print(-1);
    
else :
    count = A // (C-B);
    print(count + 1);


# 부등식의 활용
# print 개행없이 입력 -> input().split();
# split()함수
# -> separator를 기준으로 하나의 문자열을 작은 문자열 List로 나누기 위한 함수
# ex) string = "A. B. C" / string.split('.');
# -> [A, B, C]
# split()함수에 separator를 지정하지 않으면 공백문자(줄바꿈, space, tab)를 기준으로 한다.

