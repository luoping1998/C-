#include <stdio.h>
#include "../1/Merge.c" 
int main(){
	int n,s,i,j,sum,add,k;	//n个客户  s处可以提供服务 i变量 
	scanf("%d %d",&n,&s);
	int t[n],b[n],a[n],server[s];			//t[i]第i项服务需要的时间  server[i]第i处服务处 
	for(i = 0; i < n; i ++) {
		scanf("%d",&t[i]);		//输入服务时间 
	}
	Sort(t,b,a,n);			//对服务时间进行排序
	 
	for(i = 0 ; i < s; i ++){
		server[i] = 0;
	}
	
	for(add = i = j = 0 ; i < n; i ++) {
		for(add = 0,k = i; k >= 0; k=k-s) {
			//计算t[i]等待时间 
			add += t[k];
		}
		server[j] += add;
		if(j == s-1) j=0;
		else j++;
	}
	
	for(sum = i = 0; i < s; i ++) {
		sum += server[i];
	}
	printf("\n%d",sum/n);
	return 0;
} 
