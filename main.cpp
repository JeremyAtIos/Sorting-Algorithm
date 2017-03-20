#include <iostream>
#include <time.h>

using namespace std;

//冒泡排序，O(n^2)
void BubbleSort(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

//选择排序，O(n^2)
void SelectionSort(int a[], int n) {
    for (int i = 0; i < n; ++i) {

        //从未排序的序列中找到最小的元素
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[min])
                min = j;
        }

        //将最小的元素与未排序序列第一个元素交换
        if (min != i) {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

//插入排序
void InsertSort(int a[], int n, int inc, int group) {
    for (int i = group + inc; i < n; i += inc) {

        //如果后者比前者大，则不需要调整
        if (a[i] > a[i - inc]) continue;

        //从已排序序列中从后往前遍历，大于a[i]就往后移一位，否则，插入a[i]
        int temp = a[i];
        int j = i - inc;
        while (j >= 0 && a[j] > temp) {
            a[j + inc] = a[j];
            j -= inc;
        }
        a[j + inc] = temp;
    }
}

//希尔排序
void ShellSort(int a[], int n) {

    //增量从数组长度的一半开始，每次除以2，直到为1就结束
    for (int inc = n / 2; inc > 0; inc /= 2) {

        //根据增量分组，然后对每一个组进行一次插入排序
        for (int i = 0; i < inc; ++i) {
            InsertSort(a, n, inc, i);
        }
    }
}

//归并排序

void MS_Merge(int a[], int temp[], int start, int middle, int end) {

    //如果右边最小数都比左边最大数大，直接返回
    if (a[middle + 1] >= a[middle]) return;

    //遍历左右两边序列，小的先插入temp
    int i = start, j = middle + 1, k = 0;
    while (i <= middle && j <= end) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    //剩下的插入temp
    while (i <= middle) temp[k++] = a[i++];
    while (j <= end) temp[k++] = a[j++];

    //将temp中的数据复制到原序列中
    for (int l = 0; l < k; ++l)
        a[start + l] = temp[l];
}

void MS_Recursion(int a[], int temp[], int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        MS_Recursion(a, temp, start, middle);
        MS_Recursion(a, temp, middle + 1, end);
        MS_Merge(a, temp, start, middle, end);
    }
}

void MergeSort(int a[], int n) {
    //用于复用的临时数组
    int *temp = (int *)malloc(sizeof(int) * n);

    //递归调用
    MS_Recursion(a, temp, 0, n - 1);

    //释放指针
    free(temp);
}

//快速排序
void QuickSort() {

}

int main() {
    int n = 18;
    int a[] = {91, 75, 43, 6, 110, 73, 5, 12, 98, 189, 52, 73, 12, 0, 2, 79, 04, 89};
    MergeSort(a, n);
    for (int i = 0; i < n; ++i) {
        cout<<a[i]<<endl;
    }

    return 0;
}