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
	char m[LEN],n[LEN];			//m����仯��  n����Ŀ�괮
	int i,j,mLen,nLen,x[LEN][LEN],flag,min;		//i��jΪ����������x[i][j]�洢m(0~i)���ӱ��n��0~j��������С���� 
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
