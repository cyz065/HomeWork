from collections import deque

card_queue = deque();
N = int(input());

for i in range(1, N + 1) :
    card_queue.append(i);

if(N == 1) :
    print(card_queue[0]);

while(len(card_queue) > 1) :
    card_queue.popleft();
    number = card_queue.popleft();
    card_queue.append(number);
    
    if(len(card_queue) == 1) :
        print(card_queue[0]);
        break;
