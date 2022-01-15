from collections import deque;
import sys;

dq = deque();
N = int(sys.stdin.readline());

for i in range(N) :
    cmd = sys.stdin.readline();

    if "push_front" in cmd :
        dq.appendleft(cmd.split()[1]);
    elif "push_back" in cmd :
        dq.append(cmd.split()[1]);
    elif "pop_front" in cmd :
        print(dq.popleft() if dq else -1);
    elif "pop_back" in cmd :
        print(dq.pop() if dq else -1);
    elif "size" in cmd :
        print(len(dq));
    elif "empty" in cmd :
        print(0 if dq else 1);
    elif "front" in cmd :
        print(dq[0] if dq else -1);
    else :
        print(dq[-1] if dq else -1);
    
        
