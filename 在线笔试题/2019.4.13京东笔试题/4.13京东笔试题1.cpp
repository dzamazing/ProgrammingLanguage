//京东笔试题1：逃生
//思路： 对根节点的子树遍历，求节点数最多的子树。就是逃生的最少时间

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//树节点结构体
struct Node 
{
	int value;            //本节点的座位号
	vector<int> childs;   //与本节点直接相连的节点

	Node(int x) //构造函数
	{ 
		this->value = x;

	}  
};

//求unBL 边忽略后，node[i]节点连通的节点数
int getNodeEdge(vector<Node*> nodes, int i, int unBL)
{
	int count = 0;
	vector<int> integers = nodes[i]->childs;
	count += integers.size() - 1;
	for (auto item : integers)
	{
		if (item == unBL)
			continue;
		count += getNodeEdge(nodes, item, nodes[i]->value);
	}

	return count;
}

int main()
{
	int n;
	cin >> n;    //树节点数

	vector<Node*> nodes;
	for (int i = 0; i <= n; i++)
	{
		Node *node = new Node(i);
		nodes.push_back(node);
	}
	int a, b;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b;
		nodes[a]->childs.push_back(b);
		nodes[b]->childs.push_back(a);
	}

	int max_nodes = 0;
	vector<int> intergers = nodes[1]->childs;
	for (auto item : intergers)
	{
		int count = getNodeEdge(nodes, item, 1);
		max_nodes = max(count, max_nodes);
	}

	int res = max_nodes + 1;
	cout << "res = " << res << endl;

	return 0;
}