#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int change(string s)
{
	int res = 0;
	//reverse(s.begin(), s.end());
	int point = 0;  //'.'出现的次数，只允许出现一次，多余一次便是异常情况
	int big = 1;    //用于判断正负
	for (int i = 0; i < s.size(); i++)
	{
		if (i == 0 && (s[i] == '+' || s[i] == '-'))  //先判断第一个字符是否是‘+’ ‘-’号
		{
			if (s[i] == '-')
				big = -1;
			continue;
		}
		if ((s[i]<'0' || s[i]>'9')&& s[i]!= '.')
			return 0;
		if (s[i] == '.')
			point++;
		if (point > 1)
			return 0;
		if (point == 0)
		{
			int num = s[i] - '0';
			res = res * 10 + num;
		}
	}

	return res*big;
}

int main()
{
	string str;
	//cin >> str;

	while (cin >> str)
	{
		int res;
		res = change(str);
		cout << res << endl;
	}


	
	return 0;
}



