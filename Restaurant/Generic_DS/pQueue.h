#pragma once
#include"pNode.h"

template <class T>
class pQueue{
	int count;
	pNode<T>* head;
public:
	pQueue();
	void enqueue(T item, int p);
	bool dequeue(T&a);
	bool isempty();
	bool peekfront(T&a);
	void print();
	int getsize();
	void clear();
};
    template <class T>
	pQueue<T>::pQueue()
	{
		count=0;
		head=NULL;
	}
	template <class T>
	void pQueue<T>::enqueue(T item, int p) {
		//create pNode
		pNode<T>* n = new pNode<T>();
		n->setitem(item);  n->setpriority(p);
		if (!head) head = n;
		else if (p > head->getpriority()) {
			n->setnext(head); head = n;
		}
		else {
			pNode<T>*temp = head;  pNode<T>*prev =head;
			while (temp) {
				if (temp->getpriority()>=p) {
					prev = temp;
					temp = temp->getnext();
				}
				else break;
			}
			prev->setnext(n);
			n->setnext(temp);
		}
		count++;
	}
	template <class T>
	bool pQueue<T>::dequeue(T&a){
		if(head==NULL) return false;
		pNode<T>*temp=head;
		head=head->getnext();
		a=temp->getitem();
		temp->setnext(NULL);
		delete temp;
		count--;
		return true;
	}
	template <class T>
	bool pQueue<T>::isempty(){
		return head==NULL;
	}
	template <class T>
	bool pQueue<T>::peekfront(T&a){
		if(!head) return false;
		a=head->getitem();
		return true;
	}
template <class T>
void pQueue<T>::print(){
		pNode<T>*temp=head;
		while(temp){
			cout<<temp->getitem()<<" "<<temp->getpriority()<<endl;
			temp=temp->getnext();
		}
		cout << endl;
	}
template <class T>
int pQueue<T>:: getsize()
{
	return count;
}

template<class T>
void pQueue<T>::clear() {
	pNode<T>*temp = head;
	while (head != NULL) {
		head = head->getnext();
		temp->setnext(NULL);
		delete temp;
		temp = head;
	}
	count = 0;
}
