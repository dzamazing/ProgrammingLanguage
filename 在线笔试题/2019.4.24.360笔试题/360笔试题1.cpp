#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

//思路： 统计各个颜色小球的个数，然后求出所有颜色个数的最大公约数，便是最终每个篮子放的小球个数。

int max_gongyueshu(int a, int b) {
	while (b != 0)
	{
		int r = a%b;
		a = b;
		b = r;

	}
	return a;
}

int main()
{
	int count;
	cin >> count;

	if (count < 2) 
	{
		cout << 0 << endl;
	}
		
	//vector<int> ball;
	map<int, int> ball;
	vector<pair<int, int>> bucket;

	int temp;
	for (int i = 0; i < count; i++)
	{
		cin >> temp;
		ball[temp]++;
	}

	int a , b;
	a = ball.begin()->second;
	for (auto it = ++ball.begin(); it != ball.end(); it++)
	{
		b = it->second;
		a = max_gongyueshu(a, b);
		if (a == 1)
			break;
	}

	if (a == 1)
		a = 0;
	else
		a = count / a;

	cout << a << endl;

	return 0;
}
