'''
import sys
import math

T = int(sys.stdin.readline())

for i in range(T) :
    num = list(sys.stdin.readline().strip())
    num = num[2::]
    x = "";
    # 괄호가 없는 경우는 유한소수 이므로 소수점 자리수 만큼 10의 제곱수가 분모가 된다.
    if '(' not in num :
        y = 10 ** len(num)
        x = ''.join(map(str, num))
        x = int(x)
        t = math.gcd(x, y)
        x //= t; y //= t
        print("%d/%d" %(x, y))
    # t = 소수점 아래 모든 수, temp = 괄호 전의 모든수 (분자 구하기)
    # 분자는 소수점 아래 모든 수에서 괄호 전의 모든 수를 빼준다.
    # ex) 0.6(142857) -> 분자 : 6142857 - 6
    else :
        y = ''; temp = ''; cnt = 0; idx = 0
        while(idx < len(num)) :
            # 분자 구하기
            while(num[idx] != '(') :
                temp += num[idx]
                x += num[idx]
                cnt += 1
                idx += 1
            if num[idx] == "(" :
                idx += 1
                # 괄호 안에 있는 숫자를 더해서 분자를 구해주고, y에 9를 더해서 분모를 구한다.
                while(num[idx] != ')') :
                    y += '9'
                    x += num[idx]
                    idx += 1
            idx += 1
        y += '0' * cnt
        if temp == "" :
            temp = 0
        x = int(x) - int(temp)
        y = int(y)
        t = math.gcd(x, y)
        x //= t; y //= t;
        print("%d/%d" %(x, y))
'''
import sys
import math

T = int(sys.stdin.readline())

for i in range(T) :
    num = list(sys.stdin.readline().strip())
    num = num[2::]
    x = ""; idx = 0
    
    if '(' not in num :
        y = 10 ** len(num)
        x = ''.join(map(str, num))
        x = int(x)
        t = math.gcd(x, y)
        x //= t; y //= t
        print("%d/%d" %(x, y))

    else :
        tmp = ""; y = ""
        while(idx < len(num)) :
            if num[idx] == '(' :
                idx = num.index('(')
                x = num[idx + 1: len(num) - 1]
                break
            else :
                idx = num.index('(')
                tmp = num[0:idx]
        y += '9' * len(x) + '0' * len(tmp)
        x = ''.join(map(str, x))
        tmp = ''.join(map(str, tmp))
        x = tmp + x;
        if tmp == "" :
            tmp = 0
        x = int(x) - int(tmp)
        y = int(y)
        t = math.gcd(x, y)
        x //= t; y //= t;
        print("%d/%d" %(x, y))
