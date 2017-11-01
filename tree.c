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
//扩展先序存储 
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

//递归的先序、中序、后序遍历 
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

//非递归先序 
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

//非递归中序 
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
	BiTree q = NULL ;               //标记当前节点的上一节点 
	Zhan *s = zhanInit();
	while(p!=NULL || !isEmpty(s)){
		while(p!=NULL){
			Push(s,p);        //根节点入栈 
			p=p->LChild;
		}
		if(!isEmpty(s)){
			p=Top(s);                  //取栈顶元素 
			if((p->RChild==NULL)||(p->RChild==q)){      //如果当前元素的右子鼠访问过或者为空  则访问该节点 
				p=Pop(s);              //栈顶元素出栈 
				printf("%2c",p->data);
				q=p;                   //用q记录上一次访问的元素 
				p=NULL;
			}
			else{
				p=p->RChild;
			}
		}
	}	
}

void Menu(){
	printf("\n\n\n\n\t\t--------目--录--------\n");
	printf("\t\t创建二叉树-----------0\n\n");
	printf("\t\t递归先序遍历---------1\n\n");
	printf("\t\t递归中序遍历---------2\n\n");
	printf("\t\t递归后序遍历---------3\n\n");
	printf("\t\t非递归先序遍历-------4\n\n");
	printf("\t\t非递归中序遍历-------5\n\n");
	printf("\t\t非递归后序遍历-------6\n\n");
	printf("\t\t退 出----------------7\n\n\n");
	printf("\n\n请输入你的选择："); 
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
				printf("请创建一个二叉树:\n\n");
				CreateBiTree(&root);
			}
			else if(ch == 1){
				printf("递归先序遍历：\n\n");
				DPreOrder(root);
			}
			else if(ch == 2){
				printf("递归中序遍历：\n\n");
				DInOrder(root);
			}
			else if(ch == 3){
				printf("递归后序遍历：\n\n");
				DLastOrder(root);
			}
			else if(ch == 4){
				printf("先序遍历：\n\n");
				PreOrder(root);
			}
			else if(ch == 5){
				printf("中序遍历：\n\n");
				InOrder(root);
			}
			else if(ch == 6){
				printf(" 后序遍历：\n\n");
				LastOrder(root);
			}
			printf("\n\n是否继续？0/1");
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
