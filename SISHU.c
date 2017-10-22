#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000
typedef struct{
	int row,col;
	int num;
}Triple;

typedef struct{
	Triple data[MAXSIZE];
	int m,n,len;
}TSMatrix;

void FastTransTSMatrix(TSMatrix *M,TSMatrix *T){
	int num[M->n],pos[M->n];
	int i,j,col;
	T->m=M->n;
	T->n=M->m;
	T->len=M->len;
	for(i=0;i<M->n;i++){
		num[i]=0;
	}
	for(i=0;i<M->len;i++){
		num[M->data[i].col]++;
	}
	pos[0]=0;
	for(i=1;i<M->n;i++){
		pos[i]=pos[i-1]+num[i-1];
	}
	for(i=0;i<M->len;i++){
		col=M->data[i].col;
		T->data[pos[col]].row=M->data[i].col;
		T->data[pos[col]].col=M->data[i].row;
		T->data[pos[col]].num=M->data[i].num;
		pos[col]++;
	}
}

void Enter(TSMatrix *M){
	int i,j,k,num;
	M->len=0;
	printf("enter row && col:");
	scanf("%d %d",&M->m,&M->n);
	getchar();
	printf("Enter the nums:\n"); 
	for(i=0;i<M->m;i++){
		for(j=0;j<M->n;j++){
			scanf("%d",&num);
			if(num!=0){
				M->data[M->len].num=num;
				M->data[M->len].row=i;
				M->data[M->len].col=j;
				M->len++;
			}
		}
	}
}

void Print(TSMatrix *M){
	int i,j,k;
	for(i=0,k=0;i<M->m;i++){
		for(j=0;j<M->n;j++){
			if(M->data[k].row==i && M->data[k].col==j){
				printf(" %d ",M->data[k].num);
				k++;
			}
			else{
				printf(" 0 ");
			}
		}
		printf("\n");
	}
}

int Chen(TSMatrix *M,TSMatrix *T){
	int i,j,s,num;
	i=j=s=0;
	TSMatrix *ZT=malloc(sizeof(TSMatrix));
	FastTransTSMatrix(T,ZT);
	while(i<M->len&&j<ZT->len){
		if(M->data[i].row==ZT->data[j].row &&M->data[i].col==ZT->data[j].col){
			num=M->data[i].num*ZT->data[j].num;
			j++;i++;
		}
		else{
			if(M->data[i].row!=ZT->data[j].row && M->data[i].col!=ZT->data[j].col){
				if(M->data[i].row<ZT->data[i].row){
					i++;
				}
				else{
					j++;
				}
			}
			else if(M->data[i].row==ZT->data[j].row && M->data[i].col!=M->data[j].col){
				if(M->data[i].col<ZT->data[j].col){
					i++;
				}
				else{
					j++;
				}
			}
			else{
				if(M->data[i].row<ZT->data[j].row){
					i++;
				}
				else{
					j++;
				}
			}
			num=0;
		}
		s+=num;
	}
	return s;
}

int Chu(TSMatrix *M,TSMatrix *T){
	TSMatrix *ZT=malloc(sizeof(TSMatrix));
	FastTransTSMatrix(T,ZT);
	int i,s;
	for(i=0;i<ZT->len;i++){
		ZT->data[i].num=1.0/ZT->data[i].num;
	}
	s=Chen(M,ZT);
	return s;
}

TSMatrix *Add(TSMatrix *M,TSMatrix *T){
	int i,j,k;
	i=k=j=0;
	TSMatrix *A=malloc(sizeof(TSMatrix));
	while(i<M->len&&j<T->len){
		if((M->data[i].col==T->data[j].col) && (M->data[i].row==T->data[j].row)){
			A->data[k].col=M->data[i].col;
			A->data[k].row=M->data[i].row;
			A->data[k].num=M->data[i].num+T->data[j].num;
			k++;i++;j++;
		}
		else{
			if((M->data[i].col!=T->data[j].col) && (M->data[i].row!=T->data[j].row)){
				if(M->data[i].row<T->data[j].row){
					A->data[k].col=M->data[i].col;
					A->data[k].row=M->data[i].row;
					A->data[k].num=M->data[i].num;
					k++;i++;
				}
				else{
					A->data[k].col=T->data[j].col;
					A->data[k].row=T->data[j].row;
					A->data[k].num=T->data[j].num;
					k++;j++;
				}
			}
			else if((M->data[i].col==T->data[j].col) && (M->data[i].row!=T->data[j].row)){
				if(M->data[i].row<T->data[j].row){
					A->data[k].col=M->data[i].col;
					A->data[k].row=M->data[i].row;
					A->data[k].num=M->data[i].num;
					k++;i++;
				}
				else{
					A->data[k].col=T->data[j].col;
					A->data[k].row=T->data[j].row;
					A->data[k].num=T->data[j].num;
					k++;j++;
				}
			}
			else{
				if(M->data[i].col<T->data[j].col){
					A->data[k].col=M->data[i].col;
					A->data[k].row=M->data[i].row;
					A->data[k].num=M->data[i].num;
					k++;i++;
				}
				else{
					A->data[k].col=T->data[j].col;
					A->data[k].row=T->data[j].row;
					A->data[k].num=T->data[j].num;
					k++;j++;
				}
			}
		}
	}
	while(j<T->len){
		A->data[k].col=T->data[j].col;
		A->data[k].row=T->data[j].row;
		A->data[k].num=T->data[j].num;
		k++;j++;
	}
	while(i<M->len){
		A->data[k].col=M->data[i].col;
		A->data[k].row=M->data[i].row;
		A->data[k].num=M->data[i].num;
		k++;i++;
	}
	A->len=k;A->m=M->m;A->n=M->n;
	return A;
}

TSMatrix *Jian(TSMatrix *M,TSMatrix *T){
	int i;
	for(i=0;i<T->len;i++){
		T->data[i].num=-T->data[i].num;
	}
	TSMatrix *B=Add(M,T);
	for(i=0;i<T->len;i++){
		T->data[i].num=-T->data[i].num;
	}
	return B;
}

int main(){
	TSMatrix *M,*T,*Z;
	int i,S,C;
	M=malloc(sizeof(TSMatrix));
	T=malloc(sizeof(TSMatrix));
	Z=malloc(sizeof(TSMatrix));
	Enter(M);
//	Print(M);
	Enter(T);
	S=Chen(M,T);
	printf("M*T=%d\n",S);
	C=Chu(M,T);
	printf("M/T=%d\n",C);
	FastTransTSMatrix(M,Z);
	printf("A^-1=\n");
	Print(Z);
	TSMatrix *A=Add(M,T);
	printf("M+T=\n");
	Print(A);
	TSMatrix *B=Jian(M,T);
	printf("M-T=\n");
	Print(B);

	return 0; 
}
