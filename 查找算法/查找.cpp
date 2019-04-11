#include<iostream>

//注：本文件下的所有查找函数，基本都未在函数开头进行参数异常判断，实际中应添加进去

using namespace std;

//顺序查找
//思想：顺序查找也称为线形查找，属于无序查找算法。
      //从数据结构线形表的一端开始，顺序扫描，依次将扫描到的结点关键字与给定值k相比较，若相等则表示查找成功；
      //若扫描结束仍没有找到关键字等于k的结点，表示查找失败
//属性：时间复杂度：O(n) 空间复杂度：1，平均查找长度（ASL）：（n+1)/2
int SequenceSearch(int a[], int n, int value)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (a[i] == value)
			return i;
	}
	return -1;
}

//二分查找
//思想：也称为是折半查找，属于有序查找算法。
      //用给定值k先与中间结点的关键字比较，中间结点把线形表分成两个子表，
      //若相等则查找成功；
      //若不相等，再根据k与该中间结点关键字的比较结果确定下一步查找哪个子表，
      //这样递归进行，直到查找到或查找结束发现表中没有这样的结点。
      //折半查找的前提条件是需要有序表顺序存储
//属性：最坏情况下，关键词比较次数为log2(n+1),且期望时间复杂度为O(log2n)
int BinarySearch1(int a[], int n, int value)  //非递归版本
{
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == value)
			return mid;
		if (a[mid] > value)
			high = mid - 1;
		if (a[mid] < value)
			low = mid + 1;
	}
	return -1;
}

int BinarySearch2(int a[], int low, int high, int value)  //递归版本
{
	int mid = low + (high - low) / 2;
	if (a[mid] == value)
		return mid;
	if (a[mid] > value)
		return BinarySearch2(a, low, mid - 1, value);
	if (a[mid] < value)
		return BinarySearch2(a, mid + 1, high, value);
}

//二叉排序树查找
//思想：二叉查找树是先对待查找的数据进行生成树，确保树的左分支的值小于右分支的值，
      //然后在就行和每个节点的父节点比较大小，查找最适合的范围。 
      //这个算法的查找效率很高，但是如果使用这种查找方法要首先创建树。
//条件：先创建二叉排序树：
      //1. 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
      //2. 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
      //3. 它的左、右子树也分别为二叉排序树。
//原理：在二叉查找树b中查找x的过程为：
      //1. 若b是空树，则搜索失败，否则：
      //2. 若x等于b的根节点的数据域之值，则查找成功；否则：
      //3. 若x小于b的根节点的数据域之值，则搜索左子树；否则：
      //4. 查找右子树。
//属性：它和二分查找一样，插入和查找的时间复杂度均为O(log2n)，
      //但是在最坏的情况下仍然会有O(n)的时间复杂度。

//哈希表查找
//原理：根据键值方式（Key Value）进行查找，通过散列函数，定位数据元素
//属性：几乎是O(1),取决于产生冲突的多少，解决冲突，用比较函数解决
//其基本原理是：使用一个下标范围比较大的数组来存储元素。
//可以设计一个函数（哈希函数，也叫做散列函数），使得每个元素的关键字都与
//一个函数值（即数组下标，hash值）相对应，于是用这个数组单元来存储这个元素；
//也可以简单的理解为，按照关键字为每一个元素“分类”，然后将这个元素存储
//在相应“类”所对应的地方，称为桶。

//但是，不能够保证每个元素的关键字与函数值是一一对应的，
//因此极有可能出现对于不同的元素，却计算出了相同的函数值，这样就产生了“冲突”，
//换句话说，就是把不同的元素分在了相同的“类”之中。 
//总的来说，“直接定址”与“解决冲突”是哈希表的两大特点。


int main()
{
	//测试数据
	int TestData[] = { 10,20,30,40,50 };
	int count = sizeof(TestData) / sizeof(int);

	int index;

	////测试顺序查找
	//index = SequenceSearch(TestData, count, 30);

	////二分查找实现一测试
	//index = BinarySearch1(TestData, count, 30);
	//二分查找实现二测试
	index = BinarySearch2(TestData,0,count-1, 30);

	//查找结果
	if (index >= 0 && index < count) 
	{
		cout << "search success! the index of key is: " << index << endl;
	}
	else {
		cout << "search fail! " << endl;
	}

	//防闪退
	int temp;
	cin >> temp;

	return 0;
}