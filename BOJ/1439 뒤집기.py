import sys;

S = list(map(int, sys.stdin.readline().strip()));
count_zero = 0; count_one = 0;
idx = 0; check = True;

while (idx < len(S)) :
    if S[idx] == 1 :
        while (S[idx] == 1) :
            idx += 1;
            if idx >= len(S) :
                count_one += 1;
                check = False;
                break;
        if check == False :
            break;
        count_one += 1;
    idx += 1;

idx = 0;
check = True;

while (idx < len(S)) :
    if S[idx] == 0 :
        while (S[idx] == 0) :
            idx += 1;
            if idx >= len(S) :
                count_zero += 1;
                check = False;
                break;
        if check == False :
            break;
        count_zero += 1;
    idx += 1;

if count_zero > count_one :
    print(count_one);
else :
    print(count_zero);
