string = input();

length = len(string);
count = 0;
i = 0;

while True :
        if(i >= length) :
                break;
        
        elif((string[i] == "c" or string[i] == "s" or string[i] == "z") and i < length - 1) :
                if(string[i + 1] == "=") :
                        count += 1;
                        i += 2;
                elif(string[i] == "c" and string[i + 1] == "-") :
                        count += 1;
                        i += 2;
                else :
                        count += 1;
                        i += 1;
        elif((string[i] == "l" or string[i] == "n") and i < length - 1) :
                if(string[i + 1] == "j") :
                        count += 1;
                        i += 2;
                else :
                        count += 1;
                        i += 1;
        elif(string[i] == "d" and i < length - 1) :
                if(string[i + 1] == "-") :
                        count += 1;
                        i += 2;
                elif(string[i + 1] == "z") :
                        if(i < length - 2 and string[i + 2] == "=") :
                                count += 1;
                                i += 3;
                        else :
                                count += 2;
                                i += 2;
                else :
                        i += 1;
                        count += 1;
        else :
                i += 1;
                count += 1;
print(count);
