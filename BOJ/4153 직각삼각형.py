import sys

while(True) :
    length = list(map(int, sys.stdin.readline().split()))

    if length == [0, 0, 0] :
        break
    else :
        length.sort();
        A = length[0]
        B = length[1]
        C = length[2]
        if C * C == A * A + B * B :
            print("right")
        else :
            print("wrong")
