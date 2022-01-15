#include "Doubly_Linked_List.h"
#include <cassert>
#include <cstdlib>

dnode::dnode(const value_type& init_data, dnode* init_fore, dnode* init_back) {
	data_field = init_data;
	link_fore = init_fore;
	link_back = init_back;
}

void dnode::set_data(const value_type& new_data) {
	// ���� ��忡 data ����
	data_field = new_data;
}

void dnode::set_link_next(dnode* new_link) {
	// �������� link_next���� set
	link_fore = new_link;
}
void dnode::set_link_previous(dnode* new_link) {
	// �������� link_back���� set
	link_back = new_link;
}

dnode::value_type dnode::data() const {
	// ���� ����� data�� ��ȯ
	return data_field;
}

const dnode* dnode::link_next() const {
	// ���� ����� �ּ� ��ȯ �������� ���� �Ұ�
	return link_fore;
}
const dnode* dnode::link_previous() const {
	// ���� ����� �ּ� ��ȯ �������� ���� �Ұ�
	return link_back;
}

dnode* dnode::link_next() {
	// ���� ����� �ּҰ� ��ȯ
	return link_fore;
}
dnode* dnode::link_previous() {
	// ���� ����� �ּ� ��ȯ
	return link_back;
}

size_t list_length(const dnode* head_ptr) {
	/*
	* 1. cursor�� ���� list�� ������ ������ Ž���ϰ� answer�� 1�� ���������ش�.
	* 2. cursor�� NULL�� ��� ������ ����̹Ƿ� answer��ȯ
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
	*	1. cursor�� ���� list�� ������ ���� Ž���ϸ鼭 target���� �����ϴ��� Ȯ��
	*	2. target���� �����ϴ� ��� target���� ���� ù��° ����� �ּҰ��� ��ȯ
	*	3. target���� �������� �ʴ� ��� NULL ��ȯ
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
	*	1. �迭���� index�� ���� �ϴ� �Ͱ� ���� list���� position�� ��ġ�� �ּҰ� ��ȯ
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
	*	1. insert�ϱ� ���� ���ο� ��带 �����ϰ�, ���� ������ ����� link_fore���� ���� ����� link_fore���� ������ �ϰ�
	*	   ���� ������ ����� link_back���� previous_ptr���� ������ �Ͽ� ���� ����ǵ��� �Ѵ�.
	*	2. previous_ptr�� link_fore���� insert_ptr�� �Ͽ� �� ��尡 ���� ����ǵ��� �Ѵ�.
	*	3. NULL�� ���� ���� ����� �������� ��带 �߰��ϴ� ���, NULL�� �ƴ� ��쿡�� list�� �߰��� ��带 insert�ϴ� ����̴�.
	*	   NULL�� �ƴ� ��쿡�� ���� ������ ���� ���� ������ ����� ���� ��尡 link_back�� ������ �ʿ��ϹǷ� �������ش�.
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
	*	1. ���� ������ ��尡 ���ο� head�� �ȴ�.
	*	2. ���� list�� ��尡 ���� �ϴ� ��쿡�� ���� ���� ���� ���� ����� link_back�� ������ �ش�.
	*/
	head_ptr = new dnode(entry, head_ptr, NULL);
	if (head_ptr->link_next() != NULL) {
		head_ptr->link_next()->set_link_previous(head_ptr);
	}
}

void list_head_remove(dnode*& head_ptr) {
	/*
	*	1. remove_ptr�� ������ head�� ����Ų��.
	*	2. ���ο� head�� ���� head�� ���� ��尡 �ȴ�.
	*	3. remove_ptr�� �����Ͽ� head�� �����Ѵ�.
	*/
	dnode* remove_ptr;
	remove_ptr = head_ptr;
	head_ptr = head_ptr->link_next();
	delete remove_ptr;

}

void list_remove(dnode* previous_ptr) {
	/*
	*	1. remove_ptr�� ������ ��带 ����Ų��.
	*	2. previous_ptr�� ������ ��尡 ���� ����Ű�� ���� ��带 ����Ű���� �Ѵ�.
	*	3. remove_ptr�� ���� ��尡 remove_ptr�� �� ��带 ����Ű���� �Ѵ�.
	*	4. remove_ptr�� �����Ѵ�.
	*/
	dnode* remove_ptr;
	remove_ptr = previous_ptr->link_next();
	previous_ptr->set_link_next(remove_ptr->link_next());
	remove_ptr->link_next()->link_previous()->set_link_previous(remove_ptr->link_previous());
	delete remove_ptr;
}

void list_clear(dnode*& head_ptr) {
	/*
	*  1. list�� head���� �ϳ��� �����Ѵ�.
	*/
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
	/*
	*	1. source_ptr�� NULL �� ��� ������ ����� �����Ƿ� return
	*	2. source_ptr�� ����Ű�� ����� data���� �����ؼ� ���Ӱ� node�� �����ϰ� ����, �� ��尡 head�� �ȴ�.
	*	3. tail_ptr�� head_ptr�� �Ͽ� tail_ptr�� ���� ���� �̵��Ѵ�.
	*	4. source_ptr�� source�� ���� ��带 ����Ű���� �� ��, source���� NULL�� �� �� ����, �� ��忡 data���� insert�Ѵ�.
	*	5. data���� insert�Ǹ� tail_ptr�� ������ ��带 ����Ű�� ���� ���������� ��ĭ �� �̵��Ѵ�.
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