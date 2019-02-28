#include<iostream>
#include<memory>

/* 
 * shared_ptr 拷贝使得对象的引用计数增加1，赋值使得原对象引用计数减1
 */

int main()
{
	{
		int a = 10;
		std::shared_ptr<int> ptra = std::make_shared<int>(a);
		std::shared_ptr<int> ptra2(ptra);  //拷贝，引用计数加一
		std::cout << ptra.use_count() << std::endl;  //2

		int b = 20;
		int *pb = &a;
		//	std::shared_ptr<int> ptrb = pb;  //错误的语句，无法将一个int指针赋值给一个类对象
		std::shared_ptr<int> ptrb = std::make_shared<int>(b);
		ptra2 = ptrb;    //赋值,使得ptra应用数减一，ptrb的引用数加一

		std::cout << ptra.use_count() << std::endl; //1
		std::cout << ptrb.use_count() << std::endl; //2

		std::cout << *pb << std::endl;   //此时pb的值为10,因为pb最开始指向a
		pb = ptrb.get(); //获取原始指针
		std::cout << *pb << std::endl;   //此时pb的值为20,因为ptrb的原始指针指向b

		int temp;
		std::cin >> temp;

		return 0;
	}
}