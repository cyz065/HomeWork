import sys
from collections import deque

string = deque(sys.stdin.readline().strip())
upper = ""

for i in string :
    if(upper == "" and i == "U") :
        upper += i
    if(upper == "U" and i == "C") :
        upper += i
    if(upper == "UC" and i == "P") :
        upper += i
    if(upper == "UCP" and i == "C") :
        upper += i
    if(upper == "UCPC") :
        break
if(upper == "UCPC") :
    print("I love UCPC")
else :
    print("I hate UCPC")
        
    

