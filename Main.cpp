#include <iostream>
#include <string>
#include "Stack.h"
#include<math.h>
using namespace std;

bool isPalindrome(string);
char evaluate(string);

double result(double before, double after, char operate) {
	switch (operate) {
	case '^':
		return pow(before, after);
		break;
	case '*':
		return (before * after);
		break;
	case '/':
		return (before / after);
		break;
	case '+':
		return (before + after);
		break;
	case '-':
		return (before - after);
		break;
	}
}

double eval(string eq) {
	Stack<double> num;
	Stack<char> op;
	Stack<int> pri;

	for (int i = 0; i < eq.length(); i++) {
		// get number
		if (eq[i] >= '0' && eq[i] <= '9') {
			num.push(0);
			while (eq[i] >= '0' && eq[i] <= '9' && i < eq.length()) {
				num.push(num.pop() * 10 + eq[i] - '0');
				i++;
			}
			i--;
		}
		// decimal number
		else if (eq[i] == '.') {
			if (i == 0 || !(eq[i - 1] >= '0' && eq[i - 1] <= '9')) num.push(0);
			int d = 1;
			i++;
			while (eq[i] >= '0' && eq[i] <= '9' && i < eq.length()) {
				num.push(num.pop() + (eq[i] - '0') / pow(10, d++));
				i++;
			}
			i--;
		}
		// solve ()
		else if (eq[i] == ')') {
			while (pri.get() != 1 && !pri.isEmpty()) {
				double after = num.pop();
				double before = num.pop();
				char operate = op.pop();
				pri.pop();
				num.push(result(before, after, operate));
			}
			op.pop();
			pri.pop();
		}
		// operators
		else {
			char o = eq[i];
			int p = 0;
			switch (o) {
			case '(':
				p = 1;
				break;
			case '^':
				p = 2;
				break;
			case '*':
			case '/':
				p = 3;
				break;
			case '+':
			case '-':
				p = 4;
				break;
			}
			while (!pri.isEmpty() && p >= pri.get() && pri.get() != 1) {
				double after = num.pop();
				double before = num.pop();
				char operate = op.pop();
				pri.pop();
				num.push(result(before, after, operate));
			}
			op.push(o);
			pri.push(p);
		}
	}
	while (!op.isEmpty()) {
		double after = num.pop();
		double before = num.pop();
		char operate = op.pop();
		pri.pop();
		num.push(result(before, after, operate));
	}
	return num.get();
}

int main() {

	/*Stack<char> stack;
	stack.push('1');
	stack.push('2');
	stack.push('3');

	cout << stack.pop() << endl;
	cout << stack.pop() << endl;
	cout << stack.pop() << endl;*/

	cout << (isPalindrome("test") ? "Yes" : "No") << endl;
	cout << (isPalindrome("hellolleh") ? "Yes" : "No") << endl;

	cout << evaluate("(20*2+2)/2") << endl;

	cout << eval("(20*2+2)/.5") << endl;
	cout << eval("(4^(1+3))") << endl;

	return 1;
}

bool isPalindrome(string str) {

	/*// method 1
	Stack<char> stack;
	int length = str.length(), mid = length / 2, i = 0;

	while (i < mid) {
		stack.push(str[i]);
		i++;
	}

	if (length % 2 != 0) i++; // if length is odd (skip mid)

	while (i < length) { // check
		if (stack.pop() != str[i]) return false;
		i++;
	}
	return true;*/

	//// usign for loop
	//int length = str.length();
	//for (int i = 0/*first index*/, j = length - 1/*last index*/; j > i; i++, j--) {
	//	if (str[i] != str[j]) return false;
	//}
	//return true;

	// using stack
	Stack<char> stack;
	for (int i = 0; i < str.length(); i++) stack.push(str[i]);
	for (int i = 0; i < str.length(); i++) if (stack.pop() != str[i]) return false;
	return true;

}

char evaluate(string expr) {
	Stack<char> numbers, operators, ope;
	char op;
	int next, before, result = 0;
	for (int i = 0; i < expr.length(); i++) {
		// evaluate ()
		if (expr[i] == '(') {
			i++;
			while (expr[i] != ')') {
				// evaluate * and /
				if (expr[i] == '*' || expr[i] == '/') {
					op = expr[i];
					before = numbers.pop() - '0';
					i++;
					next = expr[i] - '0';
					switch (op) {
					case '*':
						result = before * next;
						break;
					case '/':
						result = before / next;
						break;
					}
					numbers.push(result + '0');
				}
				// evaluate + and -
				else if (expr[i] == '+' || expr[i] == '-')
					ope.push(expr[i]);
				else
					numbers.push(expr[i]);
				i++;
			}
			i++;
			while (!ope.isEmpty()) {
				op = ope.pop();
				next = numbers.pop() - '0'; // '0' = 48, '1' = 49 .....
				before = numbers.pop() - '0';
				switch (op) {
				case '+':
					result = before + next;
					break;
				case '-':
					result = before - next;
					break;
				}
				numbers.push(result + '0');
			}
		}

		// evaluate * and /
		if (expr[i] == '*' || expr[i] == '/') {
			op = expr[i];
			before = numbers.pop() - '0';
			i++;
			next = expr[i] - '0';
			switch (op) {
			case '*':
				result = before * next;
				break;
			case '/':
				result = before / next;
				break;
			}
			numbers.push(result + '0');
		}
		// evaluate + and -
		else if (expr[i] == '+' || expr[i] == '-')
			operators.push(expr[i]);
		else
			numbers.push(expr[i]);
	}

	while (!operators.isEmpty()) {
		op = operators.pop();
		next = numbers.pop() - '0'; // '0' = 48, '1' = 49 .....
		before = numbers.pop() - '0';
		switch (op) {
		case '+':
			result = before + next;
			break;
		case '-':
			result = before - next;
			break;
		}
		numbers.push(result + '0');
	}
	return numbers.pop();
}
