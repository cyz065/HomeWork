import sys;

circle = list(); index = 0; sequence = list();
N, K = map(int, sys.stdin.readline().split());

circle = [number for number in range(1, N + 1)];

index = K - 1;

while(len(circle) != 0) :
    num = circle.pop(index);
    sequence.append(num);
    index += K - 1;
    while(index > len(circle) - 1 and len(circle) != 0) :
        index -= len(circle);
    
print("<" + ', '.join(map(str, sequence)) + ">");

    





        
    
    
    
