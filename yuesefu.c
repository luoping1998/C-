#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int id;
	int password;
	struct Node *next;
}Node;

/*
	��������ѭ������
	����β�巨���������һ�εĵ�rear���ӵ�ͷָ�뼴�� 
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
	p->next=head;                   //����ѭ�������� 
	printf("Create successful\n");
	return head;
}

/*
	�ж������Ƿ�Ϊ�գ����ͷָ���nextָ����ͷָ�뱾��
	������ֻ��ͷָ��һ���ڵ㣬��Ϊ�ա� 
*/ 
int IF(Node *head){
	if(head->next==head) return 0; 
	else return 1;
}

/*
	���ѭ��������:
		��Ҫ�����ж�������p->next!=head;
		����ѭ��������һֱ���next�᷵�ص�head���ж��Ƿ����һ����� 
/*/ 
void Print(Node *head){
	Node *p=(Node *)malloc(sizeof(Node));
	p=head->next;
	if(IF(head)){
		printf("--ID-- --PASSWORD--\n");
		printf("  %d        %d    \n",p->id,p->password);
		
		//��������һֱ���next�᷵�ص�head���ж��Ƿ����һ����� 
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
	ִ��Լɪ�����⣺
		����һ��numΪÿ��Ҫ�������֣���һ��Ϊ�����num�����Ϊÿ���������˵�password��
		1.����ѭ����������next��ص�head�����Կ��ǵ�������headʱ������ָ��pre,p��Ҫ������nextһ�Σ�pΪҪ�������ˣ�preΪp��ǰ���� 
		2.���ǵ���������ڶ����һ�����˳��У���ôҪɾ������ˣ��͵�pre=head��pre->nxet=p���������ܽ���ɾ���� 
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
	Node *head=	Create();   //c����Լɪ�� 
	Print(head);            //��ӡ������֮�����Ϣ 
	YueSf(head);            //ִ��Լɪ����Ϸ 
}

