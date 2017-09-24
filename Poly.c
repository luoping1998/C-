#include <stdio.h>
#include <stdlib.h>
typedef struct Poly{
	int exp;        //X�Ĵ��� 
	int coef;       //ϵ�� 
	struct Poly *next;
}Poly;

/*
	��������ʽ������β�巨�Ƚ��ʺϲ��Ҽ� 
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
	һԪ����ʽ��������ǵ�ϵ��Ϊ-1,1,>0,<0�����
	Ȼ�������ĸ�������ٷֱ��Ǵ���Ϊ0��1���������������
	����Ϊ��֪������ʽ�ĳ��ȣ����һ���������+ �������ҵ���һ��ϵ��<0ʱҲ�������+ �� 
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
		
		//���һ���������+ �������ҵ���һ��ϵ��<0ʱҲ�������+ �� 
		if(p->next&&p->next->coef>0)   
			printf("+");
		p=p->next;
	}
	printf("\n");		
}

/*
	һԪ����ʽ��ӣ�
	��pa,pb,pc����ָ�룬pa,pb�ֱ�ָ�򴫽������мӷ������������ͷ�ڵ㣬������������ıȽϣ��ֱ������ز�����
	��������Ĭ��ΪX���������еģ�
	1.��pa��ָ�ڵ��X�Ĵ���< pb��ָ�ڵ��X�Ĵ���ʱ������X�Ĵη�����ƥ�䣬�޷�������Ӳ�����
	���ǣ������ݽ�С�Ľڵ�����ݴ洢���´����Ľڵ��У������ýڵ����ӵ�pc��ָ���µ������
	�����ñ���Ϣ�����½ڵ��pa�����ݽϵ�һ������ָ�������һλ��
	2.ͬ���� pb->exp<pa->exp;
	3.��pa��pb��ָ�ڵ�Ĵ�����ͬʱ���ſ��Խ��мӷ������������ڵ���ϵ����ӣ�pc->coef=pa->coef+pb->coef����
	����ֱ�Ӹ������´����ڵ㣨pc->exp=pb->exp||pa->exp��,˫���������һλ��
	������Ҫע����ǣ������ڵ�ϵ��������Ϊ0����ô�ýڵ��൱�����ýڵ㣨����Ч��Ϣ��
	���Դ�ʱ��pc������ƣ��ͷŴ˽ڵ���ڴ棬����������һ�������� 
	4.���ǵ�˫�������Ȳ�һ���������ȡ��󣬻���һ�����нڵ���Ϣδ�洢���������У�
	ԭ����ʣ��ڵ���Ϣ����pc�У������������1��3�Ĳ����� 
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
			pnew->coef=pb->coef;           //������ �׵�һ���Ľڵ����Ϣ������µĽڵ��� 
			pnew->exp=pb->exp;
			pb=pb->next; 
		}
		else if(pa->exp<pb->exp){
			pnew->coef=pa->coef;           //ͬ�� 
			pnew->exp=pa->exp;
			pa=pa->next; 
		}
		else{
			pnew->coef=pa->coef+pb->coef;    //���Խ��мӷ����� ��ϵ����ӣ����ݸ��� 
			pnew->exp=pa->exp;
			pa=pa->next;
			pb=pb->next;
		}
		if(pnew->coef!=0){                   //���½ڵ��ϵ����Ϊ0ʱ��������Ҫ���ǵ�������Ӳ�������½ڵ㣩���Ž����������� 
			rear->next=pnew;
			rear=rear->next;
		}
	}
	
	
	//���¿��ǵ����������Ȳ��ȣ�����������ʣ��ڵ�ʱ��ֱ�ӽ��ڵ���Ϣ���Ƶ��½ڵ��У����ӵ�pc��
	 
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
	����������ǽ����ڼӷ��ϵģ� 
	1.��Add�����ĵڶ�������ʽ��������ϵ����coef��������-1�� 
	2.����Add������ 
	3.��Ϊ�˲��ı�ڶ���һԪ����ʽ���ٶ�����г���-1�ģ�1���������仹ԭ�������� �� 
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
	
	//����һԪ����ʽA����Ϣ�� 
	printf("please input pa:\n");
	Poly *Ha=Create();
	printf("pa=");
	Print(Ha);
	
	//����һԪ����ʽB����Ϣ�� 
	printf("\nplease input pb:\n");
	Poly *Hb=Create();
	printf("pb=");
	Print(Hb);
	
	//����A+B�����㲢����ͷָ��C 
	Poly *Hc=Add(Ha,Hb);
	printf("\nADD:\npc=");
	Print(Hc);

	//����A-B�����㲢����ͷָ��D 
	Poly *Hd=Jian(Ha,Hb);
	printf("\nJIAN(pa-pb):\npd=");
	Print(Hd);
	
	//����B-A�����㲢����ͷָ��E 
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

