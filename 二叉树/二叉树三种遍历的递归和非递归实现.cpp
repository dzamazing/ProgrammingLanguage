#include<iostream>
#include<stack>
#include<vector>

using namespace std;

//树节点的结构
typedef struct node{
	char  data;
	struct node *lchild;
	struct node *rchild;
	node(char c) :data(c), lchild(nullptr), rchild(nullptr) {};  //构造函数
} BinTreeNode, *BinTree;  //*BinTree的意思是给 struct node*起了个别名，叫BinTree，故BinTree为指向节点的指针。

//按照先序遍历创建一棵二叉树
void createBinTree(BinTree &T) //&的意思是传进来节点指针的引用，括号内等价于 BinTreeNode* &T,目的是让传递进来的指针发生改变
{
	//注：创建二叉树时要保证最终所有的叶子节点都为 '#',才能创建完成，建议先画出树形图再输入节点值
	//例：ab##c##
	
	char c;
	cin >> c;
	if ('#' == c)  //当遇到#号时，令树的根节点为nullptr,从而结束该分支的递归
	{

		T = nullptr;
		return;
	}

	T = new BinTreeNode(c);
	createBinTree(T->lchild);
	createBinTree(T->rchild);

}

/*******  二叉树的三种递归遍历 *******/

//先序递归遍历
//打印顺序： 根节点-左子节点-右子节点
void preTraverse(BinTree T) 
{
	if (T != nullptr)
	{
		cout << T->data << " ";
		preTraverse(T->lchild);
		preTraverse(T->rchild);
	}
}

//中序递归遍历
//打印顺序： 左子节点-根节点-右子节点
void midTraverse(BinTree T)
{
	if (T != nullptr)
	{
		midTraverse(T->lchild);
		cout << T->data << " ";
		midTraverse(T->rchild);
	}
}

//后序递归遍历
//打印顺序：左子节点-右子节点-根节点
void postTraverse(BinTree T)
{
	if (T != nullptr)
	{
		postTraverse(T->lchild);
		postTraverse(T->rchild);
		cout << T->data << " ";
	}
}

/*********   二叉树的三种非递归遍历方式  ************/
//对于树的非递归遍历方式，需要采用栈去模拟实现

//非递归先序遍历
//需要一个辅助节点指针P
//处理过程：1.若根节点非空，则将根节点入栈
          //2.判断栈是否为空，若栈非空，则将P指针指向栈顶节点，打印节点数据并执行出栈操作，
                                        //同时先后判断：若P节点的右子节点非空，则该节点入栈
		                                              //若P节点的左子节点非空，则该节点入栈 
                             //若栈为空，遍历结束
          //重复第2步操作
void preTraverse2(BinTree T)
{
	if (T == nullptr)
		return;

	stack<BinTree> s;
	s.push(T);
	BinTree p = nullptr;
	while (!s.empty())
	{
		p = s.top();
		cout << p->data << " ";
		s.pop();
		if (p->rchild != nullptr)
			s.push(p->rchild);
		if (p->lchild != nullptr)
			s.push(p->lchild);
	}
}

//非递归中序遍历
//处理过程：对于任一节点，
          //1.若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P,然后对当前节点P再进行相同的处理
          //2.若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶节点，然后将当前的P置为栈顶节点的右孩子
          //3.直到P为NULL并且栈为空则遍历结束
void midTraverse2(BinTree T)
{
	if (T == nullptr)
		return;

	stack<BinTree> s;
	BinTree p = T;
	while (p != nullptr || !s.empty())
	{
		if (p != nullptr)
		{
			s.push(p);
			p = p->lchild;
		}
		else
		{
			p = s.top();
			s.pop();
			cout << p->data << " ";
			p = p->rchild;
		}
	}
}

//非递归后续遍历方法一
//思路：需要借助一个迭代器和辅助节点指针P，因为后序遍历的顺序是左右根，所以根节点一定是在最后面，所以最开始将根节点放入栈中
      //然后开始一个循环，循环的条件为栈非空。每次取出栈顶元素，并将P指针指向栈顶元素，同时将该元素插入到迭代器的开始位置，
      //然后”依次“判断弹出的栈顶元素是否有左子节点和右子节点（注意顺序很重要，因为栈是后进先出，所以要先判断左，再判断右）
      //若左子节点或右子节点非空，则将该节点推入栈中，然后重新开始下一轮循环
      //最后按顺序打印出迭代器中的元素即可（因为每次都是插入迭代器的最前面，所以顺序刚好是后序遍历顺序）
void postTraverse2_1(BinTree T)
{
	if (T == nullptr)
		return;

	stack<BinTree> s;
	vector<char> rs;
	s.push(T);
	BinTree p = nullptr;
	while (!s.empty())
	{
		p = s.top();
		s.pop();
		rs.insert(rs.begin(), p->data);  //将当前节点的数据插入到迭代器的最前面
		if (p->lchild)          //因为栈的后进先出原则，所以应该先插左节点后插右节点
			s.push(p->lchild);  //这样的话就会ci
		if (p->rchild)
			s.push(p->rchild);
	}
	for (int i = 0; i < rs.size(); i++)
		cout << rs[i] << " ";
}
//非递归后续遍历方法二
//思路：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
      //如果P不存在左孩子和右孩子，则可以直接访问它；
      //或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
      //若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，
      //左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
void postTraverse2_2(BinTree T)
{
	stack<BinTree> s;
	BinTree cur = nullptr;   //当前节点
 	BinTree pre = nullptr;   //前一次访问的节点
	s.push(T);
	while (!s.empty())
	{
		cur = s.top();
		if ((cur->lchild == nullptr &&cur->rchild == nullptr) ||
			(pre != nullptr && (pre == cur->lchild || pre == cur->rchild))) //因为只要前一个节点是这个节点的子节点，说明这个节点是一个根节点了，子节点已经提前弹出，此时这个节点也该弹出了
		{                                                                   //判断是左子节点或是右子节点主要是考虑可能只有一个孩子节点的情况而已，但只要前一个是该节点的子节点，此节点必能弹出
			cout << cur->data << " ";   //如果当前结点没有孩子结点或者孩子节点都已被访问过 
			s.pop();
			pre = cur;
		}
		else
		{
			if (cur->rchild != nullptr)
				s.push(cur->rchild);
			if (cur->lchild != nullptr)
				s.push(cur->lchild);
		}
	}
}


int main()
{
	//测试用例：ab#c##de##f## (要保证算上#后是一棵完全二叉树)
	          //先序遍历结果：abcdef
	          //中序遍历结果：bcaedf
	          //后续遍历结果：cbefda
	BinTree T;
	cout << "开始创建二叉树，请输入树节点：";
	createBinTree(T);
	cout << "二叉树创建完成！" << endl;

	cout << "递归先序遍历二叉树：" << endl;
	preTraverse(T);
	cout << endl;
	cout << "非递归先序遍历二叉树：" << endl;
	preTraverse2(T);
	cout << endl;
	cout << "递归中序遍历二叉树：" << endl;
	midTraverse(T);
	cout << endl;
	cout << "非递归中序遍历二叉树：" << endl;
	midTraverse2(T);
	cout << endl;
	cout << "递归后序遍历二叉树：" << endl;
	postTraverse(T);
	cout << endl;
	cout << "非递归后序方法一遍历二叉树：" << endl;
	postTraverse2_1(T);
	cout << endl;
	cout << "非递归后序方法二遍历二叉树：" << endl;
	postTraverse2_2(T);
	cout << endl;

	////防止程序闪退
	//int temp;
	//cin >> temp;
	
	//VS2017解决程序运行后闪退问题：
	//修改项目配置，右键点击项目，在右键菜单中选择属性，
	//然后在弹出的对话框左侧列表中选择 “配置属性--->链接器--->系统”，
	//然后在右侧的列表中，在第一项 “子系统”的值中 选择 “控制台(/ SUBSUSTEM:CONSOLE)”

	return 0;
}


