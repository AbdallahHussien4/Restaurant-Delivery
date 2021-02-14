#pragma once
#include"Node.h"

template<class T>
class linkedlist
{
	int count;
	Node<T>*head ;
	Node<T>*tail;
public:
	
	linkedlist();
	int getsize();
	bool isempty();
	void pushback(T);
	bool popfront(T&);
	void remove(int);
	Node<T>* gethead();
	void print();
	void clear();
	~linkedlist();
};
template<class T>
linkedlist<T>::linkedlist()
{
	head=NULL; tail=NULL; count =0;
}

template<class T>
int linkedlist<T>::getsize() {
	return count;
}

template<class T>
bool linkedlist<T>::isempty() {
	return count==0;
}

template<class T>
void linkedlist<T>::pushback(T a) {
	Node<T>*n = new Node<T>;
	n->setItem(a);
	if (head == NULL)
	{
		head = n; tail=n; n->setNext(NULL);
	}
	else {
		tail->setNext(n);
		tail= n;
	}
	count++;
	}


template<class T>
bool linkedlist<T>::popfront(T&a) {
	if(head==NULL) return false;
	a=head->getItem();
	Node<T>*temp = head;
	head = head->getNext();
	temp->setNext(NULL);
	delete temp;
	count--; return true;
}



template<class T>
void linkedlist<T>::remove(int n) {
	T x;
	if (n == 0) { popfront(x); return; }
	Node<T>*temp = head; Node<T>*temp2 = head;
	for (int i = 0; i < n - 1; i++)
		temp = temp->getNext();
	temp2 = temp->getNext();
	temp->setNext(temp2->getNext());
	if (n == count-1) tail = temp;
	delete temp2;
	count--;
}


template<class T>
void linkedlist<T>::print()
{
	Node<T>*temp = head;
	while (temp != NULL)
	{
		cout << temp->getItem();
		temp = temp->getNext();
	}
	cout << endl;
}
template<class T>
Node<T>* linkedlist<T>::gethead()
{
	return head;
}

template<class T>
void linkedlist<T>::clear() {
	 Node<T>*temp = head;
	 while (head != NULL) {
		 head = head->getNext();
		 temp->setNext(NULL);
		 delete temp;
		 temp = head;
	}
	 count = 0;
}

template<class T>
linkedlist<T>::~linkedlist()
{
}