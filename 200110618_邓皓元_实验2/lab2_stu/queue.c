#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    //TODO
    if(StackEmpty(Q.stack1)==1&&StackEmpty(Q.stack2)==1)//若两个栈都非空，则构成的队列非空
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //TODO
    int m;
    if(QueueLength(*Q)<MaxSize)//若队列非满
    {
        if(StackEmpty(Q->stack2)==1)//若stack2临时存放栈为空
        {
            Push(&Q->stack1,e);//则stack1数据栈的栈顶元素为队列尾，push
        }
        else//若stack2临时存放栈非空
        {
            while(StackEmpty(Q->stack2)==0)//将stack2临时存放栈的元素推入stack1数据栈中
            {
                Pop(&Q->stack2,&m);
                Push(&Q->stack1,m);
            }
            Push(&Q->stack1,e);//stack1数据栈的栈顶元素为队列尾，push
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //TODO
    int m;
    if(QueueEmpty(*Q)==0)//若队列非空
    {
        if(StackEmpty(Q->stack1)==1)//若stack1数据栈为空
        {
            Pop(&Q->stack2,e);//则stack2临时存放栈的栈顶元素为队列头，pop
        }
        else//若数据栈非空
        {
                while(StackEmpty(Q->stack1)==0)//将stack1数据栈的元素推入stack2临时存放栈中
            {
                Pop(&Q->stack1,&m);
                Push(&Q->stack2,m);
            }
            Pop(&Q->stack2,e);//stack2临时存放栈的栈顶元素为队列头，pop
            while(StackEmpty(Q->stack2)==0)//将stack2临时存放栈的元素推回stack1数据栈中
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
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    int m;
    if(QueueEmpty(Q)==0)//若队列非空
    {
        if(StackEmpty(Q.stack1)==1)//若stack1数据栈为空
        {
            GetTop(Q.stack2,e);//则stack2临时存放栈的栈顶元素为队列头，GetTop
        }
        else//若数据栈非空
        {
            while(StackEmpty(Q.stack1)==0)//将stack1数据栈的元素推入stack2临时存放栈中
            {
                Pop(&Q.stack1,&m);
                Push(&Q.stack2,m);
            }
            GetTop(Q.stack2,e);//stack2临时存放栈的栈顶元素为队列头，GetTop
            while(StackEmpty(Q.stack2)==0)//将stack2临时存放栈的元素推回stack1数据栈中
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
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        取决于你的栈如何设计，元素存在哪个队列里。
    */
    //TODO
    StackToArray(Q.stack1,seq);//元素存放在stack1栈里作为数据栈，stack2栈作为临时存放栈
}
