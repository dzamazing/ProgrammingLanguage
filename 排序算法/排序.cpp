#include<iostream>

using namespace std;

//注：本文件下的所有排序函数，基本都未在函数开头进行参数异常判断，实际中应添加进去

//排序算法分类：（1）插入排序：直接插入排序        稳定   时间：n n^2 n^2         空间：1
                             //希尔（shell）排序   不稳定 时间：n n^1.5 n^2       空间：1
              //（2）选择排序：直接选择排序        不稳定 时间：n^2 n^2 n^2       空间：1
                             //堆排序              不稳定 时间：nlogn nlogn nlogn 空间：1
              //（3）交换排序：冒泡排序            稳定   时间：n n^2 n^2         空间：1
                             //快速排序            不稳定 时间：nlogn nlogn n^2   空间：nlogn
              //（4）归并排序                      稳定   时间：nlogn nlogn nlogn 空间：n

//属性含义：稳定性 最优时间复杂度 平均时间复杂度 最坏时间复杂度 空间复杂度

//交换两个数
void swap(int& a, int& b)
{
	int temp = b;
	b = a;
	a = temp;
}

//冒泡排序
//思想：1、比较相邻的元素。如果第一个比第二个大，就交换他们两个。
      //2、对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
      //3、针对所有的元素重复以上的步骤，除了最后一个。
      //4、持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
//属性：稳定 时间：n n^2 n^2 空间：1
void Bubble_Sort(int *list, int count)
{
	int end;
	for (int i = 0; i < count-1 ; ++i) {
		end = count - 1 - i;
		for (int j = 0; j < end; ++j)
			if (list[j] > list[j + 1])  //因为这里会有j+1,所以判断条件为count-1
				swap(list[j], list[j + 1]);
	}
}
//冒泡排序的优化版本，这个版本才能体现冒泡排序的最优随时间复杂度为o(n)
void Bubble_Sort_Plus(int *list, int count)
{
	bool didSwap;  //用来标记是否有进行过交换操作
	int end;
	for (int i = 0; i < count - 1; i++) {
		didSwap = false;
		end = count - 1 - i;
		for (int j = 0; j < end; ++j)
		{
			if (list[j] > list[j + 1]) {
				swap(list[j], list[j + 1]);
				didSwap = true;
			}
		}
		//如果没有进行过交换操作，说明顺序已经是排好了的
		if (didSwap == false)
			return;
	}

}

//直接选择排序
//思想：第一次从R[0]~R[n-1]中选取最小值，与R[0]交换，
      //第二次从R[1]~R[n-1]中选取最小值，与R[1]交换，....，
      //第i次从R[i-1]~R[n-1]中选取最小值，与R[i-1]交换，.....，
      //第n-1次从R[n-2]~R[n-1]中选取最小值，与R[n-2]交换，总共通过n-1次，
      //得到一个按排序码从小到大排列的有序序列
//属性： 不稳定 时间：n^2 n^2 n^2 空间：1
void Select_Sort(int *list, int count)
{
	int min;
	for (int i = 0; i < count-1; i++)
	{
		min = i;
		for (int j = i + 1; j < count; j++)
		{
			if (list[min] > list[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(list[i], list[min]);
		}
	}
}

//直接插入排序
//思想：把n个待排序的元素看成一个有序表和一个无序表，开始时有序表中只有一个元素，无序表中有n-1个元素；
      //排序过程即每次从无序表中取出第一个元素，将它插入到有序表中，使之成为新的有序表，重复n-1次完成整个排序过程。
//属性：稳定 时间：n n^2 n^2 空间：1
void Insert_Sort(int *list, int count)
{
	int temp; //此处充当哨兵，不在list数组里面独占一个单位
	int i, j;
	//第一个for循环对从第二个开始的所有的数字遍历，
	//嵌套的for循环是每次遍历数字时都取无序区的一个元素与有序区的元素比较，
	//如果比有序区的要小则交换，直到合适的位置
	for (i = 1; i < count; i++)
	{
		temp = list[i];  //从无序区中取一个元素
		//将该元素插入到有序区的正确位置
		for (j = i - 1; list[j] > temp&&j >= 0; j--)
		{
			list[j + 1] = list[j];  //只要没找到合适的插入位置，就将有序表中的元素依次往后移一位
		}
		list[j + 1] = temp;
	}
}
//直接插入排序的另一种实现
void Insert_Sort_Plus(int *list, int count)
{
	for (int i = 1; i < count; ++i)
	{
		for (int j = i; j > 0; --j)  //取无序区的第一个元素与有序区元素进行比较
		{
			if (list[j] < list[j - 1])
				swap(list[j], list[j - 1]);
		}
	}
}

//希尔（shell）排序
//思想：（1）希尔排序（shell sort）这个排序方法又称为缩小增量排序，是1959年D·L·Shell提出来的。该方法的基本思想是：
           //设待排序元素序列有n个元素，首先取一个整数increment（小于n）作为间隔将全部元素分为increment个子序列，
           //所有距离为increment的元素放在同一个子序列中，在每一个子序列中分别实行直接插入排序。
           //然后缩小间隔increment，重复上述子序列划分和排序工作。
           //直到最后取increment = 1，将所有元素放在同一个子序列中排序为止。
      //（2）由于开始时，increment的取值较大，每个子序列中的元素较少，排序速度较快，到排序后期increment取值逐渐变小，
           //子序列中元素个数逐渐增多，但由于前面工作的基础，大多数元素已经基本有序，所以排序速度仍然很快。

//属性：不稳定 时间：n n^1.5 n^2 空间：1
void Shell_Sort(int *list, int count)
{
	int i, j;
	int temp;
	int increment = count;

	do {
		increment = increment / 3 + 1;    //更新增量
		for (i = increment; i < count; i++)   //对每个划分进行直接插入排序
		{
			if (list[i] < list[i - increment])//从无序区取一个元素，插入到对应子序列中的合适位置
			{
				temp = list[i];
				for (j = i - increment; j >=0 && list[j] > temp; j -= increment)
				{
					list[j + increment] = list[j];
				}
				list[j + increment] = temp;
			}
		}
	} while (increment > 1);
}

//堆排序（大顶堆）
//参考博客：https://www.cnblogs.com/0zcl/p/6737944.html
//大顶堆概念：堆分为最大堆和最小堆，其实就是完全二叉树。
            //最大堆要求节点的元素都要不小于其孩子，最小堆要求节点元素都不大于其左右孩子，
            //两者对左右孩子的大小关系不做任何要求，其实很好理解。
            //有了上面的定义，我们可以得知，处于最大堆的根节点的元素一定是这个堆中的最大值。
//思想：1.将初始待排序关键字序列(R1,R2....Rn)构建成大顶堆，此堆为初始的无序区
      //2.将堆顶元素R[1]与最后一个元素R[n]交换，此时得到新的无序区(R1, R2, ......Rn - 1)和新的有序区(Rn)
      //3.由于交换后新的堆顶R[1]可能违反堆的性质，因此需要对当前无序区(R1, R2, ......Rn - 1)调整为新堆，
        //然后再次将R[1]与无序区最后一个元素交换，得到新的无序区(R1, R2....Rn - 2)和新的有序区(Rn - 1, Rn)。
        //不断重复此过程直到有序区的元素个数为n - 1，则整个排序过程完成
//核心思想：每次都取堆顶的元素，将其放在序列最后面，然后将剩余的元素重新调整为最大堆，依次类推，最终得到排序的序列。
//属性：不稳定 时间：nlogn nlogn nlogn 空间：1
void Heap_Adjust(int *list, int s, int m)      //调整为一个堆
{
	int temp = list[s];
	for (int j = 2 * s + 1; j <= m; j = 2 * j + 1)
	{
		if (list[j] < list[j + 1] && j < m)   //如果左子节点小于右子节点，则将目标节点定为右子节点
		{
			j++;
		}
		if (temp > list[j]) //将当前的堆顶元素与其子节点中较大的值进行比较，若根节点的值大于左右孩子节点的值，则循环结束
			break;          //因为每次调整堆的原因只是原先的根节点与无序表的最后一个节点交换了而已，其他部分都是满足堆条件的
		list[s] = list[j];  //将较大值移至根节点处
		s = j;     //检查此次节点交换后对后面部分的堆性质是否产生了破坏 
	}
	list[s] = temp;
}
void Heap_Sort(int *list, int len)
{
	//利用数组构建最大堆，其中子节点=父节点*2+1。
	//先对前半部分进行倒序找出最大点，然后遍历交换首尾、找出最大点
	
	//创建一个大顶堆
	for (int s = len / 2 - 1; s >= 0; s--)
	{
		Heap_Adjust(list, s, len - 1);
	}

	//排序
	for (int i = len - 1; i >= 1; i--)
	{
		swap(list[0], list[i]);
		Heap_Adjust(list, 0, i - 1);
	}
}

//归并排序
//思想：是建立在归并操作上的一种有效的排序算法,该算法是采用分治法的一个非常典型的应用。
      //将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。
      //若将两个有序表合并成一个有序表，称为二路归并。
//归并操作的工作原理如下：
      //第一步：申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
      //第二步：设定两个指针，最初位置分别为两个已经排序序列的起始位置
      //第三步：比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
      //重复步骤3直到某一指针超出序列尾
      //将另一序列剩下的所有元素直接复制到合并序列尾
//属性：稳定 时间：nlogn nlogn nlogn 空间：n
//正常情况下归并排序的空间复杂度为O(n),但可以做到空间复杂度为O(1),但那样的话时间复杂度将会是O（n^2）
void Merge(int *list,int *reg, int start, int end)
{
	if (start >= end)
		return;
	int mid = start + (end - start) / 2;
	int i, j, k;
	i = start;
	j = mid +1;
	k = 0;

	while (i <= mid&&j <= end)
	{
		if (list[i] <= list[j])
			reg[k++] = list[i++];
		else
			reg[k++] = list[j++];
	}

	while (i <= mid)
		reg[k++] = list[i++];
	while (j <= end)
		reg[k++] = list[j++];

	for (int i = 0; i < k; i++)
		list[start + i] = reg[i];
}
void MSort(int *list, int *reg, int start, int end)
{
	if (start < end)
	{
		int mid = start + (end - start ) / 2;   //避免溢出int
		MSort(list, reg, start, mid);           //对左边进行排序
		MSort(list, reg, mid + 1, end);         //对右边进行排序
		Merge(list, reg, start, end);           //把排序好的数据合并
	}
}
void Merge_Sort(int *list, int count)
{
	int *reg = new int[count];
	MSort(list,reg, 0, count - 1);
	delete[] reg;
}

//快速排序
//思想：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，
      //然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
      //实现快速排序算法的关键在于先在数组中选择一个数字，接下来把数组中中的数字分成两个部分，
      //比选择数字小的数字移到数组的左边，比选择数字大的数字移到数组的右边
//属性：不稳定 时间：nlogn nlogn n^2 空间：nlogn
int Partition(int *list, int low, int high)
{
	int pivotKey;   //轴心点
	pivotKey = list[low];
	while (low < high)
	{
		while (low < high&&list[high] >= pivotKey)
		{
			high--;
		}
		swap(list[low], list[high]);  //将pivotKey移动到从后往前第一个比它小的位置，此时high后面的数组元素都大于pivotKey
		while (low < high&&list[low] <= pivotKey)
		{
			low++;
		}
		swap(list[low], list[high]);  //将pivotKey移动到从前往后第一个比它大的位置，此时low前面的数组元素都小于pivotKey

		//每一轮循环结束都将low到high之间的范围缩小，直至low>=high,pivotKey的筛选过程完成
	}
	return low;  //返回轴心点最终移动到的位置

}
void QSort(int *list, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(list, low, high);
		QSort(list, low, pivot - 1);
		QSort(list, pivot + 1, high);
	}
}
void Quick_Sort(int *list, int count)
{
	QSort(list, 0, count - 1);
}

int main()
{
	//测试数据1
	int TestData1[] = { 11,2,5,4,1,3,9,7,8,6,11,10 };
	int count1 = sizeof(TestData1) / sizeof(int);

	//测试数据2
	int TestData2[] = { 88, 4419, 10584, 452, 996650, 6754, 957, 239, 91700, 9405,
		                8560, 807347, 20205, 957730, 195132, 171, 45249, 729108, 
		                856, 6264, 713998, 558, 2726, 17671, 39225, 333, 27534, 79588, 
		                19111, 62133, 314, 296433, 940, 19684, 222752, 741, 7009, 7240,
		                49455, 9348, 103829, 384565, 1749, 177, 497, 3953, 649, 46593, 
		                2630, 245, 270603, 297637, 99204, 99867, 89431, 3986, 99454,
		                8089, 934666, 434, 983492, 39929, 6769, 955109, 65704, 18568,
		                76695, 6435, 5578, 744, 13680, 139812, 775563, 93104, 99663, 
		                322628, 6592, 12941, 403547, 619774, 5506, 1515, 72955, 9755,
		                728165, 78168, 1485, 94370, 7373};
	int count2 = sizeof(TestData2) / sizeof(int);

	////冒泡排序测试
	//Bubble_Sort(TestData1, count1);
	//Bubble_Sort(TestData2, count2);
	////优化版的冒泡排序测试
	//Bubble_Sort_Plus(TestData1, count1);
	//Bubble_Sort_Plus(TestData2, count2);

	////直接选择排序测试
	//Select_Sort(TestData1, count1);
	//Select_Sort(TestData2, count2);

	////直接插入排序实现一测试
	//Insert_Sort(TestData1, count1);
	//Insert_Sort(TestData2, count2);
	////直接插入排序实现二测试
	//Insert_Sort_Plus(TestData1, count1);
	//Insert_Sort_Plus(TestData2, count2);

	////希尔排排序测试
	//Shell_Sort(TestData1, count1);
	//Shell_Sort(TestData2, count2);

	////堆排序测试
	//Heap_Sort(TestData1, count1);
	//Heap_Sort(TestData2, count2);

	//归并排序测试
	Merge_Sort(TestData1, count1);
	Merge_Sort(TestData2, count2);

	////快速排序测试
	//Quick_Sort(TestData1, count1);
	//Quick_Sort(TestData2, count2);

	//打印测试数据1排序后的数组
	cout << "TestData1 result: " << endl;
	for (int i = 0; i < count1; ++i)
		cout << TestData1[i] << " ";
	cout << endl;

	//打印测试数据2排序后的数组
	cout << "TestData2 result: " << endl;
	for (int i = 0; i < count2; ++i)
		cout << TestData2[i] << " ";
	cout << endl;

	//防止窗口闪退
	int rest;
	cin >> rest;
	return 0;
}