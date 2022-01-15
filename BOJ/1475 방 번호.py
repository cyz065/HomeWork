import sys;
import math;

room_number = list(map(int, sys.stdin.readline().strip()));
result = 0;

room = [0 for i in range(10)];

for i in room_number :
    room[i] += 1;

if max(room) == room[9] or max(room) == room[6] :
    if room.count(max(room)) == 1 :
        result = math.ceil((room[6] + room[9]) / 2);
    else :
        result = max(room);
else :
    result = max(room);
print(result);
 

