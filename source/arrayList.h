#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "linearList.h"
#include "myException.h"
#include <initializer_list>

// MyDataStructures::arrayList<T> is an implementation of std::vector<T>

namespace MyDataStructures
{
	template <class T>
	class arrayList : public linearList<T, T*>
	{
	private:
		size_t initial_capacity = 16;
	public:
		using iterator = T*;
		struct reverse_iterator
		{
			explicit reverse_iterator(const T*& _place) :place(_place) {}
			explicit reverse_iterator(T*&& _place) :place(_place) {}
			T* place;
			T& operator*() { return *place; }
			const T& operator*() const { return *place; }
			bool operator==(const reverse_iterator& _rit) const { return place == _rit.place; }
			bool operator!=(const reverse_iterator& _rit) const { return place != _rit.place; }
			reverse_iterator& operator++() { --place; return *this; }
			reverse_iterator operator++(int)
			{
				reverse_iterator it = *this;
				--place;
				return it;
			}
			reverse_iterator& operator--() { ++place; return *this; }
			reverse_iterator operator--(int)
			{
				reverse_iterator it = *this;
				++place;
				return it;
			}
			reverse_iterator& operator+=(const int _offset) { place -= _offset; return *this; }
			reverse_iterator& operator-=(const int _offset) { place += _offset; return *this; }
			reverse_iterator operator+(const int _offset) const { return reverse_iterator(place - _offset); }
			reverse_iterator operator-(const int _offset) const { return reverse_iterator(place + _offset); }
			friend int operator-(const reverse_iterator& _rit1, const reverse_iterator& _rit2)
			{
				return _rit2.place - _rit1.place;
			}
		};

		arrayList()
			:elements(new T[initial_capacity]{}),
			arrayLength(initial_capacity), listSize(0) {}
		explicit arrayList(size_t _size)
		{
			size_t q = 1;
			while (q < _size) q <<= 1;
			arrayLength = q;
			if (!(q > 0)) throw MyException::illegalArrayListLength();
			elements = new T[q]{};
			listSize = _size;
		}
		arrayList(size_t _size, const T& _value)
		{
			size_t q = 1;
			while (q < _size) q <<= 1;
			arrayLength = q;
			if (!(q > 0)) throw MyException::illegalArrayListLength();
			elements = new T[q];
			for (size_t i = 0; i < _size; ++i)
			{
				elements[i] = _value;
			}
			listSize = _size;
		}
		arrayList(size_t _size, T&& _value)
		{
			size_t q = 1;
			while (q < _size) q <<= 1;
			arrayLength = q;
			if (!(q > 0)) throw MyException::illegalArrayListLength();
			elements = new T[q];
			for (size_t i = 0; i < _size; ++i)
			{
				elements[i] = _value;
			}
			listSize = _size;
		}
		arrayList(const arrayList<T>& _right)
		{
			elements = new T[_right.arrayLength];
			for (size_t i = 0; i < _right.listSize; ++i)
			{
				elements[i] = _right.elements[i];
			}
			arrayLength = _right.arrayLength;
			listSize = _right.listSize;
		}
		arrayList(arrayList<T>&& _right) noexcept
		{
			elements = _right.elements;
			arrayLength = _right.arrayLength;
			listSize = _right.listSize;
			_right.elements = nullptr;	
		}
		arrayList(const std::initializer_list<T>& _list)
		{
			size_t q = 1, _size = _list.size();
			while (q < _size) q <<= 1;
			arrayLength = q;
			if (!(q > 0)) throw MyException::illegalArrayListLength();
			elements = new T[q];
			listSize = _size;
			T* begin = elements;
			for (auto p = _list.begin(); p != _list.end(); ++p, ++begin)
			{
				*begin = *p;
			}
		}

		arrayList& operator=(const arrayList<T>& _right)
		{
			if(this!=&_right)
			{
				delete[] elements;
				elements = new T[_right.arrayLength];
				for (size_t i = 0; i < _right.listSize; ++i)
				{
					elements[i] = _right.elements[i];
				}
				arrayLength = _right.arrayLength;
				listSize = _right.listSize;
			
			}
			return *this;
		}
		arrayList& operator=(arrayList<T>&& _right) noexcept
		{
			if (this != &_right)
			{
				delete[] elements;
				elements = _right.elements;
				arrayLength = _right.arrayLength;
				listSize = _right.listSize;
				_right.elements = nullptr;
			}
			return *this;
		}
		arrayList& operator=(const std::initializer_list<T>& _list)
		{
			delete[] elements;
			size_t q = 1, _size = _list.size();
			while (q < _size) q <<= 1;
			arrayLength = q;
			if (!(q > 0)) throw MyException::illegalArrayListLength();
			elements = new T[q];
			listSize = _size;
			T* begin = elements;
			for (auto p = _list.begin(); p != _list.end(); ++p, ++begin)
			{
				*begin = *p;
			}
			return *this;
		}

		virtual ~arrayList() noexcept { delete[] elements; }

		virtual bool empty() const noexcept override { return listSize == 0; }
		virtual size_t size() const noexcept override { return listSize; }
		virtual size_t capacity() const noexcept { return arrayLength; }

		virtual void push_back(const T& _value) override
		{
			extendSizeByOne();
			elements[listSize - 1] = _value;
		}
		virtual void push_back(T&& _value) override
		{
			extendSizeByOne();
			elements[listSize - 1] = _value;
		}
		virtual void pop_back() override
		{
			if (listSize == 0) throw MyException::popEmptyContainer();
			else --listSize;
		}
		virtual iterator begin() const noexcept override { return elements; }
		virtual iterator end() const noexcept override { return elements + listSize; }
		virtual reverse_iterator rbegin() const noexcept { return reverse_iterator(elements + listSize - 1); }
		virtual reverse_iterator rend() const noexcept { return reverse_iterator(elements - 1); }
		virtual const T& back() const override { return *rbegin(); }
		virtual T& back() override { return *rbegin(); }
		virtual const T& front() const override { return *elements; }
		virtual T& front() override { return *elements; }
		virtual iterator insert(const iterator& _it, const T& _value) override
		{
			iterator target = extendSizeByOne(_it);
			reverse_iterator rit = rbegin();
			while (rit.place != target)
			{
				*rit = *(rit + 1);
				++rit;
			}
			*target = _value;
			return target;
		}
		virtual iterator insert(const iterator& _it, T&& _value) override
		{
			iterator target = extendSizeByOne(_it);
			reverse_iterator rit = rbegin();
			while (rit.place != target)
			{
				*rit = *(rit + 1);
				++rit;
			}
			*target = _value;
			return target;
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
			iterator target = _it;
			while (target + 1 != end())
			{
				*target = *(target + 1);
				++target;
			}
			--listSize;
			return _it;
		}
		virtual iterator erase(const iterator& _begin, const iterator& _end) override
		{
			size_t diff = _end - _begin;
			iterator target = _begin;
			while (target + diff != end())
			{
				*target = *(target + diff);
				++target;
			}
			listSize -= diff;
			return _begin;
		}
		virtual void clear() noexcept override { listSize = 0; }

		T& operator[](size_t _offset) noexcept { return elements[_offset]; }
		const T& operator[](size_t _offset) const noexcept { return elements[_offset]; }
		T& at(size_t _offset) { if (_offset < listSize) return elements[_offset]; throw MyException::subscriptOutOfRange(); }
		const T& at(size_t _offset) const { if (_offset < listSize) return elements[_offset]; throw MyException::subscriptOutOfRange(); }
	protected:
		T* elements;
		size_t arrayLength;	// capacity
		size_t listSize;		// size
	private:
		void extendLength(int newLength)
		{
			if (!(newLength > 0)) throw MyException::illegalArrayListLength();
			T* temp = elements;
			elements = new T[newLength];
			for (size_t i = 0; i < arrayLength; ++i)
			{
				elements[i] = temp[i];
			}
			arrayLength = newLength;
			delete[] temp;
		}
		void extendSizeByOne()
		{
			++listSize;
			if (!(listSize > 0)) throw MyException::outOfMemory();
			else if (listSize > arrayLength)
			{
				if (!((arrayLength << 1) > 0)) throw MyException::outOfMemory();
				else
				{
					extendLength(arrayLength << 1);
				}
			}
		}
		iterator extendSizeByOne(const iterator& it)
		{
			size_t diff = it - elements;
			extendSizeByOne();
			return elements + diff;
		}
	};
}

#endif
