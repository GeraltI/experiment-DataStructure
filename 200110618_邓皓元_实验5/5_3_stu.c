#include <stdio.h>
#include <stdlib.h>

//对起始时间与终止时间进行排序，参数可自行填写
void sort(int *a, int start, int end){
    if(start>end)//左指针位置必须大于右指针位置
    {
        return;
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
    sort(a,start,i-1);
    sort(a,i+1,end);
}

//计算空闲人数最多的起始时间和终止时间，参数可自行填写
void findPeriod(int *start,int *end,int M){
    int a[1002],b[1002],c[1002],d[1002],change[1002],num[1002];
    int maxtime[1002][2];
    int i,j,k,maxnum;
    for(i=1;i<=M;i++)
    {
        a[i]=start[i];//将a数组赋值start
        b[i]=end[i];//将b数组赋值了end
        c[i]=start[i];
    }
    sort(a,1,M);//将赋值了start的a数组排序
    sort(b,1,M);//将赋值了end的b数组排序
    for(i=M+1,j=1;i<=2*M;i++,j++)
    {
        c[i]=end[j];//构造c数组
    }
    sort(c,1,2*M);
    i=1;
    j=1;
    d[j]=c[i];//第一位赋值
    i++;
    while(i<=2*M)//得到start和finish中出现的所有时间点，不重复出现，有序
    {
        if(d[j]!=c[i])
        {
            j++;
            d[j]=c[i];
        }
        i++;
    }
    int length;//记录不重复时间点个数
    length=j;
    for(i=0;i<=length;i++)
    {
        change[i]=0;
    }
    for(i=j=k=1;i<=length;i++)
    {
        while(d[i]==a[j]&&j<=M)//计算每个时间点的人数变化
        {
            change[i]++;
            j++;
        }
        while(d[i]==b[k]&&k<=M)//计算每个时间点的人数变化
        {
            change[i+1]--;
            k++;
        }
    }
    num[1]=change[1];
    for(i=2;i<=length;i++)//计算每个时间点的人数
    {
        num[i]=num[i-1]+change[i];
    }
    maxnum=0;
    for(i=1;i<=length;i++)//寻找时间点人数最多的是多少人
    {
        if(maxnum<=num[i])
        {
            maxnum=num[i];
        }
    }
    j=0;
    for(i=1;i<=length;i++)//记录时间点人数最多的时间点
    {
        if(num[i]==maxnum)
        {
            maxtime[j][0]=d[i];
            maxtime[j][1]=d[i];
            j++;
        }
    }
    int length2;
    length2=j;
    int flag[length2][M+1];
    int maxtime2[length2][2];
    for(i=0;i<length2;i++)
    {
        for(j=1;j<=M;j++)
        {
            flag[i][j]=0;//初始化flag数组
        }
    }
    for(i=0;i<length2;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(start[j]<=maxtime[i][0]&&end[j]>=maxtime[i][1])
            {
                flag[i][j]=1;//赋值flag数组，若是时间段符合则赋值为1
            }
        }
    }
    int x;
    int length3;
    length3=0;
    for(i=0;i<length2;i++)
    {
        x=0;//标志是否有两个时间组合
        if(maxtime[i+1][1]-maxtime[i][1]==1&&i+1<length2)
        {
            x=1;
            for(j=1;j<=M;j++)
            {
                if(flag[i][j]!=flag[i+1][j])
                {
                    x=0;//若有时间段不符合则x=0
                }
            }
            if(x==1)
            {
                maxtime[i+1][0]=maxtime[i][0];
            }
        }
        if(x==0)//若无两个时间段组合则记录数据
        {
            maxtime2[length3][0]=maxtime[i][0];
            maxtime2[length3][1]=maxtime[i][1];
            length3++;
        }
    }
    for(i=0;i<length3;i++)//打印组合后时间段
    {
        printf("%d %d",maxtime2[i][0],maxtime2[i][1]);
        if(i!=length3-1)
        {
            printf(",");
        }
    }
    printf("\n");
}

int main()
{
   int N, M; //分别存储时间的段数和学生的个数
   int caseNum = 0;
   int start[1002];
   int end[1002];

   if (freopen("5_3_input.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_3_input.in");
    }

   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 1; i <=M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       findPeriod(start, end, M);
   }
   fclose(stdin);
   /* 终端输入
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M);
   }
   */
}
