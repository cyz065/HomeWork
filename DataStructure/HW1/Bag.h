#pragma once
#include "Doubly_Linked_List.h"

class Bag {
public :
	typedef std::size_t size_type;
	Bag();
	Bag(const Bag& source);
	~Bag();
	void operator =(const Bag& source);	// ������ bag��ü�� data�� ������ bag��ü�� data�� ������ ���ִ� ������ ex) bag1 = bag2
	void operator +=(const Bag& addend); // ������ bag��ü�� ������ bag��ü�� data�� �߰����ִ� ������ ex) bag1 += bag2;
	bool erase_one(const dnode::value_type& target);	// bag��ü�� �����ϴ� data�� target���� ��ġ�ϴ� data 1�� ����
	size_type count(const dnode::value_type& target) const;	// bag��ü�� �����ϴ� data�� target���� ��ġ�ϴ� ���� ������ ��ȯ
	size_type size();	// bag��ü�� �����ϴ� data�� ������ ��ȯ
	void insert(const dnode::value_type& entry);	// bag��ü�� entry���� �߰��ϴ� �Լ�
	void show_contents();	// bag��ü �ȿ� �����ϴ� data���� ���� �����ִ� �Լ�
	bool operator ==(const Bag& source);	// ������ bag��ü�� ������ bag��ü�� data�� ���� ���θ� �˷��ִ� ������ ex) bag1 == bag2
	bool operator!=(const Bag& source); // ������ bag��ü�� ������ bag��ü�� data�� ���� �ٸ��� �˷��ִ� ������ ex) bag1 != bag2
	Bag operator+(const Bag& source); // ������ bag��ü�� �����ϴ� data���� �ϳ��� ���� ���ο� bag�� ����� ������. ex) bag 1 + bag2
	void sort();	// bag��ü�� �����ϴ� data���� ������������ �����ϱ� ���� �Լ�
private :
	dnode* head_ptr;	// bag��ü�� ���� ���
	size_type many_nodes; // bag��ü �ȿ� �����ϴ� node�� ������ �˷��ش�.
};