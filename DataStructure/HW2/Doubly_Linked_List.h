#pragma once
#include <cstdlib>
#include <cassert>
// 다음 노드와 이전 노드를 가리킬 수 있는 dnode 클래스 정의
template <class Item>
class dnode {
public:
	typedef double value_type;
	dnode(const value_type& init_data = value_type(), dnode<Item>* init_fore = NULL, dnode<Item>* init_back = NULL);
	void set_data(const value_type& new_data);
	void set_link_next(dnode* new_link); // 현재 노드에 다음 노드의 link값을 설정 하기 위한 함수
	void set_link_previous(dnode* new_link); // 현재 노드에 이전 노드의 link값을 설정 하기 위한 함수
	value_type data() const;
	const dnode* link_next() const; // 현재노드에서 다음 노드로 이동하기 위한 함수
	const dnode* link_previous() const; // 현재 노드에서 이전 노드로 이동하기 위한 함수
	dnode* link_next();  // 현재 노드에서 다음 노드로 이동하면서 data의 수정을 위한 함수
	dnode* link_previous(); // 현재 노드에서 이전 노드로 이동하면서 data의 수정을 위한 함수
private:
	value_type data_field; // 노드에 저장될 데이터 값
	dnode* link_fore; // 현재 노드에서 다음 노드의 주소값을 저장하기 위한 포인터 변수
	dnode* link_back; // 현재 노드에서 이전 노드의 주소값을 저장하기 위한 포인터 변수
};

template <class Item>
dnode<Item>::dnode(const value_type& init_data, dnode<Item>* init_fore, dnode<Item>* init_back) {
	data_field = init_data;
	link_fore = init_fore;
	link_back = init_back;
}
template <class Item>
void dnode<Item>::set_data(const value_type& new_data) {
	// 현재 노드에 data 저장
	data_field = new_data;
}
template <class Item>
void dnode<Item>::set_link_next(dnode<Item>* new_link) {
	// 현재노드의 link_next값을 set
	link_fore = new_link;
}
template <class Item>
void dnode<Item>::set_link_previous(dnode<Item>* new_link) {
	// 현재노드의 link_back값을 set
	link_back = new_link;
}
template <class Item>
typename dnode<Item>::value_type dnode<Item>::data() const {
	// 현재 노드의 data값 반환
	return data_field;
}
template <class Item>
const dnode<Item>* dnode<Item>::link_next() const {
	// 다음 노드의 주소 반환 데이터의 수정 불가
	return link_fore;
}
template <class Item>
const dnode<Item>* dnode<Item>::link_previous() const {
	// 이전 노드의 주소 반환 데이터의 수정 불가
	return link_back;
}
template <class Item>
dnode<Item>* dnode<Item>::link_next() {
	// 다음 노드의 주소값 반환
	return link_fore;
}
template <class Item>
dnode<Item>* dnode<Item>::link_previous() {
	// 이전 노드의 주소 반환
	return link_back;
}

template <class Item>
void list_insert(dnode<Item>* previous_ptr, const typename dnode<Item>::value_type& entry) {
	/*
	*	1. insert하기 위한 새로운 노드를 생성하고, 새로 생성된 노드의 link_fore값을 이전 노드의 link_fore값을 갖도록 하고
	*	   새로 생성된 노드의 link_back값을 previous_ptr값을 갖도록 하여 서로 연결되도록 한다.
	*	2. previous_ptr의 link_fore값을 insert_ptr로 하여 두 노드가 서로 연결되도록 한다.
	*	3. NULL인 경우는 기존 노드의 마지막에 노드를 추가하는 경우, NULL이 아닌 경우에는 list의 중간에 노드를 insert하는 경우이다.
	*	   NULL이 아닌 경우에는 새로 생성된 노드와 새로 생성된 노드의 다음 노드가 link_back의 연결이 필요하므로 연결해준다.
	*/
	dnode<Item>* insert_ptr;
	insert_ptr = new dnode<Item>(entry, previous_ptr->link_next(), previous_ptr);
	previous_ptr->set_link_next(insert_ptr);
	if (insert_ptr->link_next() != NULL) {
		insert_ptr->link_next()->link_previous()->set_link_previous(insert_ptr);
	}

}

template <class Item>
void list_head_insert(dnode<Item>*& head_ptr, const typename dnode<Item>::value_type& entry) {
	/*
	*	1. 새로 생성된 노드가 새로운 head가 된다.
	*	2. 기존 list에 노드가 존재 하는 경우에는 새로 생긴 노드와 기존 노드의 link_back을 연결해 준다.
	*/
	head_ptr = new dnode<Item>(entry, head_ptr, NULL);
	if (head_ptr->link_next() != NULL) {
		head_ptr->link_next()->set_link_previous(head_ptr);
	}
}
template <class Item>
void list_head_remove(dnode<Item>*& head_ptr) {
	/*
	*	1. remove_ptr이 제거할 head를 가리킨다.
	*	2. 새로운 head는 기존 head의 다음 노드가 된다.
	*	3. remove_ptr을 제거하여 head를 제거한다.
	*/
	dnode<Item>* remove_ptr;
	remove_ptr = head_ptr;
	head_ptr = head_ptr->link_next();
	delete remove_ptr;

}

template <class Item>
void list_clear(dnode<Item>*& head_ptr) {
	/*
	*  1. list를 head부터 하나씩 제거한다.
	*/
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}
template <class Item>
void list_copy(const dnode<Item>* source_ptr, dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
	/*
	*	1. source_ptr이 NULL 인 경우 복사할 대상이 없으므로 return
	*	2. source_ptr이 가리키는 노드의 data값을 복사해서 새롭게 node를 생성하고 이후, 이 노드가 head가 된다.
	*	3. tail_ptr을 head_ptr로 하여 tail_ptr을 다음 노드로 이동한다.
	*	4. source_ptr이 source의 다음 노드를 가리키도록 한 후, source값이 NULL이 될 때 까지, 끝 노드에 data값을 insert한다.
	*	5. data값이 insert되면 tail_ptr은 마지막 노드를 가리키기 위해 오른쪽으로 한칸 씩 이동한다.
	*/
	head_ptr = NULL;
	tail_ptr = NULL;
	if (source_ptr == NULL)
		return;
	list_head_insert(head_ptr, source_ptr->data());
	tail_ptr = head_ptr;
	source_ptr = source_ptr->link_next();
	while (source_ptr != NULL) {
		list_insert(tail_ptr, source_ptr->data());
		tail_ptr = tail_ptr->link_next();
		source_ptr = source_ptr->link_next();
	}
}