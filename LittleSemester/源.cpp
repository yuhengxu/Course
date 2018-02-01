#include<stdio.h>
#include<malloc.h>
struct node
{
	int no;//编号
	struct node*next;//指针
};
void main()
{
	int n, k, m;
	scanf("%d%d%d", &n, &k, &m);
	struct node*head, *p, *q;
	head = (struct node *)malloc(sizeof(struct node));
	head->no = -1;//建立表头结点，标记为no为-1；
	head->next = head;//形成环形空表
	for (int i = n; i > 0; i--)//形成包含n个节点的循环链表
	{
		p = (struct node*)malloc(sizeof(struct node));
		p->next = head->next;//在表节点的后面插入新节点
		p->no = i;
		head->next = p;
	}
	while (p->next != head)//查找循环链表的最后一个节点
		p = p->next;
	p->next = head->next;//构成循环
	p = head->next;
	for(int i=1;i<k;i++)//移动到第k个人
		p = p->next;
	for (int i = 0; i < n; i++)//
	{
		for (int col = 1; col < m - 1; col++)
			p = p->next;
		q = p -> next;
		p->next = q->next;
		printf("%d", q->no);
		free(q);
	}
}