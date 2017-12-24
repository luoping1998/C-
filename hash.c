#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 99
typedef struct{
	char s[20];	
	int flag;
}str;

typedef struct{
	str data[31];
}Hash;

int intKey(char *s){
	int i;
	int key=0;
	int len=strlen(s);
	for(i=0;i<len;i++){
		key+=s[i];
	}
	return key;
}

int locate(int key){
	int count = key%31;
	return count; 
}

//一次线性 
void Xianx(Hash *p,int loc,char *s){
	int count = loc;
	while(p->data[count].flag){
		count=(count+1)%31;
	}
	strcpy(p->data[count].s,s);
	p->data[count].flag=1;
}

//随机数 
void Radom(Hash *p,char *s){
	int count=rand()%(31);
	while(p->data[count].flag){
		count=rand()%(31);
	}
	strcpy(p->data[count].s,s);
	p->data[count].flag=1;
}

//二次线性 
void Twox(Hash *p,int loc,char *s){
	int count=loc,index;
	int c=1;		//判断加的多少 
	int dir=1;		//判断方向 
	while(p->data[count].flag){
		index=(dir*c)*(dir*c);
		printf("index=%d\n",index);
		if(dir==1){
			printf("执行+\n"); 
			count=(count+index)%31;
		}else{
			printf("执行-\n"); 
			count=(count-index)%31;
			c++;
		}
		printf("count=%d\n",count);
		dir=dir*(-1);
	}
	strcpy(p->data[count].s,s);
	p->data[count].flag=1;
	printf("over\n");
}

//创建哈希表 
void createHash(Hash *p){
	int i,key,loc,count;
	char s[20];
	printf("Enter the num:");
	scanf("%d",&count);
	getchar();
	
	//初始化 
	for(i=0;i<31;i++){
		p->data[i].flag=0;
	}
	
	for(i=0;i<count;i++){
		scanf("%s",s);
		key=intKey(s);
		loc=locate(key);
		if(p->data[loc].flag){			//如果被占了 
			//Xianx(p,loc,s);				//利用线性侦测 
			Twox(p,loc,s);				//利用二次线性侦测 
			//Radom(p,s);						//伪随机数侦测 
		}else{
			strcpy(p->data[loc].s,s);
			p->data[loc].flag=1;
		}
	}
} 

//搜索 
int TwoxSearch(Hash *p,char *s){
	int loc = intKey(s);
	int count = locate(loc);
	int c=1;		//判断加的多少 
	int dir=1;		//判断方向 
	int index;
	while(strcmp(p->data[count].s,s) && c<=15){
		index=(dir*c)*(dir*c);
		if(dir==1){
			count+=index%31;
		}else{
			count-=index%31;
			count++;
		}
		dir*=-1;
	}
	return count;	
}

int XianxSearch(Hash *p,char *s){
	int loc = intKey(s);
	int count = locate(loc);
	while(strcmp(p->data[count].s,s)){
		count=(count+1)%31;
	}
	return count;
}

void printHash(Hash *p){
	int i;
	for(i=0;i<30;i++){
		if(p->data[i].flag)
			printf("locate[%d] ：%s\n",i,p->data[i].s);
	}
}

int main(){
	Hash *p = (Hash *)malloc(sizeof(Hash *));
	createHash(p);
	printHash(p); 
//	char s[20];
//	printf("Enter the str u'll search:");
//	scanf("%s",s);
//	int key = XianxSearch(p,s);
//	printf("%s->[%d]\n",s,key);
	return 0;
}

