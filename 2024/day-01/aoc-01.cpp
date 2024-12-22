#include <iostream>
#include <fstream>

const int SPACE = 32;
const int NEWLINE = 10;

struct _IDList {
	int x;
	_IDList* next;
};

typedef _IDList* IDList;

void add_id_ordered(IDList& l, int id) {
	IDList _n = new _IDList;
	_n->x = id;
	_n->next = nullptr;
	
	if (l == nullptr || id < l->x) {
		_n->next = l;
		l = _n;
	} else {
		IDList _r = l;
		while (_r->next != nullptr && _r->next->x < id)
			_r = _r->next;
		_n->next = _r->next;
		_r->next = _n;
	}
}

void print_list(const IDList& l) {
	for (IDList _r = l; _r != nullptr; _r=_r->next) 
		std::cout << _r->x << '\n';
	std::cout << std::endl;
}

void write_to_file(const IDList& l, std::fstream f) {
	for (IDList _r = l; _r != nullptr; _r=_r->next) 
		f << _r->x << '\n';
}

void delete_and_fw(IDList& l) {
	if (l != nullptr) {
		IDList _r = l->next;
		delete l;
		l = _r;
	}
}

void clear_id_list(IDList& l) {
	while (l != nullptr) {
		IDList _r = l->next;
		delete l;
		l = _r;
	}
	l = nullptr;
}

int read_number(std::fstream& f) {
	int _num = 0;
	int _read = f.get();
	while (_read == SPACE)
		_read = f.get();
	if (_read == -1)
		return -1;
	for (int i=0; _read != NEWLINE && _read != SPACE; i++) {
		_read -= '0';
		_num *= 10;
		_num += _read;
		_read = f.get();
	}
	return _num;
}

int main() {
	std::fstream fileIn;
	fileIn.open("./input", std::fstream::in);

	IDList listA = nullptr;
	IDList listB = nullptr;

	while (fileIn.good() && !fileIn.eof()) {
		int A = read_number(fileIn);
		int B = read_number(fileIn);
		if (A != -1)
			add_id_ordered(listA, A);
		if (B != -1)
			add_id_ordered(listB, B);
	}
	

	// part 1
	int sum = 0;
	IDList recA = listA;
	IDList recB = listB;

	while (recA != nullptr && recB !=nullptr) {
		int diff = recA->x - recB->x;
		diff = diff<0 ? -diff : diff;
		sum +=diff;
		recA = recA->next;
		recB = recB->next;
	}

	std::cout << "Part one: " << sum << std::endl;

	sum = 0;
	recA = listA;
	recB = listB;
	int prevA = 0;
	int prevCount = 0;
	while (recA != nullptr && recB !=nullptr) {
		int count = 0;

		// A > B
		while (recB != nullptr && recA->x > recB->x)
			recB = recB->next;

		// A == B
		while (recB != nullptr && recA->x == recB->x) {
			count++;
			recB = recB->next;
		}
		sum += (recA->x * count);

		prevA = recA->x;
		prevCount = count;
		recA = recA->next;
	}

	std::cout << "Part two: " << sum << std::endl;

	clear_id_list(listA);
	clear_id_list(listB);
	fileIn.close();
	return 0;
}
