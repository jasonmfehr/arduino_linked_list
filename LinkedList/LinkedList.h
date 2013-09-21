/*

Copyright (C) 2013 Jason Fehr

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

Very basic implementation of a templated Linked List.  The implementation 
is single linked with the tail not linked to the head.  The actual 
list implementation should not matter to the user of this class.

This list works by maintaining an index of each item in the list.  The 
index is only updated when a field is retrieved and the index is stale.  
It may also be updated by the consumer via the maintainIndex() 
function, but there should hardly ever be a reason for this function 
to be called external to the class.

*/


#ifndef LINKED_LIST
#define LINKED_LIST

#include "Arduino.h"

template <typename T>
class LinkedList {
  
  public:
    LinkedList();
    ~LinkedList();
    void addItem(T value);
    T getValue(int index);
    int numItems();
    void maintainIndex();
    T operator[](int index);
  
  private:
    typedef struct LinkedListItem {
      T value;
      LinkedListItem* next;
    } LinkedListItem;

    int _numItems;
    LinkedListItem* _head;
    LinkedListItem* _tail;
    LinkedListItem** _index;
    boolean _indexUpToDate;
};


template <typename T>
LinkedList<T>::LinkedList() {
  _head = _tail = NULL;
  _index = NULL;
  _numItems = 0;
  _indexUpToDate = false;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  LinkedListItem* tmp;

  while(_head != NULL){
    tmp = _head;
    _head = _head->next;
    delete tmp;
  }

  delete _index;
}

template <typename T>
void LinkedList<T>::addItem(T value) {
  LinkedListItem* tmp = new LinkedListItem;
  
  tmp->value = value;
  tmp->next = NULL;

  if(_head == NULL){
    _head = _tail = tmp;
  }else{
    _tail->next = tmp;
    _tail = tmp;
  }

  _numItems++;
  _indexUpToDate = false;
}

template <typename T>
T LinkedList<T>::getValue(int index) {
  if(!_indexUpToDate){
    maintainIndex();
  }

  return _index[index]->value;
}

template <typename T>
T LinkedList<T>::operator[](int index) {
  return getValue(index);
}

template <typename T>
int LinkedList<T>::numItems() {
  return _numItems;
}

template <typename T>
void LinkedList<T>::maintainIndex() {
  LinkedListItem* tmp;
  int curIndex = 0;

  if(_head != NULL){
    _index = new LinkedListItem*[numItems()];
    tmp = _head;

    while(tmp != NULL){
      _index[curIndex++] = tmp;
      tmp = tmp->next;
    }

    _indexUpToDate = true;
  }
}
#endif

