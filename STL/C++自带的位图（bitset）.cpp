#include<iostream>
#include<bitset>  //C++自带的bitset
#include<string>

using namespace std;

int main()
{
	//声明方式
	bitset<10> num;           //声明一个位图，必须指定位图的大小，默认每一位都为0
	bitset<4> foo(string("0001"));

	//位获取方法
	num[3] = 1;               //利用操作符直接赋值
	num[4] = num[3];          //直接拷贝
	cout << num << endl;
	int count = num.count();   //利用count()方法获取位图中1的个数
	cout << "count of 1 = " << count << endl;
	int size = num.size();     //利用size()方法获取位图的大小
	cout << "size of num = " << size << endl;
	int test = num.test(4);    //利用test()方法获取位图中第4位的值（0或1）
	cout << "value of 4 = " << test << endl;
	bool any = num.any();      //利用any()方法获取num中的是否有位被设置
	cout << "any = " << any << endl;
	bool none = num.none();    //利用none()方法获取num中是否所有位都没被设置
	cout << "none = " << none << endl;
	bool all = num.all();      //利用all()方法获取num中的是否所有位都被设置
	cout << "all = " << all << endl;

	//位操作方法
	num.set(2);     //将位图中第二位设置为1
	cout << "num[2]= " << num.test(2) << endl;
	num.reset(2);   //将位图中第二位设置为0
	cout << "num[2]= " << num.test(2) << endl;
	num.flip(9);   //将 2+1 位取反， 注意别超过位图大小
	cout << num << endl;

	//位图操作方法
	string s = num.to_string();
	cout << s << endl;
	unsigned long ul = num.to_ulong();
	cout << ul << endl;
	unsigned long long ull = num.to_ullong();
	cout << ull << endl;

	return 0;
}