#include <stdio.h>
#include <stdlib.h>
typedef struct Poly{
	int exp;        //X的次幂 
	int coef;       //系数 
	struct Poly *next;
}Poly;

/*
	创建多项式：采用尾插法比较适合并且简单 
*/ 

Poly* Create(){
	int c,e;
	Poly* head=(Poly *)malloc(sizeof(Poly));
	Poly *rear;
	rear=head;
	printf("please input coef and exp:");
	scanf("%d %d",&c,&e);
	getchar();
	while(c!=0){
		Poly *pnew=(Poly *)malloc(sizeof(Poly));
		pnew->coef=c;
		pnew->exp=e;
		rear->next=pnew;
		rear=rear->next;
		printf("please input coef and exp:");
		scanf("%d %d",&c,&e);
		getchar();
	} 
	rear->next=NULL;
	return head; 
}

/*
	一元多项式输出：考虑到系数为-1,1,>0,<0的情况
	然后在这四个情况中再分别考虑次幂为0，1，和其他的情况。
	又因为不知道多项式的长度，最后一个不输出‘+ ’，并且当后一项系数<0时也不输出‘+ ’ 
*/ 

void Print(Poly *head){
	Poly *p=head->next;
	if(!p) printf("0");
	while(p){
		if(p->coef==1){
			if(p->exp==1) printf("X");
			else if(p->exp==0) printf("1");
			else{
				printf("X^%d",p->exp);
			}
		}
		else if(p->coef==-1){
			if(p->exp==0) printf("-1");
			else if(p->exp==1) printf("-X");
			else printf("-X^%d",p->exp);
		}
		else if(p->coef==0){
			printf(" ");
		}
		else if(p->coef<0){
				if(p->exp==1) printf("%dX",p->coef);
				else if(p->exp==0) printf("%d",p->coef);
				else printf("%dX^%d",p->coef,p->exp);
		}
		else{
			if(p->exp==1) printf("%dX",p->coef);
			else if(p->exp==0) printf("%d",p->coef);
			else{
				printf("%dX^%d",p->coef,p->exp);
			}
		}
		
		//最后一个不输出‘+ ’，并且当后一项系数<0时也不输出‘+ ’ 
		if(p->next&&p->next->coef>0)   
			printf("+");
		p=p->next;
	}
	printf("\n");		
}

/*
	一元多项式相加：
	设pa,pb,pc三个指针，pa,pb分别指向传进来进行加法操作的链表的头节点，进行三种情况的比较，分别进行相关操作：
	（链表都是默认为X的升幂排列的）
	1.当pa所指节点的X的次幂< pb所指节点的X的次幂时，由于X的次方不相匹配，无法进行相加操作，
	于是，将次幂较小的节点的数据存储到新创建的节点中，并将该节点连接到pc所指的新的链表后，
	接着让被信息存入新节点的pa（次幂较低一方）的指针向后移一位；
	2.同理如 pb->exp<pa->exp;
	3.当pa和pb所指节点的次幂相同时，才可以进行加法操作，将两节点中系数相加（pc->coef=pa->coef+pb->coef），
	次幂直接复制入新创建节点（pc->exp=pb->exp||pa->exp）,双方均向后移一位；
	【这里要注意的是，当两节点系数相加如果为0，那么该节点相当于无用节点（无有效信息）
	所以此时的pc不向后移，释放此节点的内存，继续进行下一步操作】 
	4.考虑到双方链表长度不一，短链表读取完后，还有一链表还有节点信息未存储进新链表中，
	原样将剩余节点信息存入pc中，无须进行上述1—3的操作； 
*/ 

Poly *Add(Poly *Ha,Poly *Hb){
	
	Poly *pc=(Poly *)malloc(sizeof(Poly));
	Poly *rear,*pa,*pb;
	rear=pc;
	pa=Ha->next;
	pb=Hb->next;
	while(pa&&pb){
		Poly *pnew=(Poly *)malloc(sizeof(Poly)); 
		if(pa->exp>pb->exp){
			pnew->coef=pb->coef;           //将次幂 底的一方的节点的信息储存进新的节点中 
			pnew->exp=pb->exp;
			pb=pb->next; 
		}
		else if(pa->exp<pb->exp){
			pnew->coef=pa->coef;           //同上 
			pnew->exp=pa->exp;
			pa=pa->next; 
		}
		else{
			pnew->coef=pa->coef+pb->coef;    //可以进行加法操作 ：系数相加，次幂复制 
			pnew->exp=pa->exp;
			pa=pa->next;
			pb=pb->next;
		}
		if(pnew->coef!=0){                   //当新节点的系数不为0时（这里主要考虑到进行相加操作后的新节点），才进行下述操作 
			rear->next=pnew;
			rear=rear->next;
		}
	}
	
	
	//以下考虑到两个链表长度不等，当还有链表剩余节点时，直接将节点信息复制到新节点中，并接到pc后
	 
	while(pa){
		Poly *pnew=(Poly *)malloc(sizeof(Poly)); 
		pnew->coef=pa->coef;
		pnew->exp=pa->exp;
		rear->next=pnew;
		rear=rear->next;
		pa=pa->next; 
	}
	while(pb){
		Poly *pnew=(Poly *)malloc(sizeof(Poly)); 
		pnew->coef=pb->coef;
		pnew->exp=pb->exp;
		rear->next=pnew;
		rear=rear->next;
		pb=pb->next; 
	}
	rear->next=NULL;
	return pc;
}

/*
	减法运算就是建立于加法上的： 
	1.将Add函数的第二个不等式的所有项系数（coef）都乘以-1； 
	2.调用Add函数； 
	3.又为了不改变第二个一元多项式，再对其进行乘以-1的（1）步骤让其还原成输入样 ； 
*/ 

Poly *Jian(Poly *pa,Poly *pb){
	Poly *p,*Result;
	p=pb->next;
	while(p){
		p->coef=-1*p->coef;
		p=p->next;
	} 
	Result=Add(pa,pb);
	
	p=pb->next;
	while(p){
	p->coef=-1*p->coef;
	p=p->next;
	} 
	return Result;
}

void Qiudao(Poly *pa){
	Poly *q;
	q=pa->next;
	while(q){
		if(q->exp==0){
			q->coef=0;
		}
		else {
			q->coef*=q->exp;
			q->exp-=1;
		}
		q=q->next; 
	}	
} 

Poly *Chen(Poly *pa,Poly *pb){
	Poly *a,*b,*c,*p;
	c=(Poly *)malloc(sizeof(Poly));
	p=c;
	for(a=pa->next;a!=NULL;a=a->next){
		for(b=pb->next;b!=NULL;b=b->next){
			Poly *pnew=(Poly *)malloc(sizeof(Poly));
			pnew->exp=a->exp+b->exp;
			pnew->coef=a->coef*b->coef;
			p->next=pnew;
			p=pnew;	
		}
	} 
	p->next=NULL;
	
	Poly *m,*n,*q;
	m=c->next;
	for(n=c->next;n!=NULL;n=n->next){
		for(q=n->next;q!=NULL;m=q,q=q->next){
			if(n->exp==q->exp){
				n->coef+=q->coef;
				m->next=q->next;
			}
		}
	}
	return c;
}

int main(){
	int re;
	
	//输入一元多项式A的信息： 
	printf("please input pa:\n");
	Poly *Ha=Create();
	printf("pa=");
	Print(Ha);
	
	//输入一元多项式B的信息： 
	printf("\nplease input pb:\n");
	Poly *Hb=Create();
	printf("pb=");
	Print(Hb);
	
	//进行A+B的运算并返回头指针C 
	Poly *Hc=Add(Ha,Hb);
	printf("\nADD:\npc=");
	Print(Hc);

	//进行A-B的运算并返回头指针D 
	Poly *Hd=Jian(Ha,Hb);
	printf("\nJIAN(pa-pb):\npd=");
	Print(Hd);
	
	//进行B-A的运算并返回头指针E 
	Poly *He=Jian(Hb,Ha);
	printf("\nJIAN(pb-pa):\npd=");
	Print(He);
	
	printf("\nqiudao:\n");
	Qiudao(Ha);
	printf("\npa'=");
	Print(Ha);
	
	Qiudao(Hb);
	printf("\npb'=");
	Print(Hb);
	
	Qiudao(Hc);
	printf("\npc'=");
	Print(Hc);
	
	Qiudao(Hd);
	printf("\npd'=");
	Print(Hd);
	return 0;	
	
	Poly * He=Chen(Ha,Hb);
	printf("\npa*pb=");
	Print(He);
}

