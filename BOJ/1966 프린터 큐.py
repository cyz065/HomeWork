import sys;

def enqueue(queue, num) :
    queue.append(num);

def dequeue(queue) :
    length = len(queue);
    if(length <= 0) :
        return False;
    else :
        return queue.pop(0);
    
def size(queue) :
    return len(queue);

def empty(queue) :
    if(len(queue) <= 0) :
        return True;
    else :
        return False;

def head(queue) :
    if(len(queue) > 0) :
        return queue[0];
    else :
        return False;

def tail(queue) :
    length = len(queue);
    if(length > 0) :
        return queue[length - 1];
    else :
        return False;

test_case = int(input());
priority_array = list(); # 우선순위 저장 배열
boolean = list(); # T, F 저장 priority와 same
boolean_array = list(); # 조건에 따라 배열한 priority의 T, F 순서를 따라가기 위한 배열

for i in range(test_case) :
    N, M = map(int,input().split());
    priority = list(map(int, sys.stdin.readline().split()));
    
    for i in range(len(priority)) :
        boolean.append(False);
        
    boolean[M] = True;
    
    while(len(priority) != 0) :
        while(max(priority) != head(priority)) :
            word = dequeue(priority);
            check = dequeue(boolean);
            enqueue(priority, word);
            enqueue(boolean, check);

        priority_number = dequeue(priority);
        boolean_alphabet = dequeue(boolean);
        priority_array.append(priority_number);
        boolean_array.append(boolean_alphabet);

    result = priority_array + boolean_array;

    for i in range(len(boolean_array)) :
        if(boolean_array[i] == True) :
            print(i + 1);

    priority_array.clear();
    boolean.clear();
    boolean_array.clear();
