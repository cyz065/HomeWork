'''
# Sol 1)
def number(n) :
    num = list();
    cnt = 0;
    
    for i in range(1, n+1) :
        if(i >= 100) :
            tmp = i;
            while(tmp != 0) :
                num.append(tmp % 10);
                tmp //= 10;
            num = num[::-1];

            if((num[0] + num[2]) == num[1] * 2) :
                cnt += 1;
            num.clear();
        else :
            cnt += 1;
    return cnt;
'''
'''
# Sol 2)
def number(n) :
    num = list();
    check = list();
    cnt = 0;
    
    for i in range(1, n+1) :
        if(i >= 100) :
            tmp = i;
            tmp2 = i;
            while(tmp != 0) :
                num.append(tmp % 10);       
                tmp //= 10;
            num = num[::-1];

            for i in range(len(num) - 2) :
                if(num[i] - num[i + 1] == num[i + 1] - num[i + 2]) :
                    check.append(True);
            if(len(check) == (len(num) - 2)) :
                    cnt += 1;
            check.clear();
            num.clear();
        else :
            cnt += 1;
    return cnt;
'''
# Sol 3)
def number(n) :
    num = list();
    check = list();
    cnt = 0;
    
    for i in range(1, n+1) :
        if(i >= 100) :
            tmp = i;
            tmp2 = i;
            while(tmp != 0) :
                num.append(tmp % 10);       
                tmp //= 10;
            num = num[::-1];
            difference = num[0] - num[1];
            
            for i in range(len(num) - 2) :
                if not (num[i+1] - num[i+2] == difference) :
                    break;
                else :
                    check.append(True);
            if(all(check) & len(check) == len(num) - 2) :
                    cnt += 1;
            check.clear();
            num.clear();
        else :
            cnt += 1;
    return cnt;
            
'''
    for i in range(1, n+1) :
        if(len(str(i)) == 1) :
            cnt += 1;
        elif(len(str(i)) == 2) :
            cnt += 1;
        else :
            

            
            tmp = i;
            for j in range(len(str(i))) :
                num1 = tmp // 10 ** (len(str(tmp)) - 1);
                print("num1 : ", num1);
                num.append(num1);
                tmp = tmp % 10 ** (len(str(tmp)) - 1);

            num.clear();
'''

                #for k in range(len(num) - 3) :
                 #   if(((num[k] + num[k+2]) // 2) == num[k+1]) :
                  #      cnt += 1;
            #num.clear();
    #return cnt;

N = int(input());
print(number(N));

# 파이썬 each digit in number (각각의 자리수 구하기)
# python arithmetic sequence(등차수열의 비교)
# python comprehension ( List, tuple 등등)

          

        
        
        
