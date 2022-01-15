T = int(input());
k_list = list();
n_list = list();
apartment = list();

for i in range(T) :
    k = int(input());
    n = int(input());
    k_list.append(k);
    n_list.append(n);
    
apartment = [[i for i in range(1, 15)] for j in range(1, 16)];

for i in range(14) :
    for j in range(13) :
        apartment[i+1][j+1] = apartment[i+1][j] + apartment[i][j+1];

for i in range(T) :
    k = k_list[i];
    n = n_list[i];
    print(apartment[k][n-1]);
'''   
# Sol 1)

T = int(input());
k_list = list();
n_list = list();
floor = list();
apartment = list();

for i in range(T) :
    k = int(input());
    n = int(input());
    k_list.append(k);
    n_list.append(n);


floor = [people for people in range(1, 15)];

for i in range(15) :
    apartment.append(floor[:]);

for i in range(14) :
    for j in range(13) :
        apartment[i+1][j+1] = apartment[i+1][j] + apartment[i][j+1];

for i in range(T) :
    k = k_list[i];
    n = n_list[i];
    print(apartment[k][n-1]);

'''
# Sol 2)
'''
import copy;

T = int(input());
case = list();
floor = list();
apartment = list();

for i in range(T) :
    k = int(input());
    n = int(input());
    tmp = tuple();
    tmp += k, n;
    case.append(tmp);

for i in range(1, 15) :
    floor.append(i);

for i in range(15) :
    tmp = copy.deepcopy(floor);
    apartment.append(tmp);

for i in range(14) :
    for j in range(13) :
        apartment[i+1][j+1] = apartment[i+1][j] + apartment[i][j+1];

k = [k[0] for k in case];
n = [n[1] for n in case];

for i in range(T) :
    first, second = k[i], n[i];
    print(apartment[first][second-1]);
'''

# Sol 3)
'''
T = int(input());
k_list = list();
n_list = list();
floor = list();
apartment = list();

for i in range(T) :
    k = int(input());
    n = int(input());
    k_list.append(k);
    n_list.append(n);

floor = [people for people in range(1, 15)];

for i in range(15) :
    apartment.append(floor[:]);

for i in range(14) :
    for j in range(13) :
        apartment[i+1][j+1] = apartment[i+1][j] + apartment[i][j+1];

print(apartment);
for i in range(T) :
    k = k_list[i];
    n = n_list[i];
    print(apartment[k][n-1]);
'''  
# deepcopy VS shallow copy
# for i in range(15) :
#     apartment.append(floor);
#     floor.clear()
# ->이 경우 floor와 apartment는 같은 객체를 참조하기 때문에
#   floor.clear() 실행 이후 apartment = [[]];이 되어 버린다.
# 따라서 이를 해결하기 위해서는 다음과 같이 해주면 된다.
# apartment = [[i for i in range(1, 16)] for j in range(1, 16)];
# -> 굳이 floor만들지 않아도 더블 리스트를 만들 수 있다...
'''
list1 = [];
list2 = [];
list1 = [1, 2, 3];
list2.append(list1); #-> list2.append(list1[:]);
#-> list1을 list2에 append하면 list1과 list2는 같은 객체를 참조하게 되므로
#-> list1의 복사본을 list2에 append해주면 서로 다른 객체를 참조하게 된다.
print(list1);
print(list2);
list1.clear(); -> list1.clear(), del list1[:] '대신 list= []'를 사용하면 서로 영향을 받지 않게 된다.
print(list1);
print(list2);
'''


