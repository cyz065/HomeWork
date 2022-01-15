#include "Doubly_Linked_List.h"
#include "Stack.h"
#include "evaluator.h"
#include <iostream>
using namespace std;
int main(void) {
	evaluator e1;

	string infix = e1.read_expression();
	cout << "infix expression : " << infix << endl;

	string postfix = e1.convert_to_postfix(infix);
	cout << "infix to postifx : " << postfix << endl;

	double result = e1.evaluate_postfix(postfix);
	cout << "result : ";
	printf("%g\n", result);
}
