import sys;

N, M = map(int, sys.stdin.readline().split());

hear = set(sys.stdin.readline().rstrip() for x in range(N));
see = set(sys.stdin.readline().rstrip() for x in range(M));
same = list(hear & see);

print(len(same));
same.sort();
for i in same :
    print(i);

