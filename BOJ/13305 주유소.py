'''
import sys;

i = 0; price = 0; j = 0;

N = int(sys.stdin.readline());
distance = list(map(int, sys.stdin.readline().split()));
oil = list(map(int, sys.stdin.readline().split()));
oil.pop();
oil_min = oil[0];
price = distance[0] * oil[0];
minimum = min(oil);

while(i < len(distance) - 1) :
    if(oil[i] == minimum) :
        j += 1;
        for k in range(j, len(distance)) :
            price += distance[k] * minimum;
            print("distance : ", distance[k], "mini : ", minimum);
        break;
    if(oil[i] < oil[i + 1]) :
        j += 1;
        price += distance[j] * oil[i];
        print("distance : ", distance[j], "oil : ", oil[i]);
    elif(oil[i] > oil[i + 1]) :
        j += 1;
        price += oil[i + 1] * distance[j];
        print("distance : ", distance[j], "oil : ", oil[i]);
    else :
        j += 1;
        price += oil[i + 1] * distance[j];
        print("distance : ", distance[j], "oil : ", oil[i]);
    i += 1;

print(price);
'''        
import sys;

i = 0; price = 0; j = 0;
N = int(sys.stdin.readline());
distance = list(map(int, sys.stdin.readline().split()));
oil = list(map(int, sys.stdin.readline().split()));

#oil.pop();
oil_min = oil[0];
price = distance[0] * oil[0];
minimum = min(oil);

while(i < len(distance) - 1) :
    if(oil[i] == minimum) :
        j += 1;
        for k in range(j, len(distance)) :
            price += distance[k] * minimum;
        break;
    if(oil_min < oil[i + 1]) :
        j += 1;
        price += distance[j] * oil_min;
    elif(oil_min > oil[i + 1]) :
        oil_min = oil[i + 1];
        j += 1;
        price += oil[i + 1] * distance[j];
    else :
        j += 1;
        price += oil[i + 1] * distance[j];
    i += 1;

print(price);      

    
