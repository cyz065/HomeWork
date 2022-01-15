import sys;

T = int(sys.stdin.readline());
pattern = list(); idx = 0; cnt = 0; boolean = 1; check = True; num = 1;
for i in range(T) :
    A, B, L = map(int, sys.stdin.readline().split());
    p = sys.stdin.readline().strip();
    for i in p :
        pattern.append(i);
    a = [int(x) for x in str(A)];
    b = [int(x) for x in str(B)];

    if(len(a) > len(b)) :
        while(len(a) > len(b)) :
            b.insert(0, 0);
    else :
        while(len(a) < len(b)) :
            a.insert(0, 0);
            
    while(A != B and idx < len(a)) :
        if(a[idx] == b[idx]) :
            idx += 1;
            continue;
        if(a[idx] > b[idx]) and (pattern[0] == '-' or pattern[-1] == '-') :
            if(pattern[-1] == '-') :
                pattern = pattern[::-1];
            for i in pattern :
                if(i == '-') :
                    if(a[idx] >= 1) :
                        a[idx] -= 1;
                    elif(a[idx] < 1) :
                        check = False;
                        boolean = 0;
                        break;
                elif(i == '+') :
                    if(a[idx] <= 9) :
                        a[idx] += 1;
                    elif(a[idx] > 9) :
                        check = False;
                        boolean = 0;
                        break;
                idx += 1;
            if(check == False) :
                print('#%d' %num, -1);
                break;
            cnt += 1;
            idx = 0;
            
        if(a[idx] < b[idx]) and (pattern[0] == '+' or pattern[-1] == '+') :
            if(pattern[-1] == '+') :
                pattern = pattern[::-1];
            for i in pattern :
                if(i == '-') :
                    if(a[idx] >= 1) :
                        a[idx] -= 1;
                    elif(a[idx] < 1) :
                        check = False;
                        boolean = 0;
                        break;
                elif(i == '+') :
                    if(a[idx] <= 9) :
                        a[idx] += 1;
                    elif(a[idx] > 9) :
                        check = False;
                        boolean = 0;
                        break;
                idx += 1;
            if(check == False) :
                print('#%d' %num, -1);
                break;
            cnt += 1;
            idx = 0;
        if(a[0] > b[0] and '-' not in pattern) :
            boolean = 0;
            print('#%d' %num, -1);
            break;
        elif(a[0] < b[0] and '+' not in pattern) :
            boolean = 0;
            print('#%d' %num, -1);
            break;

    pattern.clear();
    idx = 0;
    if(boolean != 0) :
        print('#%d' %num, cnt);
    cnt = 0;
    boolean = 1;
    check = True;
    num += 1;

        
'''
import sys;

T = int(sys.stdin.readline());
pattern = list(); idx = 0; cnt = 0;
for i in range(T) :
    A, B, L = map(int, sys.stdin.readline().split());
    p = sys.stdin.readline().strip();
    for i in p :
        pattern.append(i); 
    A = str(A); B = str(B);

    if int(A) < int(B) :
        A = A.zfill(len(B));
    else :
        B = B.zfill(len(A));

    while(A != B) :
        if int(A) > int(B) :
            
'''

        
        
                
        
    

    


    

    

    

    

    


        
