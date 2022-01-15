'''
N = int(input());
number = list(map(int, input().split()));
count = 0;

for i in number :
    num = 2;
    while(i >= num) :
        if(i % num == 0) :
            if(i == num) :
                count += 1;
            else :
                break;
        num += 1;
print(count);
'''

N = int(input())
k = list(map(int, input().split()))


k.sort()
count = 0
for i in range(N):
    if k[i] == 1 or k[i] == 0:
        count += 1
        continue
    for j in range(2, (k[i]//2)+1):
        if k[i]%j == 0:
            #소수가 아니면 카운트 하나올리고 
            #print("소수아님", k[i])
            count += 1
            break

print(N-count) 


        
        






        
   


