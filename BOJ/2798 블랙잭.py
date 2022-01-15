m, n = map(int, input().split());
result = 0;
maximum = 0;

card = list(map(int, input().split()));

for i in range(0, len(card)) :
        for j in range(i+ 1, len(card)) :
                for k in range(j + 1, len(card)) :
                        tmp = card[i] + card[j] + card[k];
                        if(tmp > n) :
                                continue;
                        else :
                                result = tmp;
                                if(maximum < result) :
                                        maximum = result;
                    
print(maximum);
                        
