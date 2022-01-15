import sys

def roma_to_arab(string) :
    idx = 0; i = 0; num = 0
    while(idx < len(string)) :
        if string[idx] == 'I' or string[idx] == 'X' or string[idx] == 'C' :
            temp = a[string[idx]]
            i = idx + 1
            if i < len(string) :
                tmp = a[string[i]]
            else :
                num += temp
                break
            if temp >= tmp : 
                num += temp
            else :
                num += tmp - temp
                idx += 1
        elif string[idx] == 'V' or string[idx] == 'L' or string[idx] == 'D' or string[idx] == 'M' :
            num += a[string[idx]]
        idx += 1
    return num

def arab_to_roma(result) :
    idx = 0; i = 0; ans = list(); string = ""
    tmp = list(str(result).strip())
    for j in range(len(tmp)) :
        tmp[j] = int(tmp[j]) * (10 ** (len(tmp) - j - 1))

    while(idx < len(tmp)) :
        temp = tmp[idx]
        while(temp != 0) :
            t = temp // a_items[i][1]
            temp = temp % a_items[i][1]
            ans.append(t)
            i += 1
        idx += 1
    for i in range(len(ans)) :
        string += a_items[i][0] * ans[i]
    return string
a = {
    'M' : 1000, 'CM' : 900, 'D' : 500, 'CD' : 400, 'C' : 100,
    'XC' : 90, 'L' : 50, 'XL' : 40, 'X' : 10,
    'IX' : 9, 'V' : 5, 'IV' : 4, 'I' : 1
    }
a_items = tuple(a.items())
check = "0123456789"
T = int(sys.stdin.readline())

for i in range(T) :
    num = sys.stdin.readline().strip()
    # check를 통해 아라비아 숫자가 있는지 판별 한 후에 없으면 r to a, 있으면 a to r을 실행
    if num[0] not in check :
        number = roma_to_arab(num)
        print(number)
    else :
        number = arab_to_roma(num)
        print(number)
    
    
