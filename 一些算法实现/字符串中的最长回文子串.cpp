#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
private:
	int expandAroundCenter(string s, int left, int right)
	{
		int L = left, R = right;
		int len = s.size();
		
		while (L >= 0 && R < len && s[L] == s[R])
		{
			L--;
			R++;
		}

		return R - L - 1;  //返回此次左右扩展后找到的最长回文子串
	}

public:
	string longestPalindrome(string s)
	{
		if (s.size() < 1 || s == "")
			return "";

		int start = 0, end = 0;
		for (int i = 0; i < s.size(); i++)
		{
			int len1 = expandAroundCenter(s, i, i);   //回文子串有唯一中心点情况
			int len2 = expandAroundCenter(s, i, i + 1); //回文子串左右对称情况
			int len = max(len1, len2);

			if (len > (end - start))
			{
				start = i - (len - 1) / 2;  //回文子串的起始位置
				end = i + len / 2;          //回文子串的结束位置,len/2向下取整
			}
		}
		int res_len = end - start + 1; //回文子串的长度
		return s.substr(start, res_len); //substr的第一个参数是起始位置，第二个参数是子串长度
	}
};

int main()
{
	Solution s;
	string str = "babad";
	string substr = s.longestPalindrome(str);

	cout << substr << endl;
}