import sys;

wood = list(map(int, sys.stdin.readline().split()));
sorted_wood = sorted(wood);

for i in range(1, len(wood)) :
    for j in range(0, len(wood)-1) :
        if wood[j] > wood[j+1] :
            wood[j], wood[j + 1] = wood[j + 1], wood[j]
            print(' '.join(map(str, wood)));
            #print(*wood);
        if sorted_wood == wood :
            break;

# print(*list) -> list의 모든 elements를 괄호 없이 공백을 기준으로 출력 가능
# ex) wood = [1, 2, 3, 4, 5]
# print(*wood) = 1 2 3 4 5
# cf) https://www.geeksforgeeks.org/print-lists-in-python-4-different-ways/
