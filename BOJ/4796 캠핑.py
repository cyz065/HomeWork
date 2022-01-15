import sys;
case = 1;

while(True) :
    L, P, V = map(int, sys.stdin.readline().split());
    if(L == 0 and P == 0 and V == 0) :
        break;
    day = (V // P) * L;
    if(V % P > L) :
        day += L;
    else :
        day += V % P;
    print("Case %d:" %case, day)
    case += 1;

        
        






        
   


