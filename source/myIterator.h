#ifndef MY_ITERATOR_H
#define MY_ITERATOR_H

namespace MyIterator
{
	template <class T>
	class iterator
	{
	public:
		virtual iterator<T>& operator=(const iterator<T>& _right) = 0;
		virtual T& operator*() = 0;
		virtual const T& operator*() const = 0;
		virtual bool operator==(const iterator<T>& _right) const = 0;
		virtual bool operator!=(const iterator<T>& _right) const = 0;
		virtual ~iterator() {}
	};

	template <class T>
	class forwardIterator :public iterator<T>
	{
	public:
		virtual forwardIterator& operator++() = 0;
		virtual forwardIterator operator++(int) = 0;
		virtual ~forwardIterator() {}
	};

	template <class T>
	class forwardBackwardIterator :public forwardIterator<T>
	{
	public:
		virtual forwardBackwardIterator& operator--() = 0;
		virtual forwardBackwardIterator operator--(int) = 0;
		virtual ~forwardBackwardIterator() {}
	};

	template <class T>
	class randomAccessIterator :public forwardBackwardIterator<T>
	{
	public:
		virtual randomAccessIterator& operator+=(size_t _offset) = 0;
		virtual randomAccessIterator operator+(size_t _offset) const = 0;
		virtual randomAccessIterator& operator-=(size_t _offset) = 0;
		virtual randomAccessIterator operator-(size_t _offset) const = 0;
		virtual T& operator[](size_t _offset) const { return *(this + _offset); }
		virtual const T& operator[](size_t _offset) const { return *(this + _offset); }
		virtual int operator-(const randomAccessIterator<T>& _right) const = 0;
		virtual bool operator<(const randomAccessIterator<T>& _right) const = 0;
		virtual bool operator>(const randomAccessIterator<T>& _right) const = 0;
		virtual bool operator<=(const randomAccessIterator<T>& _right) const = 0;
		virtual bool operator>=(const randomAccessIterator<T>& _right) const = 0;
		virtual ~randomAccessIterator() {}
	};

	template <class T>
	inline void advance(forwardBackwardIterator<T>& _fwdIt, int _step)
	{
		if (_step >= 0)
		{
			for (size_t i = 0; i < _step; ++i)
			{
				++_fwdIt;
			}
		}
		else
		{
			size_t __step = -_step;
			for (size_t i = 0; i < __step; ++i)
			{
				--_fwdIt;
			}
		}
	}

	template <class T>
	inline size_t distance(const forwardIterator<T>& _front, const forwardIterator<T>& _back)
	{
		size_t _dist = 0;
		for (forwardIterator<T> _it = _front; _it != _back; ++_it, ++_dist);
		return _dist;
	}

	template <class T>
	inline void iter_swap(const iterator<T>& _front, const iterator<T>& _back)
	{
		T temp = *_front;
		*_front = *_back;
		*_back = temp;
	}
}


#endif 
