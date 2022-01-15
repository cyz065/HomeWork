import sys
N, M = map(int, sys.stdin.readline().split())
length = 0; string = "";
u = list() # 각 단어 사이에 들어가야할 _의 개수를 저장한 배열
word = [sys.stdin.readline().strip() for x in range(N)]

for i in word :
    length += len(i)
# under = 총 _의 개수
under = M - length;
# a, b = 각 단어 사이에 들어가야할 _의 개수
a = under // (N - 1); b = under % (N - 1)

# 최대값과 최소값의 차이가 1이므로, 나머지가 0이 되도록 a에 1씩 더해준다
# ex) 12 7 -> 1 1 1 1 1 1 1-> 2 2 2 2 2 1 1
for i in range(N - 1 - b) :
    u.append(a)
for i in range(b) :
    u.append(a + 1)


while(len(word) > 1) :
    string += word.pop(0)
    # 다음 단어로 소문자가 오는 경우 더 많은 _가 필요하므로, 뒤에서부터 pop해서 추가
    if word[0] > '_' :
        string += '_' * u[-1]
        u.pop()
    # 다음 단어로 대문자가 오는 경우 적은 _가 필요하므로, 앞에서 부터 pop
    else :
        string += '_' * u[0]
        u.pop(0)
string += word.pop()
print(string)
    
