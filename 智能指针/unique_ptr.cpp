#include<iostream>
#include<memory>

int main()
{
	{
		std::unique_ptr<int> uptr(new int(5));  //绑定动态对象
		//std::unique_ptr<int> uptr2 = uptr;  //不能赋值
		//std::unique_ptr<int> uptr2(uptr);   //不能拷贝
		std::unique_ptr<int> uptr2 = std::move(uptr);

		uptr2.release();  //释放所有权
	}
	//超过uptr的作用域，内存释放
	return 0;
}