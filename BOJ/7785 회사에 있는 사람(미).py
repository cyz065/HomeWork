import sys
from collections import deque

n = int(sys.stdin.readline());
log = list(); person = list();

for i in range(n) :
    name, check = sys.stdin.readline().split();
    if(name in person and check == "leave") :
        idx = person.index(name);
        log.pop(idx);
        person.pop(idx);
    else :
        log.append((name, check));
        person.append(name);

log.sort(reverse = True);

for name, check in log :
    print(name);
    
       
        
    
    
    


