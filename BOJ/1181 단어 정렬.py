N = int(input());
word = list();
word_set = set();
word_tuple = tuple();

for i in range(N) :
    tmp = input();
    word_tuple = (tmp, len(tmp));
    word.append(word_tuple);

print(word); 
word_set = set(word);
word_list = list(word_set);

word_list = sorted(word_list, key = lambda x : (len(x[0]), x[0]));   
word = [i[0] for i in word_list];

for i in word :
    print(i);

print(word_list);


# sorted함수를 사용할 때 key값을 주면 key값의 기준에 따라 정렬이 가능하다.
# 추가로 여러가지 조건을 활용해야 할 때는 람다식을 사용하면 2개 이상의 조건을 활용하여 정렬할 수 있다 하지만
# 람다식의 이용은 tuple자료형이어야 가능하다.
# tuple자료형을 set자료형으로 변환이 가능하다.
# set자료형을 list자료형으로 변환이 가능하다.
# tuple은 "=" 연산자를 이용하여 추가할 수 있다.
# list에 tuple자료형을 append 할 수 있다.
    


'''
word_list = list(word_set);
word_list = sorted(word_list, key = lambda x : x[0]);
word = tuple(word_list);
print(word);
'''
#new_word_list.clear();

'''
for i in range(len(word_list)) :
    new_word_list.append(list(word_list[i]));
    
print(new_word_list);
'''
'''
for i in range(len(word_list) - 1) :
    if(len(word_list[i]) == len(word_list[i+1])) :
        start = i - 1;
        end = i + 1;
        
            

'''
'''
for i in range(len(word_list)) :
    print(word_list[i]);

'''



        
