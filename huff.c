#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 30
#define M 2*N-1
#define MAX 50

typedef struct{
	int weight;
	char charact;
	int parent,Lchild,Rchild;
}HTNode,HuffmanTree[M+1];

typedef char * HuffmanCode[N+1];

void select(HuffmanTree ht,int g,int *s1,int *s2){
	int i,j;
	//找一个 树根(parent==0) 
	for(i=1;i<=g;i++)
		if(ht[i].parent==0){
			*s1=i;
			break;
		}
	
	for(i=1;i<=g;i++)
		if(ht[i].parent==0  &&  (ht[i].weight<ht[*s1].weight)  ){
			*s1=i;	
		}

	for(j=1;j<=g;j++){
		if(ht[j].parent==0 &&  (j!=*s1) ){
			*s2=j;
			break;
		}
	}
	
	for(j=1;j<=g;j++)
		if(ht[j].parent==0  &&  (ht[j].weight<ht[*s2].weight) && (j!=*s1)  ){
			*s2=j;	
		}
	if(*s1>*s2){
		i=*s1;
		*s1=*s2;
		*s2=i;
	}
}

void CrtHuffmanTree(HuffmanTree ht,char ch[],int w[],int n){
	int i,s1,s2;
	int m=2*n-1;
	for(i=1;i<=n;i++){
		ht[i].weight=w[i];
		ht[i].charact=ch[i]; 
		ht[i].Lchild=0;
		ht[i].Rchild=0;
		ht[i].parent=0;
	} 
	
	for(i=n+1;i<=m;i++){
		ht[i].weight=0;
		ht[i].charact='\0';
		ht[i].Lchild=0;
		ht[i].Rchild=0;
		ht[i].parent=0;
	}
	
	for(i=n+1;i<=m;i++){
		select(ht,i-1,&s1,&s2);
		ht[i].weight=ht[s1].weight+ht[s2].weight;
		ht[i].Lchild=s1;
		ht[i].Rchild=s2;
		ht[s1].parent=i;
		ht[s2].parent=i;
	}
}

void CrtHuffmanCode1(HuffmanTree ht,HuffmanCode hc,int n){
	char *cd;
	int start,i,c,p;
	cd = (char *)malloc( n*sizeof(char ) );
	cd[n-1]='\0';
	for(i=1;i<=n;i++){
		start=n-1;
		c=i;
		p=ht[i].parent;
		while(p!=0){
			--start;
			if(ht[p].Lchild==c)  cd[start]='0';
			else cd[start]='1';
			c=p;
			p=ht[p].parent;
		}
		hc[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(hc[i],&cd[start]);
	}
	free(cd);
}


/*
void print(HuffmanTree ht,int n){
	int i,temp;
	char ch;
	getchar();
	printf("input :");
	scanf("%c",&ch);
	for(i=1;i<=n;i++)
		if(ht[i].charact==ch)
			break;
	printf("ch = %c,i = %d\n",ch,i);
			
	temp=ht[i].parent;
	while(temp!=0){
		if(ht[temp].Lchild==i)
			printf("0");
		else
			printf("1");
				
	i=temp;
	temp=ht[i].parent;		
	}
		
}*/

//str:字符串    w:权值     s:字符 
int getWeightOfStr(char str[] ,int w[],char s[]){
	int i,count=0;
	int temp[58+1]={0};
	//统计每个字母 
	
	for(i=0;i<strlen(str);i++)
		temp[ (int)(str[i]-'A')+1 ]++;

	
	// 统计字符串中字符数 
	for(i=1;i<=58;i++)
		if(temp[i]!=0){
			w[count+1]=temp[i];
			s[count+1]=(char)(i-1+65);
			count++;
		}
		
	return count;
}



int main(){
	int n,i;
	//0 不使用 
	int *a,w[58+1];
	char *c,s[58+1];
	char str[MAX];
	char huff[MAX]; 
	HuffmanTree h;
	HuffmanCode hc;
	
//	printf("输入 n:");
//	scanf("%d",&n);
//	getchar();
//	a=(int*)malloc(n*sizeof(int));
//	c=(char*)malloc(n*sizeof(char));
//	for(i=0;i<n;i++){
//		printf("输入第%d个字符及权值(空格隔开)",i+1);
//		scanf("%c",&c[i+1]);
//		getchar();
//		scanf("%d",&a[i+1]);
//		getchar();
//	}
//	
//	CrtHuffmanTree(h,c,a,n);
//	
//	for(i=1;i<=2*n-1;i++)
//		printf("char: %c weight: %d par: %d L : %d R :%d \n",h[i].charact,h[i].weight,h[i].parent,h[i].Lchild,h[i].Rchild);
//		
//	
//	CrtHuffmanCode1(h,hc,n);
//	
//	for(i=1;i<=n;i++)
//		printf("%s\n",hc[i]);

	printf("\n\t字符串编译:\n输入字符串:");

	scanf("%s",str);
	n=getWeightOfStr(str,w,s);
	
	CrtHuffmanTree(h,s,w,n);

	for(i=1;i<=2*n-1;i++)
		printf("%d char: %c weight: %d par: %d L : %d R :%d \n",i,h[i].charact,h[i].weight,h[i].parent,h[i].Lchild,h[i].Rchild);
	
	CrtHuffmanCode1(h,hc,n);
	
	for(i=1;i<=n;i++)
		printf("%s\n",hc[i]); 
		
	printf("\n\t译码:\n请输入编码:");
	scanf("%s",huff);
	
	for(i=1;i<n;i++)
		if(strcmp(huff,hc[i])==0)
			printf("\nyou get :%c",s[i]);
 
		else
			printf("not found");

}

