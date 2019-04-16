#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//£¨1£©
void deleteDupValue(std::vector<int> &arr)
{
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	
	return;
}

//(2£©
int fibonacci(const int n)
{
	int result[2] = {0,1};
	if(n<2)
	    return result[n];

	int fibNMinusOne = 1;
	int fibNMinusTwo = 0;
	int fibN = 0;

	for(int i = 2;i<=n;++i)
	{
	    fibN = fibNMinusOne + fibNMinusTwo;

	    fibNMinusTwo = fibNMinusOne;
	    fibNMinusOne = fibN;

	}

	return fibN;
}

//(3)
typedef struct Node {
	int val;
    Node* left ;
	Node* right;
	Node(int value):val(value),left(nullptr),right(nullptr) {}
}TreeNode ;
void insert(Node* root, int val) 
{
	TreeNode *node = new TreeNode(val);
	if (root == nullptr)
	{		
		root = node;
	}

	TreeNode *tmp = root;
	TreeNode *p;

	while (tmp)
	{
		p = tmp;

		if (node->val > tmp->val)
			tmp = tmp->right;
		else if (node->val < tmp->val)
			tmp = tmp->left;

	}

	if (node->val > p->val)
		p->right = node;
	if (node->val < p->val)
		p->left = node;

}

//(4)
void findPath(const vector<vector<char>>& maze, const int i, const int j)
{
	int row = maze[1].size();  //ÐÐ
	int column = maze.size();  //ÁÐ

}