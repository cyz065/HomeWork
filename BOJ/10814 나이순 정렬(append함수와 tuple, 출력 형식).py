# sol 1
'''
import sys

N = int(sys.stdin.readline());
member = list(); rank = 1;

for i in range(N) :
    tmp = list();
    age, name = sys.stdin.readline().split();
    tmp.append(int(age))
    tmp.append(name)
    tmp.append(rank)
    rank += 1
    member.append(tuple(tmp));

member = sorted(member, key = lambda x : (x[0], x[2]));

for i in range(len(member)) :
    print(member[i][0], member[i][1]);
'''
# sol 2
import sys

N = int(sys.stdin.readline());
member = list();

for i in range(N) :
    age, name = sys.stdin.readline().split();
    rank = 1;
    member.append((int(age), name, rank));
    rank += 1;
    
member = sorted(member, key = lambda x : (x[0], x[2]));

for age, name, rank in member :
    print(age, name);

# append함수에 인자는 1개, 여러값을 추가 할 때에는 괄호로 묶어서
# 추가 해 주면 된다. 그럼 tuple의 형태로 list에 추가가 된다..


