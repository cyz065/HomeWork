def heap_sort(lst):
    def heapify(lst, size, i):
    	largest = i
    	L = 2*i + 1
    	R = 2*i + 2
    	if L<size and lst[i]<lst[L]: largest=L
    	if R<size and lst[largest]<lst[R]: largest=R
    	if largest != i:
    		lst[i], lst[largest] = lst[largest], lst[i]
    		heapify(lst, size, largest)
    size = len(lst)
    for i in range(size, -1, -1): heapify(lst, size, i)
    for i in range(size-1, 0, -1):
    	lst[i], lst[0] = lst[0], lst[i]
    	heapify(lst, i, 0)


N = int(input());
number_list = list();

for i in range(N) :
    tmp = int(input());
    number_list.append(tmp);
    
heap_sort(number_list);

for i in number_list :
    print(i);

