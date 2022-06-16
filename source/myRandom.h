#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include <random>
#include <ctime>

template <int min, int max, class Distribution = std::uniform_int_distribution<>>
class randomInt
{
public:
	randomInt() :_engine(std::time(nullptr)), _numbers(min, max) {	}
	template <class IntContainer>
	void operator()(IntContainer& _container)
	{
		for (auto p = _container.begin(); p != _container.end(); ++p)
		{
			*p = _numbers(_engine);
		}
	}
	template <std::size_t size>
	void operator()(int(&_container)[size])
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			_container[i] = _numbers(_engine);
		}
	}
private:
	std::default_random_engine _engine;
	Distribution _numbers;
};

template <int min, int max, class Distribution = std::uniform_real_distribution<>>
class randomDouble
{
public:
	randomDouble() :_engine(std::time(nullptr)), _numbers(static_cast<double>(min), static_cast<double>(max)) {	}
	template <class DoubleContainer>
	void operator()(DoubleContainer& _container)
	{
		for (auto p = _container.begin(); p != _container.end(); ++p)
		{
			*p = _numbers(_engine);
		}
	}
	template <std::size_t size>
	void operator()(double(&_container)[size])
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			_container[i] = _numbers(_engine);
		}
	}
private:
	std::default_random_engine _engine;
	Distribution _numbers;
};

#endif
