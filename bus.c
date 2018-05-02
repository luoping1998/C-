#include <stdio.h>
#define N 50
int MAX(int x,int y){
	if(x>y) return x;
	return y;
}

int main() {
	int c[N][N],v[N][N],i,j,n,count,value;
	for( i = 0; i < N; i ++) {
		for( j = 0; j < N; j ++){
			v[i][j]=0;
		}
	}	
	scanf("%d",&n);
	count = 0;
	int x,y;					// 起点坐标，终点坐标 
	scanf("%d %d",&x,&y);
	int sx,sy;
	scanf("%d %d",&sx,&sy);
	while(count<n){
		scanf("%d %d %d",&i,&j,&value);		//默认按从小到大顺序输入 
		v[i][j] = value;
		count ++;
	}
	j = y;
	for(i = 0; i <= x; i ++) {
		c[i][j] = MAX(v[i][j-1],v[i+1][j])+v[i][j];
	}
	for(j = y-1; j >= 0; j --) {
		for(i = 0;i <= x; i ++) {
			c[i][j] = MAX(v[i][j-1],v[i+1][j])+v[i][j];
		}
	} 
	i = x;
	j = count = 0;
	while((i>=0)&&(j<=y)){
		if(c[i-1][j] > c[i][j+1]) {
			count += v[i-1][j];
			i--;
		}else {
			count += v[i][1+j];
			j++;
		}
	}
	printf("%d\n",count);
	return 0;
} 
