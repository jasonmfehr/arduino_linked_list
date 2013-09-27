/*

Copyright (C) 2013 Jason Fehr

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

Very basic implementation of a templated Linked List.  The implementation 
is single linked with the tail linked to the head.  The actual list 
implementation should not matter to the user of this class.

This list works by maintaining a count of the number of items in the list.  
When accessing an individual item in the list, the iterator starts with 
the first item and jumps to the next item in the list until the desired 
list item is reached.  So, to locate the fifth item in the list requires 
five hops.  This method is used so that the amount of memory needed to 
store a list is minimal.

A note of caution.  This particular implementation has no safeguards 
in place to prevent reading more than the number of items in the list.  
For example, if a list has three items and the getValue() function is 
called with a parameter of five, no errors will be thrown.  Since the 
list tail is linked to the head, the iterator will simply wrap around 
and return the second item in the list.
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
  
  private:
    typedef struct LinkedListItem {
      T value;
      LinkedListItem* next;
    } LinkedListItem;

    int _numItems;
    LinkedListItem* _head;
    LinkedListItem* _tail;
};


template <typename T>
LinkedList<T>::LinkedList() {
  _head = _tail = NULL;
  _numItems = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  LinkedListItem* tmp = _head;

  for(int i=0; i<_numItems; i++){
    tmp = _head;
    _head = _head->next;
    delete tmp;
  }
}

template <typename T>
void LinkedList<T>::addItem(T value) {
  LinkedListItem* tmp = new LinkedListItem;
  
  tmp->value = value;

  if(_head == NULL){
    _head = _tail = tmp;
    _head->next = _tail;
  }else{
    _tail->next = tmp;
    _tail = tmp;
  }

  _tail->next = _head;
  _numItems++;
}

template <typename T>
T LinkedList<T>::getValue(int index) {
  LinkedListItem* item = _head;

  for(int i=1; i<=index; i++){
    item = item-> next;
  }

  return item->value;
}

template <typename T>
int LinkedList<T>::numItems() {
  return _numItems;
}
#endif

