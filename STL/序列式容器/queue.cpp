#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

//队列  先进先出
//由deque演变而来

//queue 的基本操作有：
//入队，如例：q.push(x); 将x 接到队列的末端。
//出队，如例：q.pop(); 弹出队列的第一个元素，注意，并不会返回被弹出元素的值。
//访问队首元素，如例：q.front()，即最早被压入队列的元素。
//访问队尾元素，如例：q.back()，即最后被压入队列的元素。
//判断队列空，如例：q.empty()，当队列空时，返回true。
//访问队列中的元素个数，如例：q.size()
//没有迭代器


int main()
{
	int e, n, m;
	queue<int> q1;
	for (int i = 0; i<10; i++)
		q1.push(i);
	if (!q1.empty())
		cout << "dui lie  bu kong\n";
	n = q1.size();
	cout << n << endl;
	m = q1.back();
	cout << m << endl;
	for (int j = 0; j<n; j++)
	{
		e = q1.front();
		cout << e << " ";
		q1.pop();
	}
	cout << endl;
	if (q1.empty())
		cout << "dui lie  bu kong\n";
	system("PAUSE");
	return 0;
}