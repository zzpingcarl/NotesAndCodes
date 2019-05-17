/**
 *
 *判断一个链表是否为循环链表
 *用单向循环链表测试
 *新建链表为空来测试非循环链表
 *新建链表部位空来测试循环链表
 */
# include<stdio.h>
# include<stdlib.h>

typedef struct Node{
	int data;
	struct Node * pNext;
}NODE;

NODE * Create_Circular(int);//创建单向循环链表
void Decide(NODE *);

int main(void)
{
	int num;

	printf("Please input your Link_Circular Node number(num>0):\n");
	scanf("%d",&num);//use zero or not zero to test
	NODE * pHead = NULL;
	pHead = Create_Circular(num);

	Decide(pHead);
	return 0;
}	
void Decide(NODE * pHead)
{
	NODE * p;
	p = pHead;
	for(p;p && p->pNext != pHead;p=p->pNext);

	if(p == NULL){
		printf("This Link no have circular!\n");
	}
	else{
		printf("This Link have circular!\n");
	}

	
}
NODE * Create_Circular(int num)
{
	int i = 0;
	NODE *pNew, *pTail = NULL, *pHead = NULL;
	for(i=0; i<num; i++)
	{
		pNew = (NODE*)malloc(sizeof(NODE));	
		pNew->data = i+1;
		pNew->pNext = NULL;

		if(pHead == NULL){
			pNew->pNext = pNew;
			pTail = pHead = pNew;
		}
		else{
			pNew->pNext = pHead;
			pTail = pTail->pNext = pNew;
		}
	}
	printf("Create Link_Circular Success!The number of node is %d!\n",num);

	return pHead;
}