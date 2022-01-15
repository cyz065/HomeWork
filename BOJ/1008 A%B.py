A, B = map(int, input().split());
result = str(A / B);
index = 0; i = 0; count = 0;

while(index <= len(result)) :
    if(result[i] == '.') :
        index = i;
        break;
    else :
        i += 1;
        
index += 1;

while(index < len(result)) :
    if(index != 0) :
        count += 1;
        if(count == 9) :
            break;
    else :
        break;
    index += 1;
    
for i in range(count + 2) :
    print(result[i], end="")
        
    

