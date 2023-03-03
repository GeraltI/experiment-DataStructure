#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

//Todo
//需要返回一个数组，数组元素是原始数组里最大的k个数
//注意按照从小到大的顺序排序
//可以自行添加其他辅助函数,可以根据实际需要修改函数参数
int *solve2(int arr[],int k,int N){
    int *res;
    int i;
    for(i=0;i<k;i++)
    {
        res[i]=arr[N-k+i+1];
    }
    return res;
}

#include <stdio.h>
#include <malloc.h>
void HeapAdjust(int a[],int head,int N)//一次筛选的过程
{
    int k,i;
    k=a[head];
    for(i=2*head;i<=N;i=i*2)//通过循环沿较大的孩子结点向下筛选
    {
        if(i<N&&a[i]<a[i+1])
        {
            i++;//j为较大的数组记录的下标
        }
        if(k>a[i])
        {
            break;
        }
        a[head]=a[i];
        head=i;
    }
    a[head]=k;//插入pivot
}
void HeapSort(int a[],int N)
{
    int temp,i;
    for(i=N/2;i>0;i--)//通过循环初始化最大顶堆
    {
        HeapAdjust(a,i,N);
    }
    for(i=N;i>0;i--)
    {
        temp=a[1];
        a[1]=a[i];
        a[i]=temp;//将堆顶数组记录与未排序的最后一个数组记录交换
        HeapAdjust(a,1,i-1);//重新调整为最大顶堆
    }
}

void test2(){
	int caseNum; //表示测试轮数
	if (freopen("5_2_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_2_input_5.in");
    }
	scanf("%d", &caseNum);
    int case1 = 0;
    for (; case1 < caseNum; case1++) {
		int k, N;
        scanf("%d%d", &k, &N);
        int arr[MAX];
        int i = 1;
        for (; i <=N; i++) {
            scanf("%d", &arr[i]);
        }
        int *res;
        HeapSort(arr,N);
		res = solve2(arr,k,N);
		printf("\n==== Case %d ====\n", case1 + 1);
        for (i = 0; i < k; i++) {
            printf("%d ",res[i]);
        }
    }
	fclose(stdin);
}


int main(void) {
    test2();
    return 0;
}
