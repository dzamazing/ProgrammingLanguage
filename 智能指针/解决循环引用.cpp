#include<iostream>
#include<memory>

class Parent;
class Child;

class Parent {
public:
	void setChild(std::shared_ptr<Child> child) {
		this->ChildPtr = child;
	}

	void doSomething() {
		//使用新得shared_ptr
		//weak_ptr通过lock函数从被观测得shared_ptr获得一个可用得shared_ptr资源
		//若被观测得shared_ptr指针已被析构，则lock函数返回一个存储空指针得shared_ptr
		if (this->ChildPtr.lock()) {

		}
	}

	~Parent() {

	}
private:
	std::weak_ptr<Child> ChildPtr;
};

class Child {
public:
	void setParent(std::shared_ptr<Parent> parent) {
		this->ParentPtr = parent;
	}

	void doSomething() {
		//利用引用计数判断此块内存得资源是否已被释放
		if (this->ParentPtr.use_count()){

		}
	}

	~Child(){ 
	
	}

private:
	std::shared_ptr<Parent> ParentPtr;
};

int main() {
	std::weak_ptr<Parent> wpp;  //这两个weak_ptr对象主要作用是检测 p、c两个对象得引用计数
	std::weak_ptr<Child> wpc;
	{
		std::shared_ptr<Parent> p(new Parent);
		std::shared_ptr<Child> c(new Child);
		p->setChild(c);
		c->setParent(p);
		wpp = p;
		wpc = c;
		std::cout << p.use_count() << std::endl;  //2
		std::cout << c.use_count() << std::endl;  //1
	}
	//根据栈后进先出得原理，c先出作用域，所以c得引用次数减1为0，资源被释放
	//p后出作用域，次数c得资源已被释放，所p得引用次数已经为1，出了作用域再减1变为0，资源被释放
	//综上所述解决循环引用得核心是必须让使用weak_ptr得对象先出作用域，因为weak_ptr是弱引用，只引用，不计数

	std::cout << wpp.use_count() << std::endl;    //0
	std::cout << wpc.use_count() << std::endl;    //0

	int temp;
	std::cin >> temp;

	return 0;
}
