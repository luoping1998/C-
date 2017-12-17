#include <stdio.h>
#include <stdlib.h>


#define MAX_VALUE 10


typedef struct EdgeNode{//边顶点
    int index;//该顶点下标
    struct EdgeNode *next;//存储下一个边顶点


}EdgeNode;
typedef struct HeadNode{//表顶点
    char data;
    EdgeNode *edgeNode;


}HeadNode,AdjacencyList[MAX_VALUE];


typedef struct Graph{//图
    AdjacencyList list;
    int vexNum;//当前顶点数
    int edgeNum;//当前边数




}Graph;
//找到该元素所在的下标
int locate(Graph *graph,char ch){
    int i ;
    for(i = 0;i<graph->vexNum;i++){
        if(graph->list[i].data==ch)
            return i;
    }


    return -1;


}


//构造邻接表图
Graph *createGraph(){
    Graph *graph;
    char ch;
    graph = (Graph*)malloc(sizeof(Graph));
    graph->edgeNum = 0;
    graph->vexNum = 0;
    printf("输入顶点回车退出输入\n");

    while((ch=getchar())!='\n'){
        //构造顶点表
        graph->list[graph->vexNum].data = ch;
        graph->list[graph->vexNum].edgeNode = NULL;
        graph->vexNum++;
        printf("请输入下一个顶点 回车表示结束\n");
    	getchar();
	}
    int i ;
    
    printf("当前输入的顶点数如下:\n");
    for(i = 0;i<graph->vexNum;i++){
        printf("%c  ",graph->list[i].data);
    }
    //构造边

    printf("\n请输入边数\n");
    scanf("%d",&graph->edgeNum);
    EdgeNode *node;
    for(i = 0;i<graph->edgeNum;i++){

        printf("输入边的顶点值\n");
        fflush(stdin);
        char valueA,valueB;
        scanf("%c->%c",&valueA,&valueB);
        int indexA = locate(graph,valueA);
        int indexB = locate(graph,valueB);

        //始终在头节点后插入新元素
        node = (EdgeNode*)malloc(sizeof(EdgeNode));
        node->index = indexA;
        node->next = graph->list[indexB].edgeNode;
        graph->list[indexB].edgeNode = node;

        //因为无向图 所以另外一个表顶点也要插入这条路径的边顶点
        node = (EdgeNode*)malloc(sizeof(EdgeNode));
        node->index = indexB;
        node->next = graph->list[indexA].edgeNode;
        graph->list[indexA].edgeNode = node;
    }
    return graph;
}

////输出矩阵
//void outputGraph(Graph *graph){
//    //依次输入每个表顶点的链表
//
//    int i ;
//    EdgeNode *temp;
//    for(i = 0;i<graph->vexNum;i++){
//        printf("第%d个表顶点:",i);
//        printf("%c  ",graph->list[i].data);//表头顶点的值
//        temp = graph->list[i].edgeNode;
//        while(temp){
//            //对该链表进行遍历
//            printf("%c  ",graph->list[temp->index]);
//            temp = temp->next;
//        }
//        printf("\n");
//    }
//}

//广度优先搜索
void BFSGraph(Graph *graph){
    int i ;
    int visited[graph->vexNum];
    //对访问标志数组的初始化

    for(i = 0;i<graph->vexNum;i++){
        visited[i] = 0;
    }

    EdgeNode *temp;
    for(i = 0;i<graph->vexNum;i++){
        if(visited[i]==0){
         work(graph->list[i].data);//访问表头节点
         visited[i]=1;//设置访问标签
        }
         //对该链表进行遍历访问
         temp = graph->list[i].edgeNode;
         while(temp){
            if(visited[temp->index]==0){//如果该顶点未访问过
                work(graph->list[temp->index].data);
                visited[temp->index] = 1;//设置访问标签
            }
            temp = temp->next;
    }

    }

}


//深度优先搜索
void DFSGraph(Graph *graph){
    int i ;
    int visited[graph->vexNum];
    for(i = 0;i<graph->vexNum;i++){
        visited[i] = 0;
    }
    for(i = 0;i<graph->vexNum;i++){
        if(visited[i]==0){
            work(graph->list[i].data);//访问表头节点
            visited[i]=1;//设置访问标签
        }


        int index = graph->list[i].edgeNode->index;
        DFS(graph,index,visited);
    }
}

//深度搜索
void DFS(Graph *graph,int index,int *visited){
    EdgeNode *temp;


    if(visited[index]==0){
        work(graph->list[index].data);//访问表头节点
        visited[index]=1;//设置访问标签
    }
    temp = graph->list[index].edgeNode;
    while(temp){
        if(visited[temp->index]==0){//如果该节点之前未访问过
            DFS(graph,temp->index,visited);//深入下一层
        }

        temp = temp->next;
    }
}
//图元素操作函数
void work(char ch){
    printf("%c  ",ch);


}
int main()
{
    Graph * p = createGraph();
//    outputGraph(p);
    printf("广度优先搜索遍历输出:\n");
    BFSGraph(p);
    printf("\n深度优先搜索遍历输出:\n");
    DFSGraph(p);
    return 0;
}
