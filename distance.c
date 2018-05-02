#include <stdio.h>
#include <string.h>
#define LEN 51
int Min(int a,int b,int c) {
	int min = a;
	if(min > b) {
		min = b;
	}
	if(min > c) {
		min = c;
	}
	return min;
}

int main() {
	char m[LEN],n[LEN];			//m代表变化串  n代表目标串
	int i,j,mLen,nLen,x[LEN][LEN],flag,min;		//i，j为遍历变量，x[i][j]存储m(0~i)串从变成n（0~j）串的最小步骤 
	scanf("%s %s",m,n);
	mLen = strlen(m);
	nLen = strlen(n);
	i = j = 0;
	
	x[0][0] = 0;
	for(i = 1; i <= mLen; i ++) {
		x[i][0] = i;
	} 
	for(j = 1; j <= nLen; j ++) {
		x[0][j] = j;
	}
	for(i = 1; i <= mLen; i ++) {
		for(j = 1; j <= nLen; j ++) {
			if(m[i] == n[j]) {
				flag = 0;
			} else {
				flag = 1;
			}
			x[i][j] = Min(x[i-1][j]+1,x[i][j-1]+1,x[i-1][j-1]+flag);
		}
	}
	printf("%d",x[mLen][nLen]);
	return 0;
} 
