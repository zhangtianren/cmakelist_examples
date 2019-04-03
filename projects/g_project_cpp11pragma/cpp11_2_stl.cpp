#include "cpp11_header.h"
#include<iostream>
using namespace std;


/*
std::array��������飬�����˵������Ⱥ���
(ʵ���� ���͵� for (auto i : array) ��������Ҳ�ǿ��е�)
*/
#include <array>
void test_array()
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
std::forward_listΪ��++���������Ա���list�����������ǵ�������
*/
#include <forward_list>
void test_forwardlist()
{
	std::forward_list<int> numbers = { 1,2,3,4,5,4,4 };
	std::cout << "numbers:" << std::endl;
	for (auto number : numbers)
	{
		std::cout << number << std::endl;
	}
	numbers.remove(4);
	std::cout << "numbers after remove:" << std::endl;
	for (auto number : numbers)
	{
		std::cout << number << std::endl;
	}
}

/*
std::unordered_map��std::map�÷�������࣬��STL���ڲ�ʵ�����кܴ�ͬ��
std::mapʹ�õ����ݽṹΪ����������std::unordered_map�ڲ��ǹ�ϣ���ʵ�ַ�ʽ����ϣmap�����ϲ���Ч��ΪO(1)��
���ڴ洢Ч���ϣ���ϣmap��Ҫ���ӹ�ϣ����ڴ濪����
*/
#include <unordered_map>
void test_unorderedmap()
{
	std::unordered_map<std::string, std::string> mymap =
	{
		{ "house","maison" },
		{ "apple","pomme" },
		{ "tree","arbre" },
		{ "book","livre" },
		{ "door","porte" },
		{ "grapefruit","pamplemousse" }
	};
	unsigned n = mymap.bucket_count();
	std::cout << "mymap has " << n << " buckets.\n";
	for (unsigned i = 0; i<n; ++i)
	{
		std::cout << "bucket #" << i << " contains: ";
		for (auto it = mymap.begin(i); it != mymap.end(i); ++it)
			std::cout << "[" << it->first.c_str() << ":" << it->second.c_str() << "] ";
		std::cout << "\n";
	}
}


/*
std::unordered_set�����ݴ洢�ṹҲ�ǹ�ϣ��ķ�ʽ�ṹ��
����֮�⣬std::unordered_set�ڲ���ʱ�����Զ������ⶼ��std::set���ֲ�ͬ�ĵط���
*/
#include <set>
#include <unordered_set>
void test_unorderedset()
{
	std::unordered_set<int> unorder_set;
	unorder_set.insert(7);
	unorder_set.insert(5);
	unorder_set.insert(3);
	unorder_set.insert(4);
	unorder_set.insert(6);
	std::cout << "unorder_set:" << std::endl;
	for (auto itor : unorder_set)
	{
		std::cout << itor << std::endl;
	}

	std::set<int> set;
	set.insert(7);
	set.insert(5);
	set.insert(3);
	set.insert(4);
	set.insert(6);
	std::cout << "set:" << std::endl;
	for (auto itor : set)
	{
		std::cout << itor << std::endl;
	}
}