import string;

alphabet_dict = dict();
letters = string.ascii_uppercase;  #// A ~ Z 저장
string = input();
string_UpperCase = string.upper();      #// 입력받은 문자열을 모두 대문자로
length = len(string);
count = 0; maximum = 0; same = 0; answer = 0; index = 0;

for i in letters :                     # // 딕셔너리 초기화
        alphabet_dict[i] = 0;

alphabet = list(alphabet_dict.keys());  #// 딕셔너리 Key값만 따로 저장


for i in range(0, len(letters)) :       #// A ~ Z까지의 갯수 Count
        for j in range(0, length) :
                if(alphabet[i] == string_UpperCase[j]) :
                        count += 1;
        alphabet_dict[alphabet[i]] = count;
        count = 0;

for i in letters :                      #// 가장 많은 알파벳 Check
        if(alphabet_dict[i] > maximum) :
                maximum = alphabet_dict[i];
                answer = alphabet[index];
                same = 0;
        elif(alphabet_dict[i] == maximum) :
                same += 1;
        index += 1;

if(same == 0) :
        print(answer);
elif(same != 0) :
        print("?");

