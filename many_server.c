#include <stdio.h>
#include "../1/Merge.c" 
int main(){
	int n,s,i,j,sum,add,k;	//n���ͻ�  s�������ṩ���� i���� 
	scanf("%d %d",&n,&s);
	int t[n],b[n],a[n],server[s];			//t[i]��i�������Ҫ��ʱ��  server[i]��i������ 
	for(i = 0; i < n; i ++) {
		scanf("%d",&t[i]);		//�������ʱ�� 
	}
	Sort(t,b,a,n);			//�Է���ʱ���������
	 
	for(i = 0 ; i < s; i ++){
		server[i] = 0;
	}
	
	for(add = i = j = 0 ; i < n; i ++) {
		for(add = 0,k = i; k >= 0; k=k-s) {
			//����t[i]�ȴ�ʱ�� 
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
