#include<iostream>
#include<vector>
#include<algorithm>

//动态数组
//连续空间

using namespace std;


int main()
{
	//初始化

	vector<int> a(10);  //定义了10个整型元素的向量
	vector<int> b(10, 1); //定义了10个整型元素的向量，且每个元素的初值都为1
	vector<int> c(b);   //用b向量来创建c向量，整体复制性赋值
	vector<int> d(b.begin(), b.begin() + 3); //j将b中的前三个元素赋值给d
	int num[7] = { 1,2,3,4,5,9,8 };
	vector<int> a(num, num + 7); //从数组中获得初值

	//对vector对象的操作
	a.assign(b.begin(), b.begin() + 3); //b为向量，将b的0~2个元素构成的向量赋给a
	a.assign(4, 2); //是a只含4个元素，且每个元素为2
	a.back(); //返回a的最后一个元素
	a.front(); //返回a的第一个元素
	int i = 0;
	a[i]; //返回a的第i个元素，当且仅当a[i]存在2013-12-07
    a.clear(); //清空a中的元素
	a.empty(); //判断a是否为空，空则返回ture,不空则返回false
	a.pop_back(); //删除a向量的最后一个元素
	a.erase(a.begin() + 1, a.begin() + 3); //删除a中第1个（从第0个算起）到第2个元素，也就是说删除的元素从a.begin()+1算起（包括它）一直到a.begin()+3（不包括它）
	a.push_back(5); //在a的最后一个向量后插入一个元素，其值为5
	a.insert(a.begin() + 1, 5); //在a的第1个元素（从第0个算起）的位置插入数值5，如a为1,2,3,4，插入元素后为1,5,2,3,4
    a.insert(a.begin() + 1, 3, 5); //在a的第1个元素（从第0个算起）的位置插入3个数，其值都为5
	a.insert(a.begin() + 1, num+3, num+6); //num为数组，在a的第1个元素（从第0个算起）的位置插入num的第3个元素到第5个元素（不包括b+6），如num为1,2,3,4,5,9,8，插入元素后为1,4,5,9,2,3,4,5,9,8
	a.size(); //返回a中元素的个数；
	a.capacity(); //返回a在内存中总共可以容纳的元素个数
	a.resize(10); //将a的现有元素个数调至10个，多则删，少则补，其值随机
	a.resize(10, 2); //将a的现有元素个数调至10个，多则删，少则补，其值为2
	a.reserve(100); //将a的容量（capacity）扩充至100，也就是说现在测试a.capacity();的时候返回值是100.这种操作只有在需要给a添加大量数据的时候才显得有意义，因为这将避免内存多次容量扩充操作（当a的容量不足时电脑会自动扩容，当然这必然降低性能） 
	a.swap(b); //b为向量，将a中的元素和b中的元素进行整体性交换
	a == b; //b为向量，向量的比较操作还有!=,>=,<=,>,<
	c.begin(); //返回一个迭代器，它指向容器c的第一个元素
	c.end();  // 返回一个迭代器，它指向容器c的最后一个元素的下一个位置
	c.rbegin(); // 返回一个逆序迭代器，它指向容器c的最后一个元素
	c.rend(); // 返回一个逆序迭代器，它指向容器c的第一个元素前面的位置

	//从后面添加元素
	a.push_back(3);

	//顺序遍历
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;
	vector<int>::iterator it;  //正向迭代器
	for (auto it = a.begin(); it != a.end(); it++)
		cout << *it << endl;

	//利用反向迭代器可以反向遍历
	vector<int>::reverse_iterator it;  //反向迭代器
	for (auto it = a.rbegin(); it != a.rend(); it++)
		cout << *it << endl;

	//算法
	sort(a.begin(), a.end()); //对a中的从a.begin()（包括它）到a.end()（不包括它）的元素进行从小到大排列
    sort(a.rbegin(), a.rend()); //从大到小排列
	reverse(a.begin(), a.end()); //对a中的从a.begin()（包括它）到a.end()（不包括它）的元素倒置，但不排列，如a中元素为1,3,2,4,倒置后为4,2,3,1
	copy(a.begin(), a.end(), b.begin() + 1); //把a中的从a.begin()（包括它）到a.end()（不包括它）的元素复制到b中，从b.begin()+1的位置（包括它）开始复制，覆盖掉原有元素
	find(a.begin(), a.end(), 10); //在a中的从a.begin()（包括它）到a.end()（不包括它）的元素中查找10，若存在返回其在向量中的位置

}