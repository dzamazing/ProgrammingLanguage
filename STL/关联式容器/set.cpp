#include<iostream>
#include<set>
#include<hash_set>
#include<unordered_set>

using namespace std;

//集合
//底层数据结构：红黑树
//内部无重复元素，自动排序

//常用操作
//begin(), 返回set容器的第一个元素
//end(), 返回set容器的最后一个元素
//clear(), 删除set容器中的所有的元素
//empty(), 判断set容器是否为空
//max_size(), 返回set容器可能包含的元素最大个数
//size(), 返回当前set容器中的元素个数
//rbegin　　　　, 返回的值和end()相同
//rend(), 返回的值和rbegin()相同
//count() 用来查找set中某个某个键值出现的次数。这个函数在set并不是很实用，因为一个键值在set只可能出现0或1次，这样就变成了判断某一键值是否在set出现过了。
//equal_range() ，返回一对定位器，分别表示第一个大于或等于给定关键值的元素和 第一个大于给定关键值的元素，这个返回值是一个pair类型，如果这一对定位器中哪个返回失败，就会等于end()的值。
//erase(iterator), 删除定位器iterator指向的值
//erase(first, second), 删除定位器first和second之间的值
//erase(key_value), 删除键值key_value的值
//find()  ，返回给定值值得定位器，如果没找到则返回end()。
//insert(key_value); 将key_value插入到set中 ，返回值是pair<set<int>::iterator, bool>，bool标志着插入是否成功，而iterator代表插入的位置，若key_value已经在set中，则iterator表示的key_value在set中的位置。
//inset(first, second); 将定位器first到second之间的元素插入到set中，返回值是void.
//lower_bound(key_value) ，返回第一个大于等于key_value的定位器
//upper_bound(key_value)，返回最后一个大于key_value的定位器


//相关容器

//multiset: 允许有重复元素
//hash_set: 底层结构为哈希表
//hash_multiset:底层结构为哈希表,允许有重复元素
//unordered_set: 底层结构为哈希表，不排序，不允许有重复元素