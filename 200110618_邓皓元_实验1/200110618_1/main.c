#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
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

/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}

/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
	//TODO
	while(head!=NULL){//��ͷ�ڵ㿪ʼ��ÿ�δ�ӡһ����㲢��ָ��ָ����һ����㣬ֱ����һ�����ΪNULL
        printLinkedListNode(head);//��ӡ���
        head=head->next;//ָ��ָ����һ�����
    }
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
	//TODO
	StudentLinkedListNode *pStudentLinkedListNode=malloc(sizeof(StudentLinkedListNode));//�½�����
	strcpy(pStudentLinkedListNode->StuID,student_id);//��¼ѧ��
	pStudentLinkedListNode->Grade=grade;//��¼�ɼ�
	return pStudentLinkedListNode;//��������
}


/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {//����ͷ�巨������ɼ������������
    //TODO
    StudentLinkedListNode *pStudentLinkedListNode;
    pStudentLinkedListNode=studentLinkedListCreate(node->StuID,node->Grade);//�½�һ����㲢��¼ѧ�źͳɼ�
    pStudentLinkedListNode->next=head;//��ǰ�����½��
    return pStudentLinkedListNode;//����ͷָ��
}


/** ��ת���� */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
    //TODO
    //ʹ��3��ָ�����������������ӵ���з�ת
    StudentLinkedListNode *a=malloc(sizeof(StudentLinkedListNode));
    StudentLinkedListNode *b=malloc(sizeof(StudentLinkedListNode));
    StudentLinkedListNode *c=malloc(sizeof(StudentLinkedListNode));
    a=head;//a��¼��һ�����
    b=head->next;//b��¼�ڶ������
    head->next=NULL;//��a��㵥��ȡ��
    while(b!=NULL){
        c=b->next;//��¼b֮�������
        b->next=a;//��a��b֮���nextָ��ת
        a=b;//��a�����������һ��ѭ��������ƽ�һ�����
        b=c;//��b�����������һ��ѭ��������ƽ�һ�����
    }
    head=a;//����ͷ�ڵ㸳��head
    return head;//����head
}

/** �ҵ��ཻ�ĵ�һ����� */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
    //class1��class2�ں�һ������ȫ�غϣ������ڴ��ַ��ͬ�������ҳ������ؿ�ʼ�ཻ�ĵ�һ����㡣
    //�벻Ҫ�򵥵�ͨ�����ṹ��ĳ�Ա���жϡ�
    //TODO
     int Lclass1,Lclass2,i;
     StudentLinkedListNode *CLASS1=malloc(sizeof(StudentLinkedListNode));
     StudentLinkedListNode *CLASS2=malloc(sizeof(StudentLinkedListNode));
     CLASS1=class1;//���Լ���������
     CLASS2=class2;//���Լ���������
     Lclass1=Lclass2=0;
     while(CLASS1!=NULL){//����������
        Lclass1++;
        CLASS1=CLASS1->next;
     }
     while(CLASS2!=NULL){//����������
        Lclass2++;
        CLASS2=CLASS2->next;
     }
     if(Lclass1>=Lclass2){//�����ȴ����������ƽ�ֱ�������������
        for(i=0;i<Lclass1-Lclass2;i++){
            class1=class1->next;
        }
     }
     else{//�����ȴ����������ƽ�ֱ�������������
        for(i=0;i<Lclass2-Lclass1;i++){
            class2=class2->next;
        }
     }
     while(class1!=class2){//��Ѱ��һ���ཻ���
        class1=class1->next;
        class2=class2->next;
     }
     return class1;//���ص�һ���ཻ���
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
        // �洢���ݵ�����
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

        // ��ת����
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // �����ཻ����
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // ��ӡ�ཻ���
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //�����ཻ����
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}
