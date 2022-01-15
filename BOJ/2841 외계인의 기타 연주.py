import sys

N, P = map(int, sys.stdin.readline().split())
one = list(); two = list(); three = list(); four = list(); five = list(); six = list()

melody = list(); cnt = 0

for i in range(N) :
    line, p = map(int, sys.stdin.readline().split())
    melody.append((line,p))

for i in range(len(melody)) :
    if(melody[i][0] == 1) :
        if(len(one) == 0 or one[-1] < melody[i][1]) :
            one.append(melody[i][1])
            cnt += 1
        elif(one[-1] > melody[i][1]) :
            while(len(one) > 0 and one[-1] > melody[i][1]) :
                one.pop();
                cnt += 1
            if(len(one) == 0 or one[-1] < melody[i][1]) :
                one.append(melody[i][1])
                cnt += 1
                
    elif(melody[i][0] == 2) :
        if(len(two) == 0 or two[-1] < melody[i][1]) :
            two.append(melody[i][1])
            cnt += 1
        elif(two[-1] > melody[i][1]) :
            while(len(two) > 0 and two[-1] > melody[i][1]) :
                two.pop();
                cnt += 1
            if(len(two) == 0 or two[-1] < melody[i][1]) :
                two.append(melody[i][1])
                cnt += 1

    elif(melody[i][0] == 3) :
        if(len(three) == 0 or three[-1] < melody[i][1]) :
            three.append(melody[i][1])
            cnt += 1
        elif(three[-1] > melody[i][1]) :
            while(len(three) > 0 and three[-1] > melody[i][1]) :
                three.pop();
                cnt += 1
            if(len(three) == 0 or three[-1] < melody[i][1]) :
                three.append(melody[i][1])
                cnt += 1

    elif(melody[i][0] == 4) :
        if(len(four) == 0 or four[-1] < melody[i][1]) :
            four.append(melody[i][1])
            cnt += 1
        elif(four[-1] > melody[i][1]) :
            while(len(four) > 0 and four[-1] > melody[i][1]) :
                four.pop();
                cnt += 1
            if(len(four) == 0 or four[-1] < melody[i][1]) :
                four.append(melody[i][1])
                cnt += 1

    elif(melody[i][0] == 5) :
        if(len(five) == 0 or five[-1] < melody[i][1]) :
            five.append(melody[i][1])
            cnt += 1
        elif(five[-1] > melody[i][1]) :
            while(len(five) > 0 and five[-1] > melody[i][1]) :
                five.pop();
                cnt += 1
            if(len(five) == 0 or five[-1] < melody[i][1]) :
                five.append(melody[i][1])
                cnt += 1

    elif(melody[i][0] == 6) :
        if(len(six) == 0 or six[-1] < melody[i][1]) :
            six.append(melody[i][1])
            cnt += 1
        elif(six[-1] > melody[i][1]) :
            while(len(six) > 0 and six[-1] > melody[i][1]) :
                six.pop();
                cnt += 1
            if(len(six) == 0 or six[-1] < melody[i][1]) :
                six.append(melody[i][1])
                cnt += 1
print(cnt)
