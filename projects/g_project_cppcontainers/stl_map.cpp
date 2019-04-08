#include "stl_headers.h"
#include<iostream>
using namespace std;

/*
map�ĵײ������ɺ����ʵ�ֵģ���set / multimap / multiset��ͬ��
1 ��map�������ݵ�Ч����O��logn����ѷunordered_mapһ��˼ҵײ��ǹ�ϣ����ѯ��O(1)
2 �������ʵ����ƽ�����������,����map�в�������ݻ��Զ������Ҹ����㴴����map��ģ��������������������л��ǽ�������
3 ͨ��keyֵ�Ƚ���ȷ��ÿһ��pair�Ĵ洢λ�ã����ԣ���map�д洢�����ݱ����ܹ��Ƚϴ�С
4 ���ܹ��޸�map�е�ÿ��pair�ļ�ֵkey��������Ϊ����������������Ұ���keyֵ���еģ��޸�keyֵ���ƻ�����������Ľṹ�������޸�pair�е�ʵֵvalue�Ǳ�����
5 map�м�ֵ���ܹ��ظ�,��Ҳ������multimap��Ψһ����
*/
#include <map>
void test_map(void)
{
	// ����һ���յ�map����ʱm��һ��Ԫ�ض�û��
	map<string, string> m;
	m["ƻ��"] = "apple";
	m["�㽶"] = "banana";
	/*
	operator[]��ԭ���ǣ�
	��<key, T()>����һ����ֵ�ԣ�Ȼ�����insert()�������ü�ֵ�Բ��뵽map��
	���key�Ѿ����ڣ�����ʧ�ܣ�insert�������ظ�key����λ�õĵ�����
	���key�����ڣ�����ɹ���insert���������²���Ԫ������λ�õĵ�����
	operator[]�������insert����ֵ��ֵ���е�value����
	*/

	// ��<"apple", "">����map�У�����ɹ�������value�����ã�����ƻ������ֵ�������ý����
	// ���޸���"apple"��Ӧ��value""Ϊ"ƻ��"

	m["apple"] = "ƻ��";

	// ��<"apple", "">����map�У�����ʧ�ܣ���<"apple", "ƻ��">�е�"ƻ��"����

	std::cout << m["apple"].c_str() << endl;
	std::cout << m.size() << endl;

	// ��banan����map�У��ú������쳣��
	m.at("banan");

	

	m.insert(pair<string, string>("����", "no"));
	m.insert(make_pair("���", "hello"));

	m.erase("�㽶");

	auto it1 = m.find("���");;

	cout << "���ҳɹ�: " << it1->first.c_str() << "  ->>>  " << it1->second.c_str() << endl;
}


/*
Դ��

template<class _T1, class _T2>
struct pair
{
	typedef _T1 first_type;    /// @c first_type is the first bound type
	typedef _T2 second_type;   /// @c second_type is the second bound type

	_T1 first;                //ע�⣬����pulbic
	_T2 second;

	pair() : first(T1()) , second(T2())   //����һ��key��value��Ϊ�յ�pair
	{}

	pair��const T1& a��const T2& b��: first(a)��second��b��//����һ����ֵΪa��
	//ʵֵΪb��pair
	{}
}

template <class Key, class Compare = less<Key>, class Alloc = alloc>
class set {
public:
	// typedefs:

	typedef Key key_type;//��ֵkey
	typedef Key value_type;//ʵֵvalue����ʵ�ײ�������key��value����keyֵ��
	//ֻ��ȡ����ͬ��

	typedef Compare key_compare;//�Ƚ�����Ĭ�ϴ�����less��
	//Ҳ������ʾ�Ĵ�����ָ���º�����

	typedef Compare value_compare;
private:
	typedef rb_tree<key_type, value_type,
	identity<value_type>, key_compare, Alloc> rep_type;
	rep_type t;  // red-black tree representing set
};
*/