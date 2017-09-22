#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int id;
	int password;
	struct Node *next;
}Node;

/*
	创建单项循环链表：
	利用尾插法，仅将最后一次的的rear链接到头指针即可 
*/ 
Node* Create(){
	Node *p,*head;
	int num,i,pass;
	p=head=(Node *)malloc(sizeof(Node));
	p=head;
	printf("please input num:");
	scanf("%d",&num);
	getchar();
	for(i=0;i<num;i++){
		printf("please input %d password:",i+1);
		scanf("%d",&pass);
		getchar();
		Node *pnew=(Node *)malloc(sizeof(Node));
		pnew->id=i+1;
		pnew->password=pass;
		
		p->next=pnew;
		p=p->next; 
	}
	p->next=head;                   //构成循环单链表 
	printf("Create successful\n");
	return head;
}

/*
	判断链表是否为空，如果头指针的next指向了头指针本身，
	即链表只有头指针一个节点，即为空。 
*/ 
int IF(Node *head){
	if(head->next==head) return 0; 
	else return 1;
}

/*
	输出循环单链表:
		重要的是判断条件：p->next!=head;
		利用循环单链表一直向后next会返回到head来判断是否结束一遍遍历 
/*/ 
void Print(Node *head){
	Node *p=(Node *)malloc(sizeof(Node));
	p=head->next;
	if(IF(head)){
		printf("--ID-- --PASSWORD--\n");
		printf("  %d        %d    \n",p->id,p->password);
		
		//环单链表一直向后next会返回到head来判断是否结束一遍遍历 
		while(p->next!=head){ 
			p=p->next;
			printf("  %d        %d    \n",p->id,p->password);
		}
	}
	else{
		printf("List is empty!\n");
	}
} 
/*
	执行约瑟夫环问题：
		设置一个num为每次要数的数字，第一次为输入的num，随后为每次跳出的人的password；
		1.由于循环单链表不断next会回到head，所以考虑到当到达head时，两个指针pre,p都要再往后next一次（p为要跳出的人，pre为p的前驱） 
		2.考虑到如果是排在队伍第一个的人出列，那么要删除这个人，就得pre=head，pre->nxet=p，这样才能将其删除； 
*/
void YueSf(Node *head){
	int num,i,pass;
	Node *p,*now,*pre;
	p=head;
	printf("please input the begaining:");
	scanf("%d",&num);
	getchar();
	while(IF(head)){
		for(i=0;i<num;i++){
			pre=p;
			p=p->next;
			if(p==head){
				pre=p;
				p=p->next;
			}
		}
		printf("ID:%d -- PASS:%d\n",p->id,p->password);
		num=p->password;
		if(p==head->next){
			pre=head;
		}
		pre->next=p->next;
	} 
}

int main(){
	Node *head=	Create();   //c创建约瑟夫环 
	Print(head);            //打印创建好之后的信息 
	YueSf(head);            //执行约瑟夫游戏 
}

