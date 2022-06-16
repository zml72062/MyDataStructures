#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <string>
#include <stack>
#include <cstdlib>
using namespace std;

class Calculator
{
public:
	class illegalExpression {};
	explicit Calculator(const string& s)
	{
		auto p1 = s.begin(), p2 = s.end(), p3 = s.begin();
		stack<char> symbol;
		while (p3 != p2)
		{
			if (*p3 == '(' || *p3 == ')' || *p3 == '+' || *p3 == '-' || *p3 == '*' || *p3 == '/')
			{
				if (p3 != p1)
				{
					postOrder.push_back(string(p1, p3));
					p1 = p3;
				}
				if (*p3 == '(') symbol.push('(');
				else if (*p3 == ')')
				{
					while (!symbol.empty() && symbol.top() != '(')
					{
						postOrder.push_back(string() + symbol.top());
						symbol.pop();
					}
					if (symbol.empty())
					{
						throw illegalExpression();
					}
					else
					{
						symbol.pop();
					}
				}
				else if (*p3 == '+' || *p3 == '-')
				{
					while (!symbol.empty() && symbol.top() != '(')
					{
						postOrder.push_back(string() + symbol.top());
						symbol.pop();
					}
					symbol.push(*p3);
				}
				else if (*p3 == '*' || *p3 == '/')
				{
					if (!symbol.empty() && symbol.top() != '(' && symbol.top() != '+' && symbol.top() != '-')
					{
						postOrder.push_back(string() + symbol.top());
						symbol.pop();
					}
					symbol.push(*p3);
				}
				++p1; ++p3;
			}
			else
			{
				++p3;
			}
		}
		if (p3 != p1)
		{
			postOrder.push_back(string(p1, p3));
			p1 = p3;
		}
		while (!symbol.empty())
		{
			if (symbol.top() == '(') throw illegalExpression();
			postOrder.push_back(string() + symbol.top());
			symbol.pop();
		}
	}
	double operator()()
	{
		stack<double> number;
		auto p = postOrder.begin(), q = postOrder.end();
		while (p != q)
		{
			if (*p == "+")
			{
				double c1{}, c2{};
				if (!number.empty())
				{
					c1 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				if (!number.empty())
				{
					c2 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				number.push(c1 + c2);
			}
			else if (*p == "-")
			{
				double c1{}, c2{};
				if (!number.empty())
				{
					c1 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				if (!number.empty())
				{
					c2 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				number.push(c2 - c1);
			}
			else if (*p == "*")
			{
				double c1{}, c2{};
				if (!number.empty())
				{
					c1 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				if (!number.empty())
				{
					c2 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				number.push(c1 * c2);
			}
			else if (*p == "/")
			{
				double c1{}, c2{};
				if (!number.empty())
				{
					c1 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				if (!number.empty())
				{
					c2 = number.top();
					number.pop();
				}
				else throw illegalExpression();
				number.push(c2 / c1);
			}
			else
			{
				number.push(atof(p->c_str()));
			}
			++p;
		}
		return number.top();
	}
private:
	vector<string> postOrder;
};

#endif
