#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeNode {
    int id;
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef struct ListNode {
    struct TreeNode *node; // 队列的值的类型是树节点指针
    struct ListNode *next;
} ListNode, *ListNodePtr;

typedef struct Queue {
    ListNodePtr dummyHead;
    ListNodePtr tail;
    int size;
} *QueuePtr;

// 创建链表的节点
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next) {
    ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
    curr->node = node;
    curr->next = next;
    return curr;
}

// 创建树的节点
int TreeId = 0;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right) {
    TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    curr->id = TreeId++;
    curr->val = val;
    curr->left = left;
    curr->right = right;
    return curr;
}

// 单链表队列初始化
QueuePtr InitQueue() {
    QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
    TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
    queue->size = 0;
    queue->dummyHead = createListNode(dummyTreeNode, NULL);
    queue->tail = queue->dummyHead;
    return queue;
}

// 在 queue 的尾部添加一个元素的副本
void EnQueue(QueuePtr queue, TreeNodePtr node) {
    ListNodePtr curr = createListNode(node, NULL);
    queue->tail->next = curr;
    queue->tail = queue->tail->next;
    queue->size++;
}

// 删除 queue 中的第一个元素
void DeQueue(QueuePtr queue) {
    if (queue->size == 0) {
        perror("error! the size of queue is zero when call DeQueue().");
        return;
    }
    ListNodePtr head = queue->dummyHead->next;
    queue->dummyHead->next = head->next;
    queue->size--;
    if (queue->size == 0) queue->tail = queue->dummyHead;
    free(head);
}

// 如果 queue 中没有元素, 返回 true
bool QueueEmpty(QueuePtr queue) {
    return queue->size == 0;
}

// 返回 queue 中第一个元素的引用
TreeNodePtr GetHead(QueuePtr queue) {
    if (QueueEmpty(queue)) {
        perror("error! the size of queue is zero when call front().");
        return NULL;
    } else {
        return queue->dummyHead->next->node;
    }
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

// 将输入转换为数组
void getDigits(char *buff, int *data) {
    int len = strlen(buff);
    int index = 0;
    for (int i = 0; i < len; i++) {
        int num = 0;
        if (buff[i] == '#') {
            num = -1;
            i++;
        } else {
            while (buff[i] != ' ' && buff[i] != '\0') {
                num = num * 10 + (buff[i++] - '0');
            }
        }
        data[index++] = num;
    }
}

// 创建 dot 可视化文件，感兴趣的同学可以学习
void createDotFile(const char *filename, TreeNodePtr root, int MaxSize) {
    FILE *fp = fopen(filename, "w");    // 文件指针
    if (fp == NULL) {   // 为NULL则返回
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // 开头
    // 利用层次遍历构造
    QueuePtr queue = InitQueue();
    EnQueue(queue, root);
    int id = 1;
    while (!QueueEmpty(queue)) { // 若队列不空，继续遍历。否则，遍历结束
        TreeNodePtr curr = GetHead(queue);
        DeQueue(queue);
        if (curr == NULL) continue;
        fprintf(fp, "%d [shape=circle, label=\"%d\"];\n", curr->id, curr->val);
        if (curr->left != NULL) { // 如果有左孩子，左孩子入队
            EnQueue(queue, curr->left);
            fprintf(fp, "%d->%d;\n", curr->id, curr->left->id);
        }
        id++;
        // 中间虚拟节点，补充空的左孩子或左孩子节点
        fprintf(fp, "_n%d [shape=circle, label=\"#\", style=invis];\n", id);
        fprintf(fp, "%d->_n%d [style=invis, weight=10];\n", curr->id, id);
        if (curr->right != NULL) { // 如果有右孩子，右孩子入队
            EnQueue(queue, curr->right);
            fprintf(fp, "%d->%d;\n", curr->id, curr->right->id);
        }
        id++;
    }
    fprintf(fp, "}\n"); // 结尾
    fclose(fp); // 关闭IO
}


// 绘制二叉树图片,调用 createDotFile 并使用 system 执行命令
void plot(TreeNodePtr tree_root, int i, int size, char *name) {
    char tree_filename[50], paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, size);
    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);
}


// 删除二叉树
void destoryTree(TreeNodePtr root) {
    if (!root) return;
    if (root->left) {
        destoryTree(root->left);
        root->left = NULL;
    }
    if (root->right) {
        destoryTree(root->right);
        root->right = NULL;
    }
    free(root);
}

//删除二叉树中（val为-1）结点
TreeNodePtr destoryTreeNULL(TreeNodePtr root){
    if(root)
    {
        if(root->val==-1)//运用destoryTree函数删除不为NULL且val为-1的结点
        {
            destoryTree(root);
            root = NULL;
        }
        if(root)
       {
            if(root->left) root->left=destoryTreeNULL(root->left);//递归到二叉树左孩子
            if(root->right) root->right=destoryTreeNULL(root->right);//递归到二叉树右孩子
        }
    }
    else
    {
        return NULL;
    }
    return root;
}
/** TODO:  任务一：请你通过队列来实现层次遍历构建二叉树，并返回二叉树的头结点 */
TreeNodePtr createTreeWithLevelOrder(int *data, int size) {
    QueuePtr queue1=InitQueue();//用于连接构建二叉树
    QueuePtr queue2=InitQueue();//存放单独二叉树结点
    int i,x;
    for(i=0;i<size;i++)//将数据存入二叉树，将单独二叉树结点顺序入队列
    {
        TreeNodePtr a = (TreeNodePtr) (malloc(sizeof(TreeNode)));
        a=createTreeNode(data[i],NULL,NULL);
        EnQueue(queue2,a);
    }
    TreeNodePtr a = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    a=GetHead(queue2);//将根节点放入queue1
    DeQueue(queue2);
    EnQueue(queue1,a);
    TreeNodePtr d = (TreeNodePtr) (malloc(sizeof(TreeNode)));//用于存放二叉树树根
    for(i=1;i<=size;i++)//每个循环层次遍历构建一个二叉树结点
    {
        TreeNodePtr b = (TreeNodePtr) (malloc(sizeof(TreeNode)));
        if(!QueueEmpty(queue2))//将queue2取出的单独二叉树结点作为queue1的二叉树结点的左孩子
        {
            b=GetHead(queue2);
            DeQueue(queue2);
        }
        else
        {
            b=NULL;
        }
        TreeNodePtr c = (TreeNodePtr) (malloc(sizeof(TreeNode)));
        if(!QueueEmpty(queue2))//将queue2取出的单独二叉树结点作为queue1的二叉树结点的右孩子
        {
            c=GetHead(queue2);
            DeQueue(queue2);
        }
        else
        {
            c=NULL;
        }
        TreeNodePtr a = (TreeNodePtr) (malloc(sizeof(TreeNode)));
        a=GetHead(queue1);//取出queue1中的二叉树结点进行构建
        DeQueue(queue1);
        a->left=b;//连接左孩子
        a->right=c;//连接右孩子
        if(b)
        {
            EnQueue(queue1,a->left);//将左孩子入列queue1
        }
        if(c)
        {
            EnQueue(queue1,a->right);//将右孩子入列queue1
        }
        if(i==1)
        {
            d=a;//存放树根
        }
    }
    d=destoryTreeNULL(d);//去除二叉树中不为NULL且val=-1的结点
    return d;//返回树根
}

/**
 * ================================================
 * ||                  前序遍历                   ||
 * ================================================
 */
void preOrderTraverse(TreeNodePtr root) {
    if(root)
    {
        printf("%d ",root->val);//前序递归遍历
        preOrderTraverse(root->left);
        preOrderTraverse(root->right);
    }
}

/**
 * ================================================
 * ||                  中序遍历                   ||
 * ================================================
 */
void inOrderTraverse(TreeNodePtr root) {
    if(root)
    {
        inOrderTraverse(root->left);
        printf("%d ",root->val);//中序递归遍历
        inOrderTraverse(root->right);
    }
}

/**
 * ================================================
 * ||                  后序遍历                   ||
 * ================================================
 */
void postOrderTraverse(TreeNodePtr root) {
    if(root)
    {
        postOrderTraverse(root->left);
        postOrderTraverse(root->right);
        printf("%d ",root->val);//后序递归遍历
    }
}

/** TODO: 任务二：请你通过深度优先遍历来求取该二叉树的最大路径和 */
int maxPathSum(TreeNodePtr root, int sum) {
    if(root)
    {
        sum=max(maxPathSum(root->left,0),maxPathSum(root->right,0))+root->val;//运用递归（结点最大路径和为：结点两个孩子最大路径和的max+结点val）
    }
    else
    {
        sum=0;
    }
    return sum;
}

/** ToDO: 任务三：请你通过递归求取该二叉树的所有左子叶权重之和 */
int sumOfLeftLeaves(TreeNodePtr root) {
    if(root)
    {
        if(root->left&&root->left->left==NULL&&root->left->right==NULL)//当结点左孩子为左子叶时
        {
            return root->left->val+sumOfLeftLeaves(root->right);//结点所有左子叶权重之和=结点左孩子val+结点右孩子所有左子叶权重之和
        }
    }
    else
    {
        return 0;
    }
    return sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right);//运用递归，结点所有左子叶权重之和=结点左孩子所有左子叶权重之和+结点右右孩子所有左子叶权重之和
}

/** TODO: 任务四：请你通过递归求取该树的镜像，即翻转该二叉树 */
TreeNodePtr invertTree(TreeNodePtr root) {
    if(root)
    {
        invertTree(root->left);//递归翻转左孩子
        invertTree(root->right);//递归翻转右孩子
        TreeNodePtr Left=(TreeNodePtr)(malloc(sizeof(TreeNode)));
        TreeNodePtr Right=(TreeNodePtr)(malloc(sizeof(TreeNode)));
        Left=root->right;//翻转左右孩子
        Right=root->left;//翻转左右孩子
        root->left=Left;//翻转左右孩子
        root->right=Right;//翻转左右孩子
    }
    else
    {
        return NULL;
    }
}


int main() {

    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    char num[MAX_NUM];
    bool use_graphviz = false;
    /**
     * ===============================================================
     * ||                   End Configuration                       ||
     * ===============================================================
     */

    // printf("Read data...\n");
    FILE *fp = fopen("./test.txt", "r");
    if (!fp) {
        perror("打开文件时发生错误");
        return -1;
    } else {
        int i = 0;
        // printf("success!\n");
        /**
         * ===============================================================
         * ||                   Read data here                          ||
         * ===============================================================
         */
        while (fgets(num, MAX_NUM, fp) && fgets(buff, SIZE, fp)) {
            char *nextline = strchr(buff, '\n');          //查找换行符
            if (nextline)                            //如果find不为空指针
                *nextline = '\0';                    //就把一个空字符放在这里
            printf("Case %d, data: %s, nodes number: %s", i, buff, num);
            int size = atoi(num);
            int data[size];
            getDigits(buff, data);

            /**
             * ===============================================================
             * ||       你的任务在这里，当然你也可以以任意方式修改函数的原型          ||
             * ===============================================================
             */

            /** 任务一 */
            TreeNodePtr tree_root = createTreeWithLevelOrder(data, size);
            printf("Answer for task 1 is: \n");
            printf("preOrderTraverse is:");
            preOrderTraverse(tree_root);
            printf("\n");
            printf("inOrderTraverse is:");
            inOrderTraverse(tree_root);
            printf("\n");
            printf("postOrderTraverse is:");
            postOrderTraverse(tree_root);
            printf("\n");

            /** 通过 graphviz 可视化，勿删，助教测试使用 */
            if (use_graphviz) {
                plot(tree_root, i, size, "tree");
            }

            /** 任务二 */
            int max_path_sum = maxPathSum(tree_root, 0);
            printf("Answer for task 2 is : %d \n", max_path_sum);

            /** 任务三 */
            int weight_sum = sumOfLeftLeaves(tree_root);
            printf("Answer for task 3 is : %d \n", weight_sum);

            /** 任务四 */
            TreeNodePtr invert_tree_root = invertTree(tree_root);
            printf("inOrderTraverse for task 4 is:");
            inOrderTraverse(invert_tree_root);
            printf("\n\n");

            /** 通过 graphviz 可视化，勿删，助教测试使用 */
            if (use_graphviz) {
                plot(invert_tree_root, i, size, "invert_tree");
            }

            destoryTree(invert_tree_root);
            tree_root = invert_tree_root = NULL;
            i++;

        }

        /**
         * ===============================================================
         * ||                       End read                            ||
         * ===============================================================
         */
    }

    fclose(fp);

}
