#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* 创建相交链表 */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a和b后面若干结点值相同
    // beforeCross1为跳过的a中的个数，从第beforeCross1 + 1个结点开始相交
    // beforeCross2为跳过的b中的个数，从第beforeCross2 + 1个结点开始相交
    // 相交方法是将b中的前一结点指向a中的首个相交结点
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //销毁野指针结点
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
}

void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode){
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode){
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode){
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}

/** 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // 用于单个节点输出的函数printLinkedListNode已提供
    //请你实现遍历链表的逻辑
	//TODO
	while(head!=NULL){//从头节点开始，每次打印一个结点并让指针指向下一个结点，直到下一个结点为NULL
        printLinkedListNode(head);//打印结点
        head=head->next;//指针指向下一个结点
    }
}


/** 新建一个链表node并返回 */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
    //tips:malloc的时候记得为转化为结构体指针
	//TODO
	StudentLinkedListNode *pStudentLinkedListNode=malloc(sizeof(StudentLinkedListNode));//新建链表
	strcpy(pStudentLinkedListNode->StuID,student_id);//记录学号
	pStudentLinkedListNode->Grade=grade;//记录成绩
	return pStudentLinkedListNode;//返回链表
}


/** 按照降序插入学生的成绩情况,并返回链表头指针 */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {//利用头插法将升序成绩逆序插入链表
    //TODO
    StudentLinkedListNode *pStudentLinkedListNode;
    pStudentLinkedListNode=studentLinkedListCreate(node->StuID,node->Grade);//新建一个结点并记录学号和成绩
    pStudentLinkedListNode->next=head;//向前插入新结点
    return pStudentLinkedListNode;//返回头指针
}


/** 反转链表 */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
    //TODO
    //使用3个指针遍历单链表，逐个链接点进行反转
    StudentLinkedListNode *a=malloc(sizeof(StudentLinkedListNode));
    StudentLinkedListNode *b=malloc(sizeof(StudentLinkedListNode));
    StudentLinkedListNode *c=malloc(sizeof(StudentLinkedListNode));
    a=head;//a记录第一个结点
    b=head->next;//b记录第二个结点
    head->next=NULL;//将a结点单独取出
    while(b!=NULL){
        c=b->next;//记录b之后的链表
        b->next=a;//将a，b之间的next指向反转
        a=b;//将a链表（相对于上一个循环）向后推进一个结点
        b=c;//将b链表（相对于上一个循环）向后推进一个结点
    }
    head=a;//将新头节点赋给head
    return head;//返回head
}

/** 找到相交的第一个结点 */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
    //class1和class2在后一部分完全重合（结点的内存地址相同），请找出并返回开始相交的第一个结点。
    //请不要简单地通过结点结构体的成员来判断。
    //TODO
     int Lclass1,Lclass2,i;
     StudentLinkedListNode *CLASS1=malloc(sizeof(StudentLinkedListNode));
     StudentLinkedListNode *CLASS2=malloc(sizeof(StudentLinkedListNode));
     CLASS1=class1;//用以计算链表长度
     CLASS2=class2;//用以计算链表长度
     Lclass1=Lclass2=0;
     while(CLASS1!=NULL){//计算链表长度
        Lclass1++;
        CLASS1=CLASS1->next;
     }
     while(CLASS2!=NULL){//计算链表长度
        Lclass2++;
        CLASS2=CLASS2->next;
     }
     if(Lclass1>=Lclass2){//将长度大的链表向后推进直到两链表长度相等
        for(i=0;i<Lclass1-Lclass2;i++){
            class1=class1->next;
        }
     }
     else{//将长度大的链表向后推进直到两链表长度相等
        for(i=0;i<Lclass2-Lclass1;i++){
            class2=class2->next;
        }
     }
     while(class1!=class2){//搜寻第一个相交结点
        class1=class1->next;
        class2=class2->next;
     }
     return class1;//返回第一个相交结点
}

int main(){
    freopen("./gradeImport.in","r",stdin);

    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    while(~scanf("%d%d", &num1, &num2)){
        class1 = class2 = NULL;
        // 存储数据到链表
        for(i = 0;i < num1;i++){
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class1 = studentLinkedListAdd(class1, node);
        }
        for(i = 0;i < num2;i++){
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class2 = studentLinkedListAdd(class2, node);
        }
        printf("* part1:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // 反转链表
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // 生成相交链表
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // 打印相交结点
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //销毁相交链表
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
