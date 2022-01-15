#pragma once
#include <cstdlib>
#include <cassert>
// ���� ���� ���� ��带 ����ų �� �ִ� dnode Ŭ���� ����
template <class Item>
class dnode {
public:
	typedef double value_type;
	dnode(const value_type& init_data = value_type(), dnode<Item>* init_fore = NULL, dnode<Item>* init_back = NULL);
	void set_data(const value_type& new_data);
	void set_link_next(dnode* new_link); // ���� ��忡 ���� ����� link���� ���� �ϱ� ���� �Լ�
	void set_link_previous(dnode* new_link); // ���� ��忡 ���� ����� link���� ���� �ϱ� ���� �Լ�
	value_type data() const;
	const dnode* link_next() const; // �����忡�� ���� ���� �̵��ϱ� ���� �Լ�
	const dnode* link_previous() const; // ���� ��忡�� ���� ���� �̵��ϱ� ���� �Լ�
	dnode* link_next();  // ���� ��忡�� ���� ���� �̵��ϸ鼭 data�� ������ ���� �Լ�
	dnode* link_previous(); // ���� ��忡�� ���� ���� �̵��ϸ鼭 data�� ������ ���� �Լ�
private:
	value_type data_field; // ��忡 ����� ������ ��
	dnode* link_fore; // ���� ��忡�� ���� ����� �ּҰ��� �����ϱ� ���� ������ ����
	dnode* link_back; // ���� ��忡�� ���� ����� �ּҰ��� �����ϱ� ���� ������ ����
};

template <class Item>
dnode<Item>::dnode(const value_type& init_data, dnode<Item>* init_fore, dnode<Item>* init_back) {
	data_field = init_data;
	link_fore = init_fore;
	link_back = init_back;
}
template <class Item>
void dnode<Item>::set_data(const value_type& new_data) {
	// ���� ��忡 data ����
	data_field = new_data;
}
template <class Item>
void dnode<Item>::set_link_next(dnode<Item>* new_link) {
	// �������� link_next���� set
	link_fore = new_link;
}
template <class Item>
void dnode<Item>::set_link_previous(dnode<Item>* new_link) {
	// �������� link_back���� set
	link_back = new_link;
}
template <class Item>
typename dnode<Item>::value_type dnode<Item>::data() const {
	// ���� ����� data�� ��ȯ
	return data_field;
}
template <class Item>
const dnode<Item>* dnode<Item>::link_next() const {
	// ���� ����� �ּ� ��ȯ �������� ���� �Ұ�
	return link_fore;
}
template <class Item>
const dnode<Item>* dnode<Item>::link_previous() const {
	// ���� ����� �ּ� ��ȯ �������� ���� �Ұ�
	return link_back;
}
template <class Item>
dnode<Item>* dnode<Item>::link_next() {
	// ���� ����� �ּҰ� ��ȯ
	return link_fore;
}
template <class Item>
dnode<Item>* dnode<Item>::link_previous() {
	// ���� ����� �ּ� ��ȯ
	return link_back;
}

template <class Item>
void list_insert(dnode<Item>* previous_ptr, const typename dnode<Item>::value_type& entry) {
	/*
	*	1. insert�ϱ� ���� ���ο� ��带 �����ϰ�, ���� ������ ����� link_fore���� ���� ����� link_fore���� ������ �ϰ�
	*	   ���� ������ ����� link_back���� previous_ptr���� ������ �Ͽ� ���� ����ǵ��� �Ѵ�.
	*	2. previous_ptr�� link_fore���� insert_ptr�� �Ͽ� �� ��尡 ���� ����ǵ��� �Ѵ�.
	*	3. NULL�� ���� ���� ����� �������� ��带 �߰��ϴ� ���, NULL�� �ƴ� ��쿡�� list�� �߰��� ��带 insert�ϴ� ����̴�.
	*	   NULL�� �ƴ� ��쿡�� ���� ������ ���� ���� ������ ����� ���� ��尡 link_back�� ������ �ʿ��ϹǷ� �������ش�.
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
	*	1. ���� ������ ��尡 ���ο� head�� �ȴ�.
	*	2. ���� list�� ��尡 ���� �ϴ� ��쿡�� ���� ���� ���� ���� ����� link_back�� ������ �ش�.
	*/
	head_ptr = new dnode<Item>(entry, head_ptr, NULL);
	if (head_ptr->link_next() != NULL) {
		head_ptr->link_next()->set_link_previous(head_ptr);
	}
}
template <class Item>
void list_head_remove(dnode<Item>*& head_ptr) {
	/*
	*	1. remove_ptr�� ������ head�� ����Ų��.
	*	2. ���ο� head�� ���� head�� ���� ��尡 �ȴ�.
	*	3. remove_ptr�� �����Ͽ� head�� �����Ѵ�.
	*/
	dnode<Item>* remove_ptr;
	remove_ptr = head_ptr;
	head_ptr = head_ptr->link_next();
	delete remove_ptr;

}

template <class Item>
void list_clear(dnode<Item>*& head_ptr) {
	/*
	*  1. list�� head���� �ϳ��� �����Ѵ�.
	*/
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}
template <class Item>
void list_copy(const dnode<Item>* source_ptr, dnode<Item>*& head_ptr, dnode<Item>*& tail_ptr) {
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