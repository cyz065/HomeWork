#pragma once
#include "Doubly_Linked_List.h"

template <class Item>
class Stack {
private :
	dnode<Item>* top_ptr;	// List로 구현한 Stack의 head를 알려주는 포인터
	size_t used;			// Stack의 size를 알려주는 변수
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
	*  Stack이 생성되는 경우 top_ptr을 NULL로, size는 0으로 초기화
	*/
	top_ptr = NULL;
	used = 0;
}
template <class Item>
Stack<Item>::Stack(const Stack<Item>& source) {
	/*
	* Doubly_Linked_List의 list_copy함수를 통해, List를 복사한다.
	*/
	dnode<Item>* tail_ptr;
	list_copy(source.top_ptr, top_ptr, tail_ptr);
}

template <class Item>
void Stack<Item>::push(const Item& entry) {
	/*
	* Stack의 top_ptr을 통해 삽입과 삭제가 이루어져야 하므로, top에 값을 추가한다.
	*/
	list_head_insert(top_ptr, entry);
	used++;
}

template <class Item>
void Stack<Item>::pop() {
	/*
	* Stack의 top_ptr에서 삽입과 삭제가 이루어 지므로, top가 가리키는 노드의 값을 제거하고
	* Size를 1 감소시킨다.
	*/
	assert(!empty());
	list_head_remove(top_ptr);
	used--;
}

template <class Item>
bool Stack<Item>::empty() const {
	// stack의 size가 0인 경우 True 아닌 경우 false를 반환
	return top_ptr == NULL;
}

template <class Item>
Item Stack<Item>::top() const {
	/*
	* 현재 Stack의 top_ptr이 가리키는 노드의 값을 반환한다.
	*/
	assert(!empty());
	return top_ptr->data();
}

template <class Item>
size_t Stack<Item>::size() const {
	// 현재 Stack의 크기를 반환
	return used;
}
