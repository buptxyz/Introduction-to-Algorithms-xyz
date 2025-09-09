#include <iostream>
#include <queue>
using namespace std;
const int MAXN = 1000;
int arr[MAXN];
queue<int> q[10];

void radix_sort(int n)
{
	//获取最大值的位数
	int max_value = 0;
	for (int i = 0; i < n; i++)
	{
		if (max_value < arr[i])
			max_value = arr[i];
	}
	int max_digit = 0;
	while (max_value)
	{
		max_digit++;
		max_value /= 10;
	}
	//开始排序
	int mod = 10, dev = 1;
	for (int i = 0; i < max_digit; i++, mod *= 10, dev *= 10)
	{
		for (int j = 0; j < n; j++)
		{
			int ix = arr[j] % mod / dev;
			q[ix].push(arr[j]);
		}
		int pos = 0;
		for (int j = 0; j < 10; j++)
		{
			while (!q[j].empty())
			{
				arr[pos++] = q[j].front();
				q[j].pop();
			}
		}
	}
}

int main()
{
	int n;
	cout << "请输入数组中元素的个数：";
	cin >> n;
	cout << "请输入元素: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	cout << "排序前：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	radix_sort(n);
	cout << "排序后：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
