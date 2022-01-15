import sys

while(True) :
    string = sys.stdin.readline().strip()

    if string == "0" :
        break
    else :
        if(string[::1] == string[::-1]) :
            print("yes")
        else :
            print("no")
