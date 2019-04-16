#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

//LRU缓存算法也叫LRU页面置换算法，是一种经典常用的页面置换算法

//LRU的典型实现是hash map + doubly linked list，双向链表用于存储数据结点，并且它是按照结点最近被使用的时间来存储的。
//如果一个结点被访问了，我们有理由相信它在接下来的一段时间被访问的概率要大于其它结点。于是，我们把它放到双向链表的头部。
//当我们往双向链表里插入一个结点，我们也有可能很快就会使用到它，同样把它插入到头部。我们使用这种方式不断地调整着双向链表，链表尾部的结点自然也就是最近一段时间，最久没有使用到的结点。
//那么，当我们的Cache满了，需要替换掉的就是双向链表中最后的那个结点
//如果没有哈希表，我们要访问某个结点，就需要顺序地一个个找，时间复杂度是O(n)。使用哈希表可以让我们在O(1)的时间找到想要访问的结点，或者返回未找到。

template<typename K, typename T>
struct Node {
	K key;
	T value;
	Node(K k, T v):key(k),value(v) {}
};

template<typename K, typename T>
class LRUCache
{
public:
	LRUCache(int c):capacity(c)  {}   //构造函数

	T get(K key)
	{
		_ASSERT(cacheMap.find(key) != cacheMap.end());

		//将key移到第一个，并更新cacheMap
		//将cacheMap[key]移动到目的cacheList的开头位置，高效的将他们插入到目的list并从cacheList中删除。
		cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);  
		cacheMap[key] = cacheList.begin();
		return cacheMap[key]->value;   //迭代器是指针
	}

	void set(K key, T value)
	{
		if (cacheMap.find(key) == cacheMap.end())
		{
			//不在缓存列表中，淘汰链表的最后一个元素，并将新元素插入链表中
			if (cacheList.size() == capacity)
			{
				cacheMap.erase(cacheList.back().key);  //先从map中删除最后一个键值
				cacheList.pop_back();    //再从list中删除对应的node
			}
			cacheList.push_front(Node<K, T>(key, value));
			cacheMap[key] = cacheList.begin();
		}
		else {
			//更新节点的值，并将其加到第一个位置
			cacheMap[key]->value = value;
			cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
			cacheMap[key] = cacheList.begin();
		}
	}

private:
	int capacity;
	list<Node<K, T>> cacheList;
	unordered_map < K, typename list<Node<K, T>>::iterator> cacheMap;  
	//由于iterator依赖具体的map，而map中包含了一个模板，在没有实例化的时候不能确定其类型。
    //此时加一个typename前缀即可
};

int main()
{
	int N = 10;
	LRUCache<int, int> lc(N);

	for (int i = 0; i < N; i++)
		lc.set(i,i);
	cout << "at the beginning: " << endl;
	for (int i = 0; i < N; i++)
		cout << lc.get(i) << " ";
	cout << endl;
	cout << "after inserting: " << endl;  //第0个元素被删掉了，11被插了进去
	lc.set(N + 1, N + 1);	
	for (int i = 1; i < N; i++)
		cout << lc.get(i) << " ";
	cout << lc.get(N + 1);
	cout << endl;

	return 0;
}
