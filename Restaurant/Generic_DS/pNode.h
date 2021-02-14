#pragma once
#include<iostream>

#include "Node.h"
using namespace std;

template<class T>
class pNode{
private:
	int priority;
	T item;
	pNode<T>*next;
public:
	pNode();
	int getpriority() const;
	void setpriority(const int& p);
	T getitem();
	void setitem(T);
	pNode<T>*getnext();
	void setnext(pNode<T>*);
};
template<class T>
pNode<T>::pNode(/*const T& a, const int p*/){
	/*item=a;
	priority = p;*/
	next=NULL;
}
template<class T>
int pNode<T>::getpriority() const{
	return priority;
	}
template<class T>
void pNode<T>::setpriority(const int& p){
	priority=p;
	}
template<class T>
T pNode<T>::getitem(){
	return item;
}
template<class T>
void pNode<T>::setitem(T a){
	item=a;
}
template<class T>
pNode<T>*pNode<T>::getnext(){
	return next;
}
template<class T>
void pNode<T>::setnext(pNode<T>*a){
	next =a;
}
