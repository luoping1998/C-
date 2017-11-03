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

//先序中序创建二叉树 
//void PreInCreate(BiTree *root){
//	char Pre[N];
//	char In[N];
//	int i=0,j=0,k,rflag,lflag;
//	int len;
//	char ch;
//	printf("请输入先序序列，以"#"结束：\n");
//	ch = getchar();
//	while(ch != "#"){
//		Pre[i++] = ch;
//	}
//	len = i;
//	
//	i = 0; 
//	printf("请输入中序序列，以"#"结束：\n");
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
        //递归终止  
        t = NULL;  
    }else  
    {   
        //递归主体  
        int index = 0;  
          
        while(index < len && *(pre) != *(in + index))  
        {  
            index ++;  
        }  
          
        if(index >= len)  
        {  
            printf("前序遍历或者中序遍历数组有问题!\n");  
            exit(-1);  
        }  
          
        t = (BiTree *)malloc(sizeof(BiNode));  
        t->data = *pre;  
        t->LChild = rebuildTree(pre + 1, in, index);  
        t->RChild = rebuildTree(pre + (index + 1), in + (index + 1), len - (index + 1));  
    }  
    return t;  
} 

/*根据先序序列和中序序列构造二叉树*/  
void BuildTree(int pre_begin, int pre_end, int in_begin, int in_end, BiNode pre[N], BiNode in[N])  
{  
    BiNode* T = &pre[pre_begin];
    int i = 0;  
  
    //记录根在in中相对in_begin的位置，即( in_begin + i )代表着根节点在in中的位置  
    i = search(T, in_begin, in_end, in);     
  
    //pre[pre_begin + 1] 和 pre[pre_begin + i + 1]分别为左右子树的根节点  
    //in是中序序列，( in_begin + i )代表着根节点的位置，左右子树位于它的左右两边，即（in_begain + i -1）和（in_begain + i +1)，
	//但是，若in_begin + i == in_begin则说明左子树为空； 
    //同理，若in_begin + i == in_end，则说明右子树为空；  
  
    if(in_begin + i != in_begin )  
        T->LChild = &pre[pre_begin + 1];   
    else T->LChild = NULL;  
  
    if( in_begin + i != in_end )  
        T->RChild = &pre[pre_begin + i + 1];  
    else T->RChild = NULL;  
  
    //递归左子树，能递归的条件是in_Begin  < in_begin + i - 1;   
    //若 !( in_Begin  < in_begin + i - 1 )，此时剩一个节点，为叶子节点。又或者左子树为空  
  
    if(in_begin < in_begin + i - 1)   
        BuildTree(pre_begin + 1, pre_begin + i, in_begin, in_begin + i - 1, pre, in);  
    else{  
        pre[pre_begin + i].LChild = NULL;  
        pre[pre_begin + i].RChild = NULL;  
    }  
  
    //递归右子树，能递归的条件是in_Begin + i + 1 < in_end;   
    //若 !( in_Begin + i + 1 < in_end )，此时剩一个节点，为叶子节点。又或者右子树为空  
  
    if(in_begin + i + 1 < in_end)   
        BuildTree(pre_begin + i + 1, pre_end, in_begin + i + 1, in_end, pre, in);  
    else  
    {  
        pre[pre_end].LChild = NULL;  
        pre[pre_end].RChild = NULL;  
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
	printf("\n\t\t-----------目---录----------\n\n");
	printf("\t\t先序扩展创建二叉树-----------0\n\n");
	printf("\t\t先序中序创建二叉树-----------1\n\n");
	printf("\t\t递归先序遍历-----------------2\n\n");
	printf("\t\t递归中序遍历-----------------3\n\n");
	printf("\t\t递归后序遍历-----------------4\n\n");
	printf("\t\t非递归先序遍历---------------5\n\n");
	printf("\t\t非递归中序遍历---------------6\n\n");
	printf("\t\t非递归后序遍历---------------7\n\n");
	printf("\t\t退    出---------------------8\n\n\n");
	printf("\n\n请输入你的选择:"); 
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
				printf("请以先序扩展创建一个二叉树:\n");
				CreateBiTree(&root);
			}
			else if(ch == 1){
				printf("请以先序加中序创建一个二叉树:\n");
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
				printf("递归先序遍历：\n");
				DPreOrder(root);
			}
			else if(ch == 3){
				printf("递归中序遍历：\n");
				DInOrder(root);
			}
			else if(ch == 4){
				printf("递归后序遍历：\n");
				DLastOrder(root);
			}
			else if(ch == 5){
				printf("先序遍历：\n");
				PreOrder(root);
			}
			else if(ch == 6){
				printf("中序遍历：\n");
				InOrder(root);
			}
			else if(ch == 7){
				printf(" 后序遍历：\n");
				LastOrder(root);
			}
		}
	}
	
	return 0;
}
