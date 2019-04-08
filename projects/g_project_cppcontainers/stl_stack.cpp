#include "stl_headers.h"
#include<iostream>
using namespace std;

/*
container adapter (Ĭ����dequeΪ�ײ�����)

�Ƚ���������ݽṹ����ֻ��һ�����ڣ�ֻ�ܹ��ڶ����������Ƴ���ȡ��Ԫ�أ�û��������ʽ���в���
*/

#include <stack>
#include <list>
#include <vector>
void test_stack(void)
{
	std::stack<int, std::list<int>> stk;
	// std::stack<int, std::vector<int>> stk;
	stk.push(1);
	stk.push(2);
	stk.push(3);

	std::cout << stk.size() << std::endl;
	std::cout << stk.top() << std::endl;

	stk.pop();
	std::cout << stk.size() << std::endl;
	std::cout << stk.top() << std::endl;

	stk.pop();
	std::cout << stk.size() << std::endl;
	std::cout << stk.top() << std::endl;

	stk.pop();
	std::cout << stk.size() << std::endl;
}

/*
Դ�����
template <class T, class Sequence = deque<T> >
class stack {
friend bool operator== __STL_NULL_TMPL_ARGS (const stack&, const stack&);
friend bool operator< __STL_NULL_TMPL_ARGS (const stack&, const stack&);
public:
typedef typename Sequence::value_type value_type;
typedef typename Sequence::size_type size_type;
typedef typename Sequence::reference reference;
typedef typename Sequence::const_reference const_reference;
protected:
Sequence c;           // �ײ�������Ĭ��Ϊdeque
public:
//Sequence�ӿڵķ�װ
bool empty() const { return c.empty(); }
size_type size() const { return c.size(); }
reference top() { return c.back(); }
const_reference top() const { return c.back(); }
void push(const value_type& x) { c.push_back(x); }
void pop() { c.pop_back(); }
};

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
return x.c == y.c;
}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
return x.c < y.c;
}
*/