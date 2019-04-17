#include<iostream>
#include<vector>

using namespace std;

//计数排序的基本思想为一组数在排序之前先统计这组数中其他数小于这个数的个数，则可以确定这个数的位置。
//例如要排序的数为 7 4 2 1 5 3 1 5；则比7小的有7个数，所有7应该在排序好的数列的第八位，同理3在第四位，对于重复的数字，1在1位和2位（暂且认为第一个1比第二个1小），5和1一样位于6位和7位。

//计数排序是稳定的

//计数排序有如下四个步骤。
//1 首先会对每个输入进行频率统计，得到元素的频率表；
//2 然后将频率表转换为该元素的开始索引；
//3 根据各个元素的开始索引，将相同元素分类到临时数组中。
//4 最后将临时数组中的元素写回到原数组中。
//参考博客：https://www.cnblogs.com/sun-haiyu/p/7859252.html

int  findMax(int *num, int size)
{
	int max = num[0];
	for (int i = 1; i < size; i++)
		if (num[i] > max)
			max = num[i];

	return max;
}

int findMin(int* num, int size)
{
	int min = num[0];
	for (int i = 0; i < size; i++)
		if (num[i] < min)
			min = num[i];

	return min;
}

void CountSort(int* num, int size)
{
	int max, min;
	max = findMax(num, size);
	min = findMin(num, size);
	int count_size = max - min + 1;//最大最小元素之间范围[min, max]的长度
	vector<int> count(count_size+1,0); //在需要的数组长度上额外加1，因为在统计每个元素的频率时count[]将每个元素减去最小值再加1作为索引，因此count[0]永远也不会被赋值，这保证count[0]始终为0

	//计算频率，在需要的数组长度上额外加1
	for (int i=0; i<size; i++)
		count[num[i] - min + 1]++;  // 使用加1后的索引，有重复的该位置就自增

	//频率转元素的开始索引
	for (int i = 0; i < count_size; i++)
		count[i + 1] += count[i];

	//元素按开始索引分类，用到一个和待排数组一样大临时数组存放数据
	vector<int> aux(size, 0);
	for (int i = 0; i < size; i++)
		aux[count[num[i]-min]++] =  num[i]; // 填充一个数据后，自增，以便相同的数据可以填到下一个空位

	//数据回写
	for (int i = 0; i < size; i++)
		num[i] = aux[i];
}

int main()
{
	int num[] = { 9, 7, 6, 3, 9, 2, 7, 3, 2, 8 };
	int size = sizeof(num) / sizeof(int);
	CountSort(num, size);

	for(int i = 0; i < size; i++)
		cout << num[i] << " ";
	cout << endl;

	return 0;
}