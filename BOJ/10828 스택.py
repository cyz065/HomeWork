import sys;

def push(stack, N) :
    stack.append(N);

def pop(stack) :
    if(len(stack) == 0) :
        return -1;
    else :
        return stack.pop();
    
def size(stack) :
    return len(stack);

def empty(stack) :
    if(len(stack) == 0) :
        return -1;
    else :
        return 0;

def top(stack) :
    if(len(stack) == 0) :
        return -1;
    else :
        index = len(stack) - 1;
        return stack[index];

N = int(input());
stack = list();

for i in range(N) :
    commands = sys.stdin.readline();
    commands = commands.strip();
    command = commands.split();

    if(commands.startswith("push") == True) :
        push(stack, command[1]);
        
    elif(commands == "top") :
        print(top(stack));
    elif(commands == "size") :
        print(size(stack));
    elif(commands == "pop") :
        print(pop(stack));
    elif(commands == "empty") :
        print(empty(stack));



# import sys
# sys.stdin.readline();
# -> 반복문에서 input()을 통해 입력받게 되면 시간초과가 발생할 수 있다.
# -> 따라서 반복문에서는 sys.stdin.readline()을 통해 문자열 입력을 받는것이 효율적이다.
# -> sys.stdin.readline()을 통해 입력을 받으면  개행 문자 '\n'을 포함하기 때문에 strip()메소드를 사용하여 개행문자를 제거해 준다.
# -> 숫자를 입력받아도 문자열로 저장되기 때문에 int(sys.stdin.readline())과 같이 사용하여 준다.

# sys.stdin.readline()의 활용
# -> https://blog.naver.com/lny127/222349819732
    
