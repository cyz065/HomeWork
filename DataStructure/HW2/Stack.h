#pragma once
#include "Doubly_Linked_List.h"

template <class Item>
class Stack {
private :
	dnode<Item>* top_ptr;	// List�� ������ Stack�� head�� �˷��ִ� ������
	size_t used;			// Stack�� size�� �˷��ִ� ����
public :
	Stack();
	Stack(const Stack<Item>& source);
	void push(const Item& entry);
	void pop();
	bool empty() const;
	Item top() const;
	size_t size() const;
};

template <class Item>
Stack<Item>::Stack() {
	/*
	*  Stack�� �����Ǵ� ��� top_ptr�� NULL��, size�� 0���� �ʱ�ȭ
	*/
	top_ptr = NULL;
	used = 0;
}
template <class Item>
Stack<Item>::Stack(const Stack<Item>& source) {
	/*
	* Doubly_Linked_List�� list_copy�Լ��� ����, List�� �����Ѵ�.
	*/
	dnode<Item>* tail_ptr;
	list_copy(source.top_ptr, top_ptr, tail_ptr);
}

template <class Item>
void Stack<Item>::push(const Item& entry) {
	/*
	* Stack�� top_ptr�� ���� ���԰� ������ �̷������ �ϹǷ�, top�� ���� �߰��Ѵ�.
	*/
	list_head_insert(top_ptr, entry);
	used++;
}

template <class Item>
void Stack<Item>::pop() {
	/*
	* Stack�� top_ptr���� ���԰� ������ �̷�� ���Ƿ�, top�� ����Ű�� ����� ���� �����ϰ�
	* Size�� 1 ���ҽ�Ų��.
	*/
	assert(!empty());
	list_head_remove(top_ptr);
	used--;
}

template <class Item>
bool Stack<Item>::empty() const {
	// stack�� size�� 0�� ��� True �ƴ� ��� false�� ��ȯ
	return top_ptr == NULL;
}

template <class Item>
Item Stack<Item>::top() const {
	/*
	* ���� Stack�� top_ptr�� ����Ű�� ����� ���� ��ȯ�Ѵ�.
	*/
	assert(!empty());
	return top_ptr->data();
}

template <class Item>
size_t Stack<Item>::size() const {
	// ���� Stack�� ũ�⸦ ��ȯ
	return used;
}
