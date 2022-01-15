import sys
alphabet = [0] * 26
N = int(sys.stdin.readline())
word = [sys.stdin.readline().strip() for x in range(N)]
cnt = 0

for i in word :
    j = 0
    # word의 첫번째 단어부터 단어를 구성하는 알파벳의 유무 여부 조사
    
    while(j < len(i)) :
        # 해당 알파벳 index의 값이 0이 아닌 경우에는 기존에 알파벳이 나온 경우이므로 그룹 단어가 될 수 없다.
        if alphabet[ord(i[j]) - 97] != 0 :
            break
        
        # 해당 알파벳 index의 값이 0인 경우 해당 알파벳의 값을 1로 변경하고 해당 알파벳이 나오지 않을 때까지 반복한다.
        else :
            alphabet[ord(i[j]) - 97] = 1 # 해당 index값 1로 설정
            c = i[j] # 1이 된 값의 알파벳
            j += 1 # c다음 알파벳
            
            # c가 마지막 까지 온 경우에는 앞의 단어가 그룹 단어의 조건을 만족하기 때문에 cnt를 1 증가
            if j >= len(i) :
                cnt += 1
                break
            
            # c가 나오지 않을 때 까지 j를 증가시켜 주고, c가 문자열의 끝에 도달하면 cnt를 1 증가시키고, 탈출
            while(j < len(i) and c == i[j]) :
                j += 1
                if j == len(i) :
                    cnt += 1
                    break
            
    # 다음 단어 체크를 위해 초기화
    alphabet = [0] * 26
print(cnt)

''' 
for i in range(len(string)) :
    for j in string[i] :
        
'''


'''
string = list(); # 문자열 입력
check = list(); # 알파벳 개수 check; 
common = set(); # 문자열을 이루는 알파벳...
common_list = list();
count = 0; # 공통된 알파벳의 개수 ex) aab count = 1 2 1
word_count = 0; # 결과에 부합하는 단어의 개수
result_list = list();

for i in range(N) :
    tmp = list(input());
    string.append(tmp);
print("string : ", string);

for i in range(len(string)) :
    common = set(string[i]);
    common_list = list(common);
    common_list = sorted(common_list);
    
    print("common : ", common);
    print("common_list : ", common_list);
    
    for j in range(len(string[i])) :
        check.append(0);

    for alphabet in common :
        for k in range(len(string[i])) :
            if(string[i][k] == alphabet) :
                count += 1;
                check[k] = count;              
        count = 0;
    print(check);
    check.clear();
'''                
                
        
                       

        
        






        
   


