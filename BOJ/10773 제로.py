'''
import sys;

def top(stack) :
    length = len(stack);
    return stack[length - 1];

def push(stack, word) :
    stack.append(word);

def pop(stack) :
    stack.pop();

def isEmpty(stack) :
    if(len(stack) != 0) :
        return False;
    else :
        return True;

K = int(input());
stack = list();
result = 0;

for i in range(K) :
    num = int(sys.stdin.readline());

    if(num > 0) :
        push(stack, num);
    elif(num == 0 and isEmpty(stack) == False) :
        pop(stack);

for i in stack :
    result += i;

print(result);
'''
import sys;

K = int(input());
number = list();
result = 0;

for i in range(K) :
    num = int(sys.stdin.readline());

    if(num > 0) :
        number.append(num);
    elif(num == 0 and len(number) != 0) :
        number.pop();

for i in number :
    result += i;
    
print(result);
