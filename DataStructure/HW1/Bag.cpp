#include "Doubly_Linked_List.h"
#include "Bag.h"
#include <cassert>
#include <iostream>
#include <algorithm>

Bag::Bag() {
	head_ptr = NULL;
	many_nodes = 0;
}

Bag::Bag(const Bag& source) {
	dnode* tail_ptr;
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

Bag::~Bag() {
	list_clear(head_ptr);
	many_nodes = 0;
}

void Bag::operator=(const Bag& source) {
	/*
	* 1. 자기 자신에 대한 연산자 호출인 경우 '=' 연산자가 의미가 없기 때문에 return
	* 2. 기존에 존재하는 객체를 제거하고 source 객체의 data값을 복사해서 새로운 bag을 생성한다.
	* 3. many_nodes값을 source값으로 변경한다.
	*/
	dnode* tail_ptr;
	if (this == &source)
		return;
	list_clear(head_ptr);
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

void Bag::operator+=(const Bag& addend) {
	/*
	*	1. addend에 노드가 존재하는 경우 addend객체의 노드를 하나 씩 복사한다.
	*	2. 복사가 다 끝나면 기존 bag객체의 head를 복사가 끝난 마지막 노드와 연결한다.
	*	3. head가 변경되었기 때문에 head를 copy_head_ptr로 변경
	*	4. 노드의 개수가 변경 되었기 때문에 many_nodes를 변경
	*/
	dnode* copy_tail_ptr;
	dnode* copy_head_ptr;
	if (addend.many_nodes > 0) {
		list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
		copy_tail_ptr->set_link_next(head_ptr);
		head_ptr = copy_head_ptr;
		many_nodes += addend.many_nodes;
	}
}

bool Bag::erase_one(const dnode::value_type& target) {
	/*
	*	1. target값을 갖는 첫번째 노드를 찾는다.
	*	2. target_ptr이 NULL인 경우, target값이 존재 하지 않기 때문에 false 반환
	*	3. target이 존재하는 경우 target노드를 제거할 경우에는 이전 노드와 다음 노드를 새롭게 연결해 주어야 하기 때문에 번거롭다.
	*	   따라서 target값이 존재하는 경우에는 target값을 첫번째 노드(head)의 값과 변경한 후에 head만 제거해준다.
	*	4. 이렇게 하면 중간의 노드들을 번거롭게 새로 연결해 주는 것 대신 head만 제거하면 되어 편리하다.
	*	5. node가 제거 되었기 때문에 many_nodes값을 1 감소시킨 후 true 반환
	*/
	dnode* target_ptr;
	target_ptr = list_search(head_ptr, target);
	if (target_ptr == NULL)
		return false;
	target_ptr->set_data(head_ptr->data());
	list_head_remove(head_ptr);
	--many_nodes;
	return true;
}

Bag::size_type Bag::count(const dnode::value_type& target) const {
	/*
	* 1. target값을 가지고 있는 첫번째 노드를 찾는다.
	* 2. target값을 가지고 있는 노드가 존재하는 경우, answer를 1 증가 시키고 그 다음 노드로 넘어가서 탐색을 계속한다.
	* 3. 탐색이 끝난 경우 answer를 반환
	*/
	size_type answer = 0;
	const dnode* cursor;
	cursor = list_search(head_ptr, target);
	while (cursor != NULL) {
		if (cursor->data() == target) {
			answer += 1;
		}
		cursor = cursor->link_next();
		cursor = list_search(cursor, target);
	}
	return answer;
}

Bag::size_type Bag::size() {
	// bag객체에 존재하는 노드의 개수를 반환한다.
	return many_nodes;
}


void Bag::insert(const dnode::value_type& entry) {
	// bag객체에 entry값을 추가하고 many_nodes값을 1 증가.
	list_head_insert(head_ptr, entry);
	++many_nodes;
}

void Bag::show_contents() {
	/*
	* 1. head_ptr부터 시작해서 노드의 끝까지 이동하면서 data값을 출력한다.
	*/
	const dnode* cursor = head_ptr;
	std::cout << "Contents in Bag : ";
	if (cursor == NULL) {
		std::cout << "Nothing in Bag" << std::endl;
	}
	while (cursor != NULL) {
		std::cout << cursor->data() << " ";
		cursor = cursor->link_next();
	}
	std::cout << std::endl;
}

bool Bag::operator==(const Bag& source) {
	/*
	*	1. 두 bag객체의 node개수가 다른 경우에는 무조건 서로 다르기 때문에 false반환
	*	2. 두 bag객체의 node개수가 같은 경우에는 각각의 bag객체의 data를 배열에 저장한 후, 배열을 오름차순으로 정렬하여 두 배열이 같은지 판단한다.
	*	3. 같다면 true반환, 다르면 false반환
	*/
	if (many_nodes == 0 && source.many_nodes == 0) {
		std::cout << "Two Bags are empty\n";
		return false;
	}
	else if (many_nodes != source.many_nodes)
		return false;
	else {
		dnode::value_type* arr1 = new dnode::value_type[many_nodes];
		dnode::value_type* arr2 = new dnode::value_type[source.many_nodes];
		const dnode* cursor = head_ptr;
		for (size_type i = 0; (i < many_nodes && cursor != NULL); i++) {
			arr1[i] = cursor->data();
			cursor = cursor->link_next();
		}
		cursor = source.head_ptr;
		for (size_type i = 0; (i < many_nodes && cursor != NULL); i++) {
			arr2[i] = cursor->data();
			cursor = cursor->link_next();
		}
		std::sort(arr1, arr1 + many_nodes);
		std::sort(arr2, arr2 + source.many_nodes);
		if (std::equal(arr1, arr1 + many_nodes, arr2) == true) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Bag::operator!=(const Bag& source) {
	/*
	* 1. 두 bag객체의 node 개수가 다르면 항상 true반환
	* 2. 두 bag객체의 node 개수가 같은 경우, sort()함수를 통해 기존에 bag에서 data값이 새롭게 오름차순으로 정렬된 bag 생성
	* 3. 생성된 두개의 bag의 data가 서로 같은 경우 false 반환 data가 서로 다른경우 true 반환
	*/
	if (many_nodes != source.many_nodes)
		return true;
	else {
		Bag temp_bag = Bag(*this);
		Bag tmp_bag = Bag(source);
		temp_bag.sort(); tmp_bag.sort();
		const dnode* cursor1 = temp_bag.head_ptr;
		const dnode* cursor2 = tmp_bag.head_ptr;

		while (cursor1 != NULL) {
			if (cursor1->data() != cursor2->data()) {
				return true;
			}
			cursor1 = cursor1->link_next();
			cursor2 = cursor2->link_next();
		}
		return false;
	}
}

Bag Bag::operator+(const Bag& source) {
	/*
	* 1. 복사 생성자를 통해 새로운 bag 객체 생성
	* 2. 새롭게 생성된 bag객체에 기존에 존재하는 data를 추가해준다. 
	* 3. 이렇게 새롭게 생성된 bag객체를 반환
	*/
	Bag b = Bag(source);
	const dnode* cursor = this->head_ptr;
	while (cursor != NULL) {
		b.insert(cursor->data());
		cursor = cursor->link_next();
	}
	return b;
}

void Bag::sort() {
	/*
	* 1. cursor은 이전 노드, tmp_ptr은 다음 노드를 가리킨다.
	* 2. cursor의 data가 tmp_ptr보다 큰 경우 cursor의 data와 tmp_ptr의 data를 서로 변경한다.
	* 3. 다음 노드로 넘어가 2. 과정을 반복한다.
	* 4. 노드의 끝까지 탐색 한 후에는 첫번째 노드(head)에는 list에서 가장 작은 값이 존재하게 된다.
	* 5. 2번째, 3번째 노드에 대해서도 위 과정을 반복한다.
	*/
	dnode* cursor = head_ptr;
	dnode* tmp_ptr = head_ptr;
	dnode::value_type temp;
	if (head_ptr == NULL)
		return;
	while (cursor->link_next() != NULL) {
		tmp_ptr = cursor->link_next();
		while (tmp_ptr != NULL) {
			if (cursor->data() > tmp_ptr->data()) {
				temp = cursor->data();
				cursor->set_data(tmp_ptr->data());
				tmp_ptr->set_data(temp);
			}
			tmp_ptr = tmp_ptr->link_next();
		}
		cursor = cursor->link_next();
	}
}