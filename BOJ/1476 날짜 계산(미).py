import sys;
import math;

E, S, M = map(int, sys.stdin.readline().split());
year = 0;
i = 0; j = 0; k = 0;
while(True) :
    real_S = 28 * j + S;
    real_M = 19 * k + M;
    real_E = 15 * i + E;

    if(real_S > real_E) :
        i += 1;
        real_E = 15 * i + E;
    if(real_S > real_M) :
        k += 1;
        real_M = 19 * k + M;
    if(real_S == real_M and real_S == real_E and real_E == real_M) :
        year = real_E;
        break;
    else :
        j += 1;
    print(year);
    year = math.lcm(real_S, real_M);
    year = math.lcm(year, real_E);
    print(year);
    break;
    print("S : ", real_S);
    print("M : ", real_M);
    print("E : ", real_E);
print(year);

   

