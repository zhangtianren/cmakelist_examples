#include "stl_headers.h"
#include<iostream>
using namespace std;


/*
�����Ĺ̶���С�Ŀռ䣬��ʼ��ʱҪָ����С�������Զ����䡣�ײ�ʵ��Ϊ������

1 �����vector �����ܶ�̬�������������������м�������ɾ������
2 ����� ��stl������ int[] ,�����˵������Ľӿ�
*/
#include <array>
void test_array(void)
{
	std::array<int, 4> arrayDemo = { 1,2,3,4 };
	std::cout << "arrayDemo:" << std::endl;
	for (auto itor : arrayDemo)
	{
		std::cout << itor << std::endl;
	}
	int arrayDemoSize = sizeof(arrayDemo);
	std::cout << "arrayDemo size:" << arrayDemoSize << std::endl;

}


/*
Դ��ʵ��, ԭʼ����
template<class _Ty,
size_t _Size>
class array
{	// fixed size array of values
public:
	oper ...

_Ty _Elems[_Size];
*/