import sys
N = int(sys.stdin.readline());

n = 0; i = 0;

if N < 3 :
    print(-1);
    
elif N == 3 :
    print(1);
    
else :
    cnt = N // 5
    if 5 * cnt == N :
        print(cnt);
    elif cnt == 0 :
        print(-1);
    else :
        while(n != N) :
            temp = N - 5 * cnt;
            if temp % 3 == 0 :
                i = temp // 3;
                n = 5 * cnt + 3 * i;
                break;
            cnt -= 1;
            if cnt < 0 :
                break;
        if n == N :
            print(cnt + i);
        else :
            print(-1);
'''
import sys;

N = int(sys.stdin.readline());
i = 1; j = 1;

if(N < 3) :
        print(-1);
else :
        cnt = N // 5;
        tmp = N % 5;
        if(tmp == 0) :
                print(cnt);
        else :
                while(True) :
                        temp = 5 * (cnt - i);
                        N = N - temp;
                        cnt2 = N // 3;
                        tmp = N % 3;
                        if(tmp == 0) :
                                break;
                        i += 1;
                print(cnt - i + cnt2);
'''               
                
                
                
                
        
