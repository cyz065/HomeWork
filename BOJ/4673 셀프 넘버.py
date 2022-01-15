# 1

number_list = list();

def selfNumber(end) :
    num_list = list();
    num = list();
    result = 0;
    
    for i in range(1, end + 1) :
        num_list.append(i);

    for i in range(1, len(num_list)) :
        num.append(i);
        tmp = i;
        if(i >= 10) :
            for i in range(len(str(i))) :
                num.append(tmp // 10 ** (len(str(tmp)) - 1));
                tmp = tmp % 10 ** (len(str(tmp)) - 1);
        else :
            num.append(tmp);
        for i in num :
            result += i;

        if(result in num_list) :
            num_list.remove(result);
        result = 0;
        num.clear();

    return num_list;

number_list = selfNumber(10000);
for i in number_list :
    print(i);
'''
# 2

def selfNumber(end, lst) :
    num = list();
    result = 0;
    
    for i in range(1, end + 1) :
        lst.append(i);

    for i in range(1, len(lst)) :
        num.append(i);
        tmp = i;
        if(i >= 10) :
            for i in range(len(str(i))) :
                num.append(tmp // 10 ** (len(str(tmp)) - 1));       ## 각 숫자의 자리수 구하기
                tmp = tmp % 10 ** (len(str(tmp)) - 1);
        else :
            num.append(tmp);
        for i in num :
            result += i;

        if(result in lst) :
            lst.remove(result);
        result = 0;
        num.clear();

    return lst;

number_list = list();
selfNumber(10000, number_list);

for i in number_list :
    print(i);

'''
'''
# 3
        
for i in range(1, 10001) :
    number_list.append(i);

for i in range(1, len(number_list)) :
    number.append(i);
    tmp = i;
    if(i >= 10) :
        for i in range(len(str(i))) :
            number.append(tmp // 10 ** (len(str(tmp)) - 1));
            tmp = tmp % 10 ** (len(str(tmp)) - 1);
    else :
        number.append(tmp);
    for i in number :
        result += i;

    if(result in number_list) :
        number_list.remove(result);
    result = 0
    number.clear();

for i in number_list :
    print(i);
'''


        
        






        
   


