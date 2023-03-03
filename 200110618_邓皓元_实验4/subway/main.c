#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[1000];
typedef struct {
    int N, E;//N�Ƕ�������E�Ǳ���
    int **matrix;//�����ڽӾ���
    vextype *vertex;//�洢�ڵ�����
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *path, Graph g,char pname[][20]);

Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

void printPath(int d, int *path, Graph g,char pname[][20])
{
    int k = 0;
    int path_length = 0;
    printf("·��: ");
    do {
        printf("%s->", pname[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", pname[path[k]]);
}

int isConnected(Graph g) {
    int temp[g.N][g.N];//���Ӿ���
    int i,j,k;
    int flag=1;//����ֵ
    for(i=0;i<g.N;i++)//�����Ӿ������Խ��ߺʹ��ڵı���1
    {
        for(j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis)
            {
                temp[i][j]=1;
            }
            else
            {
                temp[i][j]=0;
            }
        }
    }
    for(i=0;i<g.N;i++)//����˷�
    {
        for(j=0;j<g.N;j++)
        {
            if(temp[i][j]==1)
            {
                for(k=0;k<g.N;k++)
                {
                    if(temp[k][i]==1)
                    {
                        temp[k][j]=1;//����˳ɹ���ֵ1
                    }
                }
            }
        }
    }
    for(i=0;i<g.N;i++)
    {
        for(j=0;j<g.N;j++)
        {
            if(temp[i][j]==0)//ֻҪtemp��������һ��Ԫ�ز�Ϊ1��flag=0
            {
                flag=0;
            }
        }
    }
    return flag;
}

void nodeDegree(Graph g, int *node_degree) {
    int i,j,count;
    for(i=0;i<g.N;i++)
    {
        count=0;//��count����ÿ���ڵ�Ķ�
        for(j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis&&g.matrix[i][j]!=0)
            {
                count++;//������һ������ýڵ����ӣ���count++
            }
        }
        node_degree[i]=count;
    }
}

double clusteringCoefficient(Graph g) {
    int i,j,k;
    int count;//���ÿ���ڵ�Ķ�,����data�������ݴ��
    int COUNT;//����������������Ľڵ�֮�������ı���
    double Clustering_coefficient[g.N];//���ÿ���ڵ�ľ���ϵ��
    double sum=0;//������нڵ����ϵ��֮��
    int data[g.N];//����������������Ľڵ�
    for(i=0;i<g.N;i++)
    {
        count=0;
        for(j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis&&g.matrix[i][j]!=0)
            {
                data[count]=j;//����������������Ľڵ�
                count++;//������һ������ýڵ����ӣ���count++
            }
        }
        COUNT=0;
        for(j=0;j<count;j++)
        {
            for(k=0;k<j;k++)
            {
                if(g.matrix[data[j]][data[k]]!=max_dis&&g.matrix[data[j]][data[k]]!=0)
                {
                    COUNT++;//����������������Ľڵ�֮�������ı���
                }
            }
        }
        if(count>1)
        {
            Clustering_coefficient[i]=(double)2*COUNT/count/(count-1);
        }
        else
        {
            Clustering_coefficient[i]=0;//countС�ڵ���1ʱ����ϵ��Ϊ0
        }
    }
    for(i=0;i<g.N;i++)
    {
        sum=sum+Clustering_coefficient[i];
    }
    return sum/g.N;
}

int dijkstra(Graph g, int start, int end, int *path)
{
    int pathlength[g.N];//����̰���㷨�������·�������
    int flag[g.N];//�����жϽڵ��Ƿ�ȷ��
    int pre[g.N];//������¼·��
    int i,j,k,m;
    int sum=1;//�ж�ѭ�����е�����
    int temp;//Ѱ����һ����Ҫȷ���Ľڵ�
    temp=max_dis;
    for(i=0;i<g.N;i++)
    {
        pathlength[i]=g.matrix[start][i];
        flag[i]=1;
        pre[i]=-1;
        if(g.matrix[start][i]!=max_dis&&g.matrix[start][i]!=0)
        {
            pre[i]=start;
        }
    }
    flag[start]=0;
    while(sum!=0)
    {
        temp=max_dis;
        for(i=0;i<g.N;i++)
        {
            if(flag[i]==1&&pathlength[i]<=temp)//�ҵ����·���Ҹýڵ�δȷ��
            {
                temp=pathlength[i];
                k=i;
            }
        }
        flag[k]=0;//ȷ���Ľڵ�
        for(i=0;i<g.N;i++)
        {
            if(g.matrix[k][i]!=max_dis&&g.matrix[k][i]!=0&&temp+g.matrix[k][i]<pathlength[i])
            {
                pathlength[i]=temp+g.matrix[k][i];
                pre[i]=k;
            }
        }
        sum=0;
        for(i=0;i<g.N;i++)
        {
            sum=sum+flag[i];//�ж�ѭ�����е�������ֱ�����е㱻ȷ��
        }
    }
    k=end;
    j=1;
    while(k!=start)
    {
        k=pre[k];//ǰ��������
        j++;
    }
    k=end;
    for(i=j-1;i>=0;i--)
    {
        path[i]=k;
        k=pre[k];
    }
    return pathlength[end];
}

void computeEcc(Graph g, int *diameter, int *radius)
{
    int floyd[g.N][g.N];//���ڼ���ľ���
    int i,j,k;
    int Eccentricity[g.N];
    *diameter=0;
    *radius=max_dis;
    for(i=0;i<g.N;i++)
    {
        Eccentricity[i]=0;
        for(j=0;j<g.N;j++)
        {
            floyd[i][j]=g.matrix[i][j];//�����ڽӾ���
        }
    }
    for(k=0;k<g.N;k++)
    {
        for(i=0;i<g.N;i++)
        {
            for(j=0;j<g.N;j++)
            {
                if(floyd[i][k]+floyd[k][j]<floyd[i][j])//floyd�㷨
                {
                    floyd[i][j]=floyd[i][k]+floyd[k][j];//floyd�㷨
                }
            }
        }
    }
    for(i=0;i<g.N;i++)
    {
        for(j=0;j<g.N;j++)
        {
            if(floyd[i][j]>Eccentricity[i])
            {
                Eccentricity[i]=floyd[i][j];//����ÿ��������ڵ����
            }
        }
    }
    for(i=0;i<g.N;i++)
    {
        if(Eccentricity[i]>*diameter)
        {
            *diameter=Eccentricity[i];//���Ϊֱ��
        }
        if(Eccentricity[i]<*radius)
        {
            *radius=Eccentricity[i];//��СΪ�뾶
        }
    }
}

int main() {
    char str1[20]="��ѧ��";
    char str2[20]="����";
    int node_num;
    int edge_num;
    int line_num;
    int max;
    int maxnum;
    int start_idx, temp, weight;
    int start,end;
    int a;
    max=0;
    if (freopen("no2metro.txt", "r", stdin) == NULL)
    {
        printf("There is an error in reading file no2metro.txt");
    }
    scanf("%d\n",&node_num);
    char name[node_num][20];
    Graph g = createGraph(node_num);
    for(int i=0;i<node_num;i++)
    {
        scanf("%d %s\n",g.vertex[i],name[i]);
    }
    fclose(stdin);
    if (freopen("metro.txt", "r", stdin) == NULL)
    {
        printf("There is an error in reading file metro.txt");
    }
    scanf("%d\n",&node_num);
    scanf("%d\n",&line_num);
    while (scanf("%d\n",&edge_num) != EOF)
    {
        for (int i = 0; i < edge_num; i++)
        {
            scanf("%d %d\n", &start_idx, &weight);
            if(i==0)
            {
                temp=start_idx;
            }
            g.matrix[start_idx][temp] = weight;
            g.matrix[temp][start_idx] = weight;
            temp=start_idx;
        }
    }
    if(isConnected(g))
    {
        printf("����·ͼ������ͼ\n");
    }
    else
    {
        printf("����·ͼ��������ͼ\n");
    }
    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    for(int i=0;i<node_num;i++)
    {
        if(degree[i]>max)
        {
            max=degree[i];
            maxnum=i;
        }
    }
    printf("��·ͼ�л�����·����վ����:%s\n����%d����·ͨ��\n",name[maxnum],max/2);
    free(degree);
    if(isConnected(g))
    {
        for(a=0;a<node_num;a++)
        {
            if(!strcmp(str1,name[a]))
            {
                start=a;
            }
            if(!strcmp(str2,name[a]))
            {
                end=a;
            }
        }
        int *short_path = (int *)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, start, end, short_path);
        printf("�Ӵ�ѧ��վ������վ������Ҫ����ʱ��: %d\n", dis);
        printPath(dis, short_path, g,name);
        free(short_path);
        int diameter, radius;
        computeEcc(g, &diameter, &radius);
        printf("����·ͼ��ֱ��:%d\n", diameter);
        printf("����·ͼ�İ뾶:%d\n", radius);
    }
    fclose(stdin);
    return 0;
}
