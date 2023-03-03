#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // 用于存储奶牛产奶量

//Todo
//需要返回中位数奶牛产奶量。
//可以自行添加其他辅助函数,可以修改传参的数量
int solve1(int *a, int start, int end){
    if(start>end)//左指针位置必须大于右指针位置
    {
        return ;
    }
    //变量tmp为基准数，在此规定基准数为序列的第一个数，即左指针指向的数
    int temp=a[start];
    int i=start;
    int j=end;
    while (i != j)//外循环，直到左指针和右指针相等时退出
    {
        while(a[j]>=temp &&j>i)//内循环1，寻找到比基准数小的数时退出循环，此循环控制右指针
        {
            j--;
        }
        while(a[i]<=temp &&j>i)//内循环2，寻找到比基准数大的数时退出循环，此循环控制左指针
        {
            i++;
        }
        if(j>i)//交换前判断右指针是否大于左指针
        {
            int t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }//外循环尾
    a[start]=a[i];//执行完循环后，就找到了pivot的排序位置，将基准数temp与i位置进行交换
    a[i]=temp;
    solve1(a,start,i-1);
    solve1(a,i+1,end);
    return a[end/2];
}

void test1(){
    int caseNum; //表示测试轮数
    int n;
    int ans[N];
    if (freopen("5_1_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_1_input_5.in");
    }
    scanf("%d", &caseNum);
    for (int case1 = 0; case1 < caseNum; case1++) {
        printf("==== Case %d ====\n", case1 + 1);
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        ans[case1] = solve1(a,0,n-1);
        printf("%d\n", ans[case1]);
        printf("\n");
    }
    fclose(stdin);
}

int main() {
    test1();
    return 0;
}
