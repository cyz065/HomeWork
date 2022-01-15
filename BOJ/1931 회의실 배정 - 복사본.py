import sys;
   
N = int(input());
count = 0; maximum = 0;

meeting = list(); table = list(); tmp = list();
front = list(); rear = list();

for i in range(N) :
    time = list(map(int, sys.stdin.readline().split()));
    table.append(time);
    
table.sort();

for i in range(len(table)) :
    front.append(table[i][0]);
    rear.append(table[i][1]);

for i in range(len(table)) :
    meeting.append(table[i]);
    index = i + 1;

    while(index <= len(table) - 1) :
        if(rear[i] <= front[index]) :
            tmp.append(table[index]);
            index = table.index(tmp[0]) + 1;
            meeting.append(tmp[0]);
            break;
        index += 1;

    while(len(tmp) > 0 and index <= len(table) - 1) :
        idx = table.index(meeting[len(meeting) - 1]);
        idx2 = idx + 1;
        while(idx2 <= len(table) - 1) :
            if(rear[idx] <= front[idx2]) :
                meeting.append(table[idx2]);
                break;
            idx2 += 1;
        index += 1;

    count = len(meeting);
    if(maximum <= count) :
        maximum = count;
    meeting.clear();  
    tmp.clear();
print(maximum);

    
'''    
for i in range(len(table)) :
    stack.append(table[i]);
    index = i + 1;
    while(index <= 10) :
        if(table[i][1] <= table[index][first]) :
            tmp.append(table[index]);
        index += 1;

    if(len(tmp) > 0) :
        stack.append(tmp[0]);
        index = table.index(tmp[0]);
    print(stack);
    stack.clear();
        

    
    tmp.clear();
'''
    
            
'''
for i in table :
    stack.append(i);
    for j in range(1, len(table)) :
        if(i[1] <= table[j][0]) :
            tmp.append(table[j]);
    for k in tmp :
        
'''
    

    
        
    
    
