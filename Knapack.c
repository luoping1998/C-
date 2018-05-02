#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int main() {
	//n������� ��c�������� ��d�����ݻ� 
	//w[n]������������� ��v[n]����ļ�ֵ���� ��b[n]������������ 
	//m[i][j][k] ��i~n��װ�뱳��ʱ����������Ϊj,�ݻ�Ϊd������ֵΪm[i][j][k] 
	int n,c,d,i; 
	scanf("%d %d %d",&n,&c,&d);
	int w[50],v[50],b[50];
	for( i = 1; i <= n; i ++) {
		scanf("%d %d %d",&v[i],&w[i],&b[i]);	//�����i����Ʒ�ļ�ֵ ���� ��� 
	}
	Knapsack(v,w,b,n,c,d);
	return 0;
}

void Knapsack(int *v, int *w, int *b ,int n ,int c ,int d) {
	int i,j,k,m[50][50][50];
	int arr1,arr2;

	for(j = 0; j <= c; j ++) {
		for(k = 0; k <= d; k ++) {
			
			if((w[n]<=j)&&(b[n]<=k)) {
				m[n][j][k] = v[n];
			} else {
				m[n][j][k] = 0;	
			}
		}
	}
	for(i = n-1; i > 0; i --) {
		for(j = 0; j <= c; j ++) {
			for(k = 0; k <= d; k++) {
				if((w[i]<=j)&&(b[i]<=k)) {
					arr1 = m[i+1][j][k];
					arr2 = m[i+1][j-w[i]][k-b[i]]+v[i];
					m[i][j][k] = arr1 > arr2 ? arr1 : arr2;
//					printf("\n%d %d %d\t",m[i][j][k],arr1,arr2);
				}else {
					m[i][j][k] = m[i+1][j][k];
				}
//				printf("m[%d][%d][%d] = %d \t",i,j,k,m[i][j][k]);
			}
//			printf("\n");
		}
	}
	printf("vMax = %d\n",m[1][c][d]);
	
//Traceback
	int x[MAX],sc,sd;		//ת���õ����� 
	sc = c;
	sd = d; 	
	for(i = 1; i < n; i ++) {
		if(m[i][sc][sd] == m[i+1][sc][sd]) x[i] = 0;
		else {
			x[i] = 1; 
			sc-=w[i];
			sd-=b[i];
		}
	} 
	x[n] = (m[n][c][d]) ? 1: 0;
	
	for(i = 1; i <= n; i ++) {
		if(x[i]) printf("%d\t",i);
	}
}

