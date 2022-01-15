N = int(input());
people = [];

for i in range(N) :
    tmp = [];
    x, y = map(int, input().split());
    tmp.append(x);
    tmp.append(y);
    tmp.append(1);
    people.append(tmp);
    
for i in range(len(people) - 1) :
    for j in range(i+1, len(people)) :
        if(people[i][0] < people[j][0] and people[i][1] < people[j][1]) :
            people[i][2] += 1; # 뒤가 전부 크면 앞의 rank증가
        elif(people[i][0] > people[j][0] and people[i][1] > people[j][1]) :
            people[j][2] += 1; # 앞이 전부 크면 뒤의 rank 증가
            

for i in range(len(people)) :
    print(people[i][2], end = ' ');        

            

       
        
    
    
    


