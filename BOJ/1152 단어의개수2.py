number = int(input());
numbers = list();

for i in range(0, number) :
    num = int(input());
    numbers.append(num);

numbers.sort();

for i in range(len(numbers)) :
    print(numbers[i]);
    
''' 
numbers.sort();

for i in numbers :
    print(i);

    
'''
