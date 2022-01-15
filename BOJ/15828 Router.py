import sys
from collections import deque

router = deque()
waiting_list = list()

N = int(sys.stdin.readline())
while(True) :
    packet = int(sys.stdin.readline())
    if(packet == -1) :
        break
    else :
        if(packet == 0 and len(router) > 0) :
            router.popleft()
        elif(len(router) < N) :
            router.append(packet)

if(len(router) > 0) :
    for i in router :
        print(i, end = " ");
else :
    print("empty")
