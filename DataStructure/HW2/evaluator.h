#pragma once
#include "Doubly_Linked_List.h"
#include "Stack.h"
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

class evaluator {
public :
	string read_expression();
	string convert_to_postfix(string s);
	double evaluate_postfix(string s);
private :
	string input_string;
};

/* 
*  각각의 연산자들의 우선순위를 결정한다.
*  '('의 경우 우선순위를 가장 낮게 설정하여, '('이 top이고, 연산자가 들어오는 경우, 
*  연산자가 stack에 push되도록 한다.
*/
int prec(char c) {
	if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else if (c == '(')
		return 0;
}

string evaluator::read_expression() {
	// 변환하고자 하는 infix식을 입력하고, 입력받은 infix식을 반환한다.
	cout << "Input_string : ";
	getline(cin, input_string);
	return input_string;
}

// 숫자 or 변수는 result_string으로 바로
// 연산자 또는 괄호는 stack으로 추가;
string evaluator::convert_to_postfix(string s) {
	string result_string;
	Stack<char> stack;
	/*
	* '-'의 경우 음수를 나타내는 -, 빼기 연산을 위한 - 총 2가지의 경우가 발생한다.
	* 다음 3가지 경우에 음수를 나타내기 위한 -가 된다.
	* i) '('바로 다음에 존재하는 '-'
	* ii) 문자열의 제일 앞에 존재하는 '-'
	* iii) '-'앞에 다른 연산자("+-/*")가 존재하는 경우
	* 위 3가지 경우가 아닌 경우에는 모두 빼기 연산을 위한 '-'가 된다.
	* 
	* 따라서 음수를 나타내기 위한 '-'인 경우 빼기 연산의 '-'와 구분하기 위해 음수를 나타내는 '-'를 '~'로 변경해 준다.
	*/
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != '-')
			continue;
		if (i == 0 || s[i - 1] == '(' || strchr("+-/*", s[i - 1]) != NULL) {
			s[i] = '~';
		}
	}

	/*
	*	입력받은 문자열을 차례대로 읽어, 경우에 따라 처리해 준다.
	*	1. 만약 숫자, 소수점, '~', 변수인 경우 : 그대로 result_string에 출력을 해준다.
	*/
	for (int i = 0; i < s.length(); ++i) {
		if (isdigit(s[i]) || isalpha(s[i]) || s[i] == '.' || s[i] == '~') {
			result_string += s[i];
		}

		/*
		* 만약 연산자인 경우에는 2가지 경우에 해당하는 경우에는 stack의 top에 존재하는 연산자를 pop하고 s[i]를 push한다.
		* i) 스택이 비어있지 않은경우
		* ii) s[i]의 우선순위가 stack의 top에 존재하는 연산자보다 낮거나 같은 경우
		* iii) stack의 top이 '('가 아닌 경우
		* 3가지 경우에 해당하지 않는 경우에는 stack에 연산자를 push 해준다.
		*/
		else if (strchr("+-*/", s[i])) {
			result_string += " ";
			while ((!stack.empty()) && (prec(s[i]) <= prec(stack.top()))) {
				result_string += stack.top();
				result_string += " ";
				stack.pop();
			}
			stack.push(s[i]);
		}

		else if (s[i] == '(') {
			stack.push(s[i]);
		}
		/*
		* ')'인 경우에는 stack의 top이 '('가 될때까지 pop을 해주고, result_string에 출력한다.
		*/
		else if (s[i] == ')') {
			while (stack.top() != '(') {
				result_string += " ";
				result_string += stack.top();
				stack.pop();
			}
			stack.pop();
		}
	}
	/*
	* Stack에 일부 연산자가 남아있는 경우 모든 연산자들을 pop하여 result_string에 출력한다.
	*/
	while (!stack.empty()) {
		result_string += " ";
		result_string += stack.top();
		stack.pop();
	}

	/* 음수의 '-'와 빼기 연산의 '-'구분을 위해 사용했던 '~'를 다시 '-'로 변환하여
	* postfix로 바뀐 result_string을 return한다.
	*/
	for (int i = 0; i < result_string.length(); i++) {
		if (result_string[i] == '~')
			result_string[i] = '-';
	}

	return result_string;
}


double evaluator::evaluate_postfix(string s) {
	double num1;
	double num2;
	double input_num;
	double result;
	string tmp;
	Stack<double> evaluation;

	for (int i = 0; i < s.length(); i++) {
		/*
		* s[i]가 문자인 경우에는 변수에 해당하므로, 변수에 값을 입력받는다.
		* s[i]에 존재하는 값을 input_num의 수로 변경한다.
		* input_num이 정수인 경우에는 정수값으로 치환, 실수인 경우에는 그대로 치환
		*/
		if (isalpha(s[i])) {
			cout << "Input number of " << s[i] << " : ";
			cin >> input_num;
			if (input_num - int(input_num) == 0) {
				s.replace(i, 1, to_string(int(input_num)));
			}
			else {
				s.replace(i, 1, to_string(input_num));
			}
		}
	}
	/*
	* s[i]가 숫자 또는 '.'인 경우 공백이 나올때까지 tmp에 더해준다.
	* tmp는 최종적인 하나의 숫자가 된다. 이후, 이 숫자를 stack에 push해준다.
	*/
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) || s[i] == '.') {
			while (s[i] != ' ') {
				tmp += s[i];
				i++;
			}
			evaluation.push(stod(tmp));
			tmp = "";
		}
		/*
		* '-'인 경우, '-'다음에 공백이 존재하지 않는 경우에는 음수의 '-'이므로, 이 또한 숫자가 된다.
		* 따라서 tmp에 추가해주고, 이 숫자를 stack에 push한다.
		*/
		else if (i + 1 < s.length() && s[i] == '-' && !isspace(s[i + 1])) {
			while (!isspace(s[i])) {
				tmp += s[i];
				i++;
			}
			evaluation.push(stod(tmp));
			tmp = "";
		}
		/*
		* s[i]가 연산자인 경우, stack에서 두 수를 pop한 후, 해당하는 연산자에 따라 연산 후, 연산 결과를
		* stack에 push한다.
		*/
		else if (strchr("+-/*", s[i])) {
			num2 = evaluation.top();
			evaluation.pop();
			num1 = evaluation.top();
			evaluation.pop();
			if (s[i] == '+')
				evaluation.push(num1 + num2);
			else if (s[i] == '-')
				evaluation.push(num1 - num2);
			else if (s[i] == '*')
				evaluation.push(num1 * num2);
			else if (s[i] == '/')
				evaluation.push(num1 / num2);
		}
	}
	// 최종적으로 stack에는 1개의 숫자만 남개된다. 이 숫자가 최종적인 연산의 결과가 된다.
	// 이 결과를 반환 해 주면 stack의 postfix연산 결과가 반환된다.
	result = evaluation.top();
	evaluation.pop();
	return result;
}
