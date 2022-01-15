import sys

def push(stack, word) :
    return stack.append(word);

def pop(stack) :
    if(len(stack) <= 0) :
        return False;
    else :
        return stack.pop();

def isEmpty(stack) :
    if len(stack) == 0 :
        return True;
    else :
        return False;

def top(stack) :
    length = len(stack);
    if length == 0 :
        return False;
    else :
        return stack[length - 1];

bracket_list = list(); stack = list();

while(True) :
    string = sys.stdin.readline().rstrip();
    if(string == '.') :
        break;
    for i in string :
        if(i == '(' or i == '[' or i == ')' or i == ']') :
            bracket_list.append(i);
    if(len(bracket_list) == 0) :
        print("yes");
        bracket_list.clear();
        continue;
    elif(len(bracket_list) % 2 != 0) :
        print("no");
        bracket_list.clear();
        continue;
    else :
        for i in bracket_list :
            word = i;
            if(word == '(' or word == '[') :
                push(stack, word);
            elif((isEmpty(stack) == False) and (top(stack) == '(' and i == ')')) :
                pop(stack);
            elif((isEmpty(stack) == False) and (top(stack) == '[' and i == ']')) :
                pop(stack);
            else :
                push(stack, word);
    
    if(isEmpty(stack) == True) :
        print("yes");
    else :
        print("no");
    bracket_list.clear();
    stack.clear();
