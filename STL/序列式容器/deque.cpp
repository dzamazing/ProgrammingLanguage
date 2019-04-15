#include<iostream>
#include<algorithm>
#include<deque>

using namespace std;

//双端队列
//底层实现：循环队列
//与vector的区别： deque允许于常数时间内对头端进行元素的插入和移除操作；
                  //deque没有容量的概念，它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来
//对deque进行排序操作，为提高效率可将deque先完整复制一个到vector身上，将vector排序后再复制会deque
//deque比vector复杂的多，应尽量用vector


int main()
{
	//接口
	deque<int> que;//定义了一个整型的双端队列;
	//que.assign(beg, end) 将[beg; end)区间中的数据赋值给que。
	//que.assign(n, elem) 将n个elem的拷贝赋值给que。
	//que.at(idx) 传回索引idx所指的数据，如果idx越界，抛出out_of_range。
	//que.back() 返回容器que的最后一个元素的引用。如果que为空，则该操作未定义。
	//que.begin() 传回迭代器中的第一个数据地址。
	//que.clear() 移除容器中所有数据。
	//que.empty() 判断容器是否为空。
	//que.end() 返回一个迭代器，它指向容器que的最后一个元素的下一位置。
	//que.erase(pos) 删除pos位置的数据，传回下一个数据的位置。
	//que.erase(beg, end) 删除[beg, end)区间的数据，传回下一个数据的位置。
	//que.front() 返回容器que的第一个元素的引用。如果que为空，则该操作为空。
	//que.insert(pos, elem) 在pos位置插入一个elem拷贝，传回新数据位置
	//que.insert(pos, n, elem) 在pos（迭代器）位置插入>n个elem数据。无返回值

	//que.insert(pos, beg, end) 在pos位置插入在[beg, end)区间的数据。无返回值
	//que.max_size() 返回容器que可容纳的最多元素个数。
	//que.pop_back() 删除最后一个数据。
	//que.pop_front() 删除头部数据。
	//que.push_back(elem) 在尾部加入一个数据。
	//que.push_front(elem) 在头部插入一个数据。
	//que.rbegin() 返回一个逆序迭代器，它指向容器que的最后一个元素。
	//que.rend() 返回一个逆序迭代器，它指向容器que的第一个元素的前一个位置。
	//que.resize(num) 重新指定队列的长度。
	//que.size() 返回容器中实际数据的个数。
	//que.swap(que2) 交换容器que和que2中的所有元素。
	//swap(que1, que2) 交换容器que1和que2中的所有元素。

	deque <int> que;
	que.push_back(1);
	que.push_back(2);
	que.push_back(3);
	cout << "基本操作：" << endl;
	cout << "队列遍历：" << endl;
	deque<int>::iterator ator;
	for (ator = que.begin(); ator != que.end(); ator++)
		cout << *ator << endl;
	int a;
	cout << "队首插入元素：";
	cin >> a;
	que.push_front(a);
	cout << "队列遍历：" << endl;
	for (ator = que.begin(); ator != que.end(); ator++)
		cout << *ator << endl;
	cout << "队尾插入元素：";
	cin >> a;
	que.push_back(a);
	cout << "队列遍历：" << endl;
	for (ator = que.begin(); ator != que.end(); ator++)
		cout << *ator << endl;
	cout << "中间插入元素：";
	cin >> a;
	que.insert(que.begin() + 1/*迭代器位置，根据要求更改*/, 1, a);//第一个位置为迭代器位置，该程序插入的为在首位置之后、第一个元素之前插入。元素标号从第0个开始。 
	cout << "队列遍历：" << endl;
	for (ator = que.begin(); ator != que.end(); ator++)
		cout << *ator << endl;
	cout << "删除队首元素：" << endl;
	que.pop_front();
	cout << "队列遍历：" << endl;
	for (ator = que.begin(); ator != que.end(); ator++)
		cout << *ator << endl;
	cout << "删除队尾元素：" << endl;
	que.pop_back();
	cout << "队列遍历：" << endl;
	for (ator = que.begin(); ator != que.end(); ator++)
		cout << *ator << endl;
	cout << "队列元素个数：" << que.size() << endl;
	cout << "队列清0:" << endl;
	que.clear();
	cout << "队列元素个数：" << que.size() << endl;
	return 0;
}