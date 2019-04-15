#include<iostream>
#include <queue>
#include<functional>
using namespace std;

//优先队列具有队列的所有特性，包括基本操作，只是在这基础上添加了内部的一个排序，它本质是一个堆实现的
//和队列基本操作相同:

//top 访问队头元素
//empty 队列是否为空
//size 返回队列内元素个数
//push 插入元素到队尾(并排序)
//emplace 原地构造一个元素并插入队列
//pop 弹出队头元素
//swap 交换内容


int main()
{
	//对于基础类型 默认是大顶堆
	priority_queue<int> a;
	//等同于 priority_queue<int, vector<int>, less<int> > a;

	//             这里一定要有空格，不然成了右移运算符↓
	priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆
	priority_queue<string> b;

	for (int i = 0; i < 5; i++)
	{
		a.push(i);
		c.push(i);
	}
	while (!a.empty())
	{
		cout << a.top() << ' ';
		a.pop();
	}
	cout << endl;

	while (!c.empty())
	{
		cout << c.top() << ' ';
		c.pop();
	}
	cout << endl;

	b.push("abc");
	b.push("abcd");
	b.push("cbd");
	while (!b.empty())
	{
		cout << b.top() << ' ';
		b.pop();
	}
	cout << endl;
	return 0;
}
