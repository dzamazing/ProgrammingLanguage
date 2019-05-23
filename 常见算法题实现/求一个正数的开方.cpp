#include<iostream>

using namespace std;

//利用二分法的思想不断逼近
int sqrt(int num)
{
	if (num == 0 || num == 1)
		return num;

	long low = 0;
	long high = num;
	while (low < high)
	{
		long mid = (low + high) / 2;
		if (low == mid)
			return (int)mid;
		else if (mid*mid - num > 0)
			high = mid;
		else if (mid*mid - num < 0)
			low = mid;
		else
			return (int)mid;
	}

	return 0;
}

int main()
{
	int num;
	cin >> num;
	cout << sqrt(num) << endl;

	return 0;
}