#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

class DisjointSet
{
public:
	DisjointSet(size_t _number) :number(_number), parent(std::vector<int>(_number))
	{
		for (size_t i = 0; i < _number; ++i)
		{
			parent[i] = initial_value;
		}
	}

	int Find(int value)
	{
		if (parent[value] == initial_value)
		{
			return value;
		}
		return parent[value] = Find(parent[value]);
	}

	void Union(int value1, int value2)
	{
		int find1 = Find(value1), find2 = Find(value2);
		parent[find2] = find1;
	}
private:
	static const int initial_value = -1;
	std::vector<int> parent;
	size_t number;
};


#endif
