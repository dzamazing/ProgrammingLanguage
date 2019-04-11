//几个要求
//1、多线程生产者、多线程消费者
//2、当队列超过>100时，生产者停止生产，队列<20，消费者停止消费
//3、适当加一些print来验证你的程序，不然整个程序跑起来，你是不知道程序是什么情况的

#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>

using namespace std;

queue<int> q;
mutex m;
condition_variable cv1;  //for 100
condition_variable cv2;  //for 20
bool sig = false;

int count_p = 0;     //生产者计数
int count_c = 0;     //消费者计数

void produce(int x)
{
	unique_lock<mutex> lock(m);

	//循环检查
	while (q.size() > 100)
	{
		cv1.wait(lock);
	}
	//如果小于100
	q.push(x);
	count_p++;
	cout << "produce:" << x << " "<< count_p << endl;
	if (q.size() >= 20)
		cv2.notify_all();
}

void consume()
{
	unique_lock<mutex> lock(m);
	while (q.size() < 20)
	{
		cv2.wait(lock);
	}

	count_c--;
	cout << "consume:" << q.front() <<" "<< count_c << endl;
	q.pop();
	if (q.size() < 100)
		cv1.notify_all();
}

int main()
{
	thread producers[200];
	for (int i = 0; i < 200; i++)
		producers[i] = thread(produce, i);

	thread consumers[200];
	for (int i = 0; i < 200; i++)
		consumers[i] = thread(consume);

	for (auto& p : producers)
		p.join();
	for (auto& c : consumers)
		c.join();

	//最终的运行流程是 生产者会产生200个，而消费者会消费至181，由于只剩19个<20个，消费者停止消费

	return 0;
}
