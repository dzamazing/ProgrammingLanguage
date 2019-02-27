#include<iostream>
#include<memory>

int main()
{
	{
		std::shared_ptr<int> sh_ptr = std::make_shared<int>(10);
		std::cout << sh_ptr.use_count() << std::endl;  //1

		std::weak_ptr<int> wp(sh_ptr);
		std::cout << wp.use_count() << std::endl;      //1, weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加

		if (!wp.expired())  //expired()的功能等价于 use_count()==0,表示被观测的资源已经不复存在
		{
			std::shared_ptr<int> sh_ptr2 = wp.lock(); // lock()函数从被观测的shared_ptr获得一个可用得shared_ptr对象，从而操作资源
			std::cout << "*sh_ptr2 = " << *sh_ptr << std::endl;  //sh_ptr2指向sh_ptr指向地址得资源，所以随着sh_ptr得修改而修改
			*sh_ptr = 100;
			std::cout << "*sh_ptr2 = " << *sh_ptr << std::endl;
			std::cout << wp.use_count() << std::endl;  //2
		}

		int temp;
		std::cin >> temp;
	}

	//释放内存

	return 0;
}