import sys;

rope = list(); idx = 0;
max_weight = 0; weight_arr = list();
N = int(sys.stdin.readline());

'''
for i in range(N) :
    rope.append(int(sys.stdin.readline()));
'''

rope = [int(sys.stdin.readline()) for x in range(N)];
rope = sorted(rope, reverse = True);

'''
while(idx < length) :
    weight = rope[idx] * (idx + 1);
    if(weight > max_weight) :
        max_weight = weight;
    idx += 1;
'''
'''
for i in rope :
    weight_arr.append(i * (idx + 1));
    idx += 1;
'''

for i in rope :
    weight = i * (idx + 1);
    if(weight > max_weight) :
        max_weight = weight;
    idx += 1;
print(max_weight);

#print(max(weight_arr));
    
