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

//邻接矩阵方法存图 
typedef struct{
	int arcs[MAXVEX][MAXVEX];	//边 
	char vex[MAXVEX];			//顶点信息 
	int vexnum;					//顶点数目 
	int arcnum;					//边的数量 
}AdjMatrix;						//邻接矩阵 

int LocateVex(AdjMatrix *G,char v){
	int i;
	for(i=1;i<=G->vexnum;i++)
		if(G->vex[i]==v)
			return i;
	return 0;
}

//入队 
void Enter(Quene *S,int index){
	S->rear++;
	S->stack[S->rear]=index;	
} 

//出队
int Quite(Quene *S){
	S->top++;
	return S->stack[S->top];
}

//判空队列
int Empty_Q(Quene *S){
	if(S->rear==S->top){
		return 1;
	}
	else{
		return 0; 
	}
} 

//取队头元素
int First_Q(Quene *S){
	return S->stack[S->top+1];
} 

//入栈 
void Push(Stack *S,int index){
	S->top++;
	S->stack[S->top]=index;	
}

//出栈 
int Pop(Stack *S){
	S->top--;
	return S->stack[S->top+1];	
}

//判空 
int Empty(Stack *S){
	if(S->rear==S->top){
		return 1;
	}
	else{
		return 0;
	}
}

//取栈第一个元素 
int First(Stack *S){
	return S->stack[S->top+1];	
}

//邻接矩阵创建无向图
void Create(AdjMatrix *G) {
	int i,j,k,weight;
	char vex1,vex2;
	printf("请输入无向网中的顶点数和边数：\n");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	for(i=1; i<=G->vexnum;i++)
		for(j=1;j<=G->vexnum;j++)
			G->arcs[i][j]=INFINITY;
	
	printf("请输入无向网中%d个顶点：\n",G->vexnum);
	for(i=1;i<=G->vexnum;i++){
		printf("No.%d个顶点：顶点V",i);
		getchar();
		scanf("%c",&G->vex[i]);
	}
	printf("请输入无向网中%d条边：\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		printf("\nNo.%d条边：\n\t顶点V",k+1);
		getchar();
		scanf("%c->%c",&vex1,&vex2);
		weight=1;
		i=LocateVex(G,vex1);
		j=LocateVex(G,vex2);
		G->arcs[i][j]=weight;
		G->arcs[j][i]=weight;
	}
} 

//输出图 
void Display(AdjMatrix *G){
	int i,j;
	printf("\n图如下：\n");
	for(i=1;i<=G->vexnum;i++){
		for(j=1;j<=i;j++){
			if(G->arcs[i][j]!=INFINITY){
				printf("%c<------->%c:%d\n",G->vex[i],G->vex[j],G->arcs[i][j]);
			}
		}	
	}
}

////深度递归优先便利连通子图
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

//广度优先遍历连通子图 
void BFS(AdjMatrix *G, int index){
	int visited[MAXVEX];			//设置访问标志数组 
	Quene *S=(Quene*)malloc(sizeof(Quene));
	S->top=S->rear=-1;
	int i,w,v;
	for(i=1;i<=G->vexnum;i++){
		visited[i]=0;				//初始化标志数组 
	}
	printf("\n广度优先遍历非递归：\n");
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
////深度优先便利连通子图
//void DFS(AdjMatrix *G, int index){
//	int visited[MAXVEX];			//设置访问标志数组 
//	Stack *S=(Stack*)malloc(sizeof(Stack));
//	S->top=S->rear=-1;
//	int i,w,v;
//	for(i=1;i<=G->vexnum;i++){
//		visited[i]=0;				//初始化标志数组 
//	}
//	printf("\n深度优先遍历非递归：\n");
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

//深度优先便利连通子图
void DFS(AdjMatrix *G, int index){
	int visited[MAXVEX];			//设置访问标志数组 
	Stack *S=(Stack*)malloc(sizeof(Stack));
	S->top=S->rear=-1;
	int i,w,v;
	for(i=1;i<=G->vexnum;i++){
		visited[i]=0;				//初始化标志数组 
	}
	printf("\n深度优先遍历非递归：");
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

//入度 
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

//出度 
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
	printf("\n深度优先遍历：\n"); 
	dgDFS(G,1);
	OutDu(G);
	InDu(G);
	return 0;
}
