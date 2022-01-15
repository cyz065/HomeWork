'''
import sys

password = list(); tmp = list(); temp = list()
T = int(sys.stdin.readline())

for i in range(T) :
    key = sys.stdin.readline().strip()
    for j in key :
    # <인 경우에는 tmp에서 pop해서 temp에 추가해주고,
    # tmp가 비어있는 경우에는 커서가 처음을 가리키므로 continue
        if j == '<' :
            if len(tmp) != 0 :
                temp.append(tmp.pop())
            else :
                continue
        # >인 경우에는 temp에 있는 값을 tmp에 추가해주고, temp가 비어있는 경우에는 커서가 마지막
        # 위치를 가리키고 있으므로 continue
        elif j == '>' :
            if len(temp) != 0 :
                tmp.append(temp.pop())
            else :
                continue
        # -인 경우에는 tmp의 마지막 값을 제거해주고,
        # tmp가 비어있는 경우에는 제거할 값이 없으므로 continue
        elif j == '-' :
            if len(tmp) != 0 :
                tmp.pop()
            else :
                continue
        # 숫자, 알파벳인 경우에는 그대로 tmp에 추가
        else :
            tmp.append(j)
    # temp에 존재하는 값들을 tmp 뒤에 이어붙여 주면 원하는 결과가 나
    if len(temp) != 0 :
        t = ''.join(map(str, temp))
        t = t[::-1]
        tmp.append(t)
    string = ''.join(map(str, tmp))
    print(string)
    tmp.clear()
    temp.clear()
'''
import sys
T = int(sys.stdin.readline())
password = list(); idx = 0; now = 0
for i in range(T) :
	key = sys.stdin.readline().strip()
	
	for j in key :
		if len(password) == 0 :
			if j == '<' or j == '>' or j == '-' :
				continue
			else :
				password.append(j)
				now += 1
		else :
			if j == '<' and now >= 1 :
				now -= 1
			elif j == '<' and now == 0 :
				continue
			elif j == '>' and now < len(password) :
				now += 1
			elif j == '>' and now >= len(password) :
				continue
			elif j == '-' and now >= 1:
				password.remove(password[now - 1])
				now -= 1
			elif j == '-' and now <= 0 :
				now = 0
				continue
			else :
				password.insert(now, j)
				now += 1
	string = ''.join(map(str, password))
	print(string)
	password.clear()
	now = 0
        
