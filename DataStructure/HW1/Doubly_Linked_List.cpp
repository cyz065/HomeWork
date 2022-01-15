#include "Doubly_Linked_List.h"
#include <cassert>
#include <cstdlib>

dnode::dnode(const value_type& init_data, dnode* init_fore, dnode* init_back) {
	data_field = init_data;
	link_fore = init_fore;
	link_back = init_back;
}

void dnode::set_data(const value_type& new_data) {
	// 현재 노드에 data 저장
	data_field = new_data;
}

void dnode::set_link_next(dnode* new_link) {
	// 현재노드의 link_next값을 set
	link_fore = new_link;
}
void dnode::set_link_previous(dnode* new_link) {
	// 현재노드의 link_back값을 set
	link_back = new_link;
}

dnode::value_type dnode::data() const {
	// 현재 노드의 data값 반환
	return data_field;
}

const dnode* dnode::link_next() const {
	// 다음 노드의 주소 반환 데이터의 수정 불가
	return link_fore;
}
const dnode* dnode::link_previous() const {
	// 이전 노드의 주소 반환 데이터의 수정 불가
	return link_back;
}

dnode* dnode::link_next() {
	// 다음 노드의 주소값 반환
	return link_fore;
}
dnode* dnode::link_previous() {
	// 이전 노드의 주소 반환
	return link_back;
}

size_t list_length(const dnode* head_ptr) {
	/*
	* 1. cursor를 통해 list의 마지막 노드까지 탐색하고 answer를 1씩 증가시켜준다.
	* 2. cursor가 NULL인 경우 마지막 노드이므로 answer반환
	*/
	size_t answer = 0;
	const dnode* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link_next()) {
		++answer;
	}
	return answer;
}

dnode* list_search(dnode* head_ptr, const dnode::value_type& target) {
	/*
	*	1. cursor를 통해 list의 마지막 까지 탐색하면서 target값이 존재하는지 확인
	*	2. target값이 존재하는 경우 target값을 갖는 첫번째 노드의 주소값을 반환
	*	3. target값이 존재하지 않는 경우 NULL 반환
	*/
	dnode* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link_next())
		if (target == cursor->data())
			return cursor;
	return NULL;
}

const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target) {
	const dnode* cursor;

	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link_next())
		return cursor;
	return NULL;
}

dnode* list_locate(dnode* head_ptr, size_t position) {
	/*
	*	1. 배열에서 index로 접근 하는 것과 같이 list에서 position의 위치의 주소값 반환
	*/
	dnode* cursor = head_ptr;
	assert(0 < position);
	for (size_t i = 0; (cursor != NULL && i < position - 1); ++i)
		cursor = cursor->link_next();
	return cursor;
}

const dnode* list_locate(const dnode* head_ptr, size_t position) {
	const dnode* cursor = head_ptr;
	assert(0 < position);
	for (size_t i = 0; (cursor != NULL && i < position); ++i)
		cursor = cursor->link_next();
	return cursor;
}

void list_insert(dnode* previous_ptr, const dnode::value_type& entry) {
	/*
	*	1. insert하기 위한 새로운 노드를 생성하고, 새로 생성된 노드의 link_fore값을 이전 노드의 link_fore값을 갖도록 하고
	*	   새로 생성된 노드의 link_back값을 previous_ptr값을 갖도록 하여 서로 연결되도록 한다.
	*	2. previous_ptr의 link_fore값을 insert_ptr로 하여 두 노드가 서로 연결되도록 한다.
	*	3. NULL인 경우는 기존 노드의 마지막에 노드를 추가하는 경우, NULL이 아닌 경우에는 list의 중간에 노드를 insert하는 경우이다.
	*	   NULL이 아닌 경우에는 새로 생성된 노드와 새로 생성된 노드의 다음 노드가 link_back의 연결이 필요하므로 연결해준다.
	*/
	dnode* insert_ptr;
	insert_ptr = new dnode(entry, previous_ptr->link_next(), previous_ptr);
	previous_ptr->set_link_next(insert_ptr);
	if (insert_ptr->link_next() != NULL) {
		insert_ptr->link_next()->link_previous()->set_link_previous(insert_ptr);
	}

}

void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry) {
	/*
	*	1. 새로 생성된 노드가 새로운 head가 된다.
	*	2. 기존 list에 노드가 존재 하는 경우에는 새로 생긴 노드와 기존 노드의 link_back을 연결해 준다.
	*/
	head_ptr = new dnode(entry, head_ptr, NULL);
	if (head_ptr->link_next() != NULL) {
		head_ptr->link_next()->set_link_previous(head_ptr);
	}
}

void list_head_remove(dnode*& head_ptr) {
	/*
	*	1. remove_ptr이 제거할 head를 가리킨다.
	*	2. 새로운 head는 기존 head의 다음 노드가 된다.
	*	3. remove_ptr을 제거하여 head를 제거한다.
	*/
	dnode* remove_ptr;
	remove_ptr = head_ptr;
	head_ptr = head_ptr->link_next();
	delete remove_ptr;

}

void list_remove(dnode* previous_ptr) {
	/*
	*	1. remove_ptr은 제거할 노드를 가리킨다.
	*	2. previous_ptr이 제거할 노드가 원래 가리키던 다음 노드를 가리키도록 한다.
	*	3. remove_ptr의 다음 노드가 remove_ptr의 전 노드를 가리키도록 한다.
	*	4. remove_ptr을 제거한다.
	*/
	dnode* remove_ptr;
	remove_ptr = previous_ptr->link_next();
	previous_ptr->set_link_next(remove_ptr->link_next());
	remove_ptr->link_next()->link_previous()->set_link_previous(remove_ptr->link_previous());
	delete remove_ptr;
}

void list_clear(dnode*& head_ptr) {
	/*
	*  1. list를 head부터 하나씩 제거한다.
	*/
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
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