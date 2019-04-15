#include<iostream>
#include<string>
#include<map>
#include<hash_map>
#include<unordered_map>

using namespace std;

//映射表  key-value
//底层数据结构：红黑树
//内部无重复key，根据key自动排序

//map的基本操作函数：
//C++ maps是一种关联式容器，包含“关键字 / 值”对

//begin()         返回指向map头部的迭代器
//clear(）        删除所有元素
//count()         返回指定元素出现的次数
//empty()         如果map为空则返回true
//end()           返回指向map末尾的迭代器
//equal_range()   返回特殊条目的迭代器对
//erase()         删除一个元素
//find()          查找一个元素
//get_allocator() 返回map的配置器
//insert()        插入元素
//key_comp()      返回比较元素key的函数
//lower_bound()   返回键值 >= 给定元素的第一个位置
//max_size()      返回可以容纳的最大元素个数
//rbegin()        返回一个指向map尾部的逆向迭代器
//rend()          返回一个指向map头部的逆向迭代器
//size()          返回map中元素的个数
//swap()           交换两个map
//upper_bound()    返回键值>给定元素的第一个位置
//value_comp()     返回比较元素value的函数

int main()
{
	//三种插入方式

	// 定义一个map对象
	map<int, string> mapStudent;

	// 第一种 用insert函數插入pair
	mapStudent.insert(pair<int, string>(000, "student_zero"));

	// 第二种 用insert函数插入value_type数据
	mapStudent.insert(map<int, string>::value_type(001, "student_one"));

	// 第三种 用"array"方式插入
	mapStudent[123] = "student_first";

}

//相关容器

//multimap: 允许有重复key值
//hash_map: 底层结构为哈希表
//hash_multimap:底层结构为哈希表,允许有重复key值
//unordered_map: 底层结构为哈希表，不排序，不允许有key值