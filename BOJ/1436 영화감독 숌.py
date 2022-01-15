# Sol 1)
def movie(n) :
    cnt = 0;
    num = 666;
    title = 0;

    while(cnt < n) :
        number = str(num);
        if(number.count(str(666)) >= 1) :
            title = num;
            cnt += 1;
        num += 1;
        
    return title;
        
N = int(input());
print(movie(N));

'''
# Sol 2)
movie_title = list();
number = list();
num = 666;

while(len(movie_title) <= 10000) :
    number = str(num);
    if(number.count(str(666)) >= 1) :
        movie_title.append(num);
    num += 1;
print(movie_title[N-1]);
'''




'''
while True :
    number = str(num);
    if(number.count(str(6)) >= 3) :
        index = number.index(str(6));
        if(number[index] == number[index+1] == number[index+2]) :
            movie_title.append(num);
    num += 1;

    if(len(movie_title) >= 10000) :
        break;
for i in movie_title :
    print(i, end = " ");
 
'''

 # count(66)의 의미는?
 # -> 문자열 List에서 일치하는 것만
 # number리스트의 경우 저장되는 문자열(숫자)이 1개 이므로 count(666)하면 원하는
 # 결과를 얻을 수 있다.
 # count ex) List = [766, 66, 666] => 1개
 # number.count(str(6))은 왜 안되나...?
 # ->60666, 61666 등 첫번째 자리가 6이고 6이 3개 이상인 경우에는 index, indedx + 1, index + 2 조건이 성립 X...
 # 실행속도를 향상 시킬 수 있는 방법은?
 # -> 가능한 movie title을 배열에 저장하지 않고, 원하는 수만 출력해 주면 좀 더 빠르게 가능
