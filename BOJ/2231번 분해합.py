num = int(input());
num_list = list();
i = 1; is_True = 1;

while True :
    num_list.append(i);
    number = i;
    length = len(str(i));
    for j in range(length, 0, -1) :
        number2 = number// (10 ** (j - 1));
        number %= 10 ** (j - 1);
        num_list.append(number2);
    if(sum(num_list) == num) :
        print(i);
        break;
    elif(i >= num) :
        is_True = 0;
        break;
    i += 1;
    num_list.clear();
    
if(is_True == 0) :
    print(0);

        
   

