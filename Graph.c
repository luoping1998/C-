#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 20
#define INFINITY 32767
typedef struct{
	int stack[MAXVEX];
	int top,rear; 
}Stack;

typedef struct{
	int stack[MAXVEX];
	int top,rear;
}Quene;

int visited[MAXVEX];

//�ڽӾ��󷽷���ͼ 
typedef struct{
	int arcs[MAXVEX][MAXVEX];	//�� 
	char vex[MAXVEX];			//������Ϣ 
	int vexnum;					//������Ŀ 
	int arcnum;					//�ߵ����� 
}AdjMatrix;						//�ڽӾ��� 

int LocateVex(AdjMatrix *G,char v){
	int i;
	for(i=1;i<=G->vexnum;i++)
		if(G->vex[i]==v)
			return i;
	return 0;
}

//��� 
void Enter(Quene *S,int index){
	S->rear++;
	S->stack[S->rear]=index;	
} 

//����
int Quite(Quene *S){
	S->top++;
	return S->stack[S->top];
}

//�пն���
int Empty_Q(Quene *S){
	if(S->rear==S->top){
		return 1;
	}
	else{
		return 0; 
	}
} 

//ȡ��ͷԪ��
int First_Q(Quene *S){
	return S->stack[S->top+1];
} 

//��ջ 
void Push(Stack *S,int index){
	S->top++;
	S->stack[S->top]=index;	
}

//��ջ 
int Pop(Stack *S){
	S->top--;
	return S->stack[S->top+1];	
}

//�п� 
int Empty(Stack *S){
	if(S->rear==S->top){
		return 1;
	}
	else{
		return 0;
	}
}

//ȡջ��һ��Ԫ�� 
int First(Stack *S){
	return S->stack[S->top+1];	
}

//�ڽӾ��󴴽�����ͼ
void Create(AdjMatrix *G) {
	int i,j,k,weight;
	char vex1,vex2;
	printf("�������������еĶ������ͱ�����\n");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	for(i=1; i<=G->vexnum;i++)
		for(j=1;j<=G->vexnum;j++)
			G->arcs[i][j]=INFINITY;
	
	printf("��������������%d�����㣺\n",G->vexnum);
	for(i=1;i<=G->vexnum;i++){
		printf("No.%d�����㣺����V",i);
		getchar();
		scanf("%c",&G->vex[i]);
	}
	printf("��������������%d���ߣ�\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		printf("\nNo.%d���ߣ�\n\t����V",k+1);
		getchar();
		scanf("%c->%c",&vex1,&vex2);
		weight=1;
		i=LocateVex(G,vex1);
		j=LocateVex(G,vex2);
		G->arcs[i][j]=weight;
		G->arcs[j][i]=weight;
	}
} 

//���ͼ 
void Display(AdjMatrix *G){
	int i,j;
	printf("\nͼ���£�\n");
	for(i=1;i<=G->vexnum;i++){
		for(j=1;j<=i;j++){
			if(G->arcs[i][j]!=INFINITY){
				printf("%c<------->%c:%d\n",G->vex[i],G->vex[j],G->arcs[i][j]);
			}
		}	
	}
}

////��ȵݹ����ȱ�����ͨ��ͼ
void dgDFS(AdjMatrix *G, int index){
	int i,w;
	visited[index]=1;
	printf("%c",G->vex[index]);
	for(i=1;i<=G->vexnum;i++){
		if(G->arcs[index][i]!=INFINITY&&visited[i]!=1){
			dgDFS(G,i);
		}
	}	
}

//������ȱ�����ͨ��ͼ 
void BFS(AdjMatrix *G, int index){
	int visited[MAXVEX];			//���÷��ʱ�־���� 
	Quene *S=(Quene*)malloc(sizeof(Quene));
	S->top=S->rear=-1;
	int i,w,v;
	for(i=1;i<=G->vexnum;i++){
		visited[i]=0;				//��ʼ����־���� 
	}
	printf("\n������ȱ����ǵݹ飺\n");
	Enter(S,index);
	while(!Empty_Q(S)){
		v=First_Q(S);
		if(!visited[v]){
			printf("%c",G->vex[v]);
			visited[v]=1;
		}
		for(i=1;i<=G->vexnum;i++){
			if(G->arcs[v][i]!=INFINITY&&visited[i]!=1){
				printf("%c",G->vex[i]);
				visited[i]=1;
				Enter(S,i);
			}
		}
		Quite(S);		
	}
}
//
////������ȱ�����ͨ��ͼ
//void DFS(AdjMatrix *G, int index){
//	int visited[MAXVEX];			//���÷��ʱ�־���� 
//	Stack *S=(Stack*)malloc(sizeof(Stack));
//	S->top=S->rear=-1;
//	int i,w,v;
//	for(i=1;i<=G->vexnum;i++){
//		visited[i]=0;				//��ʼ����־���� 
//	}
//	printf("\n������ȱ����ǵݹ飺\n");
//	Push(S,index);
//	while(!Empty(S)){
//		v=First(S);
//		if(!visited[v]){
//			printf("%c",G->vex[v]);
//			visited[v]=1;
//		}
//		for(i=1;i<=G->vexnum;i++){
//			if(G->arcs[v][i]!=INFINITY&&visited[i]!=1){
//				printf("%c",G->vex[i]);
//				visited[i]=1;
//				Push(S,i);
//				v=i;
//				break;
//			}
//		}
//		if(i==G->vexnum+1){
//			Pop(S);			
//		}
//	}
//} 

//������ȱ�����ͨ��ͼ
void DFS(AdjMatrix *G, int index){
	int visited[MAXVEX];			//���÷��ʱ�־���� 
	Stack *S=(Stack*)malloc(sizeof(Stack));
	S->top=S->rear=-1;
	int i,w,v;
	for(i=1;i<=G->vexnum;i++){
		visited[i]=0;				//��ʼ����־���� 
	}
	printf("\n������ȱ����ǵݹ飺");
	Push(S,index);
	while(!Empty(S)){
		v=First(S);
		if(!visited[v]){
			printf("%c",G->vex[v]);
			visited[v]=1;
		}
		for(i=1;i<=G->vexnum;i++){
			if(G->arcs[v][i]!=INFINITY&&visited[i]!=1){
				printf("%c",G->vex[i]);
				visited[i]=1;
				Push(S,i);
				v=i;
				break;
			}
		}
		if(i==G->vexnum+1){
			Pop(S);			
		}
	}
} 

//��� 
void InDu(AdjMatrix *G){
	int cnt[G->vexnum];
	int i,j;
	for(i = 1;i <=G->vexnum;i++)
		cnt[i] = 0;
	printf("In Du:\n");
	for(i = 1;i <=G->vexnum;i++)
	{
		for(j = 1;j <=G->vexnum;j++)
			if(G->arcs[j][i]== 1)
				cnt[i]++;
		printf("%c---%d\n",G->vex[i],cnt[i]);
	} 
}

//���� 
void OutDu(AdjMatrix *G)
{
	int cnt[G->vexnum];
	int i,j;
	printf("Out Du:\n");
	for(i = 1;i <=G->vexnum;i++)
		cnt[i] = 0;
	for(i = 1;i <=G->vexnum;i++)
	{
		for(j = 1;j <=G->vexnum;j++)
			if(G->arcs[i][j]== 1)
				cnt[i]++;
		printf("%c---%d\n",G->vex[i],cnt[i]);
	}		
 }       
    
int main(){
	AdjMatrix *G ;
	int i;
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	Create(G);
	for(i=1;i<=G->vexnum;i++){
		visited[i]=0;
	}
	Display(G);
	BFS(G,1); 
	DFS(G,1);
	printf("\n������ȱ�����\n"); 
	dgDFS(G,1);
	OutDu(G);
	InDu(G);
	return 0;
}
