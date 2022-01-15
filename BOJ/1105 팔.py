import sys
L, R = sys.stdin.readline().split()
minimum = 0

# L, R 둘 중에 8의 개수가 0인 수가 있다면 그 수가 8의 개수가 최소인 수가 된다.
if L.count('8') == 0 or R.count('8') == 0 :
    minimum = 0
    print(minimum)
else :
    # 두 수의 길이가 같은 경우 가장 큰 자리수 부터 비교해서 가장 큰 자리수가 8인 경우에는 두 수의 앞자리가 8이 되므로 무조건
    # 8이 1개 이상 존재하게 된다. 따라서 minimum을 증가시켜 주고, 8이 아닌 다른 숫자인 경우에는 다른 자리수와 비교해준다.
    # 두 수의 앞 자리수가 다르고, 8이 없다면 8의 최솟값은 0이 되므로 break
    if len(L) == len(R) :
        for i in range(len(L)) :
            if L[i] == R[i] and L[i] == '8' :
                minimum += 1
            elif R[i] == L[i] :
                continue
            else :
                break
        print(minimum)
    # 두 수의 자리수가 다른 경우에는 8이 없는 자연수가 무조건 1개 이상 존재한다. 따라서 최솟값은 0이된다.
    else :
        minimum = 0
        print(minimum)
