import sys
poly = sys.stdin.readline().strip()
result = list(); idx = 0; s = ""

# 연산자를 기준으로 문자열을 분리한다.
if '+' in poly :
    p = poly.split('+')
    idx = poly.find('+')
elif '-' in poly :
    p = poly.split('-')
    idx = poly.find('-')
# 연산자가 없는 단항식인 경우
else :
    p = poly.split()

# 다항식이 음수계수로 시작하는 경우 elif '-'에서 다음과 같이 분리된다.
# ex) -2x-4 = ['', 2x, -4]
# 처음 음수계수를 표현하기 위해 '', 2x를 -2x로 수정하여 삽입.
if p[0] == '' :
    p[0] = '-'
    tmp = p.pop(0)
    tmp += p.pop(0)
    p.insert(0, tmp)

while(len(p) > 0) :
    string = ""
    # 첫번째 식을 pop
    tmp = p.pop(0)
    # pop한 식에 존재하는 x의 수 count
    x = tmp.count('x')
    # x가 존재한다면 x이전까지가 계수가 되므로 문자열을 slicing해준다.
    if 'x' in tmp :
        i = tmp.find('x')
        num = int(tmp[0:i])
    # x가 없다면 상수항이 되기 때문에 tmp그대로 num에 저장
    else :
        num = int(tmp)
    # 적분 공식에 따라 num과 x를 계산
    num = num // (x + 1)
    x += 1
    # 상수항이 1인 경우에는 상수를 생략
    if num != 1 and num != -1 :
        string += str(num)
    # 상수항이 -1인 경우에는 '-'만 추가해준다.
    elif num == -1 :
        string += '-'
    # x의 개수가 x의 차수가 되기 때문에 x의 개수만큼 반복해서 x의 차수를 표현한다.
    for i in range(x) :
        string += 'x'
    # 첫 계수가 0인경우, 즉 입력받은 식이 0인 경우 0x+W와 표현되기 때문에 앞에 0이 나오는 경우는 제외해 준다.
    if string[0] != '0' :
        result.append(string)
        
# 적분 상수를 추가해준다.
if '+' in poly :
    s = '+'.join(map(str, result))
    s += "+W"
elif '-' in poly :
    s = "-".join(map(str, result))
    s += "+W"
else :
    s = "".join(map(str, result))
    s += "+W"
    # 만일 적분 상수만 존재하는 경우에는 +W와 같이 표현된다. 앞의 +는 생략 가능하기 때문에 +를 ''로 치환하여 +를 제거해준다.
    if s[0] == '+' :
        s = s.replace("+", "", 1)
print(s)
