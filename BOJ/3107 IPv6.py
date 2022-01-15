import sys

ip = sys.stdin.readline().strip()
# 입력받은 ip를 ":"를 기준으로 나눈다.
ip = list(ip.split(":"))
cnt = 0; string = ""; tmp = "0000"
result = list();

# 0의 그룹을 제외한 ip 그룹의 갯수를 count
for i in ip :
    if i != '' :
        cnt += 1
# "::"경우에 대한 예외처리
if ip == ['','',''] :
    temp = 8 - cnt
    for i in range(temp) :
        result.append(tmp)
        
else :
    while(len(ip) > 0) :
        temp = 8 - cnt
        t = ip.pop(0)
        # :가 아닌 경우, 길이를 4로 맞추어 result에 추가
        if t != '' :
            if len(t) != 4 :
                c = 4 - len(t)
                for j in range(c) :
                    string += '0'
            string += t
            result.append(string)
            string = ""
        # ::1 or 1::의 경우 0의 그룹의 갯수만큼 result 에 추가
        elif t == '' and ip[0] == '' :
            ip.pop(0)
            for i in range(temp) :
                result.append(tmp)
        # AAAA::11 과 같이 ::가 중간에 오는 경우 0의 그룹의 갯수만큼 result에 추가
        else :
            for i in range(temp) :
                result.append(tmp) 
print(":".join(map(str, result)))
            


'''
import sys

ip = sys.stdin.readline().strip()
# 입력받은 ip를 ":"를 기준으로 나눈다.
ip = list(ip.split(":"))
cnt = 0; string = ""; tmp = "0000"
result = list()

# ip리스트에서 '' 는 ":"를 나타내고
# 숫자나 알파벳의 갯수를 구해서 8에서 빼주면 0의 그룹의 개수를
# 구할 수 있다.
for i in ip :
    if i != '' :
        cnt += 1

while(len(ip) > 0) :
    t = ip.pop(0)
    # ip리스트에서 ''가 아닌 경우에는 ip가 되므로 result 배열에 추가하되, 길이가 4가 아닌 경우 0을 추가한 후에 추가해 준다.
    if t != '' :
        if len(t) != 4 :
            c = 4 - len(t)
            for j in range(c) :
                string += '0'
        string += t
        result.append(string)
        string = ""
    # ip리스트에서 ''는 :를 나타낸다. "::"가 중간에 존재하는 경우에는 ''가 1개만 나오지만,
    # "::"가 양 끝에 존재하는 경우에는 ''가 2개가 나온다.
    # ex) ::1 -> ['', '', '1']
    # ex) 2001:0db8::7334 -> [2001, 0db8, '', 7334]
    else :
        # 양끝에 ::가 존재하는 경우 8에서 cnt를 뺀만큼 0의 그룹이 존재하므로 그 개수만큼 0000을 result에 추가해준다.
        if len(ip) > 0 and ip[0] == '' :
            ip.pop(0)
            temp = 8 - cnt
            for i in range(temp) :
                result.append(tmp)
        # 중간에 ::가 존재하는 경우, 개수만큼 0000을 추가해준다.
        else :
            temp = 8 - cnt
            for i in range(temp) :
                result.append(tmp)

# :: 의 경우에는 else의 두개의 조건 모두 충족하기 때문에 0000이 16개가 된다. 따라서 8개만 남기기 위해서
# 리스트를 슬라이싱 해준다.
result = result[0:8]#("::" 예외 해결을 위해)
print(":".join(map(str, result)))
'''
'''
import sys

ip = sys.stdin.readline().strip()
ip = list(ip.split(":"))
result = list(); cnt1 = 0; cnt2 = 0

if '' not in ip :
    for i in range(len(ip)) :
        tmp = ""
        if len(ip[i]) != 4 :
            c = 4 - len(ip[i])
            for j in range(c) :
                tmp += '0'
            tmp += ip[i]
            ip[i] = tmp
    print(":".join(map(str, ip)))
else :
    for i in ip :
        if i == '' :
            cnt1 += 1
        else :
            cnt2 += 1
    if cnt1 == 1 :
        temp = 8 - cnt2
        for i in range(len(ip)) :
            tmp = ''
            if ip[i] == '' :
                for j in range(temp) :
                    tmp += "0000"
                ip[i] = tmp
            else :
                if len(ip[i]) != 4 :
                    c = 4 - len(ip[i])
                    for j in range(c) :
                        tmp += '0'
                    tmp += ip[i]
                    ip[i] = tmp
    else :
        idx = ip.index('')
        ip.pop(idx)
        cnt1 = 0; cnt2 = 0
        for i in ip :
            if i != '' :
                cnt2 += 1
        temp = 8 - cnt2
        for i in range(len(ip)) :
            tmp = ""
            if ip[i] == '' :
                for j in range(temp) :
                    tmp += "0000"
                ip[i] = tmp
            else :
                if len(ip[i]) != 4 :
                    c = 4 - len(ip[i])
                for j in range(c) :
                    tmp += '0'
                tmp += ip[i]
                ip[i] = tmp
    cnt1 = 0; cnt2 = 0;
    for i in range(len(ip)) :
        if len(ip[i]) == 4 :
            result.append(ip[i])
        else :
            cnt1 = len(ip[i]) // 4
            tmp = "0000"
            for i in range(cnt1) :
                result.append(tmp)
    result = result[0:8]
    print(":".join(map(str, result)))
'''
