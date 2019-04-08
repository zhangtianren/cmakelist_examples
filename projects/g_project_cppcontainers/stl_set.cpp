#include "stl_headers.h"
#include<iostream>
using namespace std;

/*
set ���ظ������ݵļ���
set�ĵײ������ɺ����ʵ�ֵģ���set / multimap / multiset��ͬ��
1 ��set�������ݵ�Ч����O��logn����ѷunordered_setһ��˼ҵײ��ǹ�ϣ����ѯ��O(1)
2 �������ʵ����ƽ�����������,����map�в�������ݻ��Զ������Ҹ����㴴����map��ģ��������������������л��ǽ�������
*/
#include <string>
#include <set>
void test_set(void)
{
	set<string> str;
	str.insert("zero");

	str.insert("one");
	str.insert("one");

	str.insert("two");
	str.insert("three");
	set<string> str1(str.begin(), str.end());
	for (const auto &i : str1)
		cout << i << " ";		// one three two zero
	cout << endl;
	cout << *str.begin() << " " << str.count("one") << " " << *str.find("one") << " " << endl;	// one 1 one 

}