#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

namespace MyDataStructures
{
	template <class T, class ItT>
	class linearList
	{
	public:
		using value_type = T;
		using size_type = size_t;
		using iterator = ItT;

		virtual ~linearList() noexcept {}

		virtual bool empty() const noexcept = 0;
		virtual size_t size() const noexcept = 0;

		virtual void push_back(const T& _value) = 0;
		virtual void push_back(T&& _value) = 0;
		virtual void pop_back() = 0;
		virtual iterator begin() const noexcept = 0;
		virtual iterator end() const noexcept = 0;
		virtual const T& front() const = 0;
		virtual T& front() = 0;
		virtual const T& back() const = 0;
		virtual T& back() = 0;
		virtual iterator insert(const iterator& _it, const T& _value) = 0;
		virtual iterator insert(const iterator& _it, T&& _value) = 0;
		virtual void insert(const iterator& _it, const iterator& _begin, const iterator& _end) = 0;
		virtual iterator erase(const iterator& _it) = 0;
		virtual iterator erase(const iterator& _begin, const iterator& _end) = 0;
		virtual void clear() noexcept = 0;
	};
}

#endif
