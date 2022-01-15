#pragma once
#include "Doubly_Linked_List.h"

class Bag {
public :
	typedef std::size_t size_type;
	Bag();
	Bag(const Bag& source);
	~Bag();
	void operator =(const Bag& source);	// 좌측의 bag객체의 data를 우측의 bag객체의 data와 같도록 해주는 연산자 ex) bag1 = bag2
	void operator +=(const Bag& addend); // 좌측의 bag객체에 우측의 bag객체의 data를 추가해주는 연산자 ex) bag1 += bag2;
	bool erase_one(const dnode::value_type& target);	// bag객체에 존재하는 data중 target값과 일치하는 data 1개 제거
	size_type count(const dnode::value_type& target) const;	// bag객체에 존재하는 data중 target값과 일치하는 값의 개수를 반환
	size_type size();	// bag객체에 존재하는 data의 개수를 반환
	void insert(const dnode::value_type& entry);	// bag객체에 entry값을 추가하는 함수
	void show_contents();	// bag객체 안에 존재하는 data값을 전부 보여주는 함수
	bool operator ==(const Bag& source);	// 좌측의 bag객체와 우측의 bag객체의 data의 동일 여부를 알려주는 연산자 ex) bag1 == bag2
	bool operator!=(const Bag& source); // 좌측의 bag객체와 우측의 bag객체의 data가 서로 다른지 알려주는 연산자 ex) bag1 != bag2
	Bag operator+(const Bag& source); // 각각의 bag객체에 존재하는 data값을 하나로 합쳐 새로운 bag을 만드는 연산자. ex) bag 1 + bag2
	void sort();	// bag객체에 존재하는 data값을 오름차순으로 정렬하기 위한 함수
private :
	dnode* head_ptr;	// bag객체의 시작 노드
	size_type many_nodes; // bag객체 안에 존재하는 node의 개수를 알려준다.
};