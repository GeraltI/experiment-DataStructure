#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[1000];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的序号
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
    printf("路径: ");
    do {
        printf("%s->", pname[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", pname[path[k]]);
}

int isConnected(Graph g) {
    int temp[g.N][g.N];//连接矩阵
    int i,j,k;
    int flag=1;//返回值
    for(i=0;i<g.N;i++)//将连接矩阵主对角线和存在的边置1
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
    for(i=0;i<g.N;i++)//矩阵乘法
    {
        for(j=0;j<g.N;j++)
        {
            if(temp[i][j]==1)
            {
                for(k=0;k<g.N;k++)
                {
                    if(temp[k][i]==1)
                    {
                        temp[k][j]=1;//若相乘成功则赋值1
                    }
                }
            }
        }
    }
    for(i=0;i<g.N;i++)
    {
        for(j=0;j<g.N;j++)
        {
            if(temp[i][j]==0)//只要temp矩阵中有一个元素不为1则flag=0
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
        count=0;//用count计算每个节点的度
        for(j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis&&g.matrix[i][j]!=0)
            {
                count++;//若存在一条边与该节点连接，则count++
            }
        }
        node_degree[i]=count;
    }
}

double clusteringCoefficient(Graph g) {
    int i,j,k;
    int count;//存放每个节点的度,便于data数组数据存放
    int COUNT;//存放所有与它相连的节点之间所连的边数
    double Clustering_coefficient[g.N];//存放每个节点的聚类系数
    double sum=0;//存放所有节点聚类系数之和
    int data[g.N];//存放所有与它相连的节点
    for(i=0;i<g.N;i++)
    {
        count=0;
        for(j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis&&g.matrix[i][j]!=0)
            {
                data[count]=j;//存放所有与它相连的节点
                count++;//若存在一条边与该节点连接，则count++
            }
        }
        COUNT=0;
        for(j=0;j<count;j++)
        {
            for(k=0;k<j;k++)
            {
                if(g.matrix[data[j]][data[k]]!=max_dis&&g.matrix[data[j]][data[k]]!=0)
                {
                    COUNT++;//存放所有与它相连的节点之间所连的边数
                }
            }
        }
        if(count>1)
        {
            Clustering_coefficient[i]=(double)2*COUNT/count/(count-1);
        }
        else
        {
            Clustering_coefficient[i]=0;//count小于等于1时聚类系数为0
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
    int pathlength[g.N];//运用贪心算法计算最短路径并存放
    int flag[g.N];//用来判断节点是否确定
    int pre[g.N];//用来记录路径
    int i,j,k,m;
    int sum=1;//判断循环进行的条件
    int temp;//寻找下一个需要确定的节点
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
            if(flag[i]==1&&pathlength[i]<=temp)//找到最短路径且该节点未确定
            {
                temp=pathlength[i];
                k=i;
            }
        }
        flag[k]=0;//确定的节点
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
            sum=sum+flag[i];//判断循环运行的条件：直到所有点被确定
        }
    }
    k=end;
    j=1;
    while(k!=start)
    {
        k=pre[k];//前驱点数组
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
    int floyd[g.N][g.N];//用于计算的矩阵
    int i,j,k;
    int Eccentricity[g.N];
    *diameter=0;
    *radius=max_dis;
    for(i=0;i<g.N;i++)
    {
        Eccentricity[i]=0;
        for(j=0;j<g.N;j++)
        {
            floyd[i][j]=g.matrix[i][j];//构造邻接矩阵
        }
    }
    for(k=0;k<g.N;k++)
    {
        for(i=0;i<g.N;i++)
        {
            for(j=0;j<g.N;j++)
            {
                if(floyd[i][k]+floyd[k][j]<floyd[i][j])//floyd算法
                {
                    floyd[i][j]=floyd[i][k]+floyd[k][j];//floyd算法
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
                Eccentricity[i]=floyd[i][j];//计算每个点的最大节点距离
            }
        }
    }
    for(i=0;i<g.N;i++)
    {
        if(Eccentricity[i]>*diameter)
        {
            *diameter=Eccentricity[i];//最大为直径
        }
        if(Eccentricity[i]<*radius)
        {
            *radius=Eccentricity[i];//最小为半径
        }
    }
}

int main() {
    char str1[20]="大学城";
    char str2[20]="机场";
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
        printf("该线路图是连接图\n");
    }
    else
    {
        printf("该线路图不是连接图\n");
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
    printf("线路图中换乘线路最多的站点是:%s\n共有%d条线路通过\n",name[maxnum],max/2);
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
        printf("从大学城站到机场站最少需要多少时间: %d\n", dis);
        printPath(dis, short_path, g,name);
        free(short_path);
        int diameter, radius;
        computeEcc(g, &diameter, &radius);
        printf("该线路图的直径:%d\n", diameter);
        printf("该线路图的半径:%d\n", radius);
    }
    fclose(stdin);
    return 0;
}
