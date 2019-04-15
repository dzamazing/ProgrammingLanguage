#include<iostream>
#include<list>
#include<algorithm>

//双向链表
//不连续空间，插入和删除元素永远是常数时间

using namespace std;

void printf(list<int> list)
{
	for (auto it = list.begin(); it != list.end(); it++)
		cout << *it << " ";
	cout << endl;
}
// a predicate implemented as a function:
bool single_digit(const int& value) 
{ 
	return (value < 10); 
}

// a predicate implemented as a class:
struct is_odd {
	//重载操作符 ()
	bool operator() (const int& value) { return (value % 2) == 1; }
};


int main()
{
	int num[] = { 11,5,6,7,8,9 };
	list<int> list2(num, num + 6);

	auto ite = find(list2.begin(), list2.end(), 5); //若find失败，会返回end()迭代器

	//插入和弹出（双向均可）
	list2.push_front(1);  //从前面插入元素
	list2.push_back(3);   //从后面插入元素
	list2.pop_front();
	list2.pop_back();

	//获取元素
	list2.front();
	list2.back();

	list<int> list3(3, 1);
	list2.splice(ite, list3); //将list3拼接到ite所指的位置之前
	printf(list2);
	list2.reverse();  //将list反转
	printf(list2);
	list2.sort();     //list只能使用自带的sort(),不能用STL的sort()方法,因为sort需要迭代器是随机访问迭代器
	printf(list2);
	list2.unique();   //剔除相邻元素间的重复元素
	printf(list2);  
	list2.remove(5);  //删除list中特定的值
	printf(list2);

	//按条件删除
	list2.remove_if(single_digit);           // 移除小于10的元素
	list2.remove_if(is_odd());               // 移除奇数

	//合并有序的list
	list<int> first, second;

	first.push_back(3);
	first.push_back(2);
	first.push_back(9);
	
	second.push_back(7);
	second.push_back(1);
	second.push_back(4);
	
    first.sort();
	second.sort();
	
	first.merge(second);
	printf(first);

	first.swap(second);  //交换两个list的内容
	first.resize(8);     //调整list大小
	first.clear();       //清空

	//给动态数组分配空间
	list<int> mylist;
	int * p;
	
    // allocate an array of 5 elements using mylist's allocator:
	p = mylist.get_allocator().allocate(5); //get_allocator  //返回一个跟该list有关的分配器对象
}