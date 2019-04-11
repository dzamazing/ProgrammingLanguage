#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;


//百度笔试题1 ，祷告会
// 0 <=count<= 1000
//全排列思想解决
//辅助函数1： 是否需要交换
int isswap(string arr, int from, int to, int count)
{
	//如果要换过来的to字符在from字符的前count位内出现过，则不交换
	if (from > 0)
	{
		int j = 0;
		for (int i = 1; i <= count; i++)
		{
			j = from - i;
			if (j < 0)
				break;
			if (arr[j] == arr[to])
				return 0;
		}
	}

	for (int i = from; i < to; i++)
	{
		if (arr[i] == arr[to])
			return 0;
	}

	return 1;
}
//辅助函数2: 交换
void swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//辅助函数3: vector<char> 转string
string combine(vector<char> res)
{
	string str = "";
	for (int i = 0; i < res.size(); i++)
		str += res[i];
	return str;
}
//辅助函数4：无重复全排列
void permutations(string arr, int k, int n, vector<vector<char>> *all_res,int count)
{
	//vector<vector<char>> all_res;
	if(k == n)
	{
		vector<char> one_res;
		one_res.clear();
		for (int i = 0; i < n; i++)
		{
			one_res.push_back(arr[i]);
		}
		all_res->push_back(one_res);
	}else{
		for (int i = k; i < n; i++)
		{
			if (isswap(arr, k, i,count))
			{
				swap(&arr[k], &arr[i]);
				permutations(arr, k + 1, n,all_res,count);
				swap(&arr[i], &arr[k]);
			}
		}
	}

}
//辅助函数5：若有结果，则利用全排列得出字典序最小的结果
string getMinResult(string students, int count)
{
	vector<vector<char>> *res = new vector<vector<char>>();

	permutations(students, 0, students.size(), res, count);

	//打印全排列的结果
	//for (int i = 0; i < res->size(); i++)
	//{
	//	string temp = combine(res->at(i));
	//	cout << temp << endl;
	//}

	sort(res->begin(), res->end());
	string str = combine(res->at(0));
	return str;
}
//辅助函数6： 比较器
typedef pair<char, int> PAIR;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs)
{
	return lhs.second > rhs.second;
}
//核心函数
string rearrange(string students, int count)
{
	//判断能不能排，判断依据：若人数最多的班级的人数*count 小于其余班级的总人数，则可以排
	                        //否则返回 -1
	map<char, int> mymap;
	for (int i = 0; i < students.size(); i++)
		mymap[students[i]]++;
	
	vector<PAIR> sort_mymap(mymap.begin(), mymap.end());
	sort(sort_mymap.begin(), sort_mymap.end(), cmp_by_value); //按照学生数对班级进行排序
	
	//统计除人数最多班级外的其他班级的总人数
	int stu_count = 0;	
	for (int i = 1; i < sort_mymap.size(); i++)
	{
		stu_count = stu_count + sort_mymap[i].second;
	}
	
	if ((sort_mymap[0].second - 1) * count > stu_count)
		return "-1";

	//如果可以排列，则利用全排列输出结果
	string res = getMinResult(students, count);
	return res;
}
int main()
{
	string str = "ddgdghghh";
	string str1 = "ddddghghh";
	string res = rearrange(str1, 2);

	cout << res << endl;
	system("pause");

	return 0;

}

////百度4-2笔试题2
//int maxNormalTemp(int size, int allowedChanges, string reading)
//{
//	//滑动窗口，限定一个滑动窗口中只能含有K个0，如果超过了K个，移动左端，过程中不断取区间最大值
//	int left = 0, right = 0;  //滑动窗口的左边界和右边界
//	int max_size = 0;         //滑动窗口内元素的最大值
//	int count_0 = 0;          //滑动窗口内的0个数
//	int count_1 = 1;          //滑动窗口内的1个数
//
//	//确定最开始滑动窗口的左右边界
//	for (int i = 0; i < size; i++)
//	{
//		if (reading[i] == '0')
//			count_0++;
//		if (reading[i] == '1')
//			count_1++;
//		if (count_0 == allowedChanges)
//		{
//			right = i;
//			max_size = right - left + 1;  //1的最大值就是滑动窗口内的元素大小
//			break;
//		}
//	}
//
//	for (int i = right+1; i < size; i++)
//	{
//		right = i;     //移动滑动窗口的右端
//		if (reading[i] == '0')
//		{
//			//需要移动滑动窗口的左端
//			while (reading[left] != '0')    //移动滑动窗口的左端，直到蒋
//				left++;
//			left++;  //确定新的左边界
//
//		}
//			
//		if (reading[i] == '1')
//		{
//			//不需要移动左端，只需要移动右端
//			if ((right - left + 1) > max_size)
//				max_size = right - left + 1;
//		}
//	}
//	return max_size;
//}
//
//int main()
//{
//	string str = "1010101";
//	int size = str.size();
//	cout << size << endl;
//	int allowed = 2;
//	int max_count_1 = maxNormalTemp(size, allowed, str);
//	cout << "res : " << max_count_1 << endl;
//
//	return 0;
//}


////百度4-2笔试题3
////用贪心思想解决，每次找出错误分最大的人，让他完成一个项目

////辅助函数1，返回一个整数数组中值最大元素的下标
//int indexOfMax(int num, int* arr)
//{
//	int index = 0;
//	int max = arr[0];
//	for (int i = 1; i < num; i++)
//	{
//		if (arr[i] > max)
//			index = i;
//	}
//	return index;
//}
////辅助函数2，对所有人进行减分
//void decreaseScore(int num, int projCmptDec, int restDec, int* errorScore, int index)
//{
//	for (int i = 0; i < num; i++)
//	{
//		if (errorScore[i] == 0)
//			continue;
//
//		if (i == index)
//			errorScore[i] -= projCmptDec;
//		else
//			errorScore[i] -= restDec;
//
//		if (errorScore < 0)
//			errorScore[i] = 0;
//	}
//
//	return;
//}
////核心函数
//int minNumberOfProjects(int num, int projCmptDec, int restDec, int* errorScore)
//{
//	int res = 0;   //最小项目数
//	int index_max;
//	index_max = indexOfMax(num, errorScore);
//
//	while (errorScore[index_max] != 0)
//	{
//		res++;   //让错误分数最大的人完成一个项目
//		decreaseScore(num, projCmptDec, restDec, errorScore, index_max);
//
//		index_max = indexOfMax(num, errorScore);
//	}
//
//	return res;
//}
//
//int main()
//{
//	int num = 4;
//	int projDec = 3;
//	int restDec = 1;
//	int errorScore[] = { 9,8,2,5 };
//
//	int min_proj = minNumberOfProjects(num, projDec, restDec, errorScore);
//
//	cout << "min_proj = " << min_proj << endl;
//
//	return 0;
//}