import sys

string = list(); stack = list();
num = 1; bracket = 1; cnt = 0;

while(True) :
    string = list(sys.stdin.readline().strip())

    if('-' in string) :
        break
    else :
        for i in string :
            # {가 오면 스택에 추가
            if i == '{' :
                stack.append(i)
            # 스택의 길이가 0보다 크고, 스택의 top이 {이면 {} 괄호과 완성 되므로 스택에서 {를 제거
            elif len(stack) > 0 and i == '}' and stack[-1] == '{' :
                stack.pop()
            # 쌍을 이루는 {가 없는 경우 }를 추가해준다.
            elif i == '}' :
                stack.append(i)
        # 모든 괄호가 쌍을 이루는 경우
        if len(stack) == 0 :
            print("%d." %num, cnt)
            num += 1
        else :
            # { } -> 0 1
            while(len(stack) > 0) :
                # 괄호 쌍에서 } 자리에 {가 오는 경우 cnt 1증가, 스택에서 top제거 1다음은 0이므로 0으로 변경
                if bracket == 1 and stack[-1] == '{' :
                    cnt += 1
                    bracket = 0
                    stack.pop()
                # 괄호 쌍에서 { 자리에 {가 오는 경우 cnt 1증가, 스택에서 top제거, 0다음은 1이므로 1로 변경
                elif bracket == 0 and stack[-1] == '}' :
                    cnt += 1
                    bracket = 1
                    stack.pop()
                # 괄호 쌍에서 }자리에 1이 오는 경우에는 정상적인 괄호 이므로 top만 제거, 1을 0으로 변경
                elif bracket == 1 and stack[-1] == '}' :
                    bracket = 0
                    stack.pop()
                # 괄호 쌍에서 {자리에 0이 오는 경우에는 정상적인 괄호 이므로 top만 제거, 0을 1로 변경
                elif bracket == 0 and stack[-1] == '{' :
                    bracket = 1
                    stack.pop()
            print("%d." %num, cnt)
            num += 1
            cnt = 0
