#include "Bag.h"
#include "Doubly_Linked_List.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(void) {
	Bag b1;
	cout << "insert\n";
	b1.insert(10);
	b1.insert(10);
	b1.insert(10);
	b1.insert(20);
	b1.insert(4);
	b1.show_contents();
	cout << "\n";

	cout << "erase_one\n";
	b1.erase_one(9);
	b1.show_contents();
	b1.erase_one(10);
	b1.show_contents();
	cout << "\n";

	cout << "count\n";
	cout << b1.count(10) << endl;
	cout << b1.count(9) << endl;
	cout << "\n";

	cout << "operator +\n";
	Bag b2;
	b2.insert(1);
	b2.insert(3);
	Bag b6;
	Bag b3 = b1 + b2;
	Bag b7 = b1 + b6;
	b3.show_contents();
	b7.show_contents();
	cout << "\n";

	cout << "operator +=\n";
	b2 += b1;
	b2.show_contents();
	cout << "\n";

	cout << "operator =\n";
	Bag b4;
	b4 = b1;
	b4.show_contents();
	cout << "\n";

	cout << "operator ==\n";
	cout << (b4 == b1) << endl;
	cout << (b1 == b2) << endl;
	cout << "\n";

	cout << "operator !=\n";
	cout << (b4 != b1) << endl;
	cout << (b1 != b2) << endl;
	cout << "\n";

	cout << "sort\n";
	Bag b5;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++) {
		int num = rand() % 1000 + 1;
		b5.insert(num);
	}
	cout << "Before sorting\n";
	b5.show_contents();
	b5.sort();
	cout << "After Sorting\n";
	b5.show_contents();
}