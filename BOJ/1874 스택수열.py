import sys


def push(stack, word):
    return stack.append(word);


def pop(stack):
    if len(stack) <= 0:
        return False;
    else:
        return stack.pop();


def isEmpty(stack):
    if len(stack) == 0:
        return True;
    else:
        return False;


def top(stack):
    length = len(stack);
    if length == 0:
        return False;
    else:
        return stack[length - 1];


n = int(input());
number = list();
stack = list();
arr = list();

for i in range(n):
    tmp = int(sys.stdin.readline().strip());
    number.append(tmp);

temp = sorted(number);
index = 0;
i = 0;
while (index < len(number)):
    while (i < len(number)):
        if (temp[i] < number[index]):
            push(stack, temp[i]);
            arr.append('+');
            i += 1;
        elif (temp[i] == number[index]):
            push(stack, temp[i]);
            arr.append('+');
            i += 1;
            break;
        else:
            break;
    if (top(stack) == number[index]):
        pop(stack);
        arr.append('-');
        index += 1;
    elif (top(stack) > number[index]):
        arr.clear();
        break;
    elif (top(stack) < number[index]):
        continue;
    elif (isEmpty(stack) == True):
        continue;

if (len(arr) > 0):
    for i in arr:
        print(i);
else:
    print("NO");
