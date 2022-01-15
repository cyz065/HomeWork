import sys

N = int(sys.stdin.readline())
string = list()

for i in range(N) :
    string.append(sys.stdin.readline().strip())
    
new = {
    "a" : 1, "b" : 2, "k" : 3, "d" : 4, "e" : 5,
    "g" : 6, "h" : 7, "i" : 8, "l" : 9, "m" : 10,
    "n" : 11, "0" : 12, "o" : 13, "p" : 14, "r" : 15,
    "s" : 16, "t" : 17, "u" : 18, "w" : 19, "y" : 20
       }

for i in range(N) :
    if "ng" in string[i] :
        string[i] = string[i].replace("ng", "0");

string = sorted(string, key = lambda word : [new.get(c, ord(c)) for c in word])

for i in range(N) :
    if "0" in string[i] :
        string[i] = string[i].replace("0", "ng")

for i in string :
    print(i)

              
            
     
   


