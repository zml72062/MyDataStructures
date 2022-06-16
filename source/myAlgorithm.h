#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H

#include "myUtility.h"
#include <initializer_list>
#include <string>

namespace MyAlgorithm
{
	template <class T, class Pr = MyDataStructures::less<T>>
	constexpr T max(const T& _left, const T& _right, Pr _cmp = Pr())
	{
		return (_cmp(_left, _right) ? _right : _left);
	}
	template <class T, class Pr = MyDataStructures::less<T>>
	constexpr T min(const T& _left, const T& _right, Pr _cmp = Pr())
	{
		return (_cmp(_left, _right) ? _left : _right);
	}
	template <class T, class Pr = MyDataStructures::less<T>>
	constexpr T max(const std::initializer_list<T>& _nums, Pr _cmp = Pr())
	{
		T _max{ *_nums.begin() };
		for (auto p = _nums.begin(); p != _nums.end(); ++p)
		{
			if (p == _nums.begin())
			{
				continue;
			}
			if (_cmp(_max, *p))
			{
				_max = *p;
			}
		}
		return _max;
	}
	template <class T, class Pr = MyDataStructures::less<T>>
	constexpr T min(const std::initializer_list<T>& _nums, Pr _cmp = Pr())
	{
		T _min{ *_nums.begin() };
		for (auto p = _nums.begin(); p != _nums.end(); ++p)
		{
			if (p == _nums.begin())
			{
				continue;
			}
			if (!_cmp(_min, *p))
			{
				_min = *p;
			}
		}
		return _min;
	}
	template <class T, class U>
	U copy(const T& _begin, const T& _end, const U& _target)
	{
		T traverse = _begin;
		U copied = _target;
		for (; traverse != _end; ++traverse, ++copied) *copied = *traverse;
		return copied;
	}

	class KMPUtility
	{
	public:
		friend inline std::size_t KMPfind(const std::string& source, const std::string& tmp);
	private:
		// Record the longest common suffix-prefix length of tmp[0:n]
		static int* KMPnext(const std::string& tmp)
		{
			size_t size = tmp.size();
			int* ans = new int[size];
			ans[0] = 0;
			bool flag;
			for (size_t i = 1; i < size; ++i)
			{
				flag = false;
				int p = ans[i - 1];
				// While the next character does not match
				while (tmp[i] != tmp[p])
				{
					// The next character does not match the beginning one
					// Common suffix-prefix length = 0
					if (p == 0)
					{
						ans[i] = 0;
						flag = true;
						break;
					}
					// Compare the current character with
					// the nearest character whose left substring
					// can match the left substring of the current character
					p = ans[p - 1];
				}
				if (!flag)
				{
					ans[i] = p + 1;
				}
			}
			return ans;
		}
	};

	// KMP Algorithm
	//		Find the first place where tmp appears as a substring of source
	//		Time complexity O(source.size() + temp.size())
	inline std::size_t KMPfind(const std::string& source, const std::string& tmp)
	{
		// If tmp[0:m] == source[i:i+m], but tmp[m+1] != source[i+m+1]
		// Only if for some j, tmp[0:j] == tmp[m-j:m],
		// should we compare source[i+(m-j):i+m] with tmp[0:j]

		// Construct next array
		int* next = KMPUtility::KMPnext(tmp);

		size_t i = 0, j = 0;
		while (true)
		{
			if (j == tmp.size())
			{
				delete[] next;
				return i - j;
			}
			if (i == source.size())
			{
				delete[] next;
				return std::string::npos;
			}
			if (source[i] == tmp[j])
			{
				++i; ++j;
			}
			else
			{
				if (j == 0)
				{
					++i;
				}
				else
				{
					j = next[j - 1];
				}
			}
		}
	}


}

#endif