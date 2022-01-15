import sys;
from collections import deque;

deck = deque(); idx = 0; reverse_string = list();
string = sys.stdin.readline().strip();
while(idx < len(string)) :
    if len(deck) == 0 and string[idx] == '<' :
        while(string[idx] != '>') :
            deck.append(string[idx]);
            idx += 1;
        deck.append(string[idx]);
        idx += 1;
        reverse_string.append(list(deck));
        deck.clear();
    elif len(deck) != 0 and string[idx] == '<' :
        reverse_string.append(list(deck));
        deck.clear();
        while(string[idx] != '>') :
            deck.append(string[idx]);
            idx += 1;
        deck.append(string[idx]);
        idx += 1;
        reverse_string.append(list(deck));
        deck.clear();
    else :
        while(string[idx] != ' ') :
            deck.appendleft(string[idx]);
            idx += 1;
            if(idx >= len(string)) :
                reverse_string.append(list(deck));
                break;
            elif(string[idx] == '<') :
                break;
        if(idx >= len(string)) :
            break;
        elif(string[idx] == '<') :
            continue;
        deck.append(string[idx]);
        idx += 1;
        reverse_string.append(list(deck));
        deck.clear();

for i in reverse_string :
    for j in i :
        print(j, end = '');


