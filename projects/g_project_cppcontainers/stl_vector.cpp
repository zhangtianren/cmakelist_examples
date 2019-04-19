#include "stl_headers.h"
#include<iostream>
using namespace std;

/*
向量
https://www.cnblogs.com/sooner/p/3273395.html
vector 类是以容器（Container） 模式为基准设计的，也就是说，基本上它有 begin()，end()，size()，max_size()，empty() 以及 swap() 这几个方法。
1 vector维护的是一个连续线性空间，所以vector支持随机存取
2 vector动态增加大小时，并不是在原空间之后持续新空间（因为无法保证原空间之后尚有可供配置的空间），
而是以原大小的两倍另外配置一块较大的空间，然后将原内容拷贝过来，然后才开始在原内容之后构造新元素，并释放原空间。
因此，对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器就都失效了
3 insert 到指定的index 
	(1) 空间足够: 从index部分开始，整体向后挪动一个位置
	(2) 空间不足: size * 2 (java sdk里面是 *3/2)作为新的的size ,新申请一块内存区， 把老的数据分两段拷贝过来， 老的丢弃
4 时刻记住迭代器失效的问题

· 访问元素的方法
· vec[i] - 访问索引值为 i 的元素引用。 (索引值从零起算，故第一个元素是vec[0]。)
· vec.at(i) - 访问索引值为 i 的元素的引用，以 at() 访问会做数组边界检查，如果访问越界将会抛出一个例外，这是与operator[]的唯一差异。
· vec.front() - 回传 vector 第一个元素的引用。

· vec.back() - 回传 vector 最尾元素的引用。
· 新增或移除元素的方法
· vec.push_back() - 新增元素至 vector 的尾端，必要时会进行内存配置。
· vec.pop_back() - 删除 vector 最尾端的元素。
· vec.insert() - 插入一个或多个元素至 vector 内的任意位置。
· vec.erase() - 删除 vector 中一个或多个元素。
· vec.clear() - 清空所有元素。
关于移动构造和对push_back的效率优化
1. push_back 可以接收左值也可以接受右值，接收左值时使用拷贝构造，接收右值时使用移动构造
2. emplace_back 接收右值时调用类的移动构造
3. emplace_back 接收左值时，实际上的执行效果是先对传入的参数进行拷贝构造，然后使用拷贝构造后的副本，也就是说，emplace_back在接收一个左值的时候其效果和push_back一致！所以在使用emplace_back 时需要确保传入的参数是一个右值引用，如果不是，请使用std::move()进行转换
4. emplace_back 接收多个参数时，可以调用匹配的构造函数实现在容器内的原地构造


· 获取长度/容量
· vec.size() - 获取 vector 目前持有的元素个数。
· vec.empty() - 如果 vector 内部为空，则传回 true 值。
· vec.capacity() - 获取 vector 目前可容纳的最大元素个数。这个方法与内存的配置有关，它通常只会增加，不会因为元素被删减而随之减少。

· 重新配置／重置长度
· vec.reserve() - 如有必要，可改变 vector 的容量大小（配置更多的内存）。在众多的 STL 实做，容量只能增加，不可以减少。
· vec.resize() - 改变 vector 目前持有的元素个数。

· 迭代 (Iterator)
· vec.begin() - 回传一个Iterator，它指向 vector 第一个元素。
· vec.end() - 回传一个Iterator，它指向 vector 最尾端元素的下一个位置（请注意：它不是最末元素）。
· vec.rbegin() - 回传一个反向Iterator，它指向 vector 最尾端元素的。
· vec.rend() - 回传一个Iterator，它指向 vector 的第一个元素。
*/
#include <vector>

//遍历vector
void print_vector(vector<int> vec)
{
	//方法一
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	//方法二
	vector<int>::iterator ite = vec.begin();
	while (ite != vec.end())
	{
		cout << *ite << " ";
		ite++;
	}
	cout << endl;
}

void test_vector(void)
{
	//对象初始化
	vector<int> vec;
	vector<int> vec_0(5);//定义长度，初识值为0
	vector<int> vec_3(5, 3);//定义长度，初识值为3

							//遍历vector容器
	print_vector(vec_0);

	//vector推入元素
	vec.push_back(1);

	//第一个元素之前插入5个值为3的元素
	vec.insert(vec.begin(), 5, 3);

	//最后一个元素之后插入5个值为3的元素
	vec.insert(vec.end(), 5, 3);
	print_vector(vec);

	//删除最后一个元素
	vec.pop_back();

	//删除区间的元素
	vec.erase(vec.begin() + 2, vec.end());

	//清空vector
	vec.clear();

	//判断是否为空
	bool empty_result = vec.empty();
	cout << empty_result << endl;
}


/*
源码实现, 动态数组
https://www.cnblogs.com/sooner/p/3273395.html
*/