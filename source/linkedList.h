#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "linearList.h"
#include "myException.h"
#include <initializer_list>

// MyDataStructures::doublyLinkedList<T> is an implementation of std::list<T>

namespace MyDataStructures
{
	template <class T>
	struct doublyLinkedListNode
	{
		T* data;
		doublyLinkedListNode* next;
		doublyLinkedListNode* prev;
		doublyLinkedListNode() :data(nullptr), next(nullptr), prev(nullptr) {}
		explicit doublyLinkedListNode(const T& _data) :data(new T(_data)), next(nullptr), prev(nullptr) {}
		explicit doublyLinkedListNode(T&& _data) :data(new T(_data)), next(nullptr), prev(nullptr) {}
		doublyLinkedListNode(doublyLinkedListNode* _next, doublyLinkedListNode* _prev) :data(nullptr), next(_next), prev(_prev) {}
		~doublyLinkedListNode() { delete data; }

		T& operator*() { return *data; }
		const T& operator*() const { return *data; }
	};

	namespace linkedListIterators
	{
		template <class T>
		struct iterator
		{
		public:
			explicit iterator(doublyLinkedListNode<T>* _place) :place(_place) {}
			T& operator*() { return *(*place); }
			const T& operator*() const { return *(*place); }
			bool operator==(const iterator& _it) { return place == _it.place; }
			bool operator!=(const iterator& _it) { return place != _it.place; }
			iterator& operator++() { place = place->next; return *this; }
			iterator operator++(int)
			{
				iterator it(place);
				place = place->next;
				return it;
			}
			iterator& operator--() { place = place->prev; return *this; }
			iterator operator--(int)
			{
				iterator it(place);
				place = place->prev;
				return it;
			}
			doublyLinkedListNode<T>* place;
		};

		template <class T>
		struct reverse_iterator
		{
		public:
			explicit reverse_iterator(doublyLinkedListNode<T>* _place) :place(_place) {}
			T& operator*() { return *(*place); }
			const T& operator*() const { return *(*place); }
			bool operator==(const reverse_iterator& _rit) const { return place == _rit.place; }
			bool operator!=(const reverse_iterator& _rit) const { return place != _rit.place; }
			reverse_iterator& operator--() { place = place->next; return *this; }
			reverse_iterator operator--(int)
			{
				reverse_iterator it(place);
				place = place->next;
				return it;
			}
			reverse_iterator& operator++() { place = place->prev; return *this; }
			reverse_iterator operator++(int)
			{
				reverse_iterator it(place);
				place = place->prev;
				return it;
			}
			doublyLinkedListNode<T>* place;
		};
	}

	template <class T>
	class doublyLinkedList :public linearList<T, linkedListIterators::iterator<T>>
	{
	public:
		using iterator = linkedListIterators::iterator<T>;
		using reverse_iterator = linkedListIterators::reverse_iterator<T>;
		doublyLinkedList() :head(new doublyLinkedListNode<T>()), last(new doublyLinkedListNode<T>()), length(0)
		{
			head->next = last;
			last->prev = head;
		}
		// deep-copy a list
		doublyLinkedList(const doublyLinkedList& _right)
		{
			head = new doublyLinkedListNode<T>();
			last = new doublyLinkedListNode<T>();
			auto trav = _right.head, p = head;
			while (trav->next != _right.last)
			{
				trav = trav->next;
				p->next = new doublyLinkedListNode<T>(*(trav->data));
				p->next->prev = p;
				p = p->next;
			}
			p->next = last;
			last->prev = p;
			length = _right.length;
		}
		doublyLinkedList(doublyLinkedList&& _right) = delete;
		doublyLinkedList(const std::initializer_list<T>& _list)
		{
			head = new doublyLinkedListNode<T>();
			last = new doublyLinkedListNode<T>();
			auto trav = _list.begin();
			auto p = head;
			length = 0;
			while (trav != _list.end())
			{
				p->next = new doublyLinkedListNode<T>(*trav);
				p->next->prev = p;
				p = p->next;
				++trav; ++length;
			}
			p->next = last;
			last->prev = p;
		}

		// deep-copy a list
		doublyLinkedList& operator=(const doublyLinkedList& _right)
		{
			if (this != &_right)
			{
				clear();
				delete head;
				delete last;
				head = new doublyLinkedListNode<T>();
				last = new doublyLinkedListNode<T>();
				auto trav = _right.head, p = head;
				while (trav->next != _right.last)
				{
					trav = trav->next;
					p->next = new doublyLinkedListNode<T>(*(trav->data));
					p->next->prev = p;
					p = p->next;
				}
				p->next = last;
				last->prev = p;
				length = _right.length;
			}
			return *this;
		}
		doublyLinkedList& operator=(doublyLinkedList&& _right) = delete;
		doublyLinkedList& operator=(const std::initializer_list<T>& _list)
		{
			clear();
			delete head;
			delete last;
			head = new doublyLinkedListNode<T>();
			last = new doublyLinkedListNode<T>();
			auto trav = _list.begin();
			auto p = head;
			length = 0;
			while (trav != _list.end())
			{
				p->next = new doublyLinkedListNode<T>(*trav);
				p->next->prev = p;
				p = p->next;
				++trav; ++length;
			}
			p->next = last;
			last->prev = p;
			return *this;
		}
		~doublyLinkedList() { clear(); delete head; delete last; }

		virtual bool empty() const noexcept override { return length == 0; }
		virtual size_t size() const noexcept override { return length; }

		virtual iterator begin() const noexcept override { return iterator(head->next); }
		virtual iterator end() const noexcept override { return iterator(last); }
		virtual reverse_iterator rbegin() const noexcept { return reverse_iterator(last->prev); }
		virtual reverse_iterator rend() const noexcept { return reverse_iterator(head); }
		virtual const T& back() const override { return *rbegin(); }
		virtual T& back() override { return *rbegin(); }
		virtual const T& front() const override { return *begin(); }
		virtual T& front() override { return *begin(); }
		virtual iterator insert(const iterator& _it, const T& _value) override
		{
			auto before = _it.place->prev, after = _it.place;
			before->next = new doublyLinkedListNode<T>(_value);
			auto now = before->next;
			now->prev = before;
			now->next = after;
			after->prev = now;
			++length;
			return iterator(now);
		}
		virtual iterator insert(const iterator& _it, T&& _value) override
		{
			auto before = _it.place->prev, after = _it.place;
			before->next = new doublyLinkedListNode<T>(_value);
			auto now = before->next;
			now->prev = before;
			now->next = after;
			after->prev = now;
			++length;
			return iterator(now);
		}
		virtual void insert(const iterator& _it, const iterator& _begin, const iterator& _end) override
		{
			iterator trav = _begin, target = _it;
			while (trav != _end)
			{
				target = insert(target, *trav);
				++target; ++trav;
			}
		}
		virtual iterator erase(const iterator& _it) override
		{
			auto before = _it.place->prev, after = _it.place->next;
			delete before->next;
			before->next = after;
			after->prev = before;
			--length;
			return iterator(after);
		}
		virtual iterator erase(const iterator& _begin, const iterator& _end) override
		{
			auto before = _begin.place->prev;
			while (before->next != _end.place)
			{
				auto q = before->next;
				before->next = q->next;
				--length;
				delete q;
			}
			before->next = _end.place;
			_end.place->prev = before;
			return iterator(_end.place);
		}
		virtual void clear() noexcept override
		{
			while (head->next != last)
			{
				auto q = head->next;
				head->next = q->next;
				delete q;
			}
			last->prev = head;
			length = 0;
		}
		virtual void push_back(const T& _value) override
		{
			insert(end(), _value);
		}
		virtual void push_back(T&& _value) override
		{
			insert(end(), _value);
		}
		virtual void pop_back() override
		{
			if (length == 0) throw MyException::popEmptyContainer();
			auto q = end().place->prev;
			end().place->prev = q->prev;
			q->prev->next = end().place;
			delete q;
			--length;
		}
		virtual void push_front(const T& _value)
		{
			insert(begin(), _value);
		}
		virtual void push_front(T&& _value)
		{
			insert(begin(), _value);
		}
		virtual void pop_front()
		{
			if (length == 0) throw MyException::popEmptyContainer();
			erase(begin());
		}
	protected:
		doublyLinkedListNode<T>* head;
		doublyLinkedListNode<T>* last;
		size_t length;
	};
}

#endif
