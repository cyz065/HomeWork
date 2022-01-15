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
*  ������ �����ڵ��� �켱������ �����Ѵ�.
*  '('�� ��� �켱������ ���� ���� �����Ͽ�, '('�� top�̰�, �����ڰ� ������ ���, 
*  �����ڰ� stack�� push�ǵ��� �Ѵ�.
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
	// ��ȯ�ϰ��� �ϴ� infix���� �Է��ϰ�, �Է¹��� infix���� ��ȯ�Ѵ�.
	cout << "Input_string : ";
	getline(cin, input_string);
	return input_string;
}

// ���� or ������ result_string���� �ٷ�
// ������ �Ǵ� ��ȣ�� stack���� �߰�;
string evaluator::convert_to_postfix(string s) {
	string result_string;
	Stack<char> stack;
	/*
	* '-'�� ��� ������ ��Ÿ���� -, ���� ������ ���� - �� 2������ ��찡 �߻��Ѵ�.
	* ���� 3���� ��쿡 ������ ��Ÿ���� ���� -�� �ȴ�.
	* i) '('�ٷ� ������ �����ϴ� '-'
	* ii) ���ڿ��� ���� �տ� �����ϴ� '-'
	* iii) '-'�տ� �ٸ� ������("+-/*")�� �����ϴ� ���
	* �� 3���� ��찡 �ƴ� ��쿡�� ��� ���� ������ ���� '-'�� �ȴ�.
	* 
	* ���� ������ ��Ÿ���� ���� '-'�� ��� ���� ������ '-'�� �����ϱ� ���� ������ ��Ÿ���� '-'�� '~'�� ������ �ش�.
	*/
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != '-')
			continue;
		if (i == 0 || s[i - 1] == '(' || strchr("+-/*", s[i - 1]) != NULL) {
			s[i] = '~';
		}
	}

	/*
	*	�Է¹��� ���ڿ��� ���ʴ�� �о�, ��쿡 ���� ó���� �ش�.
	*	1. ���� ����, �Ҽ���, '~', ������ ��� : �״�� result_string�� ����� ���ش�.
	*/
	for (int i = 0; i < s.length(); ++i) {
		if (isdigit(s[i]) || isalpha(s[i]) || s[i] == '.' || s[i] == '~') {
			result_string += s[i];
		}

		/*
		* ���� �������� ��쿡�� 2���� ��쿡 �ش��ϴ� ��쿡�� stack�� top�� �����ϴ� �����ڸ� pop�ϰ� s[i]�� push�Ѵ�.
		* i) ������ ������� �������
		* ii) s[i]�� �켱������ stack�� top�� �����ϴ� �����ں��� ���ų� ���� ���
		* iii) stack�� top�� '('�� �ƴ� ���
		* 3���� ��쿡 �ش����� �ʴ� ��쿡�� stack�� �����ڸ� push ���ش�.
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
		* ')'�� ��쿡�� stack�� top�� '('�� �ɶ����� pop�� ���ְ�, result_string�� ����Ѵ�.
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
	* Stack�� �Ϻ� �����ڰ� �����ִ� ��� ��� �����ڵ��� pop�Ͽ� result_string�� ����Ѵ�.
	*/
	while (!stack.empty()) {
		result_string += " ";
		result_string += stack.top();
		stack.pop();
	}

	/* ������ '-'�� ���� ������ '-'������ ���� ����ߴ� '~'�� �ٽ� '-'�� ��ȯ�Ͽ�
	* postfix�� �ٲ� result_string�� return�Ѵ�.
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
		* s[i]�� ������ ��쿡�� ������ �ش��ϹǷ�, ������ ���� �Է¹޴´�.
		* s[i]�� �����ϴ� ���� input_num�� ���� �����Ѵ�.
		* input_num�� ������ ��쿡�� ���������� ġȯ, �Ǽ��� ��쿡�� �״�� ġȯ
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
	* s[i]�� ���� �Ǵ� '.'�� ��� ������ ���ö����� tmp�� �����ش�.
	* tmp�� �������� �ϳ��� ���ڰ� �ȴ�. ����, �� ���ڸ� stack�� push���ش�.
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
		* '-'�� ���, '-'������ ������ �������� �ʴ� ��쿡�� ������ '-'�̹Ƿ�, �� ���� ���ڰ� �ȴ�.
		* ���� tmp�� �߰����ְ�, �� ���ڸ� stack�� push�Ѵ�.
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
		* s[i]�� �������� ���, stack���� �� ���� pop�� ��, �ش��ϴ� �����ڿ� ���� ���� ��, ���� �����
		* stack�� push�Ѵ�.
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
	// ���������� stack���� 1���� ���ڸ� �����ȴ�. �� ���ڰ� �������� ������ ����� �ȴ�.
	// �� ����� ��ȯ �� �ָ� stack�� postfix���� ����� ��ȯ�ȴ�.
	result = evaluation.top();
	evaluation.pop();
	return result;
}
