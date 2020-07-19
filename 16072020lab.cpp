/*
Задание №1
Создать базовый класс список.
Реализовать на базе списка стек и очередь с виртуальными функциями вставки и вытаскивания.
*/
#include <iostream>
using namespace std;

//двусвязный список
template<typename T>
class tlist {
	struct node {
		node* prev;
		node* next;
		T     val;
		node(const T& v) :prev(NULL), next(NULL), val(v) {}
	};
private:
	node* head, * tail;
	size_t cnt;
public:
	tlist() :head(NULL), tail(NULL), cnt(0) {}
	~tlist() { clear(); }
public:
	virtual void push(const T& val) = 0;
	virtual void pop() = 0;
protected:

	void push_front(const T& val) {
		node* p = new node(val);
		if (head == NULL)
			head = tail = p;
		else {
			head->prev = p;
			p->next = head;
			head = p;
		}
		++cnt;
	}

	void push_back(const T& val) {
		node* p = new node(val);
		if (head == NULL)
			head = tail = p;
		else {
			p->prev = tail;
			tail = tail->next = p;
		}
		++cnt;
	}

	void pop_front() {
		node* t;
		if (head != NULL) {
			t = head;
			head = head->next;
			delete t;
			if (head != NULL)
				head->prev = NULL;
			else
				tail = NULL;
			--cnt;
		}
	}

	void pop_back() {
		node* t;
		if (tail != NULL) {
			t = tail;
			tail = tail->prev;
			delete t;
			if (tail != NULL)
				tail->next = NULL;
			else
				head = NULL;
			--cnt;
		}
	}
public:
	void clear() {
		while (head != NULL)
			pop_front();
		cnt = 0;
	}

	bool empty()  const { return (head == NULL); }
	size_t size() const { return cnt; }

	const T& peek() const { return head->val; }
	T& peek() { return head->val; }
};

//стек(LIFO)
template<typename T>
class tstack : public tlist<T> {
public:
	virtual void push(const T& val) { tlist<T>::push_front(val); }
	virtual void pop() { tlist<T>::pop_front(); }
};

//очередь(FIFO)
template<typename T>
class tqueue : public tlist<T> {
public:
	virtual void push(const T& val) { tlist<T>::push_back(val); }
	virtual void pop() { tlist<T>::pop_front(); }
};

int main() {

	tstack<char> s;
	for (char c = 'A'; c <= 'Z'; ++c)
		s.push(c);
	for (; !s.empty(); s.pop())
		cout << s.peek();
	cout << endl;

	tqueue<int> q;
	for (int i = 0; i < 10; ++i)
		q.push(i);
	for (; !q.empty(); q.pop())
		cout << q.peek() << ' ';
	cout << endl;
}