'''
import sys;
import collections;

N = int(sys.stdin.readline());
book = list();

for i in range(N) :
    book.append(sys.stdin.readline().rstrip());

book = dict(collections.Counter(book));
book = list(book.items());
book = sorted(book, key = lambda x : (-x[1], x[0]));

print(book[0][0]);
'''
import sys;

N = int(sys.stdin.readline());
book = list(); temp = list();

for i in range(N) :
    title = sys.stdin.readline().rstrip();
    tmp = list();
    tmp.append(title);
    tmp.append(1);
    temp.append(tmp);

for i in temp :
    cnt = temp.count(i);
    tmp = list();
    tmp.append(i[0]);
    tmp.append(cnt);
    book.append(tmp);

book = sorted(book, key = lambda x : (-x[1], x[0]));

print(book[0][0]);
