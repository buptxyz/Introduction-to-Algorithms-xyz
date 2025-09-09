#include <iostream>
using namespace std;
const int MAXN = 1000;
int arr[MAXN];

void counting_sort(int n)
{
	int min_value = 0x3f3f3f3f, max_value = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max_value)
			max_value = arr[i];
		if (arr[i] < min_value)
			min_value = arr[i];
	}
	int len = max_value - min_value + 1;
	int* bucket = new int[len]();
	for (int i = 0; i < n; i++)
	{
		bucket[arr[i] - min_value]++;
	}
	for (int i = 0, j = 0; i < len; i++)
	{
		while (bucket[i] != 0)
		{
			arr[j++] = i + min_value;
			bucket[i]--;
		}
	}
	delete bucket;
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
	counting_sort(n);
	cout << "排序后：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
