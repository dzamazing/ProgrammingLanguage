#include<iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
	
};

void createList(ListNode* head)
{
	ListNode* pre = head;
	int temp;
	while (cin >> temp)
	{
		ListNode* node = new ListNode(temp);
		pre->next = node;
		pre = node;
	}
}

void printL(ListNode* head)
{
	if (head == nullptr)
		return;

	ListNode* node = head;
	while (node->next != nullptr)
	{
		cout << node->val << "->";
		node = node->next;
	}
	cout <<node->val<< endl;
}

//k个一组翻转链表
ListNode*  reverseKGroup(ListNode* head, int k)
{
	ListNode* cur = head;
	ListNode* pre = nullptr;
	ListNode* next = nullptr;
	ListNode* check = head;
	int canProcess = 0;
	int count = 0;
	// 检查链表长度是否满足翻转
	while (canProcess<k && check != nullptr)
	{
		check = check->next;
		canProcess++;
	}
	// 满足条件，进行翻转
	if (canProcess == k)
	{
		while (count < k && cur != nullptr)
		{
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
			count++;
		}
		if (next != nullptr)
			head->next = reverseKGroup(next, k); // head 为链表翻转后的尾节点
		
			return pre; // prev 为链表翻转后的头结点
	}
	else {
		return head; // 不满住翻转条件，直接返回 head 即可
	}
}

//翻转链表
ListNode* reverseAll(ListNode* head)
{
	ListNode* pRHead = nullptr;
	ListNode* pCur = head;
	ListNode* pNext = nullptr;
	ListNode* pPre = nullptr;

	while (pCur != nullptr)
	{
		pNext = pCur->next;
		pCur->next = pPre;
		pPre = pCur;
		pCur = pNext;
	}
	
	pRHead = pPre;

	return pRHead;
}

//返回倒数第K个节点
ListNode* findLastKthNode(ListNode* head, int k)
{
	if (head == nullptr || k == 0)
		return nullptr;
	ListNode*pTail = head, *pHead = head;
	for (int i = 1; i<k; ++i)
	{
		if (pHead->next != nullptr)
			pHead = pHead->next;
		else
			return nullptr;
	}
	while (pHead->next != nullptr)
	{
		pHead = pHead->next;
		pTail = pTail->next;
	}
	return pTail;
}

//快速删除给定节点
ListNode* deleteNode(ListNode* head, ListNode* todelete)
{
	todelete->val = todelete->next->val;
	todelete->next = todelete->next->next;

	return head;
}

int main()
{
	ListNode* head = new ListNode(0);
	createList(head);
	printL(head);

	head = reverseKGroup(head, 2);
	printL(head);

	head = reverseAll(head);
	printL(head);

	ListNode* kNode;
	kNode = findLastKthNode(head, 2);
	printL(kNode);

	head = deleteNode(head, kNode);
	printL(head);
}





