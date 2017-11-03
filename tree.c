#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//�������򴴽������� 
//void PreInCreate(BiTree *root){
//	char Pre[N];
//	char In[N];
//	int i=0,j=0,k,rflag,lflag;
//	int len;
//	char ch;
//	printf("�������������У���"#"������\n");
//	ch = getchar();
//	while(ch != "#"){
//		Pre[i++] = ch;
//	}
//	len = i;
//	
//	i = 0; 
//	printf("�������������У���"#"������\n");
//	ch = getchar();
//	while(ch != "#"){
//		In[i++] = ch;
//	}
//	
//	BiTree *root = (BiTree *)malloc(sizeof(BiTree));
//	root->data = Pre[j];
//	
//	BiTree *flag = root;
//	k = rflag = i = Find(root->data, In);
//	
//	while(i <= rflag) {
//		i = Find(Pre[j++], In);
//		if(In[i] != "#"){
//			BiTree *Node = malloc(sizeof(BiTree));
//			Node->data = In[i];
//			
//			if(i < k){
//				flag->LChild = Node;
//			}
//			else{
//				flag->RChild = Node;
//			}
//		}
//	}
//	
//}

int search(BiNode* T, int in_begin, int in_end, BiNode in[N])  
{	
	int location,i;
    for (i = in_begin; i <= in_end; i++)  
    {  
        if (T->data == in[i].data){  
            location = i - in_begin;  
            return location;
        }  
    }  
}  
  
BiTree rebuildTree(char *pre, char *in, int len)  
{  
    BiTree t;  
    if(len <= 0)  
    {   
        //�ݹ���ֹ  
        t = NULL;  
    }else  
    {   
        //�ݹ�����  
        int index = 0;  
          
        while(index < len && *(pre) != *(in + index))  
        {  
            index ++;  
        }  
          
        if(index >= len)  
        {  
            printf("ǰ��������������������������!\n");  
            exit(-1);  
        }  
          
        t = (BiTree *)malloc(sizeof(BiNode));  
        t->data = *pre;  
        t->LChild = rebuildTree(pre + 1, in, index);  
        t->RChild = rebuildTree(pre + (index + 1), in + (index + 1), len - (index + 1));  
    }  
    return t;  
} 

/*�����������к��������й��������*/  
void BuildTree(int pre_begin, int pre_end, int in_begin, int in_end, BiNode pre[N], BiNode in[N])  
{  
    BiNode* T = &pre[pre_begin];
    int i = 0;  
  
    //��¼����in�����in_begin��λ�ã���( in_begin + i )�����Ÿ��ڵ���in�е�λ��  
    i = search(T, in_begin, in_end, in);     
  
    //pre[pre_begin + 1] �� pre[pre_begin + i + 1]�ֱ�Ϊ���������ĸ��ڵ�  
    //in���������У�( in_begin + i )�����Ÿ��ڵ��λ�ã���������λ�������������ߣ�����in_begain + i -1���ͣ�in_begain + i +1)��
	//���ǣ���in_begin + i == in_begin��˵��������Ϊ�գ� 
    //ͬ����in_begin + i == in_end����˵��������Ϊ�գ�  
  
    if(in_begin + i != in_begin )  
        T->LChild = &pre[pre_begin + 1];   
    else T->LChild = NULL;  
  
    if( in_begin + i != in_end )  
        T->RChild = &pre[pre_begin + i + 1];  
    else T->RChild = NULL;  
  
    //�ݹ����������ܵݹ��������in_Begin  < in_begin + i - 1;   
    //�� !( in_Begin  < in_begin + i - 1 )����ʱʣһ���ڵ㣬ΪҶ�ӽڵ㡣�ֻ���������Ϊ��  
  
    if(in_begin < in_begin + i - 1)   
        BuildTree(pre_begin + 1, pre_begin + i, in_begin, in_begin + i - 1, pre, in);  
    else{  
        pre[pre_begin + i].LChild = NULL;  
        pre[pre_begin + i].RChild = NULL;  
    }  
  
    //�ݹ����������ܵݹ��������in_Begin + i + 1 < in_end;   
    //�� !( in_Begin + i + 1 < in_end )����ʱʣһ���ڵ㣬ΪҶ�ӽڵ㡣�ֻ���������Ϊ��  
  
    if(in_begin + i + 1 < in_end)   
        BuildTree(pre_begin + i + 1, pre_end, in_begin + i + 1, in_end, pre, in);  
    else  
    {  
        pre[pre_end].LChild = NULL;  
        pre[pre_end].RChild = NULL;  
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
	printf("\n\t\t-----------Ŀ---¼----------\n\n");
	printf("\t\t������չ����������-----------0\n\n");
	printf("\t\t�������򴴽�������-----------1\n\n");
	printf("\t\t�ݹ��������-----------------2\n\n");
	printf("\t\t�ݹ��������-----------------3\n\n");
	printf("\t\t�ݹ�������-----------------4\n\n");
	printf("\t\t�ǵݹ��������---------------5\n\n");
	printf("\t\t�ǵݹ��������---------------6\n\n");
	printf("\t\t�ǵݹ�������---------------7\n\n");
	printf("\t\t��    ��---------------------8\n\n\n");
	printf("\n\n���������ѡ��:"); 
}

int main(){
	BiTree *root;
	int ch = 0 ,c ;
	char s;
	int end;
	BiNode pre[N], in[N]; 
	while(ch!=7){
		Menu();
		scanf("%d",&ch);
		getchar();
		if(ch == 8){
			break;
		}else{
			if(ch == 0){
				printf("����������չ����һ��������:\n");
				CreateBiTree(&root);
			}
			else if(ch == 1){
				printf("������������򴴽�һ��������:\n");
				for(ch = 0; ch < N; ch++){
					s = getchar();
					if(s != '#'){
						pre[ch].data = s;
					}
					else{
						end = ch;
						break;
					}
				}
				
				for(ch = 0; ch < N; ch++){
					s = getchar();
					if(s != '#'){
						in[ch].data = s;
					}
					else{
						end = ch;
						break;
					}
				}
				BuildTree(0,end,0,end,pre,in);
				root = &pre[0];
			}
			else if(ch == 2){
				printf("�ݹ����������\n");
				DPreOrder(root);
			}
			else if(ch == 3){
				printf("�ݹ����������\n");
				DInOrder(root);
			}
			else if(ch == 4){
				printf("�ݹ���������\n");
				DLastOrder(root);
			}
			else if(ch == 5){
				printf("���������\n");
				PreOrder(root);
			}
			else if(ch == 6){
				printf("���������\n");
				InOrder(root);
			}
			else if(ch == 7){
				printf(" ���������\n");
				LastOrder(root);
			}
		}
	}
	
	return 0;
}
