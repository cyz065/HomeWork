import sys
from collections import deque

N = int(sys.stdin.readline())
sequence = list(); stack = list();
sequence = [int(sys.stdin.readline()) for x in range(N)]
sequence.sort()
sequence = deque(sequence)

# 수열의 element가 1개일 때는 그대로 출력
if(len(sequence) == 1) :
        print(sequence[0])
# 수열의 element의 개수가 짝수일 경우에는 2개씩 짝이 생기므로, 2개씩 묶은후에 결과를 stack에 저장
elif(len(sequence) % 2 == 0) :
        while(len(sequence) > 0) :
                num1 = sequence.pop()
                num2 = sequence.pop()
                if(num1 * num2 > num1 + num2) :
                        stack.append(num1 * num2)
                else :
                        stack.append(num1 + num2)
        print(sum(stack))
# 수열의 element의 개수가 홀수인 경우 중간값(양수 0 음수)에 따라서 결과가 달라지기 때문에 양끝부터 연산 후 stack에 저장
else :
        # 양수인 경우
        while(len(sequence) >= 2 and sequence[-1] > 0 and sequence[-2] > 0) :
                num1 = sequence.pop()
                num2 = sequence.pop()
                if(num1 * num2 > num1 + num2) :
                        stack.append(num1 * num2);
                else :
                        stack.append(num1 + num2);
        # 음수인 경우
        while(len(sequence) >= 2 and sequence[0] < 0 and sequence[1] < 0) :
                num1 = sequence.popleft();
                num2 = sequence.popleft();
                stack.append(num1 * num2);
        # 음수, 양수 -> 짝수 and 0이 1개 | 음수, 양수 둘중에 하나가 홀수개인 경우
        if(len(sequence) == 1) :
                stack.append(sequence[0])
                print(sum(stack))
        # 음수 1개, 양수 1개, 0 이 있는 경우
        if(len(sequence) == 3) :
                tmp = sequence[0] * sequence[1] + sequence[2];
                stack.append(tmp);
                print(sum(stack));
        # 0이 여러개 있는 경우
        else :
                # 0의 개수를 1개로
                sequence_set = list(set(sequence));
                sequence_set.sort();
                # 음수, 양수 둘중에 1개가 홀수개인 경우
                if(len(sequence_set) == 2) :
                        if(sequence_set[0] * sequence_set[1] > sequence_set[0] + sequence_set[1]) :
                                stack.append(sequence_set[0] * sequence_set[1]);
                        else :
                                stack.append(sequence_set[0] + sequence_set[1]);
                        print(sum(stack));
                # 음수, 양수가 홀수개 있는 경우
                if(len(sequence_set) == 3) :
                        tmp = sequence_set[0] * sequence[1] + sequence_set[2];
                        stack.append(tmp);
                        print(sum(stack));
                
        

