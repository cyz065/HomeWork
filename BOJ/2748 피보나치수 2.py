import sys
a = 0; b = 1; result = 0;
n = int(sys.stdin.readline())

if n == 1 :
    print(b)
else :
    for i in range(n - 1) :
        result += b
        b += a
        a = result - b
    print(result)
