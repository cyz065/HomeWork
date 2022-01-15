alphabet = [];
string = [];
check = [];

for i in range (ord('a'), (ord('z')) + 2) :
        alphabet.append(chr(i));

index = 0; count = 0; maximum = 0; k = 0; same = 0;

string = input();
length = len(string);

string2 = string.lower();

for i in range(0, len(alphabet) - 1) :
        for j in range(0, length) :
                if(string2[j] == alphabet[index]) :
                        count += 1;
        check.append(count);
        count = 0;
        index += 1;

maximum = check[0];

for i in range(1, len(alphabet) - 1) :
        if(maximum < check[i]) :
                maximum = check[i];
                k = i;
                same = 0;
        elif(maximum == check[i]) :
                same += 1;

if(same != 0) :
        print("?");
elif(same == 0) :
        print(chr(k+65));
