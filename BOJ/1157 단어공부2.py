import string

alphabet = list(string.ascii_uppercase);
string = [];
check = [];

index = 0; count = 0; maximum = 0;
same = 0; answer = 0;

string = input();
length = len(string);

string_UpperCase = string.upper();

for i in range(0, len(alphabet)) :
        for j in range(0, length) :
                if(string_UpperCase[j] == alphabet[index]) :
                        count += 1;
        check.append(count);
        count = 0;
        index += 1;

maximum = check[0];
answer = alphabet[0];

for i in range(1, len(alphabet)) :
        if(maximum < check[i]) :
                maximum = check[i];
                answer = alphabet[i];
                same = 0;
        elif(maximum == check[i]) :
                same += 1;

if(same != 0) :
        print("?");
elif(same == 0) :
        print(answer);      


