#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <ctime>
#include <cstdio>

#define START_CLOCK		{ std::clock_t __FIRST__CLOCK__ = std::clock();
#define END_CLOCK		std::clock_t __SECOND__CLOCK__ = std::clock(); std::printf("\nTime:  %.6lf sec\n", (double)(__SECOND__CLOCK__ - __FIRST__CLOCK__) / CLOCKS_PER_SEC); }

namespace MyDataStructures
{

	template <class T>
	struct less
	{
		constexpr bool operator()(const T& _left, const T& _right) const
		{
			return _left < _right;
		}
	};

	template <class T>
	struct greater
	{
		constexpr bool operator()(const T& _left, const T& _right) const
		{
			return _left > _right;
		}
	};

	template <class T>
	struct lessEqual
	{
		constexpr bool operator()(const T& _left, const T& _right) const
		{
			return _left <= _right;
		}
	};

	template <class T>
	struct greaterEqual
	{
		constexpr bool operator()(const T& _left, const T& _right) const
		{
			return _left >= _right;
		}
	};
}

#endif