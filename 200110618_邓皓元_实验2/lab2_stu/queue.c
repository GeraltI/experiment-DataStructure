#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    //TODO
    if(StackEmpty(Q.stack1)==1&&StackEmpty(Q.stack2)==1)//������ջ���ǿգ��򹹳ɵĶ��зǿ�
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    int m;
    if(QueueLength(*Q)<MaxSize)//�����з���
    {
        if(StackEmpty(Q->stack2)==1)//��stack2��ʱ���ջΪ��
        {
            Push(&Q->stack1,e);//��stack1����ջ��ջ��Ԫ��Ϊ����β��push
        }
        else//��stack2��ʱ���ջ�ǿ�
        {
            while(StackEmpty(Q->stack2)==0)//��stack2��ʱ���ջ��Ԫ������stack1����ջ��
            {
                Pop(&Q->stack2,&m);
                Push(&Q->stack1,m);
            }
            Push(&Q->stack1,e);//stack1����ջ��ջ��Ԫ��Ϊ����β��push
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    int m;
    if(QueueEmpty(*Q)==0)//�����зǿ�
    {
        if(StackEmpty(Q->stack1)==1)//��stack1����ջΪ��
        {
            Pop(&Q->stack2,e);//��stack2��ʱ���ջ��ջ��Ԫ��Ϊ����ͷ��pop
        }
        else//������ջ�ǿ�
        {
                while(StackEmpty(Q->stack1)==0)//��stack1����ջ��Ԫ������stack2��ʱ���ջ��
            {
                Pop(&Q->stack1,&m);
                Push(&Q->stack2,m);
            }
            Pop(&Q->stack2,e);//stack2��ʱ���ջ��ջ��Ԫ��Ϊ����ͷ��pop
            while(StackEmpty(Q->stack2)==0)//��stack2��ʱ���ջ��Ԫ���ƻ�stack1����ջ��
            {
                Pop(&Q->stack2,&m);
                Push(&Q->stack1,m);
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    int m;
    if(QueueEmpty(Q)==0)//�����зǿ�
    {
        if(StackEmpty(Q.stack1)==1)//��stack1����ջΪ��
        {
            GetTop(Q.stack2,e);//��stack2��ʱ���ջ��ջ��Ԫ��Ϊ����ͷ��GetTop
        }
        else//������ջ�ǿ�
        {
            while(StackEmpty(Q.stack1)==0)//��stack1����ջ��Ԫ������stack2��ʱ���ջ��
            {
                Pop(&Q.stack1,&m);
                Push(&Q.stack2,m);
            }
            GetTop(Q.stack2,e);//stack2��ʱ���ջ��ջ��Ԫ��Ϊ����ͷ��GetTop
            while(StackEmpty(Q.stack2)==0)//��stack2��ʱ���ջ��Ԫ���ƻ�stack1����ջ��
            {
                Pop(&Q.stack2,&m);
                Push(&Q.stack1,m);
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    //TODO
    StackToArray(Q.stack1,seq);//Ԫ�ش����stack1ջ����Ϊ����ջ��stack2ջ��Ϊ��ʱ���ջ
}
