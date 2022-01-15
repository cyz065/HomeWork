import sys

n = int(sys.stdin.readline())
tmp = list()
for i in range(n + 1) :
    tmp.append(set(str(i)))

for i in tmp :
    print(type(i))
    print(i)
    i.intersection()

    

    

    

    


        
