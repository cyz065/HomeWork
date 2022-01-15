import sys;

N = list(sys.stdin.readline().strip());

if '0' not in N :
    print(-1);

else :
    if sum(map(int, N)) % 3 != 0 :
        print(-1);
    else :
        N.sort(reverse = True);
        print(''.join(N));

'''
import sys;

N = sys.stdin.readline().strip();
number = list();

if '0' not in N :
    print(-1);

else :
    for i in N :
        number.append(int(i));
    if(sum(number) % 3 != 0) :
        print(-1);
    else :
        number = sorted(number, reverse = True);
        for i in number :
            print(i, end = '');
'''

# stdin으로 받은 입력을 list로 하면 각 자리수 별로 끊어서 사용할 수 있다.
