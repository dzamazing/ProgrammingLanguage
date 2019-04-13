//4.13京东笔试题
//思路：贪心，先把每个子串在目标串中的位置统计出来，取位于目标串最前面的位置，截去匹配的这部分生成一个新的目标串，同时计数加一
      //依次循环，直至目标串截为空或子串在目标串中无匹配位置
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int findIndex(string s, string p)
{
	int index;
	index = s.find(p);
	if (index != -1)
		return index + p.size() - 1;  //返回父串的最终位置
	else
		return -1;
}

int count(int m, vector<string> strset, string s)
{
	int count = 0;
	vector<int> finalIndex;
	int temp;
	while (1)
	{
		finalIndex.clear();
		for (int i = 0; i < strset.size(); i++)
		{
			temp = findIndex(s, strset[i]);
			if (temp != -1)
				finalIndex.push_back(temp);
		}
		if (finalIndex.size() != 0)
		{
			sort(finalIndex.begin(), finalIndex.end()); //排序

			s = s.substr(finalIndex[0] + 1);
			count++;
		}
		else {
			return count;
		}
	}
	return count;
}

int main()
{
	int m;
	vector<string> strset;
	string str;

	cin >> m;
	string temp;
	for (int i = 0; i<m; i++)
	{
		cin >> temp;
		strset.push_back(temp);
	}

	cin >> str;
	int res;
	res = count(m, strset, str);
	cout << res << endl;

	return 0;
}
