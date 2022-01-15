import sys
chem = list(sys.stdin.readline().strip())
stack = list()
result = 0; stack_result = 0; temp_result = 0;
H = 0; C = 0; O = 0; element = 0; ele = 0;
num_string = "01234565789"

while(len(chem) > 0) :
    tmp = chem.pop(0)
    if(tmp == 'H') :
        element = tmp
        H += 1
    elif(tmp == "C") :
        element = tmp
        C += 1
    elif(tmp == "O") :
        element = tmp
        O += 1
    elif(tmp == '(') :
        if(len(stack) > 0) :
            stack.clear()
            stack_result = 0
        tmp = chem.pop(0)
        while(tmp != ')') :
            stack.append(tmp)
            tmp = chem.pop(0)
        for i in range(len(stack)) :
            if(stack[i] == "H") :
                temp_result += 1
                ele = stack[i]
                stack_result += 1
            elif(stack[i] == "C") :
                temp_result += 12
                ele = stack[i]
                stack_result += 12
            elif(stack[i] == "O") :
                temp_result += 16
                ele = stack[i]
                stack_result += 16
            else :
                if(stack[i] in num_string) :
                    stack[i] = int(stack[i])
                if(ele == "H") :
                    temp_result += (stack[i] - 1)
                    stack_result += (stack[i] - 1)
                elif(ele == "C") :
                    temp_result += 12 * (stack[i] - 1)
                    stack_result += 12 * (stack[i] - 1)
                elif(ele == "O") :
                    temp_result += 16 * (stack[i] - 1)
                    stack_result += 16 * (stack[i] - 1)
    else :
        tmp = int(tmp)
        if(len(stack) != 0) :
            temp_result += stack_result * (tmp - 1)
            stack.clear()
            stack_result = 0
        elif(element == "H") :
            H += tmp - 1
        elif(element == "C") :
            C += tmp - 1
        elif(element == "O") :
            O += tmp - 1
result = temp_result + H + (12 * C) + (16 * O)
print(result)
