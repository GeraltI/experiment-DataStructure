#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // ���ڴ洢��ţ������

//Todo
//��Ҫ������λ����ţ��������
//�����������������������,�����޸Ĵ��ε�����
int solve1(int *a, int start, int end){
    if(start>end)//��ָ��λ�ñ��������ָ��λ��
    {
        return ;
    }
    //����tmpΪ��׼�����ڴ˹涨��׼��Ϊ���еĵ�һ����������ָ��ָ�����
    int temp=a[start];
    int i=start;
    int j=end;
    while (i != j)//��ѭ����ֱ����ָ�����ָ�����ʱ�˳�
    {
        while(a[j]>=temp &&j>i)//��ѭ��1��Ѱ�ҵ��Ȼ�׼��С����ʱ�˳�ѭ������ѭ��������ָ��
        {
            j--;
        }
        while(a[i]<=temp &&j>i)//��ѭ��2��Ѱ�ҵ��Ȼ�׼�������ʱ�˳�ѭ������ѭ��������ָ��
        {
            i++;
        }
        if(j>i)//����ǰ�ж���ָ���Ƿ������ָ��
        {
            int t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }//��ѭ��β
    a[start]=a[i];//ִ����ѭ���󣬾��ҵ���pivot������λ�ã�����׼��temp��iλ�ý��н���
    a[i]=temp;
    solve1(a,start,i-1);
    solve1(a,i+1,end);
    return a[end/2];
}

void test1(){
    int caseNum; //��ʾ��������
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
