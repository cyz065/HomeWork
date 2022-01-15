import sys;

N = int(sys.stdin.readline());
result = 0; temp = 0;
atm = list(map(int, sys.stdin.readline().split()));
atm.sort();

for i in range(N) :
    temp += atm[i];
    result += temp;
print(result);

'''
for i in range(N) :
    for j in range(0, i + 1) :
        result += atm[j];

print(result);
'''
