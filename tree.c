#include <stdio.h>
#include <stdlib.h>
#define N 100 
typedef struct Node{
	char data;
	struct Node *LChild;
	struct Node *RChild;
}BiNode , *BiTree;

typedef struct Zhan{
	int top;
	int rear;
	BiTree data[N];
}Zhan;

Zhan *zhanInit(){
	Zhan *p = (Zhan *)malloc(sizeof(Zhan));
	p->top = p->rear = -1;
	return p ;	
}

BiNode *Pop(Zhan *p){
	BiNode *root = p->data[p->top];
	p->top-- ;
	return root;
} 

BiNode *Top(Zhan *p){
	BiNode *root = p->data[p->top];
	return root;
} 

void Push(Zhan *s,BiNode *root){
	s->top++;
	s->data[s->top] = root;
}

int isEmpty(Zhan *p){
	if(p->top == p->rear){
		return 1;
	}
	else{
		return 0;
	}
}
//��չ����洢 
void CreateBiTree(BiTree *root){
	char ch;
	ch=getchar();
	if(ch=='#') *root=NULL;
	else{
		*root = (BiTree)malloc(sizeof(BiNode));
		(*root)->data = ch;
		CreateBiTree(&(*root)->LChild); 
		CreateBiTree(&(*root)->RChild); 
	}
}

//�ݹ���������򡢺������ 
void DPreOrder(BiTree root){
	if(root){
		printf("%2c",root->data);
		DPreOrder((root->LChild));
		DPreOrder((root->RChild));
	}
}

void DInOrder(BiTree root){
	if(root){
		DInOrder((root->LChild));
		printf("%2c",root->data);
		DInOrder((root->RChild));
	}
}

void DLastOrder(BiTree root){
	if(root){
		DLastOrder((root->LChild));
		DLastOrder((root->RChild));
		printf("%2c",root->data);
	}
}

//�ǵݹ����� 
void PreOrder(BiTree root){
	BiTree p = root ;
	Zhan *s = zhanInit();
	while(p!=NULL || !isEmpty(s)){
		while(p!=NULL){
			printf("%2c",p->data);
			Push(s,p);
			p=p->LChild;
		}
		if(!isEmpty(s)){
			p=Pop(s);
			p=p->RChild;
		}
	}	
}

//�ǵݹ����� 
void InOrder(BiTree root){
	BiTree p = root ;
	Zhan *s = zhanInit();
	while(p!=NULL || !isEmpty(s)){
		while(p!=NULL){
			Push(s,p);
			p=p->LChild;
		}
		if(!isEmpty(s)){
			p=Pop(s);
			printf("%2c",p->data);
			p=p->RChild;
		}
	}	
}

void LastOrder(BiTree root){
	BiTree p = root ;
	BiTree q = NULL ;               //��ǵ�ǰ�ڵ����һ�ڵ� 
	Zhan *s = zhanInit();
	while(p!=NULL || !isEmpty(s)){
		while(p!=NULL){
			Push(s,p);        //���ڵ���ջ 
			p=p->LChild;
		}
		if(!isEmpty(s)){
			p=Top(s);                  //ȡջ��Ԫ�� 
			if((p->RChild==NULL)||(p->RChild==q)){      //�����ǰԪ�ص���������ʹ�����Ϊ��  ����ʸýڵ� 
				p=Pop(s);              //ջ��Ԫ�س�ջ 
				printf("%2c",p->data);
				q=p;                   //��q��¼��һ�η��ʵ�Ԫ�� 
				p=NULL;
			}
			else{
				p=p->RChild;
			}
		}
	}	
}

void Menu(){
	printf("\n\n\n\n\t\t--------Ŀ--¼--------\n");
	printf("\t\t����������-----------0\n\n");
	printf("\t\t�ݹ��������---------1\n\n");
	printf("\t\t�ݹ��������---------2\n\n");
	printf("\t\t�ݹ�������---------3\n\n");
	printf("\t\t�ǵݹ��������-------4\n\n");
	printf("\t\t�ǵݹ��������-------5\n\n");
	printf("\t\t�ǵݹ�������-------6\n\n");
	printf("\t\t�� ��----------------7\n\n\n");
	printf("\n\n���������ѡ��"); 
}

int main(){
	BiTree *root;
	int ch = 0 ;
	int c ;
	while(ch!=7){
		Menu();
		scanf("%d",&ch);
		getchar();
		if(ch == 7){
			break;
		}else{
			if(ch == 0){
				printf("�봴��һ��������:\n\n");
				CreateBiTree(&root);
			}
			else if(ch == 1){
				printf("�ݹ����������\n\n");
				DPreOrder(root);
			}
			else if(ch == 2){
				printf("�ݹ����������\n\n");
				DInOrder(root);
			}
			else if(ch == 3){
				printf("�ݹ���������\n\n");
				DLastOrder(root);
			}
			else if(ch == 4){
				printf("���������\n\n");
				PreOrder(root);
			}
			else if(ch == 5){
				printf("���������\n\n");
				InOrder(root);
			}
			else if(ch == 6){
				printf(" ���������\n\n");
				LastOrder(root);
			}
			printf("\n\n�Ƿ������0/1");
			scanf("%d",&c);
			if(c == 0){
				break;
			}
			else {
				;
			}
			
		}
	}
//	CreateBiTree(&root);
//	LastOrder(root);
	return 0;
}
