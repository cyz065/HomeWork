import sys;
import math;
import collections;

N = int(sys.stdin.readline());
numbers = list();

for i in range(N) :
    tmp = int(sys.stdin.readline())
    numbers.append(tmp);
    
num_arr = sorted(numbers);
num_counter = collections.Counter(num_arr);
frequency = num_counter.most_common(2);

most = frequency[0][0];

if len(frequency) > 1 :
    if frequency[0][1] == frequency[1][1] :
        most = frequency[1][0];

avg = round(sum(num_arr) / N);
print(avg);
#  평균값

center = int(N // 2);
print(num_arr[center]);
# 중앙값

print(most);
# 최빈값

ran = num_arr[-1] - num_arr[0];
print(ran)
# 범위

