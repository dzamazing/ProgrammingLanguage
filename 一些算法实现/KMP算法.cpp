#include<iostream>
#include<vector>
#include<string>

using namespace std;

void printNext(vector<int> next)
{
	cout << "next: ";
	for (int i = 0; i < next.size(); i++)
	{
		cout << next[i] << " ";
	}
	cout << endl;
}

vector<int> getNext(string ps)
{
	vector<int> next(ps.size());
	next[0] = -1;  //这时候只能主串往后移一步
	int j = 0;
	int k = -1;
	while (j < (ps.size() - 1))
	{
		if (k == -1 || ps[j] == ps[k]) {
			//if (ps[++j] == ps[++k])
			//	next[j] = next[k];
			//else
			//	next[j] = k;
			next[++j] = ++k;
		}
		else
			k = next[k];
	}
	//打印
	printNext(next);

	return next;
}

int KMP(const string &ts, const string &ps)  //ts：主串 ps: 模式串
{
	int i = 0; //主串的位置
	int j = 0; //模式串的位置
	vector<int> next = getNext(ps);

	int l_ts = ts.length(), l_ps = ps.length();  //注意：string的size()和length()返回的是无符号整形
	                                             //而当一个有符号整形数和一个无符号整形数进行大小比较时，会先将有符号整形数转换成无符号整形数后再进行比较
	                                             //如此一来一个负整数将会变的非常大
	while (i < l_ts && j < l_ps)
	{

#if 1
		if (j == -1 || ts[i] == ps[j])
		{
			i++;
			j++;
		}
		else {
			j = next[j];
		}	

#else
		if (ts[i] == ps[j])
		{
			i++;
			j++;
			cout << "j: " << j << " i :" << i << endl;
		}
		else {
			j = next[j];
			if (j == -1) {
				j = 0;
				i++;
			}
			cout << "j: " << j << " i :" << i << endl;
		}
#endif


	}

	if (j == ps.size())
		return i - j;
	else
		return -1;
}


int main()
{
	string ts, ps;

	while (ts != "/" && ps != "/")
	{
		cout << "请输入主串ts: ";
		cin >> ts;
		cout << "请输入模式串ps: ";
		cin >> ps;
		cout << "搜索结果为： " << KMP(ts, ps) << endl;
	}
}
