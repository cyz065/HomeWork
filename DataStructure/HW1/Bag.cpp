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
	* 1. �ڱ� �ڽſ� ���� ������ ȣ���� ��� '=' �����ڰ� �ǹ̰� ���� ������ return
	* 2. ������ �����ϴ� ��ü�� �����ϰ� source ��ü�� data���� �����ؼ� ���ο� bag�� �����Ѵ�.
	* 3. many_nodes���� source������ �����Ѵ�.
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
	*	1. addend�� ��尡 �����ϴ� ��� addend��ü�� ��带 �ϳ� �� �����Ѵ�.
	*	2. ���簡 �� ������ ���� bag��ü�� head�� ���簡 ���� ������ ���� �����Ѵ�.
	*	3. head�� ����Ǿ��� ������ head�� copy_head_ptr�� ����
	*	4. ����� ������ ���� �Ǿ��� ������ many_nodes�� ����
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
	*	1. target���� ���� ù��° ��带 ã�´�.
	*	2. target_ptr�� NULL�� ���, target���� ���� ���� �ʱ� ������ false ��ȯ
	*	3. target�� �����ϴ� ��� target��带 ������ ��쿡�� ���� ���� ���� ��带 ���Ӱ� ������ �־�� �ϱ� ������ ���ŷӴ�.
	*	   ���� target���� �����ϴ� ��쿡�� target���� ù��° ���(head)�� ���� ������ �Ŀ� head�� �������ش�.
	*	4. �̷��� �ϸ� �߰��� ������ ���ŷӰ� ���� ������ �ִ� �� ��� head�� �����ϸ� �Ǿ� ���ϴ�.
	*	5. node�� ���� �Ǿ��� ������ many_nodes���� 1 ���ҽ�Ų �� true ��ȯ
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
	* 1. target���� ������ �ִ� ù��° ��带 ã�´�.
	* 2. target���� ������ �ִ� ��尡 �����ϴ� ���, answer�� 1 ���� ��Ű�� �� ���� ���� �Ѿ�� Ž���� ����Ѵ�.
	* 3. Ž���� ���� ��� answer�� ��ȯ
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
	// bag��ü�� �����ϴ� ����� ������ ��ȯ�Ѵ�.
	return many_nodes;
}


void Bag::insert(const dnode::value_type& entry) {
	// bag��ü�� entry���� �߰��ϰ� many_nodes���� 1 ����.
	list_head_insert(head_ptr, entry);
	++many_nodes;
}

void Bag::show_contents() {
	/*
	* 1. head_ptr���� �����ؼ� ����� ������ �̵��ϸ鼭 data���� ����Ѵ�.
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
	*	1. �� bag��ü�� node������ �ٸ� ��쿡�� ������ ���� �ٸ��� ������ false��ȯ
	*	2. �� bag��ü�� node������ ���� ��쿡�� ������ bag��ü�� data�� �迭�� ������ ��, �迭�� ������������ �����Ͽ� �� �迭�� ������ �Ǵ��Ѵ�.
	*	3. ���ٸ� true��ȯ, �ٸ��� false��ȯ
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
	* 1. �� bag��ü�� node ������ �ٸ��� �׻� true��ȯ
	* 2. �� bag��ü�� node ������ ���� ���, sort()�Լ��� ���� ������ bag���� data���� ���Ӱ� ������������ ���ĵ� bag ����
	* 3. ������ �ΰ��� bag�� data�� ���� ���� ��� false ��ȯ data�� ���� �ٸ���� true ��ȯ
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
	* 1. ���� �����ڸ� ���� ���ο� bag ��ü ����
	* 2. ���Ӱ� ������ bag��ü�� ������ �����ϴ� data�� �߰����ش�. 
	* 3. �̷��� ���Ӱ� ������ bag��ü�� ��ȯ
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
	* 1. cursor�� ���� ���, tmp_ptr�� ���� ��带 ����Ų��.
	* 2. cursor�� data�� tmp_ptr���� ū ��� cursor�� data�� tmp_ptr�� data�� ���� �����Ѵ�.
	* 3. ���� ���� �Ѿ 2. ������ �ݺ��Ѵ�.
	* 4. ����� ������ Ž�� �� �Ŀ��� ù��° ���(head)���� list���� ���� ���� ���� �����ϰ� �ȴ�.
	* 5. 2��°, 3��° ��忡 ���ؼ��� �� ������ �ݺ��Ѵ�.
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