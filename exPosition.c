#include <stdio.h>
int main(){
	int n;
	printf("���������鳤�ȣ�");
	scanf("%d",&n);
	int *a = (int *)malloc(sizeof(int)*n);
	int i = 0;
	printf("����������:\n");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	printf("������ָ��±꣺");
	int split ;
	scanf("%d",&split);
	swapArray(a,n,split);
	for(i=0;i<n;i++){
		printf("%3d",a[i]);
	}
	return 0;
}

void swapArray(int a[],int n,int split){
	swap(a,0,split);
	swap(a,split+1,n-1);
	swap(a,0,n-1);
}

void swap(int a[],int left,int right){
	int temp;
	for(;left<right;left++,right--){
		temp = a[left];
		a[left] = a[right];
		a[right] = temp;
	}
}
