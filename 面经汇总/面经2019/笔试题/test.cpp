#include "stdafx.h"
#include "iostream"
using namespace std;

const int R = 5;
const int C = 5;

int maps[R][C];
int visited[R][C];

typedef struct node
{
	int x;
	int y;
	int f;

	node(int x = -1, int y = -1, int f = -1)
	{
		this->x = x;
		this->y = x;
		this->f = f;
	}
}Node;

typedef struct myqueue
{
	Node list[30];
	int head;
	int tail;

	myqueue()
	{
		head = 0;
		tail = 0;

	}
	void push(Node & n1)//节点n1入队
	{
		list[tail] = n1;
		tail++;
	}

	Node getHead()//返回队列的头结点
	{
		return list[head];
	}

	void pop()//队首元素出队
	{
		head++;
	}
	bool isEmpty()//队列是否为空，队列为空返回true，否则返回false
	{
		if (head == tail)
			return true;
		else
			return false;
	}
}Myqueue;

bool isValied(int x, int y)//判断以x,y为横纵坐标的访问是否合法
{
	if (x >= 0 && y >= 0 && x <= 4 && y <= 4 && visited[x][y] == 0 && maps[x][y] == 0)
		return true;
	else
		return false;
}

bool equal(Node n1, Node n2)//判断两个节点是否相等。
{
	if (n1.x == n2.x && n1.y == n2.y)
		return true;
	else
		return false;
}

int BFS(Myqueue & q, Node start, Node end)//对maps地图以start为起始点，end为终止节点进行广度优先搜索，
{                                         //函数返回最后一个end节点在队列数组list中的下标。
	q.push(start);
	while (!q.isEmpty())
	{

		Node t = q.getHead();//从队头取元素
							 //cout<<t.x<<" "<<t.y<<endl;// 4 4
							 // Node left(t.x, t.y-1, q.head);//??
		Node left;
		left.x = t.x;
		left.y = t.y - 1;
		left.f = q.head;//队头元素为其左节点的父节点，此时q.head为队头元素在list数组中的下标。

		Node right;
		right.x = t.x;
		right.y = t.y + 1;
		right.f = q.head;

		Node up;
		up.x = t.x - 1;
		up.y = t.y;
		up.f = q.head;

		Node down;
		down.x = t.x + 1;
		down.y = t.y;
		down.f = q.head;

		if (isValied(left.x, left.y))//访问
		{
			visited[left.x][left.y] = 1;
			q.push(left);
			if (equal(left, end))
				return q.tail - 1;
		}
		if (isValied(up.x, up.y))
		{
			visited[up.x][up.y] = 1;
			q.push(up);
			if (equal(up, end))
				return q.tail - 1;
		}
		if (isValied(right.x, right.y))
		{
			visited[right.x][right.y] = 1;
			q.push(right);
			if (equal(right, end))
				return q.tail - 1;
		}
		if (isValied(down.x, down.y))
		{
			visited[down.x][down.y] = 1;
			q.push(down);
			if (equal(down, end))
				return q.tail - 1;
		}
		q.pop();
	}
	return -1;
}

int main()
{
	for (int i = 0; i<R; i++)
		for (int j = 0; j<C; j++)
		{
			cin >> maps[i][j];
			visited[i][j] = maps[i][j];
		}
	Myqueue q;
	Node start(4, 4, -1);//为了输出路径方便，将终点和起点的位置对换，这样输出路线时就像链表一样操作
	Node end(0, 0, -1);

	int index = BFS(q, start, end);

	while (q.list[index].f != -1)//等于-1时说明找到了start节点，也就是到达了(4, 4)点，此时还没输出该点
	{
		cout << "(" << q.list[index].x << ", " << q.list[index].y << ")" << endl;
		index = q.list[index].f;
	}
	cout << "(" << q.list[index].x << ", " << q.list[index].y << ")";
}
