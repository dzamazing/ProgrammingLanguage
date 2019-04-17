#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//桶排序的思想：
//1 根据输入建立适当个数的桶，每个桶可以存放某个范围内的元素；
//2 将落在特定范围内的所有元素放入对应的桶中；
//3 对每个非空的桶中元素进行排序，可以选择通用的排序方法，比如插入、快排；
//4 按照划分的范围顺序，将桶中的元素依次取出。排序完成。

//平均时间复杂度为O(n)
//桶排序可以是稳定的。这取决于我们对每个桶中的元素采取何种排序方法，比如桶内元素的排序使用快速排序，那么桶排序就是不稳定的；如果使用的是插入排序，桶排序就是稳定的。
//要注意：如何选择桶的个数，以及使用哪个映射函数将元素转换成桶的索引都是不一定的。

//本程序说明：
//桶的数量为数组长度
//映射函数使用bucketIndex = (value * arr.length) / (maxValue + 1) ,加1是为了保证最大元素可以存到数组最后一个位置

int findMax(int *num, int size)
{
	int max = num[0];
	for (int i = 0; i < size; i++)
		if (num[i] > max)
			max = num[i];
	return max;
}

//映射函数
int toBucketIndex(int value, int maxValue, int N)
{
	return (value*N) / (maxValue + 1); //加1是为了保证最大元素可以存到数组最后一个位置
}

void BucketSort(int* num, int size)
{
	int N = size; 
	vector<vector<int>> buckets(N);

	// 根据每个元素的值，分配到对应范围的桶中
	int max = findMax(num, size);
	for (int i = 0; i < size; i++)
	{
		int index = toBucketIndex(num[i], max, N);
		buckets[index].push_back(num[i]);
	}

	// 对每个非空的桶排序，排序后顺便存入临时的temp中
	vector<int> temp;
	for (int i = 0; i < N; i++)
	{
		if (buckets[i].size() != 0)
		{
			sort(buckets[i].begin(), buckets[i].end());

			for (int j = 0; j < buckets[i].size(); j++)
				temp.push_back(buckets[i][j]);
		}
	}

	// 将temp中的数据写入原数组
	for (int i = 0; i < temp.size(); i++)
		num[i] = temp[i];
}

int main()
{
	int num[] = { 44, 67, 32, 21, 9, 98, 44, 111, 99, 6 };
	int size = sizeof(num) / sizeof(int);
	BucketSort(num, size);
	for (int i = 0; i < size; i++)
		cout << num[i] << " ";
	cout << endl;

	return 0;
}