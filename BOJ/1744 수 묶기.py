import sys
from collections import deque

N = int(sys.stdin.readline())
sequence = list(); stack = list()

for i in range(N) :
	num = int(sys.stdin.readline())
	sequence.append(num)
sequence.sort()
sequence = deque(sequence)
if(len(sequence) == 1) :
    print(sequence[0])
    
elif(len(sequence) % 2 == 0) :
    while(len(sequence) > 0) :
        num1 = sequence.pop();
        num2 = sequence.pop();
        if(num1 * num2 > num1 + num2) :
            stack.append(num1 * num2);
        else :
            stack.append(num1 + num2);
    if(len(sequence) == 0) :
        print(sum(stack));
else :
    while(len(sequence) >=2 and sequence[-1] > 0 and sequence[-2] > 0) :
        num1 = sequence.pop()
        num2 = sequence.pop()
        if(num1 * num2 > num1 + num2) :
            stack.append(num1 * num2)
        else :
            stack.append(num1 + num2)
    while(len(sequence) >= 2 and sequence[0] < 0 and sequence[1] < 0) :
        num1 = sequence.popleft()
        num2 = sequence.popleft()
        stack.append(num1 * num2)
    if(len(sequence) == 0) :
        print(sum(stack))
    elif(len(sequence) == 1) :
        stack.append(sequence[0])
        print(sum(stack))
    elif(len(sequence) == 3) :
        tmp = sequence[0] * sequence[1] + sequence[2]
        stack.append(tmp)
        print(sum(stack))
    else :
        sequence_set = list(set(sequence));
        sequence_set.sort();
        if(len(sequence_set) == 2) :
            if(sequence_set[0] + sequence_set[1] > sequence_set[0] * sequence_set[1]) :
                stack.append(sequence_set[0] + sequence_set[1]);
            else :
                stack.append(sequence_set[0] * sequence_set[1]);
            print(sum(stack))
        if(len(sequence_set) == 3) :
            tmp = sequence[0] * sequence[1] + sequence[2];
            stack.append(tmp);
            print(sum(stack));


