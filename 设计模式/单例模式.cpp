#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;

//单例模式
//懒汉式：在第一次用到类实例的时候才会去实例化
//饿汉式：在单例类定义的时候就进行实例化

//由于要进行线程同步，所以在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间。
//在访问量较小时，采用懒汉实现，这是以时间换空间

//饿汉式
class Singleton1
{
public:
	static Singleton1* getInstance();
	Singleton1(const Singleton1&) = delete;
	Singleton1& operator=(const Singleton1&) = delete;
private:
	Singleton1() {};
	//把复制构造函数和=操作符也设为私有，防止被复制
	//Singleton1(const Singleton1&) {}; 
	//Singleton1& operator=(const Singleton1&) {};

	static Singleton1* instance;

};

Singleton1* Singleton1::instance = new Singleton1();

Singleton1* Singleton1::getInstance()
{
	return instance;
}

//加锁的经典懒汉实现
class Singleton2
{
public:
	static mutex sig_mutex;
	static Singleton2* getInstance();

	Singleton2(const Singleton2&) = delete;
	Singleton2& operator=(const Singleton2&) = delete;

private:
	static Singleton2* instance;

	Singleton2() {};
	////把复制构造函数和=操作符也设为私有，防止被复制
	//Singleton2(const Singleton2&) {};
	//Singleton2& operator=(const Singleton2&) {};

};

mutex Singleton2::sig_mutex;
Singleton2* Singleton2::instance = nullptr;
Singleton2* Singleton2::getInstance()
{
	unique_lock<mutex> ulock(sig_mutex); //通过unique_lock智能控制互斥量的加锁和解锁

	if (instance == nullptr)
		instance = new Singleton2();

	return instance;
}

//内部静态变量的懒汉实现
class Singleton3
{
public:
	static mutex sig_mutex;
	static Singleton3* getInstance();
	Singleton3(const Singleton3&) = delete;
	Singleton3& operator=(const Singleton3&) = delete;
private:
	Singleton3() {};
	////把复制构造函数和=操作符也设为私有，防止被复制
	//Singleton3(const Singleton3&) {};
	//Singleton3& operator=(const Singleton3&) {};
};
mutex Singleton3::sig_mutex;
Singleton3* Singleton3::getInstance()
{
	unique_lock<mutex> ulock(sig_mutex); //通过unique_lock智能控制互斥量的加锁和解锁
	static Singleton3 instance;
	
	return &instance;
}

int main()
{
	Singleton1* singleton1_1 = Singleton1::getInstance();
	Singleton1* singleton1_2 = Singleton1::getInstance();

	if (singleton1_1 == singleton1_2)
		cout << "singleton1_1 = singleton1_2" << endl;

	Singleton2* singleton2_1 = Singleton2::getInstance();
	Singleton2* singleton2_2 = Singleton2::getInstance();

	if (singleton2_1 == singleton2_2)
		cout << "singleton2_1 = singleton2_2" << endl;

	Singleton3* singleton3_1 = Singleton3::getInstance();
	Singleton3* singleton3_2 = Singleton3::getInstance();

	if (singleton3_1 == singleton3_2)
		cout << "singleton3_1 = singleton3_2" << endl;



	return 0;
}