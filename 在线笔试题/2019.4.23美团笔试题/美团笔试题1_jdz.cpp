#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

bool cmp(const pair<int, int>& x, const pair<int, int>& y)
{
	return x.second < y.second;
}

void sortMapByValue(map<int, int > &num, vector<pair<int, int>> &tempv)
{
	for (auto it = num.begin(); it != num.end(); it++)
		tempv.push_back(make_pair(it->first, it->second));

	sort(tempv.begin(), tempv.end(), cmp);
}

void printV(vector<vector<int>> v, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		for (int j = 0; j < m; j++)
			cout << v[i][j] << " ";
	}
}

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> num;
	map<int, int> first;
	map<int, int> second;

	num.resize(n);
	for (int i = 0; i < n; i++)
		num[i].resize(m);

	for(int i=0; i<n; i++)
		for (int j = 0; j < m; j++) 
		{
			cin >> num[i][j];
			if((i+j)%2 == 0)
				first[num[i][j]]++;
			else
				second[num[i][j]]++;
		}

	vector<pair<int, int>> v_left;
	vector<pair<int, int>> v_right;

	sortMapByValue(first, v_left);
	sortMapByValue(second, v_right);

	//选定放入棋盘的两个数
	int left = v_left[0].first;
	int right = v_right[0].first;
    int left_num = v_left[0].second;
	int right_num = v_right[0].second;

	int leftchange = (n*m) / 2 - left_num;
	int rightchange = (n*m+1) / 2 - right_num;

	//当重复次数最多的数字相同时，需要分情况讨论
	if (left == right)
	{
		if (left_num == right_num)
		{
			if (left_num == (n*m / 2))
				rightchange = right_num;
			else
			{

			}
		}
	}
	
	return leftchange + rightchange;

	//int count = 0;
	//for (int i = 0; i<n; i++)
	//	for (int j = 0; j < m; j++)
	//	{
	//		if ((i + j) % 2 == 0 && num[i][j] != left)
	//		{
	//			num[i][j] = left;
	//			count++;
	//		}
	//		else if ((i + j) %2 != 0 && num[i][j] != right)
	//		{
	//			num[i][j] = right;
	//			count++;
	//		}
	//	}
	//cout << endl << count << endl;
	//printV(num, n, m);

	return 0;
}