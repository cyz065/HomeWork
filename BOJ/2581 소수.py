import math

M = int(input());
N = int(input());
count = 0; prime_number = list();
sum_result = 0;

for i in range(M, N + 1) :
    num = i;
    end = int(math.sqrt(num));
    
    for j in range(1, num + 1) :
        if(num % j == 0) :
            count += 1;
    if(count == 2) :
        prime_number.append(num);
    count = 0;

for i in prime_number :
    sum_result += i;

if(len(prime_number) > 0) :
    print(sum_result);
    print(prime_number[0]);
else :
    print(-1);


# 에라토스체네스의 체...?
        


        
        






        
   


