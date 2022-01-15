import sys

A, B = map(int, sys.stdin.readline().split())
cnt = 1; b = list(); tmp = 0;
tmp = str(B)
tmp = tmp[-1]

if(tmp == '3' or tmp == '5' or tmp == '7' or tmp == '9') :
    print(-1)
else :
    while(A < B) :
        if(B % 2 == 0) :
            B //= 2
            cnt += 1
        else :
            tmp = str(B)
            tmp = tmp[-1]
            if(tmp == '1') :
                for i in str(B) :
                    b.append(i)
                b.pop()
                B = ''.join(map(str,b))
                B = int(B)
                b.clear()
                cnt += 1
            else :
                break
    if(A == B) :
        print(cnt)
    else :
        print(-1)

'''
import sys
A, B = map(int, sys.stdin.readline().split());
b = list();

for i in str(B) :
    b.append(i);

B = ''.join(map(str, b));
print(B);
'''
