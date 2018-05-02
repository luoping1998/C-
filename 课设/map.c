#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "stack.c"
#define MAXVEX 50
#define INFINITY 3276767
//点 
typedef struct{
	char name[20];
}Vertype;

typedef struct{
	int pay;
	int flag;
}Mon;

typedef struct{
	int month;
	int day; 
	int hours;
	int minutes;
	int seconds;
}Time;

typedef struct{
	int type;		//type:0 火车；1 汽车； 2 火车； 3 飞机； 4 步行；
	int money;		//花费 
	Time sTime;
	Time eTime;	
	char traNum[20];
}Way;

//边 

typedef struct{
//	int end;		//边的结束点 
	int distance;	//路程
	Way Method[MAXVEX];
	int count;
}Acretype;

//图 
typedef struct{
	Acretype acre[MAXVEX][MAXVEX];	//边信息 
	Vertype vex[MAXVEX];			//顶点信息
	int vexnum; 
	int acrnum;
}AdjMatrix;

int LocateVex(AdjMatrix *G,char *v){
	int i;
	for(i=0;i<G->vexnum;i++)
		if(strcmp(G->vex[i].name,v)==0)
			return i;
//	printf("City %s not exist!\n",v); 
	return -1;
}

//将Type转换成方式str 
char* Translate(int index){
	char* str =(char *)malloc(sizeof(char)*10);
	if(index == 1 ){
		strcpy(str,"Train");
	}else if(index == 2){
		strcpy(str,"Bus");
	}else if(index == 3){
		strcpy(str,"Airplan");
	}else if(index == 4){
		strcpy(str,"Foot");
	}else {
		strcpy(str,"Noway");
	}
	return str;
}

AdjMatrix *Create(){     //创建有向图的邻接矩阵 
	AdjMatrix *G;
	Time begin,over;
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	int weight,pay,Ty;
	char str[20],start[20],end[20];
	char N[20];
	int index;
	int count = 0;
	FILE *fp;   
	if((fp = fopen("./vex.txt","r")) == NULL)      //判断文件是否存在及可读  
    {	   
       	printf("Open Falied!");   
       	return ;   
    }   
  //  printf("Passed openfile.\n");
    while (!feof(fp))                                   //循环读取每一行，直到文件尾  
    {   
    //	printf("now %d.\n",count);
       	fscanf(fp,"%d %s",&index,str); 
       	strcpy(G->vex[index].name,str);
    //   	printf("count = %d | index = %d | str = %s \n",count,index,str);
		count++;
	}
//	printf("now end.\n");
    fclose(fp);                  
//	printf("now vexnum = %d.\n",count);	
	G->vexnum=count;					//给图的节点计数赋值 
	G->acrnum=0;
	count = 0;
	int i,j,k;
	
//	printf("now chushihua.\n");
	//初始化邻接矩阵 
	for(i=0;i<G->vexnum;i++)
		for(j=0;j<=G->vexnum;j++){
			G->acre[i][j].distance=0;
			G->acre[i][j].count=0;
		}
			
	//printf("now enter.\n");
	//录入边的信息 
    Acretype code;                    //读取缓冲区  
    if((fp = fopen("./acre.txt","r")) == NULL)      //判断文件是否存在及可读  
    {	   
       	printf("Open Falied!");   
       	return ;   
    }   
    while (!feof(fp))                                   //循环读取每一行，直到文件尾  
    {   
    //	printf("now %d.\n",count);
       	fscanf(fp,"%s %s %10s %d.%d %d:%d:%d %d.%d %d:%d:%d %d %d %d",start,end,N,&begin.month,&begin.day,&begin.hours,
		   &begin.minutes,&begin.seconds,&over.month,&over.day,&over.hours
		   ,&over.minutes,&over.seconds,&weight,&pay,&Ty); 
       	
       	i = LocateVex(G,start);
       	j = LocateVex(G,end);
       	if(i!=-1 && j!=-1){
       		G->acre[i][j].distance=weight;
       		strcpy(G->acre[i][j].Method[G->acre[i][j].count].traNum,N);
       		G->acre[i][j].Method[G->acre[i][j].count].money=pay;
      	 	G->acre[i][j].Method[G->acre[i][j].count].type=Ty;
       		G->acre[i][j].Method[G->acre[i][j].count].sTime=begin;
       		G->acre[i][j].Method[G->acre[i][j].count].eTime=over;
       		G->acre[i][j].count++;
			count ++;
		}
       	
     // printf("startTime:%d.%d %d:%d:%d | endTime:%d.%d %d:%d:%d\n",begin.month,begin.day,begin.hours,begin.minutes,begin.seconds,over.month,over.day,over.hours,over.minutes,over.seconds);
        	//DO SOMETHING ELSE  
	}
    fclose(fp);                                         //关闭文件   
	G->acrnum=count;
	
	return G;
}

//输出图 
void Display(AdjMatrix *G){
	int i,j,k;
	char str[10];
	printf("\n\n  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
	printf("  *                                                                                                                                                             *\n");
	printf("  *\t\t\t\t\t\t\t\t   Car        Schedule\t\t\t\t\t                                                *\n");
	printf("  *                                                                                                                                                             *\n");
	printf("  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
	printf("  |        Start   City       |         End   City       |   Train  Num   |     Start  Time     |       End   Time    |   Distance   |     Pay    |     Type    |\n");
	printf("  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			if(G->acre[i][j].distance!=0){
				for(k=0;k<G->acre[i][j].count;k++){
					strcpy(str,Translate(G->acre[i][j].Method[k].type));
					printf("  | %18s        | %18s       |%10s      |   %2d.%2d %2d: %2d: %2d  |   %2d.%2d %2d: %2d: %2d  | %8d     |%8d    |  %8s   |\n",
							G->vex[i].name,G->vex[j].name,G->acre[i][j].Method[k].traNum,G->acre[i][j].Method[k].sTime.month,G->acre[i][j].Method[k].sTime.day,G->acre[i][j].Method[k].sTime.hours,G->acre[i][j].Method[k].sTime.minutes,G->acre[i][j].Method[k].sTime.seconds,
							G->acre[i][j].Method[k].eTime.month,G->acre[i][j].Method[k].eTime.day,G->acre[i][j].Method[k].eTime.hours,G->acre[i][j].Method[k].eTime.minutes,G->acre[i][j].Method[k].eTime.seconds,G->acre[i][j].distance,G->acre[i][j].Method[k].money,str);
				}
			}
		}	
	}
	printf("  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
}

//添加节点或者路径信息 
AdjMatrix * Add(AdjMatrix *G){
	int index;
	char ch;
	char sCity[20],eCity[20],num[20];
	Time begin,over;
	int distance,pay,type;
	int end;
	FILE *fp,*fq;
	char str[20];
	fflush(stdin);
	printf("\t\t\t\t   Do u want to add City ?(Y/N)：   ");
	fflush(stdin);
	ch = getchar();
	while(ch=='Y'||ch=='y'){
		printf("\t\t\t\t   Enter City Name u want to add :   ");
		fflush(stdin);
		gets(str);
		fflush(stdin);
		index = G->vexnum;
		//printf("str=%s | index = %d\n",str,index);
		fflush(stdin);
		if(LocateVex(G,str)==-1){				//地名不存在 
			strcpy(G->vex[index].name,str);
			if((fq = fopen("./vex.txt","a+")) == NULL)      //判断文件是否存在及可读  
    		{	   
    	  	 	printf("Open Falied!");   
      	 		return 0;   
    		} else{
    			fflush(stdin);
    			fprintf(fq,"\n%d %s",index,str);
				G->vexnum++;
				//printf("str=%s | vexnum = %d\n",str,G->vexnum);	
				fclose(fq);
			}  
    		
		}else{
			printf("\t\t\t\t   The City has exited!\n");
		}
		printf("\t\t\t\t   Continue?(Y/N)  ");
		ch=getchar();
		fflush(stdin);
	}
	
	printf("\t\t\t\t   Do u want to add any Information ?(Y/N):   ");
	fflush(stdin);
	ch = getchar();
	printf("\t\t\t\t   Add Information:\n");
	printf("\t\t\t\t   Now Enter the pass information %s can lead to :\n");
	printf("\t\t\t\t   For example:\tChengdu(startCity) Changsha(endCity) G901 1.2 10:20:08(startTime) 1.3 12:34:19(EndTime) 1000 300 0 \n\t\t\t\t   ");
	
	if((fp = fopen("./acre.txt","a+")) == NULL)      //判断文件是否存在及可读  
    {	   
       	printf("Open Falied!");   
       	return 0;   
    }   
    while(ch=='y'||ch == 'Y'){
    	printf("\t\t\t\t   ");
		scanf("%s %s %s %d.%d %d:%d:%d %d.%d %d:%d:%d %d %d %d",sCity,eCity,num,&begin.month,&begin.day,&begin.hours,&begin.minutes,&begin.seconds,
		&over.month,&over.day,&over.hours,&over.minutes,&over.seconds,&distance,&pay,&type);
		fflush(stdin);
		fprintf(fp,"\n%s %s %s %d.%d %d:%d:%d %d.%d %d:%d:%d %d %d %d",sCity,eCity,num,begin.month,begin.day,begin.hours,begin.minutes,begin.seconds,
		over.month,over.day,over.hours,over.minutes,over.seconds,distance,pay,type); 
		printf("\t\t\t\t   Continue?(Y/N)    ");
		ch=getchar();
		fflush(stdin);
	}
    fclose(fp);     
    AdjMatrix *Copy=Create();
	printf("\t\t\t\t   End.\n");             
	return Copy;
}

AdjMatrix * Delete(AdjMatrix *G){
	FILE *fq,*fp,*ff;
	char str[20],ch;
	char sCity[20],eCity[20];
	Time begin,over;
	int distance,pay,type;
	int i,j,k,arecs;
	int count=0;
	arecs=0;
	Time t;
	t.hours=t.day=t.minutes=t.month=t.seconds=0;
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			if(G->acre[i][j].count!=0){
				arecs++;
			}
		}
	}
	fflush(stdin);
	printf("\t\t\t\t   Enter the name u want to DELETE:   ");
	gets(str);
	int index = LocateVex(G,str);
	if(index==-1) {
		printf("\t\t\t\t   City not Exist!\n");
		return G;
	}
	fflush(stdin);
	for(i=index;i<G->vexnum;i++){
		strcpy(G->vex[i].name,G->vex[i+1].name);
	}
	G->vexnum--;
	if((fq = fopen("./vex.txt","w+")) == NULL)      //判断文件是否存在及可读  
    {	   
    	printf("Open Falied!");   
      	return ;   
    }  else{
    	for(i=0;i<G->vexnum;i++){
    		if(i==G->vexnum-1){
    			fprintf(fq,"%d %s",i,G->vex[i].name);	
			} else{
				fprintf(fq,"%d %s\n",i,G->vex[i].name);
			}
   		}
	}
	fclose(fq);
	
	AdjMatrix *Copy=Create();
	if((fp = fopen("./acre.txt","w+")) == NULL)      //判断文件是否存在及可读  
    {	   
    	printf("Open Falied!");   
      	return G;   
    }  else{
			for(i=0;i<Copy->vexnum;i++){
				for(j=0;j<Copy->vexnum;j++){
					if(Copy->acre[i][j].count!=0){
						strcpy(sCity,Copy->vex[i].name);
    					strcpy(eCity,Copy->vex[j].name);
    					for(k=0;k<Copy->acre[i][j].count;k++){
    						if(count==Copy->acrnum-1){
    							fprintf(fp,"%s %s %s %d.%d %d:%d:%d %d.%d %d:%d:%d %d %d %d" ,
								sCity,eCity,Copy->acre[i][j].Method[k].traNum,Copy->acre[i][j].Method[k].sTime.month,Copy->acre[i][j].Method[k].sTime.day,
								Copy->acre[i][j].Method[k].sTime.hours,Copy->acre[i][j].Method[k].sTime.minutes,
								Copy->acre[i][j].Method[k].sTime.seconds,Copy->acre[i][j].Method[k].eTime.month,
								Copy->acre[i][j].Method[k].eTime.day,Copy->acre[i][j].Method[k].eTime.hours,
								Copy->acre[i][j].Method[k].eTime.minutes,Copy->acre[i][j].Method[k].eTime.seconds,
								Copy->acre[i][j].distance,Copy->acre[i][j].Method[k].money,Copy->acre[i][j].Method[k].type);
							} else{
								fprintf(fp,"%s %s %s %d.%d %d:%d:%d %d.%d %d:%d:%d %d %d %d\n" ,
								sCity,eCity,Copy->acre[i][j].Method[k].traNum,Copy->acre[i][j].Method[k].sTime.month,Copy->acre[i][j].Method[k].sTime.day,
								Copy->acre[i][j].Method[k].sTime.hours,Copy->acre[i][j].Method[k].sTime.minutes,
								Copy->acre[i][j].Method[k].sTime.seconds,Copy->acre[i][j].Method[k].eTime.month,
								Copy->acre[i][j].Method[k].eTime.day,Copy->acre[i][j].Method[k].eTime.hours,
								Copy->acre[i][j].Method[k].eTime.minutes,Copy->acre[i][j].Method[k].eTime.seconds,
								Copy->acre[i][j].distance,Copy->acre[i][j].Method[k].money,Copy->acre[i][j].Method[k].type);
								count++;
							}
						}			
					}
				}
			}
		}
	fclose(fp);
	return Copy;
}

		
void printWay(AdjMatrix *G,int vex[][MAXVEX],int index){
	int i=0;
	while(vex[index][i]!=index){
		printWay(G,vex,vex[index][i]);
		i++;
	}
	printf("----> %s ",G->vex[index].name);
}

void printMoney(AdjMatrix *G,int vex[][MAXVEX],int start,int index,Mon money[][MAXVEX]){
	int i=0;
	while(vex[index][i]!=index){
		printMoney(G,vex,index,vex[index][i],money);
		i++;
	}
	printf("----> %s [%s %s %d]",G->vex[index].name,
	G->acre[start][index].Method[money[start][index].flag].traNum,
	Translate(G->acre[start][index].Method[money[start][index].flag].type),money[start][index].pay);
}

//最少钱 
void Money(AdjMatrix *G,int start,int end,int dist[],int path[]){
	int i,j,k,p,flag;
	int mindist;
	int vex[MAXVEX][MAXVEX];
	Mon pay[MAXVEX][MAXVEX];
	int minmoney=INFINITY;
	
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			vex[i][j]=-1;
			pay[i][j].pay=0;
		}
	}
	
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			minmoney=INFINITY;
			if(G->acre[i][j].distance!=0){
				//printf("\ni=%d j=%d \n",i,j);
				for(k=0;k<G->acre[i][j].count;k++){
					//printf("k = %d |come in\n",k);
					if(minmoney>G->acre[i][j].Method[k].money){
						//printf("k = %d | min = %d | acre = %d\n",k,minmoney,G->acre[i][j].Method[k].money);
						minmoney=G->acre[i][j].Method[k].money;
						pay[i][j].flag=k;
						
					}
				}
				pay[i][j].pay=minmoney;
				//printf("pay[%d][%d].pay=%d\t\n",i,j,minmoney);
			}
		}
	}
	
	for(i=0;i<G->vexnum;i++){
		path[i]=0;
	}
	
	for(i=0;i<G->vexnum;i++){
		dist[i]=pay[start][i].pay;
		if(dist[i]!=0) vex[i][0]=i;			//存储点 
	}
	
	int min;
	int c=G->vexnum;
	path[start]=1;			//表示start点在S中 
	for(j=0;j<G->vexnum;j++){
		mindist=INFINITY;
		for(i=0;i<G->vexnum;i++){
			if((dist[i]!=0)&&(path[i]!=1)){
				if(mindist>dist[i]){
					mindist=dist[i];
					k=i;
				}
			} 
			/*else if((path[i]==0)&&(dist[i]==0)){
				int count =CountG(G,i);
				if(!count) {
					int mm=INFINITY,t,r,dis[G->vexnum];
					int diCou=0;
					int d=0;
					while(!CountG(G,i)){
						for(r=0;r<G->vexnum;r++){
							if(mm>pay[r][i].pay){
								mm=pay[r][i].pay;
								t=r;
							}
						}
						diCou++;
						if(t==start){
							dis[G->vexnum-diCou]=t;d+=mm;
							break;
						} else{
							dis[G->vexnum-diCou]=t;
							d+=mm;
						}				
					}
					
					for(r=G->vexnum-1;r>G->vexnum-diCou;i--){
						printf("dis[%d]=%d\t",r,dis[r]);
					}
					printf("\n");
				}
			}*/ 
		}
	//	printf("mindist=%d | k=%d\n",mindist,k);
		
		min=INFINITY;
		path[k]=1;		//在start中 
		
		int f;
		for(i=0;i<G->vexnum;i++){
			if(pay[k][i].pay!=0){
				if(min>pay[k][i].pay){
					min=pay[k][i].pay;
					f=i;
				}
			}
		}
		//printf("min = %d | f = %d\n",min,f);
		
		if(dist[f]==0){			//不在S中 
			dist[f]=min+mindist;
			vex[f][0]=k;
			p=0;
			while(vex[f][p]!=-1){
				p++;
			}
			vex[f][p]=f;
			vex[f][p-1]=k;
		} else {
			if(dist[f]>(min+mindist)){
				dist[f]=min+mindist;
				p=0;
				while(vex[f][p]!=-1){
					p++;
				}
				vex[f][p]=f;
				vex[f][p-1]=k;
			}
		}
		/*for(i=0;i<G->vexnum;i++){
			printf("dist[%d]=%d | path[%d]=%d\t",i,dist[i],i,path[i]);
		}
		printf("\n");*/
	}
	/*
	for(i=0;i<G->vexnum;i++){
		printf("2:  dist[%d] = %d\t",i,dist[i]);
	}
	for(i=0;i<G->vexnum;i++){
		printf("\npath[%d] = %d\t",i,path[i]);
	}
	*/
	if(dist[end]!=0){
		printf("\n\tThe cheapest way from %s to %s is %d yuan:\n\n\t%s ",G->vex[start].name,G->vex[end].name,dist[end],G->vex[start].name);
		printMoney(G,vex,start,end,pay);	
	} else{
		printf("\n\tThere is no way from %s to %s \n",G->vex[start].name,G->vex[end].name);
	}
}

//最短路径 
void shortDist(AdjMatrix *G,int start,int end,int dist[],int path[]){
	int i,j,k,p;
	int mindist;
	int vex[MAXVEX][MAXVEX];
	
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			vex[i][j]=-1;
		}
	}
	
	for(i=0;i<G->vexnum;i++){
		path[i]=0;
	}
	
	for(i=0;i<G->vexnum;i++){
		dist[i]=G->acre[start][i].distance;
		if(dist[i]!=0) vex[i][0]=i;			//存储点 
	}
	
	int min;
	int c=G->vexnum;
	path[start]=1;	//表示start点在S中 
	for(j=0;j<G->vexnum;j++){
		mindist=INFINITY;
		for(i=0;i<G->vexnum;i++){
			if((dist[i]!=0)&&(path[i]!=1)){
				if(mindist>dist[i]){
					mindist=dist[i];
					k=i;
				}	
				//printf("\tk=%d | mindist =%d | i=%d |dist[%d]= %d\n",k,mindist,i,i,dist[i]);
			} 
		}
		
		min=INFINITY;
		path[k]=1;		//在start中 
		
		int f;
	
		for(i=0;i<G->vexnum;i++){
			if(G->acre[k][i].distance!=0){
				if(min>G->acre[k][i].distance){
					min=G->acre[k][i].distance;
					f=i;
				}
			}
		}

		if(path[f]==0){			//不在S中 
			dist[f]=min+mindist;
			vex[f][0]=k;
			p=0;
			while(vex[f][p]!=-1){
				p++;
			}
			vex[f][p]=f;
			vex[f][p-1]=k;
		} else {
			if(dist[f]>(min+mindist)){
				dist[f]=min+mindist;
				p=0;
				while(vex[f][p]!=-1){
					p++;
				}
				vex[f][p]=f;
				vex[f][p-1]=k;
			}
		}
	}
	if(dist[end]!=0){
		printf("\n\tThe shortest way from %s to %s is %d km:\n\n\t%s ",G->vex[start].name,G->vex[end].name,dist[end],G->vex[start].name);
		printWay(G,vex,end);	
	} else{
		printf("\n\tThere is no way from %s to %s \n",G->vex[start].name,G->vex[end].name);
	}

}

Time timeCost(Time start,Time end){
	Time count;
	count.day=count.hours=count.minutes=count.month=count.seconds=0;
	count.day=end.day-start.day;
	count.month=end.month-start.month;
	count.hours=end.hours-start.hours;
	count.minutes=end.minutes-start.minutes;
	count.seconds=end.seconds-start.seconds;
	if(count.seconds<0){
		count.minutes--;
		count.seconds=60-count.seconds;
	}
	if(count.minutes<0){
		count.hours--;
		count.minutes=60-count.minutes;
	}
	if(count.hours<0){
		count.day--;
		count.hours=60-count.hours;
	}
	if(count.day<0){
		count.month--;
		count.day=60-count.day;
	}
	if(count.month<0){
		printf("error!\n");
	}
	return count;
}

int timeCount(AdjMatrix *G,int start,int end){
	Time begin,over;
	int i;
	int tt[MAXVEX];
	for(i=0;i<G->acre[start][end].count;i++){
			
	}
}
//最短时间 
void shortTime(AdjMatrix *G,int start,int end,int dist[],int path[]){
	int i,j,k,p;
	int mindist;
	int vex[MAXVEX][MAXVEX];
	int time[MAXVEX][MAXVEX];
	
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			vex[i][j]=-1;
		}
	}
	
	for(i=0;i<G->vexnum;i++){
		path[i]=0;
	}
	
	for(i=0;i<G->vexnum;i++){
		dist[i]=G->acre[start][i].distance;
		if(dist[i]!=0) vex[i][0]=i;			//存储点 
	}
	
	int min;
	int c=G->vexnum;
	path[start]=1;	//表示start点在S中 
	for(j=0;j<G->vexnum;j++){
		mindist=INFINITY;
		for(i=0;i<G->vexnum;i++){
			if((dist[i]!=0)&&(path[i]!=1)){
				if(mindist>dist[i]){
					mindist=dist[i];
					k=i;
				}	
				//printf("\tk=%d | mindist =%d | i=%d |dist[%d]= %d\n",k,mindist,i,i,dist[i]);
			} 
		}
		
		min=INFINITY;
		path[k]=1;		//在start中 
		
		int f;
	
		for(i=0;i<G->vexnum;i++){
			if(G->acre[k][i].distance!=0){
				if(min>G->acre[k][i].distance){
					min=G->acre[k][i].distance;
					f=i;
				}
			}
		}

		if(path[f]==0){			//不在S中 
			dist[f]=min+mindist;
			vex[f][0]=k;
			p=0;
			while(vex[f][p]!=-1){
				p++;
			}
			vex[f][p]=f;
			vex[f][p-1]=k;
		} else {
			if(dist[f]>(min+mindist)){
				dist[f]=min+mindist;
				p=0;
				while(vex[f][p]!=-1){
					p++;
				}
				vex[f][p]=f;
				vex[f][p-1]=k;
			}
		}
	}
	if(dist[end]!=0){
		printf("\n\tThe shortest way from %s to %s is %d km:\n\n\t%s ",G->vex[start].name,G->vex[end].name,dist[end],G->vex[start].name);
		printWay(G,vex,end);	
	} else{
		printf("\n\tThere is no way from %s to %s \n",G->vex[start].name,G->vex[end].name);
	}

}

//最少节点 
void LessDist(AdjMatrix *G,int start,int end,int dist[],int path[]){
	int i,j,k,p;
	int mindist;
	int vex[MAXVEX][MAXVEX];
	int less[MAXVEX][MAXVEX];
	
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			vex[i][j]=-1;
			less[i][j]=0;
			if(G->acre[i][j].distance!=0){
				less[i][j]=1;
			}
		}
	}
	
	for(i=0;i<G->vexnum;i++){
		path[i]=0;
	}
	
	for(i=0;i<G->vexnum;i++){
		dist[i]=less[start][i];
		if(dist[i]!=0) vex[i][0]=i;			//存储点 
	}
	
	int min;
	int c=G->vexnum;
	path[start]=1;	//表示start点在S中 
	for(j=0;j<G->vexnum;j++){
		mindist=INFINITY;
		for(i=0;i<G->vexnum;i++){
			if((dist[i]!=0)&&(path[i]!=1)){
				if(mindist>dist[i]){
					mindist=dist[i];
					k=i;
				}	
				//printf("\tk=%d | mindist =%d | i=%d |dist[%d]= %d\n",k,mindist,i,i,dist[i]);
			} 
		}
		
		min=INFINITY;
		path[k]=1;		//在start中 
		
		int f;
	
		for(i=0;i<G->vexnum;i++){
			if(less[k][i]!=0){
				if(min>less[k][i]){
					min=less[k][i];
					f=i;
				}
			}
		}

		if(path[f]==0){			//不在S中 
			dist[f]=min+mindist;
			vex[f][0]=k;
			p=0;
			while(vex[f][p]!=-1){
				p++;
			}
			vex[f][p]=f;
			vex[f][p-1]=k;
		} else {
			if(dist[f]>(min+mindist)){
				dist[f]=min+mindist;
				p=0;
				while(vex[f][p]!=-1){
					p++;
				}
				vex[f][p]=f;
				vex[f][p-1]=k;
			}
		}
	}
	if(dist[end]!=0){
		printf("\n\tThe least node's path from %s to %s :\n\n\t%s ",G->vex[start].name,G->vex[end].name,G->vex[start].name);
		printWay(G,vex,end);	
	} else{
		printf("\n\tThere is no way from %s to %s \n",G->vex[start].name,G->vex[end].name);
	}

}

void SearchVex(AdjMatrix *G,char *v){
	int j = LocateVex(G,v);
	if(j==-1){
		printf("\tCity not exist!\n");
		return ;
	}
	int i,k;
	char str[20];
	printf("\n\n  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
	printf("  *                                                                                                                                                             *\n");
	printf("  *\t\t\t\t\t\t\t\t   Vex        Schedule\t\t\t\t\t                                                *\n");
	printf("  *                                                                                                                                                             *\n");
	printf("  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
	printf("  |        Start   City       |         End   City       |   Train  Num   |     Start  Time     |       End   Time    |   Distance   |     Pay    |     Type    |\n");
	printf("  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");
	
	for(i=0;i<G->vexnum;i++){
		if(G->acre[i][j].distance!=0){
			for(k=0;k<G->acre[i][j].count;k++){
				strcpy(str,Translate(G->acre[i][j].Method[k].type));
				printf("  | %18s        | %18s       |%10s      |   %2d.%2d %2d: %2d: %2d  |   %2d.%2d %2d: %2d: %2d  | %8d     |%8d    |  %8s   |\n",
							G->vex[i].name,G->vex[j].name,G->acre[i][j].Method[k].traNum,G->acre[i][j].Method[k].sTime.month,G->acre[i][j].Method[k].sTime.day,G->acre[i][j].Method[k].sTime.hours,G->acre[i][j].Method[k].sTime.minutes,G->acre[i][j].Method[k].sTime.seconds,
							G->acre[i][j].Method[k].eTime.month,G->acre[i][j].Method[k].eTime.day,G->acre[i][j].Method[k].eTime.hours,G->acre[i][j].Method[k].eTime.minutes,G->acre[i][j].Method[k].eTime.seconds,G->acre[i][j].distance,G->acre[i][j].Method[k].money,str);
				}
		}
	}
	int t=i;
	i=j;
	j=t;
	for(i=0;i<G->vexnum;i++){
		if(G->acre[i][j].distance!=0){
			for(k=0;k<G->acre[i][j].count;k++){
				strcpy(str,Translate(G->acre[i][j].Method[k].type));
				printf("  | %18s        | %18s       |%10s      |   %2d.%2d %2d: %2d: %2d  |   %2d.%2d %2d: %2d: %2d  | %8d     |%8d    |  %8s   |\n",
							G->vex[i].name,G->vex[j].name,G->acre[i][j].Method[k].traNum,G->acre[i][j].Method[k].sTime.month,G->acre[i][j].Method[k].sTime.day,G->acre[i][j].Method[k].sTime.hours,G->acre[i][j].Method[k].sTime.minutes,G->acre[i][j].Method[k].sTime.seconds,
							G->acre[i][j].Method[k].eTime.month,G->acre[i][j].Method[k].eTime.day,G->acre[i][j].Method[k].eTime.hours,G->acre[i][j].Method[k].eTime.minutes,G->acre[i][j].Method[k].eTime.seconds,G->acre[i][j].distance,G->acre[i][j].Method[k].money,str);
				}
		}
	}
	printf("  *-------------------------------------------------------------------------------------------------------------------------------------------------------------*\n");	
}

void Search(AdjMatrix *G){
	int dist[MAXVEX],path[MAXVEX];
	char start[20],end[20];
	char ch='6';
	char sear[20];
	int begin=-1,over=-1;
	while(ch!='5'){
		printf("\n\n\n\t\t\t\t   *====================================================================================*\n");
		printf("\t\t\t\t   |                                                                                    |\n");
		printf("\t\t\t\t   |                               SEARCH        SCHDULE                                |\n");
		printf("\t\t\t\t   |                                                                                    |\n");
		printf("\t\t\t\t   *====================================================================================*\n");
		printf("\t\t\t\t   |                               Short  ---------  [0]                                |\n");
		printf("\t\t\t\t   |                               Money  ---------  [1]                                |\n");
		printf("\t\t\t\t   |                               Vex    ---------  [2]                                |\n");
		printf("\t\t\t\t   |                               Less   ---------  [3]                                |\n");
		printf("\t\t\t\t   |                               Change ---------  [4]                                |\n");
		printf("\t\t\t\t   |                               Quite  ---------  [5]                                |\n");
		printf("\t\t\t\t   *====================================================================================*\n");
		printf("\n\n\tPLEASE Enter Ur Choice:   ");
		fflush(stdin);
		ch=getchar();
		fflush(stdin);
		switch(ch) {
		case '0':
			while(begin==-1||over==-1){
				printf("\tPlease enter the start :\t");
				fflush(stdin); 
				gets(start);
				fflush(stdin);
				printf("\tPlease enter the end :\t");
				gets(end);
				fflush(stdin);
				begin=LocateVex(G,start);
				over=LocateVex(G,end);
			}
			shortDist(G,begin,over,dist,path);
			break;
		case '1'://
	 	while(begin==-1||over==-1){
			printf("\tPlease enter the start :\t");
			fflush(stdin); 
			gets(start);
			fflush(stdin);
			printf("\tPlease enter the end :\t");
			gets(end);
			fflush(stdin);
			begin=LocateVex(G,start);
			over=LocateVex(G,end);
		}
			Money(G,begin,over,dist,path);
			break;
		case '2'://节点 
			printf("\tPlease enter the city u want:\t");
			fflush(stdin);
			gets(sear);
			fflush(stdin);
			SearchVex(G,sear);
			break;
		case '3'://节点 
		while(begin==-1||over==-1){
			printf("\tPlease enter the start :\t");
			fflush(stdin); 
			gets(start);
			fflush(stdin);
			printf("\tPlease enter the end :\t");
			gets(end);
			fflush(stdin);
			begin=LocateVex(G,start);
			over=LocateVex(G,end);
		}	
			LessDist(G,begin,over,dist,path);
			break;
		case '4'://改 
			begin=-1,over=-1;
			while(begin==-1||over==-1){
				printf("\tPlease enter the start :\t");
				fflush(stdin); 
				gets(start);
				fflush(stdin);
				printf("\tPlease enter the end :\t");
				gets(end);
				fflush(stdin);
				begin=LocateVex(G,start);
				over=LocateVex(G,end);
			}
			break;
		case '5'://退出 
			break;
		default:
			printf("\tThe Choice not exist! \n");
			fflush(stdin);
			break;	
	}
	//printf("\n\n\n\tPress any key to continue !");
	fflush(stdin); 
	//getchar();
	}
}
	
void Menue(){
	char ch='7';
	AdjMatrix *G=Create();
	while(ch!='5'){
		printf("\n\n\n\t\t\t\t   *====================================================================================*\n");
		printf("\t\t\t\t   |                                                                                    |\n");
		printf("\t\t\t\t   |                               MENUE         SCHDULE                                |\n");
		printf("\t\t\t\t   |                                                                                    |\n");
		printf("\t\t\t\t   *====================================================================================*\n");
		printf("\t\t\t\t   |                               LOG IN ---------  [0]                                |\n");
		printf("\t\t\t\t   |                               ADD IN ---------  [1]                                |\n");
		printf("\t\t\t\t   |                               DElETE ---------  [2]                                |\n");
		printf("\t\t\t\t   |                               SHOW   ---------  [3]                                |\n");
		printf("\t\t\t\t   |                               SEARCH ---------  [4]                                |\n");
		printf("\t\t\t\t   |                               QUETE  ---------  [5]                                |\n");
		//printf("\t\t\t\t   |                               QUETE  ---------  [6]                                |\n");
		printf("\t\t\t\t   *====================================================================================*\n");
		printf("\n\n\t\t\t\t   PLEASE Enter Ur Choice:   ");
		fflush(stdin);
		ch=getchar();
		switch(ch) {
		case '0'://登录 
			break;
		case '1'://加 
			G=Add(G);
			break;
		case '2'://删 
			G=Delete(G);
			break;
		case '3'://改 
			Display(G); 
			break;
		case '4'://查 
			 Search(G);
			break;
		case '5'://显示
			break;
		default:
			printf("\t\t\t\t   The Choice not exist! \n");
			fflush(stdin);
			break;	
	}
	fflush(stdin); 
//	getchar();
	}
}

int main(){
//	int dist[MAXVEX];
//	int path[MAXVEX];
//	AdjMatrix *G=Create();
//	Display(G);
//	Money(G,0,2,dist,path);
	//Search(G);
	//shortDist(G,0,2,dist,path);
////	G=Add(G);
////	fflush(stdin);
////	Display(G);
////	G=Delete(G);
////	Display(G);
	Menue();
	return 0;
}
