import sys
N, L = map(int, sys.stdin.readline().split());
location = list(map(int, sys.stdin.readline().split()));

tape = N;
start = 0; end = 1; diff = 0;
location.sort();

if N == 1 :
    print(tape)
else :
    while(end < N) :
        while(location[end] - location[start] + 1 <= L) :
            diff = location[end] - location[start] + 1
            end += 1
            tape -= 1
            if end >= N :
                break
        start = end
        end += 1
    print(tape)



'''
import sys;

N, L = map(int,sys.stdin.readline().split());
location = list(map(int, sys.stdin.readline().split()));
i = 0; idx = 1;
tape = N;
location.sort();

if(tape == 1) :
    print(tape);
else :
    while(idx < N) :
        diff = location[idx] - location[i] + 1;
        if(diff == L) :
            idx += 1;
            tape -= 1;
        while(diff <= L) :
            diff = location[idx] - location[i] + 1;
            if(diff < L) :
                print("i : ", i, "idx : ", idx, end = " ");
                idx += 1;
                tape -= 1;
            if(diff == L) :
                print("Apple");
                tape -= 1;
                i = idx;
                break;
            else :
                i = idx;
                break;
        i = idx;
        idx += 1;
    print(tape);
'''
   

