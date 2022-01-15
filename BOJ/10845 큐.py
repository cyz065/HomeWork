import sys;

def push(queue, num) :
    queue.append(num);

def pop(queue) :
    length = len(queue);
    if(length <= 0) :
        return -1;
    else :
        return queue.pop(0);

def size(queue) :
    return len(queue);

def empty(queue) :
    if(len(queue) <= 0) :
        return 1;
    else :
        return 0;

def front(queue) :
    if(len(queue) > 0) :
        return queue[0];
    else :
        return -1;

def back(queue) :
    length = len(queue);
    if(length > 0) :
        return queue[length - 1];
    else :
        return -1;

N = int(input());
queue = list();

for i in range(N) :
    command = sys.stdin.readline().strip();

    if(command.startswith("push")) :
        tmp = command.split();
        num = tmp[1];
        push(queue, num);
    elif(command == "front") :
        print(front(queue));
    elif(command == "back") :
        print(back(queue));
    elif(command == "size") :
        print(size(queue));
    elif(command == "empty") :
        print(empty(queue));
    elif(command == "pop") :
        print(pop(queue));
        

    
