#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<iterator>

using namespace std;

class Solution {
public:
	//方法二：利用递归，（DFS)此方法较动态规划要好很多
	//参考链接：https://blog.csdn.net/fys465253658/article/details/81215869
	//基本思想：举例子说明最容易理解，例如 nums = [1, 5, 4, 3, 7];
	//第一步：对数组进行排序，nums = [1, 3, 4, 5, 7], 求出其和的一半 half = 10; 对于数组中元素要么在这一个子集中，要么在另外一个子集中。
	//第二步：例如1如果在一个子集中，相当于在[3, 4, 5, 7]中去找一个子集和为9的再加上1这个元素，或者1在另外一个子集中，所以就相当于在[3, 4, 5, 7] 中找一个和依旧为10 的子集，因此我们可以获得递归方程式；
	//recur(nums, 0, 10) = recur(nums, 1, 9) || recur(nums, 1, 10);
	bool canPartition(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int sum = accumulate(nums.begin(), nums.end(), 0); //求和
		if (sum % 2)  //判断和是否是偶数，若为奇数则肯定不能划分等和子集
			return false;
		int half = sum / 2; //获取子集的和（总和的一半）
		auto iter = max_element(nums.begin(), nums.end()); //查找值最大的元素
		if (*iter > half)  //若最大元素值就超过总和的一半，则肯定不能划分等和子集
			return false;
		if (*iter == half) //若最大元素值等于总和的一半，则肯定能划分等和子集，且其中一个子集只有一个元素
			return true;
		vector<int> res(half + 1, 0);
		res[0] = 1;  //索引0代表能凑成和为0的子集
		for (size_t i = 0; i < nums.size(); ++i)
		{
			for (int j = half; j >= nums[i]; j--)
			{
				if (res[j - nums[i]])
				{
					res[j] = 1;
					if (j == half)
						return true;
				}
			}
		}
		return res[half];
	}

	//DFS，此方法会存储满足的一组子集的下标索引
	bool dfs(vector<int> &nums, vector<int> &index, int target, int i)
	{
		if (target == 0)
			return true;
		else if (target > 0)
		{
			for (int j = i; j < nums.size(); j++)
			{
				index.push_back(j);
				if (!dfs(nums, index, target - nums[j], j + 1))
				{
					index.pop_back();
				}
					
				else
					return true;
			}
		}

		return false;
	}
};

int main()
{
	Solution s;
	int size;
	cin >> size;
	vector<int> nums;
	int temp;
	for (int i = 0; i < size; i++)
	{
		cin >> temp;
		nums.push_back(temp);
	}

	int sum = accumulate(nums.begin(), nums.end(), 0); //求和
	sort(nums.begin(), nums.end());   //排序
	bool canOrnot = false;
	vector<int> index;    //存放一组子集的索引
	//canOrnot = s.canPartition(nums);
	canOrnot = s.dfs(nums, index, sum / 2, 0);
	cout <<"can Or not is  " <<canOrnot << endl;
	cout << endl;

	if (canOrnot) // 如果可以划分，打印两组子集
	{
		vector<int> list1;
		vector<int> list2;
		vector<int>::iterator temp;

		for (int i = 0; i < nums.size(); i++)
		{
			temp = find(index.begin(), index.end(), i);
			if (temp != index.end())
				list1.push_back(nums[i]);
			else
				list2.push_back(nums[i]);
		}

		for (int i = 0; i < list1.size(); i++)
			cout << list1[i] << " ";
		cout << endl;

		for (int i = 0; i < list2.size(); i++)
			cout << list2[i] << " ";
		cout << endl;
	}
}
