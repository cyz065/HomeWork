from collections import deque;
import sys;

dq = deque();
bracket = sys.stdin.readline().split();
start = 0; l_bracket = 0; r_bracket = 0; count = 0;
iron = list();

while(start < len(bracket) - 1) :
    end = start + 1;
    while(True) :
        if bracket[start] == '(' :
            l_bracket += 1;
        elif bracket[start] == ')' :
            r_bracket += 1;
        if l_bracket > 1 and r_bracket > 1 and l_bracket == r_bracket :
            iron = bracket[start:];
            break;
        start += 1;

print(iron);



    
        
