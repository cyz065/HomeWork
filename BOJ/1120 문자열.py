import sys;

A, B = sys.stdin.readline().split();
diff = 0; idx = 0; difference = list(); boolean = 1;

if len(A) == len(B) :
    for i in range(len(A)) :
        if(A[i] != B[i]) :
            diff += 1;
    print(diff);
    
else :
    while(idx + len(A) <= len(B)) :
        string = B[idx : len(A) + idx];
        for i in range(len(A)) :
            if(A[i] != string[i]) :
                diff += 1;
        if(diff == 0) :
            print(0);
            boolean = 0;
            break;
        difference.append(diff);
        diff = 0;
        idx += 1;

    if(boolean != 0) :
        print(min(difference));



    





        
    
    
    
