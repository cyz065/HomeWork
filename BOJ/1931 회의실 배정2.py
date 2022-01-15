'''
import sys;

N = int(input());
count = 0; maximum = 0;

table = list(); stack = list();

for i in range(N) :
    time = list(map(int, sys.stdin.readline().split()));
    table.append(time);
    
table.sort();

for i in range(len(table)) :
    stack.append(table[i]);
    index = i + 1;
    
    while(index <= len(table) - 1) :
        if(table[i][1] <= table[index][0]) :
            stack.append(table[index]);
            index = table.index(stack[len(stack) - 1]);
            index2 = index;
            break;
        index += 1;

    while(index <= len(table) - 1) :
        idx = table.index(stack[len(stack) - 1]);
        idx2 = idx + 1;
        while(idx2 <= len(table) - 1) :
            if(table[idx][1] <= table[idx2][0]) :
                stack.append(table[idx2]);
                break;
            idx2 += 1;
        index += 1;
    
    count = len(stack);
    if(maximum <= count) :
        maximum = count;
    print(stack);
    stack.clear();  
print(maximum);
'''
import sys;

N = int(input());
count = 0; maximum = 0;

meeting = list(); table = list(); stack = list();
tmp = list();
first = 0; second = 1;

for i in range(N) :
    time = list(map(int, sys.stdin.readline().split()));
    table.append(time);
    
table.sort();

for i in range(len(table)) :
    stack.append(table[i]);
    index = i + 1;
    
    while(index <= len(table) - 1) :
        if(table[i][1] <= table[index][0]) :
            tmp.append(table[index]);
            index = table.index(tmp[0]) + 1;
            stack.append(tmp[0]);
            break;
        index += 1;

    while(len(tmp) > 0 and index <= len(table) - 1) :
        if(len(tmp) > 0) :
            idx = table.index(stack[len(stack) - 1]);
            idx2 = idx + 1;
            while(idx2 <= len(table) - 1) :
                if(table[idx][1] <= table[idx2][0]) :
                    stack.append(table[idx2]);
                    break;
                idx2 += 1;
            index += 1;
    
    count = len(stack);
    if(maximum <= count) :
        maximum = count;
    print(stack);
    stack.clear();  
    tmp.clear();
print(maximum);
