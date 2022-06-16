#ifndef LIST_ADAPTERS_H
#define LIST_ADAPTERS_H

#include "linkedList.h"

namespace MyDataStructures
{
	template <class T>
	class Stack: protected doublyLinkedList<T>
	{
	public:
		virtual ~Stack() {}

		using doublyLinkedList<T>::empty;
		using doublyLinkedList<T>::size;
		virtual T& top()
		{
			return doublyLinkedList<T>::back();
		}
		virtual const T& top() const
		{
			return doublyLinkedList<T>::back();
		}
		virtual void push(const T& _value)
		{
			doublyLinkedList<T>::push_back(_value);
		}
		virtual void push(T&& _value)
		{
			doublyLinkedList<T>::push_back(_value);
		}
		virtual void pop()
		{
			doublyLinkedList<T>::pop_back();
		}
	};

	template <class T>
	class Queue :protected doublyLinkedList<T>
	{
	public:
		virtual ~Queue() {}

		using doublyLinkedList<T>::empty;
		using doublyLinkedList<T>::size;
		using doublyLinkedList<T>::front;
		virtual void push(const T& _value)
		{
			doublyLinkedList<T>::push_back(_value);
		}
		virtual void push(T&& _value)
		{
			doublyLinkedList<T>::push_back(_value);
		}
		virtual void pop()
		{
			doublyLinkedList<T>::pop_front();
		}
	};

}

#endif
