#include<iostream>  
#include<stack>  
using namespace std;

//栈 后进先出
//由deque演变而来

//stack的基本操作有：
//1.入栈：如s.push(x);
//2.出栈:如 s.pop().注意：出栈操作只是删除栈顶的元素，并不返回该元素。
//3.访问栈顶：如s.top();
//4.判断栈空：如s.empty().当栈空时返回true。
//5.访问栈中的元素个数，如s.size（）;
//没有迭代器

int main(void)
{
	stack<double>s;//定义一个栈  
	for (int i = 0; i<10; i++)
		s.push(i);
	while (!s.empty())
	{
		printf("%lf\n", s.top());
		s.pop();
	}
	cout << "栈内的元素的个数为：" << s.size() << endl;
	return 0;
}