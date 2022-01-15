import sys;

N = int(sys.stdin.readline());
count = 0; idx = 9; length = len(str(N));

for i in range(1, length) :
    count += idx * i;
    idx *= 10;

count += (N - 10 ** (length - 1) + 1) * length;
print(count);
