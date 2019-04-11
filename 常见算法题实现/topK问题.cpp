//在海量数据中找出前最小的5个元素和最大的5个元素

#include<iostream>
#include<queue>
#include<iterator>
#include<functional>

using namespace std;

//生成n个随机数
vector<int> produceNumbers(int n)
{
	vector<int> data;

	int temp;
	for (int i = 0; i < n; i++)
	{
		temp = rand() % INT_MAX;
		cout << temp << " ";
		data.push_back(temp);
	}
	cout << endl;

	return data;
}
//打印vector
void print_vector(vector<int> data)
{
	for (int i = 0; i < data.size(); i++)
		cout << data[i] << " ";
	cout << endl;
}
//打印优先队列
void print_priorityqueue(priority_queue<int, vector<int>, greater<int>> data)
{
	while (!data.empty())
	{
		cout << data.top() << " ";
		data.pop();
	}
	cout << endl;
}

//方法一：
//利用小顶堆来解决，小顶堆维护当前扫描到的最大K个数，其后每一次的扫描到的元素，
//若大于堆顶，则入堆，然后删除堆顶；依此往复，直至扫描完所有元素。
//算法的时间复杂度是O(N*logK)
priority_queue<int, vector<int>, greater<int>> topK_1(int K,vector<int> data)
{
	//priority_queue<int> sort_data;
	priority_queue<int, vector<int>, greater<int>> sort_data;
	for (int i=0; i<data.size(); i++)
	{
			int temp = data[i];
		if (sort_data.size() < K || temp > sort_data.top())
			sort_data.push(temp);
		if (sort_data.size() > K)
			sort_data.pop();
	}

	return sort_data;
}

//方法二：
//利用快速排序的分划函数找到分划位置K，则其前面的内容即为所求。该算法是一种非常有效的处理方式，时间复杂度是O(N)
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int partition(vector<int> &arr, int low, int high)
{
	int pivotKey = arr[low];
	while (low < high)
	{
		while (low < high && arr[high] <= pivotKey)
			high--;
		swap(arr[low], arr[high]);
		while (low < high && arr[low] >= pivotKey)
			low++;
		swap(arr[low], arr[high]);
	}

	return low;
}

vector<int> topK_2(vector<int> &arr, int K)
{
	vector<int> res;
	if (K == 0)
		return res;
	if (arr.size() < K)
		return arr;
	int low = 0;
	int high = arr.size() - 1;
	int pivot = partition(arr, low, high);
	while ((pivot + 1) != K)
	{
		if ((pivot + 1) > K)
			high = pivot - 1;
		else
			low = pivot + 1;

		pivot = partition(arr, low, high);
	}

	for (int i = 0; i < K; i++)
		res.push_back(arr[i]);

	return res;
}

int main()
{
	vector<int> data;
	priority_queue<int, vector<int>, greater<int>> res1;   //小顶堆
	vector<int> res2;
	data = produceNumbers(10);
	res1 = topK_1(3, data);
	print_priorityqueue(res1);

	res2 = topK_2(data, 3);
	print_vector(res2);

	return 0;
}