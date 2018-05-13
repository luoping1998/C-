#include <stdio.h>
#define N 50
int main() {
	int n,i,j,ch,a[N];
	int sum = 0;
	int q,ji;
	ch = 2;
	ji = 1;
	scanf("%d",&n);
	for(i = 0; i < N; i ++) {
		if( (sum + ch) > n ) {
			j = i;
			break;
		}else {
			a[i] = ch;
			sum += ch;
			j = i;
			ch ++;
		}
	}
	for(i = 0; i < j; i ++){
//		printf("%d\t",a[i]);
	}
	q = n-sum;
//	printf("\n j = %d, q = %d\n",j,q);
	
	if(q > 0){
		i = j-1;
		while(q > 0) {
			a[i]++;
			q--;
			i--;
		}
	}
	for(i = 0; i < j; i ++) {
//		printf("%d\t",a[i]);
		ji *= a[i];
	}
	
	printf("%d\n",ji);
	return 0;
}
