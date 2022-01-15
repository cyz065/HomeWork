from itertools import combinations;
import string;

n, k = map(int, input().split()); # N, K 입력
string = list();        # 중복을 제외한, 입력받은 문자열 저장
common_set = {'a', 'n', 't', 'i', 'c'};  # 공통알파벳
alphabet = set();    # 입력받은 모든 문자열 
alphabet_list = list(); # 정렬
answer = 0; # 개수 count

if (k < 5) :
    for i in range(n) :
        word= input();
    print(0);
    
elif (k == 26) :
    for i in range(n) :
        word = input();
    print(n);
    
else :
    for i in range(0, n) :
        word = input();
        string_set = set(word);     # 입력받은 word에서 중복되는 문자 제거 antartica - a, n t, i, c, r
        diff_set = string_set - common_set; # a,n,t,i,c 제거
        string.append(list(diff_set)); # [[r], [h,e,l,o], [r]]
        alphabet = alphabet.union(string_set); # 입력받은 모든 알파벳 저장. 중복을 제외한 모든 알파벳이 저장 되어 있음.
        
    diff_set = alphabet - common_set; # {r, h, e, l, o}
    diff_list = list(diff_set);
    diff_list = sorted(diff_list);
    
    if(len(diff_list) >= (k - 5)) :     # combination 할 때, k가 더 크면 combi가 X nCr에서 r이 더 크면  X
        permu = combinations(diff_list, k - 5);
    
        for i in permu :
            count = 0;
            spell_list = list(i); # spell_list 모든 경우의 수가 list형태로 저장...
            for j in string :   # j = [r], [h,e,l,o]... 
                true = 1;
                for k in j:     # k = r, h, e, l, o ...
                    if k not in spell_list : # 가능한 조합에 k가 없는경우, 즉 단어를 만들 수 없으면 true = 0
                        true = 0;
                if true == 1:
                    count += 1;          
            answer = max(answer, count);
        print(answer);
    else :
        print(n);
    
