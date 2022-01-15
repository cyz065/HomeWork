#pragma once
#pragma once
#include <cstdlib>

// 다음 노드와 이전 노드를 가리킬 수 있는 dnode 클래스 정의
class dnode {
public:
	typedef double value_type;
	dnode(const value_type& init_data = value_type(), dnode* init_fore = NULL, dnode* init_back = NULL);
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