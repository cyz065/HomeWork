import sys

def roma_to_arab(string) :
    idx = 0; i = 0; num = 0
    while(idx < len(string)) :
        if string[idx] == 'I' or string[idx] == 'X' or string[idx] == 'C' :
            temp = a[string[idx]]
            i = idx + 1
            # i에서 다음 인덱스의 문자를 읽어온다.
            if i < len(string) :
                tmp = a[string[i]]
                
            # idx가 문자열의 끝을 나타내는 경우 예외 처리
            # 마지막 숫자인 temp만 더해주고 loop 탈출
            else :
                num += temp
                break
            
            # I, X, C 다음에 큰 숫자가 오지 않는 경우에는 두 문자가 각각 하나의 숫자가 되므로 temp만 더해준다.
            if temp >= tmp :
                num += temp
                
            # I, X, C 다음에 큰 숫자가 오는 경우에는 두 문자가 하나의 로마 숫자가 되므로 idx를 1 증가 시켜준다. 따라서
            # loop한번을 돌게되면 idx는 2씩 증가하게 된다.
            else :
                num += tmp - temp
                idx += 1
                
        # V, L, D, M 다음에는 작은 수만 올 수 있기 때문에 num을 더해준다.
        elif string[idx] == 'V' or string[idx] == 'L' or string[idx] == 'D' or string[idx] == 'M' :
            num += a[string[idx]]
        idx += 1
    return num
'''
def arab_to_roma(res) :
    idx = 0; i = 0; ans = list(); string = ""
    tmp = list(str(res).strip())
    for j in range(len(tmp)) :
        tmp[j] = int(tmp[j]) * (10 ** (len(tmp) - j - 1))
        
    while(idx < len(tmp)) :
        temp = tmp[idx]
        while(temp != 0) :
            t = temp // a_v[i]
            temp = temp % a_v[i]
            ans.append(t)
            i += 1
        idx += 1
    for i in range(len(ans)) :
        string += a_k[i] * ans[i]
    return string
'''
def arab_to_roma(res) :
    idx = 0; i = 0; ans = list(); string = ""
    
    # 아라비아 숫자로 표현된 숫자를 각각 자리수 대로 나누어 준다
    # ex) 2428 -> [2000, 400, 20, 8]
    tmp = list(str(res).strip())
    for j in range(len(tmp)) :
        tmp[j] = int(tmp[j]) * (10 ** (len(tmp) - j - 1))
        
    while(idx < len(tmp)) :
        temp = tmp[idx]
        
        # Greedy를 활용하여 value값을 큰 수부터 차례대로 나누어서 각각의 value값이 몇번씩 나오는지를 나타내 준다.
        # ex) 2428 -> ans = [2, 0, 0, 1, 0, 0, 0, 0, 2, 0, 1, 0, 3] 
        while(temp != 0) :
            t = temp // a_items[i][1]
            temp = temp % a_items[i][1]
            ans.append(t)
            i += 1
        idx += 1
        
    # ans 배열은 dict a의 key값의 순서와 일치하기 때문에 ans의 값을 통해 해당 key가 몇번 나오는지를 파악하여, 로마 숫자로 표현해준다.
    for i in range(len(ans)) :
        string += a_items[i][0] * ans[i]
    return string

a = {
    'M' : 1000, 'CM' : 900, 'D' : 500, 'CD' : 400, 'C' : 100,
    'XC' : 90, 'L' : 50, 'XL' : 40, 'X' : 10,
    'IX' : 9, 'V' : 5, 'IV' : 4, 'I' : 1
    }

a_items = tuple(a.items())
r1 = sys.stdin.readline().strip()
r2 = sys.stdin.readline().strip()

num1 = roma_to_arab(r1)
num2 = roma_to_arab(r2)
result = num1 + num2
string = arab_to_roma(result)

print(result)
print(string)

