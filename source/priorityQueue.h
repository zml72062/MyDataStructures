#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "arrayList.h"

namespace MyDataStructures
{
	template <class T>
	class fullBinaryTree :protected arrayList<T>
	{
	public:
		using arrayList<T>::arrayList;
		using arrayList<T>::operator=;
		using arrayList<T>::empty;
		using arrayList<T>::size;
		using arrayList<T>::operator[];
		using arrayList<T>::at;
		using arrayList<T>::iterator;
		using arrayList<T>::reverse_iterator;
		using arrayList<T>::push_back;
		using arrayList<T>::pop_back;
		using arrayList<T>::begin;
		using arrayList<T>::end;
		using arrayList<T>::rbegin;
		using arrayList<T>::rend;
		iterator leftSon(iterator _it)
		{
			size_t diff = _it - begin(), target = (diff << 1) + 1;
			if (begin() + target < end())
			{
				return begin() + target;
			}
			return end();
		}
		iterator rightSon(iterator _it)
		{
			size_t diff = _it - begin(), target = (diff << 1) + 2;
			if (begin() + target < end())
			{
				return begin() + target;
			}
			return end();
		}
		iterator parent(iterator _it)
		{
			if (_it == begin())
			{
				return end();
			}
			size_t diff = _it - begin(), target = (diff - 1) >> 1;
			return begin() + target;
		}
	};

	template <class U>
	void _swap(U& _left, U& _right)
	{
		U temp = _left;
		_left = _right;
		_right = temp;
	}

	template <class T, class Pred = MyDataStructures::less<T>>
	class priorityQueue
	{
	private:
		arrayList<T> data;
		size_t length;
		T& operator[](size_t _offset) { return data[_offset]; }

		void percolate_down(size_t _place)
		{
			size_t left = ((_place << 1) + 1), right = ((_place << 1) + 2);
			Pred comp;
			if (left < length)
			{
				if (comp(operator[](_place), operator[](left)))
				{
					_swap(operator[](_place), operator[](left));
					percolate_down(left);
				}
			}
			if (right < length)
			{
				if (comp(operator[](_place), operator[](right)))
				{
					_swap(operator[](_place), operator[](right));
					percolate_down(right);
				}
			}
		}
		void make_heap()
		{
			if (length == 0 || length == 1) return;
			size_t t = length >> 1;
			for (size_t j = t; j > 0; --j)
			{
				percolate_down(j - 1);
			}
		}
		void percolate_up(size_t _place)
		{
			if (_place == 0) return;
			Pred comp;
			size_t t = (_place - 1) >> 1;
			if (comp(operator[](t), operator[](_place)))
			{
				_swap(operator[](t), operator[](_place));
				percolate_up(t);
			}
		}
		size_t percolate_son(size_t _place)
		{
			size_t left = ((_place << 1) + 1), right = ((_place << 1) + 2);
			Pred comp;
			if (left < length && right < length)
			{
				if (comp(operator[](left), operator[](right)))
				{
					_swap(operator[](_place), operator[](right));
					percolate_son(right);
				}
				else
				{
					_swap(operator[](_place), operator[](left));
					percolate_son(left);
				}
			}
			else if (left < length)
			{
				_swap(operator[](_place), operator[](left));
				percolate_son(left);
			}
			else if (right < length)
			{
				_swap(operator[](_place), operator[](right));
				percolate_son(right);
			}
			else
			{
				_swap(operator[](_place), operator[](length - 1));
				return _place;
			}
		}
	public:
		size_t size() const noexcept { return length; }
		bool empty() const noexcept { return length == 0; }

		template <class U>
		priorityQueue(const U& _begin, const U& _end) :data(), length(0)
		{
			for (auto p = _begin; p != _end; ++p) push(*p);
		}
		priorityQueue(const std::initializer_list<T>& _list) :data(_list)
		{
			length = data.size();
			make_heap();
		}

		priorityQueue<T, Pred>& operator=(const priorityQueue<T, Pred>& _right) = default;
		priorityQueue<T, Pred>& operator=(priorityQueue<T, Pred>&& _right) = default;
		priorityQueue<T, Pred>& operator=(const std::initializer_list<T>& _list)
		{
			data = _list;
			length = data.size();
			make_heap();
		}

		const T& top() const
		{
			if (empty()) throw MyException::popEmptyContainer();
			return data[0];
		}
		void push(const T& _value)
		{
			data.push_back(_value);
			++length;
			percolate_up(length - 1);
		}
		void push(T&& _value)
		{
			data.push_back(_value);
			++length;
			percolate_up(length - 1);
		}
		void pop()
		{
			if (length == 0) throw MyException::popEmptyContainer();
			size_t _place = percolate_son(0);
			data.pop_back();
			--length;
			if (_place != length)
			{
				percolate_up(_place);
			}
		}
	};
}

#endif
