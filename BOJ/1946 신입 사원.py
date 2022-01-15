import sys;

grade = list(); success = list();
T = int(sys.stdin.readline());

for i in range(T) :
    N = int(sys.stdin.readline());
    for i in range(N) :
        g = tuple(map(int, sys.stdin.readline().split()));
        grade.append(g);
    grade.sort();
    success.append(grade[0]);
    temp = grade[0][1];
    for j in range(1, len(grade)) :
        if(temp > grade[j][1]) :
            success.append(grade[j]);
            temp = grade[j][1];
    print(len(success));
    grade.clear();
    success.clear();
