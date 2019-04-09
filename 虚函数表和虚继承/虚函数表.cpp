#include <iostream>

//参考博客网址：https://blog.csdn.net/lyztyycode/article/details/81326699

using namespace std;

class Base1 {

public:

	virtual void f() { cout << "Base1::f" << endl; }

	virtual void g() { cout << "Base1::g" << endl; }

	virtual void h() { cout << "Base1::h" << endl; }

};

class Base2 {

public:

	virtual void f() { cout << "Base2::f" << endl; }

	virtual void g() { cout << "Base2::g" << endl; }

	virtual void h() { cout << "Base2::h" << endl; }

};

class Base3 {

public:

	virtual void f() { cout << "Base3::f" << endl; }

	virtual void g() { cout << "Base3::g" << endl; }

	virtual void h() { cout << "Base3::h" << endl; }

};

class Derive : public Base1, public Base2, public Base3 {

public:

	virtual void f() { cout << "Derive::f" << endl; }   //重写了父类的虚函数

	virtual void g1() { cout << "Derive::g1" << endl; } //未重写父类的虚函数

};

typedef void(*Fun)(void);     //声明一个函数指针

int main()

{

	Fun pFun = NULL;

	Derive d;         //声明一个子类实例对象

	int** pVtab = (int**)&d; //指针的指针

	//Base1's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);

	pFun = (Fun)pVtab[0][0];  //第一个父类的虚函数表的第一个虚函数

	pFun();      //Derive::f  因为此时这个虚函数已被子类重写了，所以调用的是Derive的f()

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);

	pFun = (Fun)pVtab[0][1]; //子类中第一个父类的虚函数表的第二个虚函数

	pFun();        //Base1::g  因为子类没有重写这个虚函数，所以打印结果是Base1的 g()

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);

	pFun = (Fun)pVtab[0][2]; //子类中第一个父类的虚函数表的第三个虚函数

	pFun(); //Base1::h  因为子类没有重写这个虚函数，所以打印结果是Base1的 h()

	//Derive's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);

	pFun = (Fun)pVtab[0][3]; //子类中第一个虚函数表的第四个虚函数

	pFun();   //Derive::g1 因为子类的成员函数被放到了第一个父类的表中。（所谓的第一个父类是按照声明顺序来判断的）

	//The tail of the vtable

	pFun = (Fun)pVtab[0][4];  //打印子类第一个虚函数表的结束节点，就像字符串的结束符“/0”一样，其标志了虚函数表的结束。
	                          //这个结束标志的值在不同的编译器下是不同的。在WinXP+VS2003下，这个值是NULL。
	                          //而在Ubuntu 7.10 + Linux 2.6.22 + GCC 4.1.3下，这个值是如果1，表示还有下一个虚函数表，
	                          //如果值是0，表示是最后一个虚函数表。

	cout << pFun << endl;    //打印结果：00000000

	//Base2's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);

	pFun = (Fun)pVtab[1][0];  //子类中第二个父类虚函数表的第一个虚函数

	pFun();    //Derive::f   因为已被子类重写后的虚函数覆盖

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);

	pFun = (Fun)pVtab[1][1];  //子类中第二个父类虚函数表的第二个虚函数

	pFun();  //Base2::g

	pFun = (Fun)pVtab[1][2]; //子类中第二个父类虚函数表的第三个虚函数

	pFun(); //Base2::h

	//The tail of the vtable

	pFun = (Fun)pVtab[1][3];

	cout << pFun << endl;   ////打印结果：00000000

	//Base3's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);

	pFun = (Fun)pVtab[2][0];  //子类中第三个父类虚函数表的第一个虚函数

	pFun();   //Derive::f   因为已被子类重写后的虚函数覆盖

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);

	pFun = (Fun)pVtab[2][1];  //子类中第三个父类虚函数表的第二个虚函数

	pFun();   //Base3:g

	pFun = (Fun)pVtab[2][2];  //子类中第三个父类虚函数表的第三个虚函数

	pFun();   //Base3:h

	//The tail of the vtable

	pFun = (Fun)pVtab[2][3];

	cout << pFun << endl;    ////打印结果：00000000

	return 0;

}