#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <string>
#include <iostream>

namespace MyException
{
	class exception
	{
	public:
		exception() {}
		virtual void printError() 
		{
			std::cerr << information;
		}
		virtual ~exception() {}
	protected:
		std::string information;
	};

	class illegalParameter : public exception {};

	class illegalArrayListLength :public illegalParameter
	{
	public:
		illegalArrayListLength()
		{
			information = "Illegal ArrayList Length!\n";
		}
	};

	class subscriptOutOfRange :public illegalParameter
	{
	public:
		subscriptOutOfRange()
		{
			information = "Subscript Out Of Range!\n";
		}
	};

	class outOfMemory :public exception
	{
	public:
		outOfMemory()
		{
			information = "Out Of Memory!\n";
		}
	};

	class popEmptyContainer : public exception
	{
	public:
		popEmptyContainer()
		{
			information = "Can't Pop Empty Container!\n";
		}
	};
}

#endif
