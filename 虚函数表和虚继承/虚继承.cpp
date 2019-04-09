#include<iostream>

using namespace std;

class Animal {
public:
	int name;
	virtual void breathe()
	{
		cout << "Animal breathe" << endl;
	}
};

class LandAnimal : virtual public Animal {
public:
	int numLegs;
	virtual void run()
	{
		cout << "Land animal run" << endl;
	}
};

class Mammal : virtual public Animal {
public:
	int numBreasts;
	virtual void milk()
	{
		cout << "Mammal milk" << endl;
	}
};

class Human : public Mammal, public LandAnimal {
public:
	int race;
	void breathe()
	{
		cout << "Human breathe" << endl;
	}

	void milk()
	{
		cout << "Human milk" << endl;
	}

	void run()
	{
		cout << "Human run" << endl;
	}

	void eat()
	{
		cout << "Human eat" << endl;
	}
};

int main()
{
	Human human;
	
	cout << "用LandAnimal指针调用Human实例的方法" << endl;
	LandAnimal *laPtr = NULL;
	laPtr = &human;
	laPtr->run();

	cout << "用Mammal指针调用Human实例的方法" << endl;
	Mammal *mPtr = NULL;
	mPtr = &human;
	mPtr->milk();

	cout << "用Animal指针调用Human实例的方法" << endl;
	Animal *aPtr = NULL;
	aPtr = &human;
	aPtr->breathe();   //如果没有使用虚继承的话此处会报错，因为因为Human类同时继承了LandAnimal类和Mammal类。
	                   //这里会有二义性，编译器不知道该调用那个父类中的breathe()
	return 0;
}

//一个子类虚继承自另一个基类，它不再像普通继承那样直接拥有一份基类的内存结构，而是加了一个虚表指针vbptr指向虚基类，这个虚基类在msvc中被放在的类的内存空间的最后。
//这样，当出现类似这里的菱形继承时，基类Animal在子类Human中出现一次，子类Human所包含的Mammal类和LandAnimal类各有一个虚基类指向虚基类。
//从而避免了菱形继承时的冲突。
//详细虚继承内存分布见博客：https://www.cnblogs.com/demian/p/6538301.html

