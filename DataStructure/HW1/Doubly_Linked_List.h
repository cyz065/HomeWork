#pragma once
#pragma once
#include <cstdlib>

// ���� ���� ���� ��带 ����ų �� �ִ� dnode Ŭ���� ����
class dnode {
public:
	typedef double value_type;
	dnode(const value_type& init_data = value_type(), dnode* init_fore = NULL, dnode* init_back = NULL);
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

size_t list_length(const dnode* head_ptr);
dnode* list_search(dnode* head_ptr, const dnode::value_type& target);
const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target);
dnode* list_locate(dnode* head_ptr, size_t position);
const dnode* list_locate(const dnode* head_ptr, size_t position);
void list_insert(dnode* prevoius_ptr, const dnode::value_type& entry);
void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry);
void list_head_remove(dnode*& head_ptr);
void list_remove(dnode* previous_ptr);
void list_clear(dnode*& head_ptr);
void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr);