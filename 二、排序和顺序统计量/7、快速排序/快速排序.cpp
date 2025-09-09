#include <iostream>

int Paritition1(int A[], int low, int high)
{
    int pivot = A[low];
    while (low < high)
    {
        while (low < high && A[high] >= pivot)
        {
            --high;
        }
        A[low] = A[high];
        while (low < high && A[low] <= pivot)
        {
            ++low;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

/*
  int Paritition2(int A[], int low, int high) {
  int pivot = A[high];
  int i = low - 1;
  for(int j = low; j < high; j++)
  {
      if(A[j] <= pivot)
      {
          i++;
          std::swap(A[i], A[j]);
      }
  }
   std::swap(A[i + 1], A[high]);
   return i + 1;
}
*/

void QuickSort(int A[], int low, int high) // 快排母函数
{
    if (low < high)
    {
        int pivot = Paritition1(A, low, high);
        QuickSort(A, low, pivot - 1);
        QuickSort(A, pivot + 1, high);
    }
}

void PrintArray(int A[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int A[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int n = sizeof(A) / sizeof(A[0]);
    std::cout << "原数组: ";
    PrintArray(A, n);
    QuickSort(A, 0, n - 1);
    std::cout << "排序后: ";
    PrintArray(A, n);
    return 0;
}