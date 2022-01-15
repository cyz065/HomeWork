'''
import sys;

def push(stack, word) :
    stack.append(word);
    
def top(stack) :
    if(len(stack) == 0) :
        return False;
    else :
        index = len(stack) - 1;
        return stack[index];
    
def deque(stack) :
    return stack.pop(0);

def head(stack) :
    return stack[0];

def isEmpty(stack) :
    if(len(stack) == 0) :
        return True;
    else :
        return False;
    
T = int(input());
string = list();
queue = list();
stack = list();

for i in range(T) :
    text = sys.stdin.readline().strip();
    string = list(text);

    for j in range(len(string)) :
        word = deque(string);
        queue.append(word);
    
    while(True) :
        while(head(queue) != ')') :
            word = deque(queue);
            push(stack, word);
            if(len(queue) <= 0) :
                break;
        if(len(queue) <= 0) :
            break;
          
        if(head(queue) == ')') :
            word = deque(queue);
            if(isEmpty(stack) == False and head(stack) == '(') :
                stack.pop();
            elif(isEmpty(stack) == True) :
                push(stack, word);
        if(len(queue) <= 0) :
            break;

    if(isEmpty(stack) == True) :
            print("YES");
    else :
        print("NO");
    stack.clear();
    queue.clear();
'''
'''
import sys;

def push(stack, word) :
    stack.append(word);

def pop(stack) :
    stack.pop();
    
def deque(queue) :
    return queue.pop(0);

def front(queue) :
    return queue[0];

def rear(queue) :
    length = len(queue);
    return queue[length - 1];

def isEmpty(stack) :
    if(len(stack) == 0) :
        return True;
    else :
        return False;
    
T = int(input());
string = list();
queue = list();
stack = list();

for i in range(T) :
    text = sys.stdin.readline().strip();
    string = list(text);

    for j in range(len(string)) :
        word = deque(string);
        queue.append(word);
    
    while(True) :
        while(len(queue) >= 1 and front(queue) != ')') :
            word = deque(queue);
            push(stack, word);

        if(len(queue) <= 0) :
            break;
          
        if(front(queue) == ')') :
            word = deque(queue);
            if(isEmpty(stack) == False and front(stack) == '(') :
                stack.pop();
            elif(isEmpty(stack) == True) :
                push(stack, word);

    if(isEmpty(stack) == True) :
            print("YES");
    else :
        print("NO");
    stack.clear();
    queue.clear();
'''    
# Final)
import sys;

def push(stack, word) :
    stack.append(word);

def pop(stack) :
    if(len(stack) <= 0) :
        return -1;
    
    return stack.pop();

def isEmpty(stack) :
    if(len(stack) == 0) :
        return True;
    else :
        return False;
    
def top(stack) :
    length = len(stack);
    if(length == 0) :
        return -1;
    
    return stack[length - 1];
    
T = int(input());
string = list();
stack_string = list();
stack_check = list();

for i in range(T) :
    text = sys.stdin.readline().strip();
    string = list(text);

    for j in range(len(string)) :
        word = pop(string);
        stack_string.append(word);
    
    while(True) :
        while(len(stack_string) >= 1 and top(stack_string) != ')') :
            word = pop(stack_string);
            push(stack_check, word);

        if(len(stack_string) <= 0) :
            break;
          
        if(top(stack_string) == ')') :
            word = pop(stack_string);
            if(isEmpty(stack_check) == False and top(stack_check) == '(') :
                stack_check.pop();
            elif(isEmpty(stack_check) == True) :
                push(stack_check, word);

    if(isEmpty(stack_check) == True) :
            print("YES");
    else :
        print("NO");
    stack_check.clear();
    stack_string.clear();

# 다양한 Stack 연산
# Stack & Queue의 활용
# ref) Stack을 이용한 Postfix 계산...

