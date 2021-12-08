#pragma once
template<class T>
class StackNode {
public:
	T info;
	StackNode* next;

	StackNode(T info, StackNode* next) {
		this->info = info;
		this->next = next;
	}
};

template<class T>
class Stack
{
private:
	StackNode<T>* top;

public:
	Stack() {
		top = 0;
	}

	bool isEmpty() {
		return top == 0;
	}

	void push(T info) {
		top = new StackNode<T>(info, top);
	}

	T get() {
		if (isEmpty()) return 0;
		return top->info;
	}

	T pop() {
		// more than one element
		StackNode<T>* temp = top;
		top = top->next;
		T el = temp->info;
		delete temp;
		return el;
	}
};

