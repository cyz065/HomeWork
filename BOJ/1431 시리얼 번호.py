import sys
N = int(sys.stdin.readline());
serial = list(); number = 0
num = "0123456789"


for i in range(N) :
    tmp = sys.stdin.readline().strip();
    for j in tmp :
        if(j in num) :
            number += int(j)
    serial.append((tmp, number))
    number = 0;

serial = sorted(serial, key = lambda x : (len(x[0]), x[1], x[0]))
for name, cnt in serial :
    print(name);

