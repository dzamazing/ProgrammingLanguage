#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>

#pragma warning(disable:4996)£»

using namespace std;
map<int, int> mapleft;
map<int, int> mapright;
int map1[100010];
int sum_left(int k)
{
	map<int, int>::reverse_iterator  iter;
	int sum = 0;
	int num = mapleft.rbegin()->first;
	for (iter = mapleft.rbegin(); iter != mapleft.rend(); iter++)
	{
		//cout<<iter->first<<" l "<<iter->second<<endl;
		if (sum<(iter->second) && k != (iter->first))
		{
			sum = iter->second;
			num = iter->first;
		}
	}
	if (sum == 0)
		return 999999999;
	return num;
}
int sum_right(int k)
{
	map<int, int>::reverse_iterator  iter;
	int sum = 0;
	int num = mapright.rbegin()->first;
	for (iter = mapright.rbegin(); iter != mapright.rend(); iter++)
	{
		// cout<<iter->first<<" r "<<iter->second<<endl;
		if (sum<(iter->second) && k != (iter->first))
		{
			sum = iter->second;
			num = iter->first;
		}
	}
	if (sum == 0)
		return 999999999;
	return num;
}
int main()
{
	mapleft.clear();
	mapright.clear();
	int n, m;
	scanf("%d %d", &n, &m);
	int sum = 0;
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			int temp;
			scanf("%d", &temp);
			map1[sum++] = temp;
		}
	}
	map<int, int>::iterator  it;
	for (int i = 0; i<sum; i = i + 2)
	{
		it = mapleft.find(map1[i]);
		if (it == mapleft.end())
			mapleft[map1[i]] = 1;
		else
			mapleft[map1[i]]++;
	}
	for (int i = 1; i<sum; i = i + 2)
	{
		it = mapright.find(map1[i]);
		if (it == mapright.end())
			mapright[map1[i]] = 1;
		else
			mapright[map1[i]]++;
	}
	int zleft = sum_left(999999999);
	int zongleft;
	if (sum_right(zleft) == 999999999)
		zongleft = mapleft[zleft];
	else
		zongleft = mapleft[zleft] + mapright[sum_right(zleft)];

	int zright = sum_right(999999999);
	int zongright;
	if (sum_left(zright) == 999999999)
		zongright = mapright[zright];
	else
		zongright = mapright[zright] + mapleft[sum_left(zright)];

	//printf("%d %d\n",zongleft,zongright);
	if (zongright>zongleft)
		printf("%d\n", m*n - zongright);
	else
		printf("%d\n", m*n - zongleft);
	return 0;
}