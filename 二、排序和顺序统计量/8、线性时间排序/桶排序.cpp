#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1000;
const int BUCKET_SIZE = 10;//默认每个桶的范围
int arr[MAXN];

void insert_sort(vector<int> &v){
	int len=v.size(),temp,i,j;
	for(i=1;i<len;i++){
		temp = v[i];
		for(j=i;j>0 && v[j-1]>temp;j--){
			v[j]=v[j-1];
		}
		v[j]=temp;
	}
}

void bucket_sort(int n){
	int min_value = 0x3f3f3f3f, max_value = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max_value)
			max_value = arr[i];//获取输入数据的最大值
		if (arr[i] < min_value)
			min_value = arr[i];//获取输入数据的最小值
	}
	//桶的初始化
	int len = (max_value-min_value)/BUCKET_SIZE+1;
	vector<int> bucket[len];
	//将数据分配到桶
	for(int i=0;i<n;i++){
		bucket[(arr[i]-min_value)/BUCKET_SIZE].push_back(arr[i]);
	}
	for(int i=0,j=0;i<len;i++){
		//这里建议使用插入排序或者计数排序。当然也可以使用堆排序，快速排序等等
		insert_sort(bucket[i]);
		for(auto x:bucket[i]){
			arr[j++]=x;
		}
	}
}

int main(){
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
	bucket_sort(n);
	cout << "排序后：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
