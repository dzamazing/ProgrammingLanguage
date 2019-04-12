#include<iostream>
#include<cstring>

//vs准备弃用strcpy的，安全性较低，所以微软提供了strcpy_s来代替，
//如果想继续使用strcpy的，必须在main前面加上这一句
#pragma warning(disable:4996) 
//#define _CRT_SECURE_NO_WARNINGS   //这一句也可以解决上述问题，这是关闭所有警告的，上面是关闭某一种警告

//strcpy_s(str, strlen(str1) + 1, str1);  strcpy_s是需要三个参数的，中间需要传入 要复制的字符串的长度+1 的参数

using namespace std;

//类声明
class String
{
public:
	String(const char* str = NULL);   //通过构造函数
	String(const String& s);          //拷贝构造函数
	~String();     //析构函数

	String operator+(const String &str) const;    //重载+
	String& operator=(const String &str);         //重载=
	String& operator+=(const String &str);        //重载+=
	bool operator==(const String &str) const;     //重载==
	char& operator[](int n) const;                //重载[]

	size_t size() const;       //获取长度
	const char* c_str() const; //获取C字符串

	friend istream& operator>>(istream &is, String &str); //输入
	friend ostream& operator<<(ostream &os, String &str); //输出

private:
	char* data;     //数据
	int length;   //长度
};

String::String(const char *str)
{
	if (!str)
	{
		length = 0;
		data = new char[1];
		*data = '\0';
	}
	else {
		length = strlen(str);
		data = new char[length+1];
		strcpy_s(data, str);
	}
}

String::String(const String& str)
{
	length = str.size();
	data = new char[length + 1];
	strcpy(data, str.c_str());
}

String::~String()
{
	delete[] data;
	length = 0;
}

String String::operator+(const String& str) const
{
	String newString;
	newString.length = length + str.length;
	newString.data = new char[newString.length + 1];
	strcpy(newString.data, data);
	strcat(newString.data, str.data);
	return newString;
}

String& String::operator=(const String &str)
{
	if (this == &str)
		return *this;

	delete[] data;
	length = str.length;
	data = new char[length + 1];
	strcpy(data, str.c_str());
	return *this;
}

String& String::operator+=(const String &str)
{
	length += str.length;
	char *newData = new char[length + 1];
	strcpy(newData, data);
	strcat(newData, str.data);
	delete[] data;
	data = newData;
	return *this;
}

inline bool String::operator==(const String &str) const
{
	if (length != str.length)
		return false;
	return strcmp(data, str.data) ? false : true;
}

inline char& String::operator[](int n) const
{
	if (n >= length)
	{
		return data[length - 1];
	}
	else {
		return data[n];
	}
}

inline size_t String::size() const
{
	return length;
}

istream& operator>>(istream& is, String &str)
{
	char tem[1000];
	is >> tem;
	str.length = strlen(tem);
	str.data = new char[str.length + 1];
	strcpy(str.data, tem);
	return is;
}

ostream& operator<<(ostream &os, String &str) //输出
{
	os << str.data;
	return os;
}

inline const char* String::c_str() const
{
	return data;
}

//测试
int main()
{
	String s;
	cin >> s;
	cout << s << ": " << s.size() << endl;

	char a[] = "hello", b[] = "World!";
	String s1(a), s2(b);
	cout << s1 << "+" << s2 << "=" << s1 + s2 << endl;

	String s3 = s1 + s2;
	if (s1 == s3) cout << "First: s1 == s3" << endl;
	s1 += s2;
	if (s1 == s3) cout << "Second: s1 == s3" << endl;
}