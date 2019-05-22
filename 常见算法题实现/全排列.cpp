#include<iostream>
#include<vector>
#include<algorithm>
#include"mylib.h"

using namespace std;

//库函数法
vector<vector<int>> permute1(vector<int>& nums) {

	sort(nums.begin(), nums.end());

	vector<vector<int>> res;

	do {
		res.push_back(nums);
	} while (next_permutation(nums.begin(), nums.end()));

	return res;
}

//回溯
void exchange(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}
void solve(int index, vector<int>& nums, vector<vector<int>> &rtn) {
	if (index == nums.size() - 1) {
		rtn.push_back(nums);
		return;
	}
	else {
		for (int i = index; i<nums.size(); i++) {
			exchange(nums[index], nums[i]);
			solve(index + 1, nums, rtn);
			exchange(nums[index], nums[i]);
		}

	}
}
vector<vector<int>> permute2(vector<int>& nums) {
	vector<vector<int>> rtn;
	solve(0, nums, rtn);
	return rtn;
}


//方法三
vector<vector<int>> permute3(vector<int>& nums)
{
	vector<vector<int>> re_all;
	if (nums.size()<2)
	{
		re_all = { nums };
	}
	else
	{
		for (int i = 0; i<nums.size(); i++)
		{
			int head = nums[i];
			vector<vector<int>> re;
			vector<int> num = nums;
			num.erase(num.begin() + i);
			re = permute3(num);
			for (int j = 0; j<re.size(); j++)
			{
				re[j].insert(re[j].begin(), head);
				re_all.push_back(re[j]);
			}
		}
	}
	return re_all;
}

int main()
{
	int n;
	cin >> n;

	vector<int> nums;
	nums.resize(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];

	vector<vector<int>> res = permute2(nums);

	for (int i = 0; i < res.size(); i++)
		printVector(res[i]);

	return 0;

}