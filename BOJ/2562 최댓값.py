
number = [];
maximum = 0;
index = 1;

for i in range(0, 9) :
        num = int(input());
        number.append(num);

for i in range(0, len(number)) :
        if(maximum < number[i]) :
                maximum = number[i];
                index = i + 1;

print(maximum);
print(index);

        
