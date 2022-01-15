import sys

N, K = map(int, sys.stdin.readline().split());
idx = 0; count = 0; coin = list();

coin = [int(sys.stdin.readline()) for x in range(N)];
coin.sort(reverse = True);

while(K != 0) :
    while(idx < N) :
        if(coin[idx] <= K) :
            c = coin[idx];
            break;
        idx += 1;
    count += K // c;
    K %= c;
print(count);
