#pragma once

template<typename DataType>
struct node{
	node(DataType data,node *previous = nullptr,node *next = nullptr):data(data),previous(previous),next(next){}
	node *next;
	node *previous;
	DataType data;
};

template<typename DataType>
class LinkedList{
public:
	void insert();
	void append();


protected:
	node<DataType> *head;
	node<DataType> *tail;
};

template<typename DataType>
class iterator {
public:
	iterator operator++();
	iterator operator--();
	iterator operator*();
private:
	node<DataType> *current;
};