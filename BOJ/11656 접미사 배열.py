'''
import sys

S = sys.stdin.readline().strip()
queue = list()

for i in range(0, len(S)) :
    queue.append(S[i:])
    
queue.sort()
for i in queue :
    print(i)
'''

import sys

S = list(sys.stdin.readline().strip())
queue = list()
n = len(S)

while(n > 0) :
    string = ''.join(map(str, S))
    queue.append(string)
    S.pop(0)
    n -= 1
queue.sort()

for i in queue :
    print(i)
    
