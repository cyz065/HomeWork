import sys;
from itertools import permutations;

N = int(sys.stdin.readline());
num_arr = list(map(int, sys.stdin.readline().split()));
number = list();
idx = 0; result1 = 0; result2 = 0;

b = 0; sum_list = list(); c = list();
permute = list(permutations(num_arr, N));

for i in permute :
    a = list(i)
    for i in range(0, len(a) - 1) :
       b += abs(a[i] - a[i + 1]);
    c.append(b);
    if(b == 57) :
        sum_list.append(a);
    b = 0;
print(sum_list);
print(max(c));

print("--------------------------------------------");

while(len(num_arr) != 0) :
    max_num = max(num_arr);
    idx = num_arr.index(max_num);
    number.append(num_arr.pop(idx));
    if(len(num_arr) == 0) :
        break;

    min_num = min(num_arr);
    idx = num_arr.index(min_num);
    number.append(num_arr.pop(idx));

for i in range(0, len(number) - 1) :
    result1 += abs(number[i] - number[i + 1]);

number.insert(0, number[-1]);
number.pop();

for i in range(0, len(number) - 1) :
    result2 += abs(number[i] - number[i + 1]);
    
print(max(result1, result2));


