import sys;

N = int(input());
table = list(); count_arr = list();
index = 0; count = 0;

for i in range(N) :
    schedule = list(map(int, sys.stdin.readline().split()));
    table.append(schedule);

for i in range(len(table)) :
    count += table[i][1];
    index = i;

    index += table[index][0];
    idx = index;

    while(idx < len(table)) :
        idx2 = idx;
        while(idx2 + table[idx2][0] <= len(table)) :
            count += table[idx2][1];
            idx2 += table[idx2][0];
            if(idx2 >= len(table)) :
                idx2 = idx + 1;
                break;
        count_arr.append(count);
        count = table[i][1];
        idx += 1;
    count = 0;
print(count_arr);
print(max(count_arr));
        
'''
import sys;

N = int(input());
table = list(); count_arr = list();
index = 0; count = 0;

for i in range(N) :
    schedule = list(map(int, sys.stdin.readline().split()));
    table.append(schedule);

for i in range(len(table)) :
    count += table[i][1];
    index = i;

    index += table[index][0];
    idx = index;

    while(idx < len(table)) :
        idx2 = idx;
        while(idx2 + table[idx2][0] <= len(table)) :
            count += table[idx2][1];
            idx2 += table[idx2][0];
            if(idx2 >= len(table)) :
                break;
        count_arr.append(count);
        count = table[i][1];
        idx += 1;
    count = 0;
print(count_arr);
print(max(count_arr));
'''
'''
import sys;

N = int(input());
table = list(); count_arr = list();
index = 0; count = 0;

for i in range(N) :
    schedule = list(map(int, sys.stdin.readline().split()));
    table.append(schedule);

for i in range(len(table)) :
    count += table[i][1];
    index = i;

    while(index + table[index][0] < len(table)) :
        index += table[index][0];
        idx = index;

        while(idx < len(table)) :
            idx2 = idx;
            while(idx2 + table[idx2][0] < len(table)) :
                count += table[idx2][1];
                idx2 += table[idx2][0];
                '''
'''
                if(idx2 + table[idx2][0] < len(table)) :
                    #count += table[idx2][1];
                    idx2 += table[idx2][0];
                '''
'''
            count_arr.append(count);
            count = table[i][1]
            idx += 1;
print(count_arr);
'''



'''
import sys;

def top(stack) :
    return stack[len(stack) - 1];

N = int(input());
table = list(); stack = list();
maximum = 0; length = 0; index = 0; result = 0;

for i in range(N) :
    schedule = list(map(int, sys.stdin.readline().split()));
    table.append(schedule);

for i in range(len(table)) :
    stack.append(table[i]);
    if(i + table[i][0] > len(table)) :
        stack.pop();
    else :
        tmp = top(stack);
        index = tmp[0];
    if(index < i) :
        index = i + table[i][0];
    length += index;

    while(length <= len(table) - 1) :
        if(index + table[index][0] > len(table) - 1) :
            break;
        stack.append(table[index]);
        tmp = top(stack);
        index = index + tmp[0];
        length += tmp[0];

    length = 0;

    if(len(stack) > 0) :
        for i in stack :
            result += i[1];
        if(maximum <= result) :
            maximum = result;
    result = 0;
    print(stack);
    stack.clear();
print(maximum);
'''    
        
        

    
