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

// 새로운 부분집합이 생성 되는 경우 초기화
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
	// data[i] >= target이 되는 i를 찾는다.
	for (i = 0; i < data_count; i++) {
		// target값이 존재하는 경우 이므로 1을 return
		if (target == data[i])
			return 1;
		// data[i]가 더 큰 경우에는 i번째 subset에 target이 존재할 가능성이 있으므로 i번째 subset을 탐색하기 위해 break
		else if (data[i] > target)
			break;
	}

	// leaf인 경우에는 target이 재귀적 탐색에도 존재하지 않는 경우이므로 0을 반환한다.
	if (is_leaf())
		return 0;
	else {
		// i번째 subset을 재귀적으로 탐색한다.
		tmp = subset[i];
		tmp->count(target);
	}
}

template <class Item>
bool Set<Item>::loose_insert(const Item& entry) {
	int i;
	Set* tmp;

	// data[i] >= entry인 i를 찾는다.
	for (i = 0; i < data_count; i++) {
		// set이므로 중복을 허용하지 않는다.
		// 따라서 값이 존재하는 경우 삽입이 이루어지지 않기 때문에 false 반환
		if (entry == data[i])
			return false;

		// 적절한 삽입 위치를 찾는다.
		else if (data[i] > entry)
			break;
	}

	// 추가하고자 하는 곳이 leaf인 경우 data[i]보다 큰 값들은 우측으로 한칸 씩 이동시키고
	// entry값을 data[i]에 추가 및 보유 데이터 개수를 1 증가
	if (is_leaf()) {
		for (int x = data_count; x > i; x--)
			data[x] = data[x - 1];
		data_count++;
		data[i] = entry;
		return true;
	}

	// root가 child를 가지는 경우, child에 대해 entry 탐색을 위해
	// subset[i]에 대해 재귀 호출을 한다.
	else {
		tmp = subset[i];
		bool b = tmp->loose_insert(entry);

		// subset[i]가 MAXIMUM보다 많은 데이터를 가지고 있는 경우 B-Tree rule을 위반하게 되므로
		// B-Tree rule을 위반하지 않도록 2개의 subtree로 분할하는 역할을 한다.
		if (tmp->data_count > MAXIMUM)
			fix_excess(i);
		return b;
	}
}

// loose_insert이후 B-Tree가 B-Tree rule을 만족하지 못하는 경우,
// B-Tree rule을 만족하도록 B-Tree를 수정하는 함수
template <class Item>
void Set<Item>::fix_excess(int i) {
	int idx;
	Set* tmp = subset[i];

	// subset의 중간 entry값을 root에 올려보내기 위해
	// root에 공간을 만들어 준다.
	for (idx = data_count; idx > i; idx--) {
		data[idx] = data[idx - 1];
	}
	// subset의 중간 entry 값을 root로 올려 보낸다.
	data[i] = tmp->data[minimum];
	data_count++;

	// 1개의 subset을 2개로 분할한다.
	Set* left = new Set(minimum);
	Set* right = new Set(minimum);
	left->data_count = minimum;
	right->data_count = minimum;

	// 1개의 subset에 있던 값들을 2개의 subset에 각각 복사 해준다.
	for (idx = 0; idx < minimum; idx++) {
		left->data[idx] = tmp->data[idx];
		right->data[idx] = tmp->data[idx + minimum + 1];
	}

	// 기존의 subset이 leaf가 아닌 경우, subset의 child에 대해서도
	// 값을 복사하여 각각의 subset에 추가한다.
	int child_idx = (tmp->child_count) / 2;
	for (idx = 0; idx < child_idx; idx++) {
		left->subset[idx] = tmp->subset[idx];
		right->subset[idx] = tmp->subset[idx + child_idx];
	}
	if (child_idx > 0) {
		left->child_count = minimum + 1;
		right->child_count = minimum + 1;
	}

	// 새롭게 추가된 subset을 root의 subset 배열에 추가한다.
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
		// 전체 트리에서의 root를 고치기 위한 역할
		Set* child = new Set(minimum);

		// 기존의 data와 subset을 새로운 공간에 저장
		for (int x = 0; x < data_count; x++)
			child->data[x] = data[x];
		for (int x = 0; x < child_count; x++)
			child->subset[x] = subset[x];
		child->child_count = child_count;
		child->data_count = data_count;

		// 기존 root의 data와 subset을 초기화
		data_count = 0;
		child_count = 1;

		// subset에 대하여 fix_excess를 호출하여
		// 비어 있는 root에 data를 전달하여
		// 정상적인 B-Tree를 생성한다.
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

	// root가 비어있고 자식subset만 존재하는 경우
	// tree의 height를 낮추는 역할

	if (data_count == 0 && child_count == 1) {
		// 임시 변수 tmp를 설정하여 tmp의 data와 subset을 root에 복사하여 root에 값들을 올려보낸다.
		Set* tmp = subset[0];
		for (int x = 0; x < tmp->data_count; x++)
			data[x] = tmp->data[x];
		for (int x = 0; x < tmp->child_count; x++)
			subset[x] = tmp->subset[x];
		child_count = tmp->child_count;
		data_count = tmp->data_count;
		// 역할이 끝난 tmp는 제거
		delete tmp;
	}
}

template <class Item>
bool Set<Item>::loose_erase(const Item& target) {
	int i;
	Set* tmp;
	// data[i] >= target인 i를 찾는다.
	for (i = 0; i < data_count; i++) {
		if (data[i] >= target)
			break;
	}
	// target이 존재하지 않고, leaf인 경우 B-Tree 내부에 target이 없으므로
	// false를 반환
	if (data[i] != target && is_leaf()) {
		return false;
	}
	// target이 root에 존재하는 경우 해당 target만 제거한 뒤, data의 값들을 빈 공간이 없도록 이동시킨다.
	else if (data[i] == target && is_leaf()) {
		for (int x = i + 1; x < data_count; x++)
			data[x - 1] = data[x];
		data_count--;
		return true;
	}

	// target이 root에 없는 경우 target을 찾기 위해 subset으로 내려간다.
	else if (data[i] != target && !is_leaf()) {
		tmp = subset[i];
		bool b = tmp->loose_erase(target);

		// 자식에서 target을 찾은 경우, 값을 제거한 뒤, B-Tree Rule을 위배할 수 있으므로
		// fix_shortage를 통해 B-Tree를 알맞게 고친다.
		if (tmp->data_count < minimum)
			fix_shortage(i);
		return b;
	}
	// target이 root에 존재하는 경우
	// 최대값을 찾아서 최대값을 data[i]에 저장한다.
	else if(data[i] == target && !is_leaf()) {
		tmp = subset[i];
		tmp->remove_biggest(data[i]);

		// 최대값을 제거한 곳에서 B-Tree Rule을 위반하는 경우
		// fix_shortage를 통해 수정한다.
		if (tmp->data_count < minimum)
			fix_shortage(i);
		return true;
	}
}

// B-Tree를 B-Tree Rule을 만족하도록 고쳐주는 역할을 한다.
// 이때 4가지의 경우가 존재한다.
template <class Item>
void Set<Item>::fix_shortage(int i) {
	Set* now = subset[i];
	Set* previous = subset[i - 1];
	Set* next = subset[i + 1];

	// Case 1. i - 1 에서 가져오는 경우
	if (i != 0 && previous->data_count > minimum) {
		Set* child = subset[i];
		Set* sibling = subset[i - 1];

		// 1. data[i-1]의 값을 subset[i]로 이동 시키기 위해 subset[i]의 data배열을 우측으로 한칸씩 이동
		for (int x = child->data_count - 1; x >= 0; x--)
			child->data[x + 1] = child->data[x];
		// 1. data[i-1]의 값은 child의 [0]번째 값보다 작으므로, root의 data를 child의 가장 앞에 추가
		child->data[0] = data[i - 1];

		// 2. sibling이 가지고 있는 자식을 child에 1개 전달하기 위해 subset을 1칸씩 이동
		if (!child->is_leaf()) {
			for (int x = child->data_count; x >= 0; x--)
				child->subset[x + 1] = child->subset[x];
		}
		
		// 2. subset[i-1]의 가장 큰 값을 root로 올려보냄
		data[i - 1] = sibling->data[sibling->data_count - 1];

		// 3. sibling의 마지막 자식을 child의 첫번째로 이동
		if (!sibling->is_leaf()) {
			child->subset[0] = sibling->subset[sibling->data_count];
			child->child_count++;
			sibling->child_count--;
		}
		sibling->data_count--;
		child->data_count++;
	}

	// i + 1 에서 가져오는 경우
	else if (i != data_count && next->data_count > minimum) {
		Set* child = subset[i];
		Set* sibling = subset[i + 1];

		// 1. root의 data[i]를 subset[i]으로 이동
		child->data[child->data_count] = data[i];
		child->data_count++;

		// 2. subset[i+1]의 첫번째 data를 root로 이동
		data[i] = sibling->data[0];

		// 2. subset[i+1]의 data가 1개 줄었으므로, data 배열을 좌측으로 한칸씩 이동시킨다.
		for (int x = 1; x < sibling->data_count; x++)
			sibling->data[x - 1] = sibling->data[x];

		// 3. subset[i]가 children이 있는 경우 subset[i+1]의 첫 subset
		// 을 subset[i]의 끝으로 이동
		if (!child->is_leaf() && !sibling->is_leaf()) {
			child->subset[child->data_count] = sibling->subset[0];
			child->child_count++;
			sibling->child_count--;
		}

		// subset[i+1]의 자식이 subset[i]로 이동했으므로, subset배열을 좌측으로 한칸씩 이동시킨다.
		if (!sibling->is_leaf()) {
			for (int x = 1; x <= sibling->data_count; x++)
				sibling->subset[x - 1] = sibling->subset[x];
		}
		sibling->data_count--;
	}

	// i - 1 과 합치는 경우
	else if (i != 0 && previous->data_count == minimum) {
		Set* sibling = subset[i];
		Set* child = subset[i - 1];

		// 1. data[i - 1]의 값을 subset[i-1]의 마지막으로 이동
		child->data[child->data_count] = data[i - 1];
		child->data_count++;

		// 2. subset[i]의 모든 데이터를 subset[i-1]로 이동
		for (int x = 0; x < sibling->data_count; x++)
			child->data[x + child->data_count] = sibling->data[x];

		// 2. subset[i]의 모든 데이터를 subset[i-1]로 이동
		if (!child->is_leaf()) {
			for (int x = 0; x < sibling->child_count; x++) {
				child->subset[x + child->child_count] = sibling->subset[x];
				//child->child_count++;
			}
		}

		// 3. data[i - 1]의 값의 이동으로 발생한 data의 빈 공간을 메꾸는 역할
		for (int x = i; x < data_count; ++x)
			data[x - 1] = data[x];


		// 3. subset[i]를 subset[i - 1]로 이동시켜서 발생한 공백을 메우는 역할
		for (int x = i + 1; x <= data_count; ++x)
			subset[x - 1] = subset[x];

		child->data_count += sibling->data_count;
		child->child_count += sibling->child_count;
		data_count--;
		child_count--;
		delete(sibling);
	}

	// i와 i+1을 합치는 경우
	else {
		Set* child = subset[i];
		Set* sibling = subset[i + 1];

		// 1. data[i]를 subset[i]의 끝으로 옮긴다.
		child->data[child->data_count] = data[i];
		child->data_count++;

		// 2. subset[i+1]의 모든 값을 subset[i]로 이동;
		for (int x = 0; x < sibling->data_count; x++)
			child->data[x + child->data_count] = sibling->data[x];

		if (!child->is_leaf()) {
			for (int x = 0; x < sibling->child_count; x++) {
				child->subset[x + child->child_count] = sibling->subset[x];
			}
		}

		// 3. 이후의 subset과 data를 이동;
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
	// leaf인 경우 data의 가장 마지막 위치에 가장 큰값이 존재하므로 해당 값을 반환
	if (is_leaf()) {
		removed_entry = data[data_count - 1];
		data_count--;
		return removed_entry;
	}

	// leaf가 아닌 경우 오른쪽 자식에 큰 값이 존재하므로 오른쪽 자식으로 넘어간다.
	else {
		Set* tmp = subset[child_count - 1];
		tmp->remove_biggest(removed_entry);

		// 큰 값을 제거해 주는 경우 B-Tree Rule을 위반할 수 있으므로
		// fix_shortage를 통해 B-Tree를 알맞게 수정한다.
		if (tmp->data_count < minimum)
			fix_shortage(child_count - 1);
	}
}

template <class Item>
void Set<Item>::show_contents(const Set<Item>* root, size_t depth) {
	size_t i;

	if (root != NULL) {
		for (i = root->data_count; i > 0; i--) {
			// root가 leaf가 아닌 경우, 가장 오른쪽에 존재하는 자식부터 출력해가 위해
			// 재귀호출을 통해 오른쪽 자식으로 계속해서 넘어가고,
			// depth를 점점 증가시킨다.
			if (!root->is_leaf()) {
				show_contents(root->subset[i], depth + 1);
			}

			// leaf인 경우 더 이상 내려갈 곳이 없으므로 해당 노드의 값들을 출력한다.
			cout << setw(4 * depth) << "" << root->data[i - 1] << endl;
		}

		// 방문한 노드의 다음 자식노드로 이동한다.
		if (!root->is_leaf())
			show_contents(root->subset[i], depth + 1);
	}
}


	



	



