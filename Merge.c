#include <stdio.h>
int main(){
	int i = 0;
	int k,n;
	printf("请输入数组长度n：\n");
	scanf("%d",&n);
	getchar();
	int *a  = (int*)malloc(n*sizeof(int));
	int *b  = (int*)malloc(n*sizeof(int));
	int *s  = (int*)malloc(n*sizeof(int));
	printf("请输入数组：\n");
	for(i = 0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	int j = SplitArray(a,s,n);
	while(j>0){
		MergePass(a,s,n,b,j);
		j=SplitArray(b,s,n);
		if(j>=1){
			MergePass(b,s,n,a,j);
			j=SplitArray(a,s,n);
		}else{
			for(k=0;k<n;k++){
				a[k]=b[k];
			}	 
			break;
		}
	}
	printf("有序序列如下：\n");
	for(k=0;k<n;k++){
		printf("%3d",a[k]);
	}
	
	return 0;
}

int SplitArray(int a[],int s[],int n){
	//按从小到大顺序分组 记录在s中 返回s中有效值的个数 
	int i,j;	//i用来记录a数组中实时便利到的下标，j用来记录s数组中的下标
	j=i=0;
	while(i+1<n){
		if(a[i]<=a[i+1]){
			i ++;
		}else{
			s[j]=i;
			j++;i++;		
		}
	}
	s[j]=i;	//由于遍历到最后一个的时候会自己退出，所以手动将数组最后一个下标记录下来。
//	for(i=0;i<=j;i++){
//		printf("%3d",s[i]);
//	}
//	printf("j=%d out\n",j);
	return j;
} 

void MergePass(int a[],int s[],int n,int b[],int j){
	//将a中的数组两两小组一合并 存入b中  
//	printf("come mergepass.\n");
	int i = 0;
	int start,k;
	while(i<=j){
		if(i==0) start = 0;
		else start = s[i-1]+1;
		if(i+1>j){
//			printf("\ncome zhaochao.\n");
			for(k = start;k<n;k++){
				b[k] = a[k];
			}
			break;
		}else{
			Merge(a,s[i],s[i+1],b,start);
			i=i+2;	
		}
	}
//	printf("\nout merge\n");
}

void Merge(int a[],int r,int l,int b[],int start){
	//将start~r 与 r+1~l 数组合并到b中,且b中的下标也为start~l 
//	printf("come Merge\n");
//	printf("start:%d r=%d l=%d\n",start,r,l);
	int i,j,k;
	i=k=start;
	j=r+1;
	
	while((i<=r)&&(j<=l)){
		if(a[i]<a[j]){
			b[k] = a[i];
			i++;k++;
		}else{
			b[k]=a[j];
			k++;
			j++;
		}
	}
	
	if(i<=r){
		for(;i<=r;i++){
			b[k]=a[i];
			k++;
		}
	}
	
	if(j<=l){
		for(;j<=l;j++){
			b[k]=a[j];
			k++;
		}
	}
	
//	for(i=start;i<=l;i++){
//		printf("%4d",b[i]);
//	}
//	printf(" out .\n");
}
