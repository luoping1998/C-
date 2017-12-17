#include <stdio.h>
#include <stdlib.h>


#define MAX_VALUE 10


typedef struct EdgeNode{//�߶���
    int index;//�ö����±�
    struct EdgeNode *next;//�洢��һ���߶���


}EdgeNode;
typedef struct HeadNode{//����
    char data;
    EdgeNode *edgeNode;


}HeadNode,AdjacencyList[MAX_VALUE];


typedef struct Graph{//ͼ
    AdjacencyList list;
    int vexNum;//��ǰ������
    int edgeNum;//��ǰ����




}Graph;
//�ҵ���Ԫ�����ڵ��±�
int locate(Graph *graph,char ch){
    int i ;
    for(i = 0;i<graph->vexNum;i++){
        if(graph->list[i].data==ch)
            return i;
    }


    return -1;


}


//�����ڽӱ�ͼ
Graph *createGraph(){
    Graph *graph;
    char ch;
    graph = (Graph*)malloc(sizeof(Graph));
    graph->edgeNum = 0;
    graph->vexNum = 0;
    printf("���붥��س��˳�����\n");

    while((ch=getchar())!='\n'){
        //���춥���
        graph->list[graph->vexNum].data = ch;
        graph->list[graph->vexNum].edgeNode = NULL;
        graph->vexNum++;
        printf("��������һ������ �س���ʾ����\n");
    	getchar();
	}
    int i ;
    
    printf("��ǰ����Ķ���������:\n");
    for(i = 0;i<graph->vexNum;i++){
        printf("%c  ",graph->list[i].data);
    }
    //�����

    printf("\n���������\n");
    scanf("%d",&graph->edgeNum);
    EdgeNode *node;
    for(i = 0;i<graph->edgeNum;i++){

        printf("����ߵĶ���ֵ\n");
        fflush(stdin);
        char valueA,valueB;
        scanf("%c->%c",&valueA,&valueB);
        int indexA = locate(graph,valueA);
        int indexB = locate(graph,valueB);

        //ʼ����ͷ�ڵ�������Ԫ��
        node = (EdgeNode*)malloc(sizeof(EdgeNode));
        node->index = indexA;
        node->next = graph->list[indexB].edgeNode;
        graph->list[indexB].edgeNode = node;

        //��Ϊ����ͼ ��������һ������ҲҪ��������·���ı߶���
        node = (EdgeNode*)malloc(sizeof(EdgeNode));
        node->index = indexB;
        node->next = graph->list[indexA].edgeNode;
        graph->list[indexA].edgeNode = node;
    }
    return graph;
}

////�������
//void outputGraph(Graph *graph){
//    //��������ÿ�����������
//
//    int i ;
//    EdgeNode *temp;
//    for(i = 0;i<graph->vexNum;i++){
//        printf("��%d������:",i);
//        printf("%c  ",graph->list[i].data);//��ͷ�����ֵ
//        temp = graph->list[i].edgeNode;
//        while(temp){
//            //�Ը�������б���
//            printf("%c  ",graph->list[temp->index]);
//            temp = temp->next;
//        }
//        printf("\n");
//    }
//}

//�����������
void BFSGraph(Graph *graph){
    int i ;
    int visited[graph->vexNum];
    //�Է��ʱ�־����ĳ�ʼ��

    for(i = 0;i<graph->vexNum;i++){
        visited[i] = 0;
    }

    EdgeNode *temp;
    for(i = 0;i<graph->vexNum;i++){
        if(visited[i]==0){
         work(graph->list[i].data);//���ʱ�ͷ�ڵ�
         visited[i]=1;//���÷��ʱ�ǩ
        }
         //�Ը�������б�������
         temp = graph->list[i].edgeNode;
         while(temp){
            if(visited[temp->index]==0){//����ö���δ���ʹ�
                work(graph->list[temp->index].data);
                visited[temp->index] = 1;//���÷��ʱ�ǩ
            }
            temp = temp->next;
    }

    }

}


//�����������
void DFSGraph(Graph *graph){
    int i ;
    int visited[graph->vexNum];
    for(i = 0;i<graph->vexNum;i++){
        visited[i] = 0;
    }
    for(i = 0;i<graph->vexNum;i++){
        if(visited[i]==0){
            work(graph->list[i].data);//���ʱ�ͷ�ڵ�
            visited[i]=1;//���÷��ʱ�ǩ
        }


        int index = graph->list[i].edgeNode->index;
        DFS(graph,index,visited);
    }
}

//�������
void DFS(Graph *graph,int index,int *visited){
    EdgeNode *temp;


    if(visited[index]==0){
        work(graph->list[index].data);//���ʱ�ͷ�ڵ�
        visited[index]=1;//���÷��ʱ�ǩ
    }
    temp = graph->list[index].edgeNode;
    while(temp){
        if(visited[temp->index]==0){//����ýڵ�֮ǰδ���ʹ�
            DFS(graph,temp->index,visited);//������һ��
        }

        temp = temp->next;
    }
}
//ͼԪ�ز�������
void work(char ch){
    printf("%c  ",ch);


}
int main()
{
    Graph * p = createGraph();
//    outputGraph(p);
    printf("������������������:\n");
    BFSGraph(p);
    printf("\n������������������:\n");
    DFSGraph(p);
    return 0;
}
