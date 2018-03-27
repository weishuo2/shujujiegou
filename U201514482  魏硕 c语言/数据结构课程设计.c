#include <stdio.h>
#include <stdlib.h>               
#include <string.h>
#include<time.h> 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 40

typedef int status;

typedef struct ArcNode { //������Ϣ 
	int adjvex; //�û���ָ��Ķ����λ�� 
	struct ArcNode *nextarc; //ָ����һ������ָ��
	int Weight; //������¼����Ȩֵ 
}ArcNode;

typedef struct VNode { //�����Ϣ 
	int num;//������
	char name[20];//����ָ������
	char captial[20];//����ʡ��
	int people;//�������� 
	char phone[15];//�绰���� 
	char where[50];//����λ�� 
	ArcNode *firstarc; //ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {//ͼ��Ϣ 
	AdjList vertices;
	int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ��� 
	int kind; //ͼ�������־ 
}aLGraph, *ALGraph;

typedef struct Queue {
	int *base;
	int capacity;  //�������
	int front;
	int rear;
	int now; //��ǰ����
}*Queue;

typedef struct lowtree{//��С��������������
	char adjvex[20];
	int lowcost; 
}closedge[MAX_VERTEX_NUM]; 

ALGraph G[MAX_VERTEX_NUM];//�洢���ͼ 
int visited[MAX_VERTEX_NUM];//���ʱ�ǣ�0��ʾδ���ʹ���1��ʾ���ʹ�

//ͼ 
int InitGraphs(void);//ͼ��Ϊ�� 
ALGraph CreateGraph(ALGraph G);//����ͼ 
ALGraph DestroyGraph(ALGraph T);//����ͼ 
status LocateVex(ALGraph G, char* ch);//�������ݣ��ж��ýڵ�λ�� 
status CorrectVex(ALGraph G, char* ch);//�޸�ָ�������ֵ 
VNode* GetVex(ALGraph G, char* ch);//���ָ������ָ�� 
status CorrectArc(ALGraph G, char* v1,char* v2);//�滻ָ������ֵ 
status FirstAdjVex(ALGraph G, char* ch);//���ָ�������һ���ڽӵ�λ�� 
status NextAdjVex(ALGraph G, char* v);//��ʾ�����ڽӵ� 
status Arcweight(ALGraph T,char* v1,char* v2);//��ѯ����Ȩֵ 
ALGraph InsertVex(ALGraph G);//���붥��
status DeleteVex(ALGraph G, char* ch);//ɾ������ 
status InsertArc(ALGraph G, char* v1, char* v2,int weight);//����һ���� 
status DeleteArc(ALGraph G, char* v1, char* v2);//ɾ��һ���� 
int Save(ALGraph G);//���浽�ļ� 
ALGraph Load(ALGraph G);//���ļ��ж��� 
int Minspantree(ALGraph G,char* v);//�Ӷ���v����������С������ 
int Iscolorok(ALGraph G,int vex,int color[]);//�жϸö�����û����ͬ��ɫ���ڽӵ� 
int graphcolor(ALGraph G,int m);//��m����ɫ��ɫ 

//���в�������
int InitQueue(Queue Q);//�������� 
int EnQueue(Queue Q, int e);//��� 
int DeQueue(Queue Q);//���� 
int IsQueueEmpty(Queue Q); //�п� 
int DestroyQueue(Queue Q);//�ݻٶ��� 

int main(void)   
{				
	int i,op=1,back,weight,m;
	clock_t start,finish;
	double duration;
	char e1[20],e2[20];
	VNode* p=NULL;
	InitGraphs(); 
	while (op)
	 {
		system("cls");
		system("color 1F");//ϵͳ�������ɫ
		printf("\t\t********************************************************************\n");
		printf("\t\t*                                                                  *\n");
		printf("\t\t*                     ��ͼ�Ĺ���ʵ�ֲ˵� ��                        *\n");
		printf("\t\t*                                                                  *\n");
		printf("\t\t*                      0.�˳�ϵͳ                                  *\n");
		printf("\t\t*ͼ������                                                          *\n");
		printf("\t\t*                      1.����ͼ                                    *\n");
		printf("\t\t*                      2.����ͼ                                    *\n");
		printf("\t\t*���������                                                        *\n");
		printf("\t\t*                      3.�޸Ķ����ֵ                              *\n");
		printf("\t\t*                      4.��ö���ֵ                                *\n");
		printf("\t\t*                      5.���붥��                                  *\n");
		printf("\t\t*                      6.ɾ������                                  *\n");
		printf("\t\t*                      7.��õ�һ�ڽӵ�                            *\n");
		printf("\t\t*                      8.��������ڽӵ�                            *\n");
		printf("\t\t*��������                                                          *\n");
		printf("\t\t*                      9.�޸Ļ���Ȩֵ                              *\n");
		printf("\t\t*                      10.��ѯ����Ȩֵ                             *\n");
		printf("\t\t*                      11.���뻡                                   *\n");
		printf("\t\t*                      12.ɾ����                                   *\n");
		printf("\t\t*���Ӳ�����                                                        *\n");
		printf("\t\t*                      13.�����ļ�                                 *\n");
		printf("\t\t*                      14.���ļ��ж�����                           *\n");
		printf("\t\t*                      15.������С������                           *\n");
		printf("\t\t*                      16.����Ⱦɫ��                               *\n");
		printf("\t\t*                                                                  *\n");
		printf("\t\t********************************************************************\n\n");
		printf("\t\t                       ���������ѡ��");
		scanf("%d",&op);getchar();
		switch(op)
		{
			case 1:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				G[i]=CreateGraph(G[i]);
				printf("�ɹ�����ͼ��\n");
				getchar();
				break;
			case 2:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 
				G[i]=DestroyGraph(G[i]);
				printf("��ͼ���ٳɹ���\n");
				getchar();
				break;
			case 3:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				printf("��������Ҫ�޸Ķ���ĵ�����");
				scanf("%s",e1);getchar();
				back=CorrectVex(G[i],e1);
				if(back == -1)
					printf("�ý�㲻����\n");
				else
					printf("�޸ĳɹ�\n");		
				getchar();
				break;
			case 4:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				printf("��������Ҫ���ҵĵ�����");
				scanf("%s",e1);getchar();
				p=GetVex(G[i],e1);
				if(p == NULL)
					printf("�ý�㲻����\n");
				else
					printf("��ϢΪ\n���ƣ�%s  ʡ�᣺%s  ��ţ�%d   �˿�����%d �绰���ţ�%s ����λ�ã�%s",p->name,p->captial,p->num,p->people,p->phone,p->where);
				getchar();
				break;
			case 5:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();	
				G[i]=InsertVex(G[i]);
				printf("����ɹ���\n");
				getchar();break;
			case 6:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 		
				printf("��������Ҫɾ���ĵ�����");
				scanf("%s",e1);getchar();
				back=DeleteVex(G[i],e1);
				if(back == 0)
					printf("�ý�㲻����\n");
				else
					printf("ɾ���ɹ���\n");
				getchar();break;
			case 7:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				printf("��������Ҫ���ҵĵ�����");
				scanf("%s",e1);getchar();
				back=FirstAdjVex(G[i],e1);
				if(back == -1)
					printf("�õ�һ�ڽӵ㲻����\n");	
				getchar();break;
			case 8:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				printf("��������Ҫ���ҵĵ�����");
				scanf("%s",e1);getchar();
				back=NextAdjVex(G[i],e1);
				getchar();break;
			case 9:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 		
				printf("��������Ҫ�ı�ĵ�һ��������");
				scanf("%s",e1); getchar(); 
				printf("��������Ҫ�ı�ĵڶ���������");
				scanf("%s",e2); getchar();
				if(CorrectArc(G[i],e1,e2) != -1)
					printf("�޸ĳɹ���\n");
				else 
					printf("�û�������!\n"); 
				getchar();break;
			case 10:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 		
				printf("��������Ҫ��ѯȨֵ�ĵ�һ��������");
				scanf("%s",e1);getchar();
				printf("��������Ҫ��ѯȨֵ�ĵڶ���������");
				scanf("%s",e2);getchar();
				back=Arcweight(G[i],e1,e2);
				if(back == -1)
					printf("�û�������\n");
				else
					printf("�û�ȨֵΪ%d",back);
				getchar();break;
			case 11:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				printf("�����������Ļ��ĵ�һ���ص㣺");
				scanf("%s",e1);getchar();
				printf("�����������Ļ��ĵڶ����ص㣺");
				scanf("%s",e2);getchar();
				printf("�����������Ļ���Ȩֵ��");
				scanf("%d",&weight);getchar();
				back=InsertArc(G[i],e1,e2,weight);
				if(back == 0)
					printf("��㲻����\n");
				else
					printf("����ɹ���\n");
				getchar();break; 
			case 12:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 		
				printf("������ɾ���Ļ��ĵ�һ���ص㣺");
				scanf("%s",e1);getchar();
				printf("������ɾ���Ļ��ĵڶ����ص㣺");
				scanf("%s",e2);getchar();
				back=DeleteArc(G[i],e1,e2);
				if(back == 0)
					printf("�û�������\n");
				else
					printf("ɾ���ɹ���\n");
				getchar();break; 
			case 13:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				if(Save(G[i]))
					printf("�ļ�����ɹ���\n");
				else
					printf("�ļ�����ʧ�ܣ�\n");
				getchar();break; 
			case 14:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				G[i]=Load(G[i]);
				printf("�ļ���ȡ�ɹ���\n");
				getchar();break;	
			case 15:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				start=clock();
				printf("�����빹���������ʼ���㣺");
				scanf("%s",e1);getchar(); 
				back=Minspantree(G[i],e1);
				if(back == -1)
					printf("�޴˶���\n");
				finish=clock();
				duration=(double)(finish-start)/CLOCKS_PER_SEC;
				printf("����ʱ��Ϊ%f��\n",duration); 
				getchar();break;
			case 16:
				system("cls");
				printf("�������ͼ�ı�ţ�0-19����");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("��ͼΪ��ͼ��\n");
					getchar();
					break;
				} 	
				back=-1;
				m=1;
				start=clock();
				while(back < 0)
				{
					back=graphcolor(G[i],m);
					m++;
				}
				printf("��ͼ����Ⱦɫ��Ϊ%d\n",back);
				finish=clock();
				duration=(double)(finish - start)/CLOCKS_PER_SEC;
				printf("����ʱ��Ϊ%f��\n",duration); 
				getchar();break;
		}
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
} 

int InitQueue(Queue Q)
{
	Q->base = (int *)malloc(sizeof(int) * MAX_VERTEX_NUM);
	Q->capacity = MAX_VERTEX_NUM;
	Q->front = 0;
	Q->rear = 0;
	Q->now = 0;
	return OK;
}

int EnQueue(Queue Q, int e)
{
	Q->now++;
	Q->base[Q->rear] = e;
	Q->rear++;
	return OK;
}

int DeQueue(Queue Q)
{
	int e;
	if (IsQueueEmpty(Q))
		return -1;
	else
	{
		e = Q->base[Q->front];
		Q->now--;
		Q->front++;
		return e;
	}
}

int IsQueueEmpty(Queue Q)
{
	if (Q->now == 0)
		return TRUE;
	else
		return FALSE;
}

int DestroyQueue(Queue Q)
{
	free(Q->base);
	free(Q);
	Q = NULL;
	return OK;
}

int InitGraphs(void)
{
	int i;
	for (i = 0; i<MAX_VERTEX_NUM; i++)
		G[i] = NULL;
	return OK;
}

ALGraph CreateGraph(ALGraph T)
{
	int i, j, k, weight;
	char tou[20], wei[20];
	ArcNode *p,*q;
	T = (ALGraph)malloc(sizeof(aLGraph));
	i=3;
	if(i<1 || i>4)
	{
		printf("���ʹ���\n");
		return NULL;
	}
	T->kind=i;
	printf("������ͼ�Ķ�����:");
	scanf("%d", &T->vexnum); getchar();
	printf("������ͼ�ı���:");	
	scanf("%d", &T->arcnum); getchar();	
	for (i = 0; i < T->vexnum; i++)
	{
		printf("�����%d��������Ϣ\n", i+1);
		T->vertices[i].num=i;
		printf("���ƣ�");
		scanf("%s",T->vertices[i].name);getchar();
		printf("ʡ�᣺");
		scanf("%s",T->vertices[i].captial);getchar();
		printf("�˿�����");
		scanf("%d",&T->vertices[i].people);getchar();
		printf("�绰���ţ�");
		scanf("%s",T->vertices[i].phone);getchar();
		printf("����λ�ã�");
		scanf("%s",T->vertices[i].where);getchar();
		T->vertices[i].firstarc = NULL;
	} 
	for (k = 0; k < T->arcnum; k++)
	{
		printf("�������%d������Ȩֵ:",k+1);
		scanf("%d", &weight); getchar();
		printf("�����뻡ͷ:");
		scanf("%s", tou); getchar();
		printf("�����뻡β:");
		scanf("%s", wei); getchar();
		
		p = (ArcNode*)malloc(sizeof(ArcNode));
		j = LocateVex(T, wei);	
		i = LocateVex(T, tou);
		p->adjvex = j;
		p->Weight = weight;
		p->nextarc = T->vertices[i].firstarc;//���ڱ�ͷ 
		T->vertices[i].firstarc = p;

		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = i;
		q->Weight=weight;
		q->nextarc = T->vertices[j].firstarc; //���ڱ�ͷ
		T->vertices[j].firstarc = q;
	}
	return T;
}

ALGraph DestroyGraph(ALGraph T)
{
	int i;
	ArcNode *p, *pcrs;
	if (T == NULL)
		return NULL;
	for (i = 0; i < T->vexnum; i++)
	{
		p = T->vertices[i].firstarc;
		while (p != NULL)
		{
			pcrs = p->nextarc;
			free(p);
			p = pcrs;
		}
	}
	free(T);
	T = NULL;
	return T;
}

status CorrectVex(ALGraph G, char* ch)
{
	int i,e;
	i=LocateVex(G,ch);
	printf("��������Ҫ�޸ĵ�ѡ�1.����  2.ʡ��  3.�˿��� 4.�绰���� 5.����λ��\n");
	scanf("%d",&e);getchar();
	if(e==1)
	{
		printf("�������޸ĺ�����֣�");
		scanf("%s",G->vertices[i].name);getchar();
		return 1; 
	}
	else if(e==2)
	{
		printf("�������޸ĺ��ʡ�᣺");
		scanf("%s",G->vertices[i].captial);getchar();
		return 1;
	}
	else if(e==3)
	{
		printf("�������޸ĺ���˿�����");
		scanf("%d",&G->vertices[i].people);getchar();
		return 1;
	} 
	else if(e==4)
	{
		printf("�������޸ĺ�ĵ绰���ţ�");
		scanf("%s",G->vertices[i].phone);getchar();
		return 1;
	} 
	else if(e==5)
	{
		printf("�������޸ĺ�ĵ���λ�ã�");
		scanf("%s",G->vertices[i].where);getchar();
		return 1;	
	}
	else
		return -1;
}
	 

status LocateVex(ALGraph G, char* ch)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
		if (!strcmp(G->vertices[i].name,ch))
			return i;
	return -1;
}

VNode* GetVex(ALGraph G, char* ch)
{
	int e;
	e = LocateVex(G, ch);
	if (e != -1)
		return &G->vertices[e];
	else
		return NULL;
}

status CorrectArc(ALGraph G, char* v1,char* v2)
{
	int i, j;
	ArcNode *adj;
	i = LocateVex(G, v1);
	j = LocateVex(G, v2);
	if (i == -1 || j == -1)
		return -1;
	adj=G->vertices[i].firstarc;
	while(adj != NULL)
	{
		if(adj->adjvex == j)
		{
			printf("������ı���Ȩֵ��");
			scanf("%d",&adj->Weight);getchar();
			return 1;
		}
		adj=adj->nextarc;
	}
	return -1;
}

status FirstAdjVex(ALGraph G, char* ch)
{
	ArcNode *p;
	int e;
	e = LocateVex(G, ch);
	if (e == -1)
		return -1;
	else
	{
		p = G->vertices[e].firstarc;
		if (p != NULL)
		{
			printf("��ţ�%d  ������%s  ʡ�᣺%s  �˿�����%d  �绰���ţ�%s ����λ�ã�%s\n",G->vertices[p->adjvex].num,G->vertices[p->adjvex].name,\
			G->vertices[p->adjvex].captial,G->vertices[p->adjvex].people,G->vertices[p->adjvex].phone,G->vertices[p->adjvex].where);
			return 1;
		}
		else
			return -1;
	}
}

status NextAdjVex(ALGraph G, char* v)
{
	ArcNode *p;
	int e1, e2;
	e1 = LocateVex(G, v);
	if (e1 == -1)
		return -1;
	p = G->vertices[e1].firstarc;
	printf("�����ڽӵ���ϢΪ\n");
	while (p != NULL)
	{
		printf("��ţ�%d  ������%s  ʡ�᣺%s  �˿�����%d  �绰���ţ�%s ����λ�ã�%s\n",G->vertices[p->adjvex].num,G->vertices[p->adjvex].name,\
		G->vertices[p->adjvex].captial,G->vertices[p->adjvex].people,G->vertices[p->adjvex].phone,G->vertices[p->adjvex].where);
		p = p->nextarc;
	}
	return 1;
}

status Arcweight(ALGraph T,char* v1,char* v2)
{
	int i, j;
	ArcNode *adj;
	i = LocateVex(T, v1);
	j = LocateVex(T, v2);
	if (i == -1 || j == -1)
		return -1;
	if(i == j)
		return 0;
	adj=T->vertices[i].firstarc;
	while(adj != NULL)
	{
		if(adj->adjvex == j)
			return adj->Weight;
		adj=adj->nextarc;
	}
	return -1;
} 

ALGraph InsertVex(ALGraph T)//��������λ�� 
{
	printf("��������붥�����:");
	scanf("%s",T->vertices[T->vexnum].name);getchar();
	printf("��������붥��ʡ��:");
	scanf("%s",T->vertices[T->vexnum].captial);getchar();
	printf("��������붥���˿���:");
	scanf("%d",&T->vertices[T->vexnum].people);getchar();
	printf("��������붥��绰����:");
	scanf("%s",T->vertices[T->vexnum].phone);getchar(); 
	printf("��������붥�����λ��:");
	scanf("%s",T->vertices[T->vexnum].where);getchar(); 
	T->vertices[T->vexnum].num = T->vexnum;
	T->vertices[T->vexnum].firstarc = NULL;
	T->vexnum++;
	return T;
}

status DeleteVex(ALGraph G, char* ch)
{
	ArcNode *p, *pcrs;
	int i, j;
	j = LocateVex(G, ch);
	if (j == -1)
		return ERROR;
	p = G->vertices[j].firstarc;	
	while (p)//�ͷ�������chΪͷ���Ļ� 
	{
		pcrs = p;
		p = p->nextarc;
		free(pcrs);
		G->arcnum--;
	}
	
	for (i = j; i < G->vexnum - 1; i++) //���нڵ�ǰ��һλ 
		G->vertices[i] = G->vertices[i + 1];
	G->vexnum--;
	
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->vertices[i].firstarc;
		while (p != NULL)
		{
			if (p->adjvex != j)
			{	
				if (p->adjvex > j)//�ڵ���Ÿı� 
					p->adjvex--;
				pcrs = p;
				p = p->nextarc;
			
			}
			else
			{
				if (G->vertices[i].firstarc == p)
				{
					G->vertices[i].firstarc = p->nextarc;
					free(p);
					p = G->vertices[i].firstarc;
				}
				else
				{
					pcrs->nextarc = p->nextarc;
					free(p);
					p = pcrs->nextarc;
				}
			}
		}
	}
	return OK;
}

status InsertArc(ALGraph T, char* v1, char* v2,int weight)
{
	ArcNode *p,*adj;
	int i, j;
	i = LocateVex(T, v1);
	j = LocateVex(T, v2);
	if (i == -1 || j == -1)
		return ERROR;
	adj=T->vertices[i].firstarc;
	while(adj != NULL)
	{
		if(adj->adjvex == j)
			return FALSE;
		adj=adj->nextarc;
	}
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->Weight=weight;
	p->adjvex = j;
	p->nextarc = T->vertices[i].firstarc;
	T->vertices[i].firstarc = p;
	T->arcnum++;
	adj = (ArcNode*)malloc(sizeof(ArcNode));
	adj->adjvex = i;
	adj->Weight=p->Weight;
	adj->nextarc = T->vertices[j].firstarc;
	T->vertices[j].firstarc = adj;
	return OK;
}

status DeleteArc(ALGraph T, char* v1, char* v2)
{
	int i, j;
	ArcNode *p, *pcrs;
	i = LocateVex(T, v1);
	j = LocateVex(T, v2);
	if (i == -1 || j == -1)
		return ERROR;
	p = T->vertices[i].firstarc;
	if (p->adjvex == j)
	{ 
		T->vertices[i].firstarc = p->nextarc;
		free(p); 
	} 
	else
	{
		while (p->adjvex != j)
		{
			pcrs = p;
			p = p->nextarc;
			if(p == NULL)
				break;
		}
	}
	if(p==NULL)  
		return FALSE;
	else
	{
		pcrs->nextarc = p->nextarc;
		free(p);
		T->arcnum--;
		if (T->kind >= 2)
		{
			p = T->vertices[j].firstarc;
			if (p->adjvex == i)
			{
				T->vertices[j].firstarc = p->nextarc;
				free(p);
			}			
			else
			{
				while (p->adjvex != i)
				{
					pcrs = p;
					p = p->nextarc;
					if(p == NULL)
						break;
				}
			}
			if (p->adjvex == i)
			{
				pcrs->nextarc = p->nextarc;
				free(p);
			}
			if (p == NULL)
				return FALSE;
		}
	}
	return OK;
}

int Save(ALGraph T)
{
	FILE *fp;
	int i;
	ArcNode* arc;
	if ((fp = fopen("shuju.txt", "w+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return ERROR;
	}
	fprintf(fp, "������� %d\n", T->vexnum);
	fprintf(fp, "������ %d\n", T->arcnum);
	fprintf(fp, "ͼ������Ϊ�� %d\n", T->kind);
	for(i = 0 ; i < T->vexnum; i++)
		 fprintf(fp,"%d  %s  %d  %s  %s %s\n",T->vertices[i].num,T->vertices[i].name,T->vertices[i].people,T->vertices[i].captial,T->vertices[i].phone,T->vertices[i].where);
	for (i = 0; i < T->vexnum; i++)
	{
		fprintf(fp, "%d ", i);
		arc = T->vertices[i].firstarc;
		while (arc != NULL)
		{
			fprintf(fp, "%d ", arc->adjvex);
			fprintf(fp,"%d  ",arc->Weight);
			arc = arc->nextarc;
		}
		fprintf(fp, "-1\n");
	}
	fclose(fp);
	return OK;
}

ALGraph Load(ALGraph T)
{
	FILE *fp;
	char line[256];
	int i, e,weight,arc;
	T = (ALGraph)malloc(sizeof(aLGraph));
	fp = fopen("shuju.txt", "r");
	fgets(line, 250, fp);
	sscanf(line, "%*s%d", &(T->vexnum));
	fgets(line, 250, fp);//��������ո� 
	sscanf(line, "%*s%d", &arc);
	fgets(line, 250, fp);
	sscanf(line, "%*s%d", &T->kind);//�����ַ������ǲ���ֵ 
	for (i = 0; i < T->vexnum; i++)
		T->vertices[i].firstarc = NULL;
	for (i = 0; i < T->vexnum; i++)
	{ 
		fscanf(fp, "%d", &T->vertices[i].num);
		fscanf(fp, "%s", T->vertices[i].name);
		fscanf(fp, "%d", &T->vertices[i].people);
		fscanf(fp, "%s", T->vertices[i].captial);
		fscanf(fp, "%s", T->vertices[i].phone);
		fscanf(fp, "%s", T->vertices[i].where);
	} 
	for (i = 0; i < T->vexnum; i++)
	{
		fscanf(fp, "%*d");
		fscanf(fp, "%d", &e);
		while (e != -1)
		{
			fscanf(fp, "%d", &weight);
			InsertArc(T, T->vertices[i].name, T->vertices[e].name,weight);
			fscanf(fp, "%d", &e);
		}
		fgetc(fp);
	}
	T->arcnum=arc;
	fclose(fp);
	return T;
}

int Minspantree(ALGraph T,char* v)
{
	int i,j,k,min,flag,minsum,weight;
	closedge closedges;
	printf("��С������Ϊ��\n");
	k=LocateVex(T,v);
	if(k == -1)
		return -1;
	for(j=0;j < T->vexnum;j++)//��ʼ�� 
		if(j != k)
		{ 
			strcpy(closedges[j].adjvex,T->vertices[k].name);
			closedges[j].lowcost=Arcweight(T,v,T->vertices[j].name);//�����ڻ��Ļ���Ȩֵ��-1 
		} 
	closedges[k].lowcost=0;
	
	for(i=1;i<T->vexnum;i++)
	{
		min=0;//Ѱ����С�� 
		for(j=0,flag=0;j<T->vexnum;j++)
		{
			if(closedges[j].lowcost>0 && flag==0)
			{
				min=closedges[j].lowcost;
				flag=1;
			}
			if((min>0) && (closedges[j].lowcost <= min) && (closedges[j].lowcost>0))
			{
				min=closedges[j].lowcost;
				minsum=j;
			}
		}
		printf("��%d����:  %s  %s  Ȩֵ%d\n",i,closedges[minsum].adjvex,T->vertices[minsum].name,min);
		closedges[minsum].lowcost=0;
		for(j=0;j < T->vexnum;j++)
		{
			weight=Arcweight(T,T->vertices[minsum].name,T->vertices[j].name);//ͬ��������0
			if(((closedges[j].lowcost < 0) && (weight > 0)) || ((closedges[j].lowcost>0) && (weight>0) && (weight < closedges[j].lowcost)))
			{ 
				strcpy(closedges[j].adjvex,T->vertices[minsum].name);
				closedges[j].lowcost=weight;
			} 
		}
			
	}
	return OK;
}

int Iscolorok(ALGraph T,int vex,int color[])
{
	ArcNode *adj;
	adj=T->vertices[vex].firstarc;
	while(adj != NULL)
	{
		if(color[adj->adjvex] == color[vex])
			return 0;
		adj=adj->nextarc;
	}
	return 1;
}

int graphcolor(ALGraph T,int m)
{
	int i,k,color[40],max;
    for(i=0;i < T->vexnum;i++)
        color[i]=0;
    k=0;
    while(k>=0)
    {
        color[k]=color[k]+1;
        while(color[k] <= m)
            if (Iscolorok(T,k,color))
				break;
            else 
				color[k]=color[k]+1;
        if((color[k] <= m) && (k == T->vexnum))
        {
        	max=color[0];
            for(i=0;i < T->vexnum;i++)
            {
            	printf("%s:%d\n",T->vertices[i].name,color[i]);
            	if(color[i] > max)
            		max=color[i];
            }
            return max;          
        }
        else if((color[k] <= m) && (k < T->vexnum))
                k=k+1;    //������һ������
        else
        {
            color[k]=0;
            k=k-1;//����
        }
    }
    return -1; 
} 
