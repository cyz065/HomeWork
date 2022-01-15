import sys
N = int(sys.stdin.readline())
M = int(sys.stdin.readline())
stu = list(map(int, sys.stdin.readline().split())) # 추천받은 학생을 나타내는 수열
pic = list(); s = list(); old = 0

while(len(stu) > 0) :
    # 추천받은 학생을 처음부터 pop해서 [학생, 추천 수, 등록 순서]의 list를 만든다.
    name = stu.pop(0)
    rec = 1
    tmp = [name, rec, old]

    # 사진첩에 등록 가능한 공간이 있고, 해당 학생이 사진첩에 있지 않은 경우 사진첩에 등록하고, 사진첩에 등록되어 있음을 표시하기 위해
    # s list에 이름을 추가해 준다.
    if len(pic) < N and name not in s :
        pic.append(tmp)
        s.append(name)
    #s list에 이름이 있는 경우, 즉 사진첩에 이미 올라가 있는 학생인 경우에는 해당 학생을 찾아서 추천수를 1 증가시킨다.
    elif name in s :
        for i in range(len(pic)) :
            if pic[i][0] == name :
                pic[i][1] += 1

    # 사진첩에 등록 가능한 공간이 없고, s에 없는 새로운 학생이 오는 경우 추천순서, 등록 순서 기준으로 사진첩을 정렬해준다.
    else :
        pic = sorted(pic, key = lambda x : (x[1], x[2]))
        # 사진첩에서 가장 처음 오는 학생이 추천순서가 가장 적거나, 등록된지 오래된 학생이므로 이 학생이 제거되고 새로운 학생을 추가한다.
        # s에도 기존의 학생을 새로운 학생으로 대체한 후에, 등록 순서를 나타내는 old를 증가시킨다.
        i = s.index(pic[0][0])
        pic[0][0] = name
        pic[0][1] = rec
        pic[0][2] = old
        s[i] = name
    old += 1

# 학생 순서대로 출력하기 위해 정렬
pic = sorted(pic, key = lambda x : x[0])

for i in range(len(pic)) :
    print(pic[i][0], end = " ")
