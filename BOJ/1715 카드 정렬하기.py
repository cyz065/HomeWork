'''
import sys
from collections import deque

N = int(sys.stdin.readline())
card = list(); stack = list()
card = [int(sys.stdin.readline()) for x in range(N)]
card.sort()
card = deque(card)
if(len(card) == 1) :
	print(card[0])
else :
	while(len(card) > 0) :
		num1 = card.popleft()
		num2 = card.popleft()
		stack.append(num1 + num2)
		if(len(card) != 0) :
			card.append(stack[-1])
			card = list(card)
			card.sort()
			card = deque(card)
	print(sum(stack))
'''

import sys
import heapq

N = int(sys.stdin.readline());
card = []; cnt = 0;

for i in range(N) :
    tmp = int(sys.stdin.readline());
    heapq.heappush(card, tmp);

while(len(card) > 1) :
    num1 = heapq.heappop(card);
    num2 = heapq.heappop(card);
    heapq.heappush(card, num1 + num2);
    cnt += num1 + num2;
print(cnt);
    
