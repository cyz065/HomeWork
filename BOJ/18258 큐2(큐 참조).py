'''
from collections import deque;
import sys;

queue = deque();
N = int(input());

for i in range(N) :
    cmd = sys.stdin.readline().split();
    
    if "push" in cmd :
        queue.append(cmd[1]);
        
    elif "front" in cmd :    
        if len(queue) == 0 :
            print(-1);
        else :
            print(queue[0]);
        
    elif "pop" in cmd :
        if len(queue) == 0 :
            print(-1);
        else :
            print(queue.popleft());
            
    elif "size" in cmd :
        print(len(queue));
        
    elif "empty" in cmd :
        if len(queue) == 0 :
            print(1);
        else :
            print(0);
        
    elif "back" in cmd :
        if len(queue) == 0 :
            print(-1);
        else :
            print(queue[-1]);
'''
from collections import deque;
import sys;

queue = deque();
N = int(sys.stdin.readline());

for i in range(N) :
    cmd = sys.stdin.readline()
    if "push" in cmd :
        queue.append(cmd.split()[1]);
        
    elif "front" in cmd :
        print(queue[0] if len(queue) else -1);
        
    elif "pop" in cmd :
        print(queue.popleft() if len(queue) else -1);
        
    elif "size" in cmd :
        print(len(queue));
        
    elif "empty" in cmd :
        print(0 if len(queue) else 1);
    else :
        print(queue[-1] if len(queue) else -1);

# Wow...
# split()[1]...


