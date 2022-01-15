import sys;
set_list = list();

n, m = map(int, sys.stdin.readline().split());

for i in range(n + 1) :
    set_list.append(set(str(i)));

for i in range(m) :
    cmd, a, b = map(int, sys.stdin.readline().split());
    if(cmd == 0) :
        union = set_list[a] & set_list[b];
print(union);
