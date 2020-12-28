/*
利用双向链表解决约瑟夫环问题（也可以使用循环链表）
问题描述：
    将n个人围成一圈开始报数，每次报到m的人出列，它的下一个
    人从1开始重新报数，直到所有玩家出列。 
解决思路，使用一个双向循环链表模拟整个游戏成员，每一个节点
代表一玩家。 
*/

# include <stdio.h>
# include <stdlib.h>
# include <malloc.h>

// 双向链表类型定义
typedef struct NODE
{
    int data;              // 数据域 
    struct NODE * next;    // 储存前驱地址 
    struct NODE * prior;   // 储存此节点的后一个节点的地址 
}Node, * pNode;

// 双向循环链表的创建
pNode Create_DCList(int len);
// 在长度为n的双向循环链表上，报数为m的玩家出列
void Josephus(pNode pHead, int n, int m, int k);

int main(void)
{
    pNode pHead;
    int n, k, m;
    printf("输入玩家个数 n = ");
    scanf("%d", &n);
    printf("输入开始报数的序号 k = ");
    scanf("%d", &k);
    printf("报数为 m 的人出列 m = ");
    scanf("%d", &m);
    pHead = Create_DCList(n);
    Josephus(pHead, n, m, k); 
    
    return 0;
}

// 双向循环链表的创建
pNode Create_DCList(int len)
{
    pNode pHead = NULL;
    pNode s, q;
    int i;
    for (i = 1; i <= len; ++i)
    {
        s = (pNode)malloc(sizeof(Node));
        if (NULL == s)
        {
            printf("动态内存分配失败！\n");
            exit(-1);
        }
        s->data = i;
        s->next = NULL;
        
        // 将新节点插入双向循环链表
        if (NULL == pHead)
        {
            pHead = s;
            s->prior = pHead;
            s->next = pHead;
        } 
        else
        {
            s->next = q->next;
            q->next = s;
            s->prior = q;
            pHead->prior = s;
        }
        // q始终指向链表最后一个节点
        q = s; 
    }
    
    return pHead;
}

// 在长度为n的双向循环链表上，报数为m的玩家出列
void Josephus(pNode pHead, int n, int m, int k)
{
    pNode p, q;
    int i;
    p = pHead;
    // 从第k个人开始报数 
    for (i = 1; i < k; ++i)
    {
        q = p;
        p = p->next;
    }
    while (p->next != p) // 当只剩下一个节点时停止循环 
    {
        for (i = 1; i < m; ++i)
        {
            q = p;
            p = p->next; 
        }
        q->next = p->next;  // 将p节点删除
        p->next->prior = q;
        printf("%4d", p->data);  // 输出出列的玩家 
        free(p);
        p = q->next;     
    }
    printf("%4d\n", p->data);
    free(p);
    p = NULL;
    
    return;
}
