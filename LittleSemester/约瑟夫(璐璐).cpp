#include<stdio.h>
#include<malloc.h>
struct node
{
	int no;//编号
	struct node*next;//指针
};
int main()
{
	int n, k, m;
	scanf("%d,%d,%d", &n, &k, &m);
	if (n < 1 || k < 1 || m < 1)
	{
		printf("n,m,k must bigger than 0.\n");
		return 0;
	}
	if (k > n)
	{
		printf("k should not bigger than n.\n");
		return 0;
	}
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
						 //p = head->next;
	for (int i = 0; i < k - 1; i++)//移动到第k个人
		p = p->next;
	int i;
	for (i = 0; i < n; i++)//
	{
		int flag = 0;
		for (int col = 1; col < m; col++)
			p = p->next;
		q = p->next;
		p->next = q->next;
		if (i % 10 == 0 && i != 0)
		{
			printf("\n");
		
		}
		printf("%d", q->no);
		if (i != n - 1&& i%10!=9)printf("#");
		if (i == n - 1)printf(".\n");
		free(q);
	}
}