#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

template <class Item>
class Set {
private :
	int data_count;
	int child_count;
	int minimum;
	int MAXIMUM;
	
	Item* data;
	Set** subset;

	bool is_leaf() const { return child_count == 0; }
	bool loose_insert(const Item& entry);
	void fix_excess(int i);
	Item remove_biggest(Item& removed_entry);
	void fix_shortage(int i);
	bool loose_erase(const Item& target);
public :
	Set(int minimum = 1);
	size_t count(const Item& target) const;
	bool insert(const Item& entry);
	bool erase(const Item& target);
	void show_contents(const Set<Item>* root, size_t depth);
};

// ���ο� �κ������� ���� �Ǵ� ��� �ʱ�ȭ
template <class Item>
Set<Item>::Set(int minimum) {
	this->minimum = minimum;
	MAXIMUM = 2 * minimum;
	data = new Item[MAXIMUM + 1];
	subset = new Set * [MAXIMUM + 2];
	data_count = 0;
	child_count = 0;
}


template <class Item>
size_t Set<Item>::count(const Item & target) const {
	int i;
	Set* tmp;
	// data[i] >= target�� �Ǵ� i�� ã�´�.
	for (i = 0; i < data_count; i++) {
		// target���� �����ϴ� ��� �̹Ƿ� 1�� return
		if (target == data[i])
			return 1;
		// data[i]�� �� ū ��쿡�� i��° subset�� target�� ������ ���ɼ��� �����Ƿ� i��° subset�� Ž���ϱ� ���� break
		else if (data[i] > target)
			break;
	}

	// leaf�� ��쿡�� target�� ����� Ž������ �������� �ʴ� ����̹Ƿ� 0�� ��ȯ�Ѵ�.
	if (is_leaf())
		return 0;
	else {
		// i��° subset�� ��������� Ž���Ѵ�.
		tmp = subset[i];
		tmp->count(target);
	}
}

template <class Item>
bool Set<Item>::loose_insert(const Item& entry) {
	int i;
	Set* tmp;

	// data[i] >= entry�� i�� ã�´�.
	for (i = 0; i < data_count; i++) {
		// set�̹Ƿ� �ߺ��� ������� �ʴ´�.
		// ���� ���� �����ϴ� ��� ������ �̷������ �ʱ� ������ false ��ȯ
		if (entry == data[i])
			return false;

		// ������ ���� ��ġ�� ã�´�.
		else if (data[i] > entry)
			break;
	}

	// �߰��ϰ��� �ϴ� ���� leaf�� ��� data[i]���� ū ������ �������� ��ĭ �� �̵���Ű��
	// entry���� data[i]�� �߰� �� ���� ������ ������ 1 ����
	if (is_leaf()) {
		for (int x = data_count; x > i; x--)
			data[x] = data[x - 1];
		data_count++;
		data[i] = entry;
		return true;
	}

	// root�� child�� ������ ���, child�� ���� entry Ž���� ����
	// subset[i]�� ���� ��� ȣ���� �Ѵ�.
	else {
		tmp = subset[i];
		bool b = tmp->loose_insert(entry);

		// subset[i]�� MAXIMUM���� ���� �����͸� ������ �ִ� ��� B-Tree rule�� �����ϰ� �ǹǷ�
		// B-Tree rule�� �������� �ʵ��� 2���� subtree�� �����ϴ� ������ �Ѵ�.
		if (tmp->data_count > MAXIMUM)
			fix_excess(i);
		return b;
	}
}

// loose_insert���� B-Tree�� B-Tree rule�� �������� ���ϴ� ���,
// B-Tree rule�� �����ϵ��� B-Tree�� �����ϴ� �Լ�
template <class Item>
void Set<Item>::fix_excess(int i) {
	int idx;
	Set* tmp = subset[i];

	// subset�� �߰� entry���� root�� �÷������� ����
	// root�� ������ ����� �ش�.
	for (idx = data_count; idx > i; idx--) {
		data[idx] = data[idx - 1];
	}
	// subset�� �߰� entry ���� root�� �÷� ������.
	data[i] = tmp->data[minimum];
	data_count++;

	// 1���� subset�� 2���� �����Ѵ�.
	Set* left = new Set(minimum);
	Set* right = new Set(minimum);
	left->data_count = minimum;
	right->data_count = minimum;

	// 1���� subset�� �ִ� ������ 2���� subset�� ���� ���� ���ش�.
	for (idx = 0; idx < minimum; idx++) {
		left->data[idx] = tmp->data[idx];
		right->data[idx] = tmp->data[idx + minimum + 1];
	}

	// ������ subset�� leaf�� �ƴ� ���, subset�� child�� ���ؼ���
	// ���� �����Ͽ� ������ subset�� �߰��Ѵ�.
	int child_idx = (tmp->child_count) / 2;
	for (idx = 0; idx < child_idx; idx++) {
		left->subset[idx] = tmp->subset[idx];
		right->subset[idx] = tmp->subset[idx + child_idx];
	}
	if (child_idx > 0) {
		left->child_count = minimum + 1;
		right->child_count = minimum + 1;
	}

	// ���Ӱ� �߰��� subset�� root�� subset �迭�� �߰��Ѵ�.
	subset[child_count] = new Set(minimum);
	for (idx = child_count; idx > i; idx--) {
		subset[idx] = subset[idx - 1];
	}
	child_count++;
	subset[i] = left;
	subset[i + 1] = right;
}

template <class Item>
bool Set<Item>::insert(const Item& entry) {
	if (!loose_insert(entry)) {
		cout << entry << " Already Exist!" << endl;
		return false;
	}
	if (data_count > MAXIMUM) {
		// ��ü Ʈ�������� root�� ��ġ�� ���� ����
		Set* child = new Set(minimum);

		// ������ data�� subset�� ���ο� ������ ����
		for (int x = 0; x < data_count; x++)
			child->data[x] = data[x];
		for (int x = 0; x < child_count; x++)
			child->subset[x] = subset[x];
		child->child_count = child_count;
		child->data_count = data_count;

		// ���� root�� data�� subset�� �ʱ�ȭ
		data_count = 0;
		child_count = 1;

		// subset�� ���Ͽ� fix_excess�� ȣ���Ͽ�
		// ��� �ִ� root�� data�� �����Ͽ�
		// �������� B-Tree�� �����Ѵ�.
		subset[0] = child;
		fix_excess(0);
	}
}

template <class Item>
bool Set<Item>::erase(const Item& target) {
	if (!loose_erase(target)) {
		cout << target << " Not Exist!" << endl;
		return false;
	}

	// root�� ����ְ� �ڽ�subset�� �����ϴ� ���
	// tree�� height�� ���ߴ� ����

	if (data_count == 0 && child_count == 1) {
		// �ӽ� ���� tmp�� �����Ͽ� tmp�� data�� subset�� root�� �����Ͽ� root�� ������ �÷�������.
		Set* tmp = subset[0];
		for (int x = 0; x < tmp->data_count; x++)
			data[x] = tmp->data[x];
		for (int x = 0; x < tmp->child_count; x++)
			subset[x] = tmp->subset[x];
		child_count = tmp->child_count;
		data_count = tmp->data_count;
		// ������ ���� tmp�� ����
		delete tmp;
	}
}

template <class Item>
bool Set<Item>::loose_erase(const Item& target) {
	int i;
	Set* tmp;
	// data[i] >= target�� i�� ã�´�.
	for (i = 0; i < data_count; i++) {
		if (data[i] >= target)
			break;
	}
	// target�� �������� �ʰ�, leaf�� ��� B-Tree ���ο� target�� �����Ƿ�
	// false�� ��ȯ
	if (data[i] != target && is_leaf()) {
		return false;
	}
	// target�� root�� �����ϴ� ��� �ش� target�� ������ ��, data�� ������ �� ������ ������ �̵���Ų��.
	else if (data[i] == target && is_leaf()) {
		for (int x = i + 1; x < data_count; x++)
			data[x - 1] = data[x];
		data_count--;
		return true;
	}

	// target�� root�� ���� ��� target�� ã�� ���� subset���� ��������.
	else if (data[i] != target && !is_leaf()) {
		tmp = subset[i];
		bool b = tmp->loose_erase(target);

		// �ڽĿ��� target�� ã�� ���, ���� ������ ��, B-Tree Rule�� ������ �� �����Ƿ�
		// fix_shortage�� ���� B-Tree�� �˸°� ��ģ��.
		if (tmp->data_count < minimum)
			fix_shortage(i);
		return b;
	}
	// target�� root�� �����ϴ� ���
	// �ִ밪�� ã�Ƽ� �ִ밪�� data[i]�� �����Ѵ�.
	else if(data[i] == target && !is_leaf()) {
		tmp = subset[i];
		tmp->remove_biggest(data[i]);

		// �ִ밪�� ������ ������ B-Tree Rule�� �����ϴ� ���
		// fix_shortage�� ���� �����Ѵ�.
		if (tmp->data_count < minimum)
			fix_shortage(i);
		return true;
	}
}

// B-Tree�� B-Tree Rule�� �����ϵ��� �����ִ� ������ �Ѵ�.
// �̶� 4������ ��찡 �����Ѵ�.
template <class Item>
void Set<Item>::fix_shortage(int i) {
	Set* now = subset[i];
	Set* previous = subset[i - 1];
	Set* next = subset[i + 1];

	// Case 1. i - 1 ���� �������� ���
	if (i != 0 && previous->data_count > minimum) {
		Set* child = subset[i];
		Set* sibling = subset[i - 1];

		// 1. data[i-1]�� ���� subset[i]�� �̵� ��Ű�� ���� subset[i]�� data�迭�� �������� ��ĭ�� �̵�
		for (int x = child->data_count - 1; x >= 0; x--)
			child->data[x + 1] = child->data[x];
		// 1. data[i-1]�� ���� child�� [0]��° ������ �����Ƿ�, root�� data�� child�� ���� �տ� �߰�
		child->data[0] = data[i - 1];

		// 2. sibling�� ������ �ִ� �ڽ��� child�� 1�� �����ϱ� ���� subset�� 1ĭ�� �̵�
		if (!child->is_leaf()) {
			for (int x = child->data_count; x >= 0; x--)
				child->subset[x + 1] = child->subset[x];
		}
		
		// 2. subset[i-1]�� ���� ū ���� root�� �÷�����
		data[i - 1] = sibling->data[sibling->data_count - 1];

		// 3. sibling�� ������ �ڽ��� child�� ù��°�� �̵�
		if (!sibling->is_leaf()) {
			child->subset[0] = sibling->subset[sibling->data_count];
			child->child_count++;
			sibling->child_count--;
		}
		sibling->data_count--;
		child->data_count++;
	}

	// i + 1 ���� �������� ���
	else if (i != data_count && next->data_count > minimum) {
		Set* child = subset[i];
		Set* sibling = subset[i + 1];

		// 1. root�� data[i]�� subset[i]���� �̵�
		child->data[child->data_count] = data[i];
		child->data_count++;

		// 2. subset[i+1]�� ù��° data�� root�� �̵�
		data[i] = sibling->data[0];

		// 2. subset[i+1]�� data�� 1�� �پ����Ƿ�, data �迭�� �������� ��ĭ�� �̵���Ų��.
		for (int x = 1; x < sibling->data_count; x++)
			sibling->data[x - 1] = sibling->data[x];

		// 3. subset[i]�� children�� �ִ� ��� subset[i+1]�� ù subset
		// �� subset[i]�� ������ �̵�
		if (!child->is_leaf() && !sibling->is_leaf()) {
			child->subset[child->data_count] = sibling->subset[0];
			child->child_count++;
			sibling->child_count--;
		}

		// subset[i+1]�� �ڽ��� subset[i]�� �̵������Ƿ�, subset�迭�� �������� ��ĭ�� �̵���Ų��.
		if (!sibling->is_leaf()) {
			for (int x = 1; x <= sibling->data_count; x++)
				sibling->subset[x - 1] = sibling->subset[x];
		}
		sibling->data_count--;
	}

	// i - 1 �� ��ġ�� ���
	else if (i != 0 && previous->data_count == minimum) {
		Set* sibling = subset[i];
		Set* child = subset[i - 1];

		// 1. data[i - 1]�� ���� subset[i-1]�� ���������� �̵�
		child->data[child->data_count] = data[i - 1];
		child->data_count++;

		// 2. subset[i]�� ��� �����͸� subset[i-1]�� �̵�
		for (int x = 0; x < sibling->data_count; x++)
			child->data[x + child->data_count] = sibling->data[x];

		// 2. subset[i]�� ��� �����͸� subset[i-1]�� �̵�
		if (!child->is_leaf()) {
			for (int x = 0; x < sibling->child_count; x++) {
				child->subset[x + child->child_count] = sibling->subset[x];
				//child->child_count++;
			}
		}

		// 3. data[i - 1]�� ���� �̵����� �߻��� data�� �� ������ �޲ٴ� ����
		for (int x = i; x < data_count; ++x)
			data[x - 1] = data[x];


		// 3. subset[i]�� subset[i - 1]�� �̵����Ѽ� �߻��� ������ �޿�� ����
		for (int x = i + 1; x <= data_count; ++x)
			subset[x - 1] = subset[x];

		child->data_count += sibling->data_count;
		child->child_count += sibling->child_count;
		data_count--;
		child_count--;
		delete(sibling);
	}

	// i�� i+1�� ��ġ�� ���
	else {
		Set* child = subset[i];
		Set* sibling = subset[i + 1];

		// 1. data[i]�� subset[i]�� ������ �ű��.
		child->data[child->data_count] = data[i];
		child->data_count++;

		// 2. subset[i+1]�� ��� ���� subset[i]�� �̵�;
		for (int x = 0; x < sibling->data_count; x++)
			child->data[x + child->data_count] = sibling->data[x];

		if (!child->is_leaf()) {
			for (int x = 0; x < sibling->child_count; x++) {
				child->subset[x + child->child_count] = sibling->subset[x];
			}
		}

		// 3. ������ subset�� data�� �̵�;
		for (int x = i + 1; x < data_count; x++)
			data[x - 1] = data[x];

		for (int x = i + 2; x <= data_count; x++)
			subset[x - 1] = subset[x];

		child->data_count += sibling->data_count;
		child->child_count += sibling->child_count;
		data_count--;
		child_count--;
		delete(sibling);
	}
}

template <class Item>
Item Set<Item>::remove_biggest(Item& removed_entry) {
	// leaf�� ��� data�� ���� ������ ��ġ�� ���� ū���� �����ϹǷ� �ش� ���� ��ȯ
	if (is_leaf()) {
		removed_entry = data[data_count - 1];
		data_count--;
		return removed_entry;
	}

	// leaf�� �ƴ� ��� ������ �ڽĿ� ū ���� �����ϹǷ� ������ �ڽ����� �Ѿ��.
	else {
		Set* tmp = subset[child_count - 1];
		tmp->remove_biggest(removed_entry);

		// ū ���� ������ �ִ� ��� B-Tree Rule�� ������ �� �����Ƿ�
		// fix_shortage�� ���� B-Tree�� �˸°� �����Ѵ�.
		if (tmp->data_count < minimum)
			fix_shortage(child_count - 1);
	}
}

template <class Item>
void Set<Item>::show_contents(const Set<Item>* root, size_t depth) {
	size_t i;

	if (root != NULL) {
		for (i = root->data_count; i > 0; i--) {
			// root�� leaf�� �ƴ� ���, ���� �����ʿ� �����ϴ� �ڽĺ��� ����ذ� ����
			// ���ȣ���� ���� ������ �ڽ����� ����ؼ� �Ѿ��,
			// depth�� ���� ������Ų��.
			if (!root->is_leaf()) {
				show_contents(root->subset[i], depth + 1);
			}

			// leaf�� ��� �� �̻� ������ ���� �����Ƿ� �ش� ����� ������ ����Ѵ�.
			cout << setw(4 * depth) << "" << root->data[i - 1] << endl;
		}

		// �湮�� ����� ���� �ڽĳ��� �̵��Ѵ�.
		if (!root->is_leaf())
			show_contents(root->subset[i], depth + 1);
	}
}


	



	



