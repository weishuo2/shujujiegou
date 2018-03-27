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

typedef struct ArcNode { //弧的信息 
	int adjvex; //该弧所指向的顶点的位置 
	struct ArcNode *nextarc; //指向下一条弧的指针
	int Weight; //用来记录网的权值 
}ArcNode;

typedef struct VNode { //结点信息 
	int num;//顶点编号
	char name[20];//顶点指代地名
	char captial[20];//顶点省会
	int people;//顶点人数 
	char phone[15];//电话区号 
	char where[50];//地理位置 
	ArcNode *firstarc; //指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {//图信息 
	AdjList vertices;
	int vexnum, arcnum; //图的当前顶点数和弧数 
	int kind; //图的种类标志 
}aLGraph, *ALGraph;

typedef struct Queue {
	int *base;
	int capacity;  //最大容量
	int front;
	int rear;
	int now; //当前个数
}*Queue;

typedef struct lowtree{//最小生成树辅助数组
	char adjvex[20];
	int lowcost; 
}closedge[MAX_VERTEX_NUM]; 

ALGraph G[MAX_VERTEX_NUM];//存储多个图 
int visited[MAX_VERTEX_NUM];//访问标记，0表示未访问过，1表示访问过

//图 
int InitGraphs(void);//图置为空 
ALGraph CreateGraph(ALGraph G);//创建图 
ALGraph DestroyGraph(ALGraph T);//销毁图 
status LocateVex(ALGraph G, char* ch);//给定数据，判定该节点位置 
status CorrectVex(ALGraph G, char* ch);//修改指定顶点的值 
VNode* GetVex(ALGraph G, char* ch);//获得指定顶点指针 
status CorrectArc(ALGraph G, char* v1,char* v2);//替换指定弧的值 
status FirstAdjVex(ALGraph G, char* ch);//获得指定顶点第一个邻接点位置 
status NextAdjVex(ALGraph G, char* v);//显示所有邻接点 
status Arcweight(ALGraph T,char* v1,char* v2);//查询弧的权值 
ALGraph InsertVex(ALGraph G);//插入顶点
status DeleteVex(ALGraph G, char* ch);//删除顶点 
status InsertArc(ALGraph G, char* v1, char* v2,int weight);//新增一条弧 
status DeleteArc(ALGraph G, char* v1, char* v2);//删除一条弧 
int Save(ALGraph G);//保存到文件 
ALGraph Load(ALGraph G);//从文件中读出 
int Minspantree(ALGraph G,char* v);//从顶点v出发构造最小生成树 
int Iscolorok(ALGraph G,int vex,int color[]);//判断该顶点有没有相同颜色的邻接点 
int graphcolor(ALGraph G,int m);//用m种颜色着色 

//队列操作函数
int InitQueue(Queue Q);//创建队列 
int EnQueue(Queue Q, int e);//入队 
int DeQueue(Queue Q);//出队 
int IsQueueEmpty(Queue Q); //判空 
int DestroyQueue(Queue Q);//摧毁队列 

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
		system("color 1F");//系统命令，调颜色
		printf("\t\t********************************************************************\n");
		printf("\t\t*                                                                  *\n");
		printf("\t\t*                     ◆图的功能实现菜单 ◆                        *\n");
		printf("\t\t*                                                                  *\n");
		printf("\t\t*                      0.退出系统                                  *\n");
		printf("\t\t*图操作：                                                          *\n");
		printf("\t\t*                      1.创建图                                    *\n");
		printf("\t\t*                      2.销毁图                                    *\n");
		printf("\t\t*顶点操作：                                                        *\n");
		printf("\t\t*                      3.修改顶点的值                              *\n");
		printf("\t\t*                      4.获得顶点值                                *\n");
		printf("\t\t*                      5.插入顶点                                  *\n");
		printf("\t\t*                      6.删除顶点                                  *\n");
		printf("\t\t*                      7.获得第一邻接点                            *\n");
		printf("\t\t*                      8.获得所有邻接点                            *\n");
		printf("\t\t*弧操作：                                                          *\n");
		printf("\t\t*                      9.修改弧的权值                              *\n");
		printf("\t\t*                      10.查询弧的权值                             *\n");
		printf("\t\t*                      11.插入弧                                   *\n");
		printf("\t\t*                      12.删除弧                                   *\n");
		printf("\t\t*附加操作：                                                        *\n");
		printf("\t\t*                      13.存入文件                                 *\n");
		printf("\t\t*                      14.从文件中读数据                           *\n");
		printf("\t\t*                      15.生成最小生成树                           *\n");
		printf("\t\t*                      16.最少染色数                               *\n");
		printf("\t\t*                                                                  *\n");
		printf("\t\t********************************************************************\n\n");
		printf("\t\t                       请输入你的选择：");
		scanf("%d",&op);getchar();
		switch(op)
		{
			case 1:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				G[i]=CreateGraph(G[i]);
				printf("成功创建图！\n");
				getchar();
				break;
			case 2:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 
				G[i]=DestroyGraph(G[i]);
				printf("该图销毁成功！\n");
				getchar();
				break;
			case 3:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				printf("请输入需要修改顶点的地名：");
				scanf("%s",e1);getchar();
				back=CorrectVex(G[i],e1);
				if(back == -1)
					printf("该结点不存在\n");
				else
					printf("修改成功\n");		
				getchar();
				break;
			case 4:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				printf("请输入需要查找的地名：");
				scanf("%s",e1);getchar();
				p=GetVex(G[i],e1);
				if(p == NULL)
					printf("该结点不存在\n");
				else
					printf("信息为\n名称：%s  省会：%s  编号：%d   人口数：%d 电话区号：%s 地理位置：%s",p->name,p->captial,p->num,p->people,p->phone,p->where);
				getchar();
				break;
			case 5:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();	
				G[i]=InsertVex(G[i]);
				printf("插入成功！\n");
				getchar();break;
			case 6:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 		
				printf("请输入需要删除的地名：");
				scanf("%s",e1);getchar();
				back=DeleteVex(G[i],e1);
				if(back == 0)
					printf("该结点不存在\n");
				else
					printf("删除成功！\n");
				getchar();break;
			case 7:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				printf("请输入需要查找的地名：");
				scanf("%s",e1);getchar();
				back=FirstAdjVex(G[i],e1);
				if(back == -1)
					printf("该第一邻接点不存在\n");	
				getchar();break;
			case 8:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				printf("请输入需要查找的地名：");
				scanf("%s",e1);getchar();
				back=NextAdjVex(G[i],e1);
				getchar();break;
			case 9:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 		
				printf("请输入需要改变的第一个地名：");
				scanf("%s",e1); getchar(); 
				printf("请输入需要改变的第二个地名：");
				scanf("%s",e2); getchar();
				if(CorrectArc(G[i],e1,e2) != -1)
					printf("修改成功！\n");
				else 
					printf("该弧不存在!\n"); 
				getchar();break;
			case 10:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 		
				printf("请输入需要查询权值的第一个地名：");
				scanf("%s",e1);getchar();
				printf("请输入需要查询权值的第二个地名：");
				scanf("%s",e2);getchar();
				back=Arcweight(G[i],e1,e2);
				if(back == -1)
					printf("该弧不存在\n");
				else
					printf("该弧权值为%d",back);
				getchar();break;
			case 11:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();	
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				printf("请输入新增的弧的第一个地点：");
				scanf("%s",e1);getchar();
				printf("请输入新增的弧的第二个地点：");
				scanf("%s",e2);getchar();
				printf("请输入新增的弧的权值：");
				scanf("%d",&weight);getchar();
				back=InsertArc(G[i],e1,e2,weight);
				if(back == 0)
					printf("结点不存在\n");
				else
					printf("插入成功！\n");
				getchar();break; 
			case 12:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 		
				printf("请输入删除的弧的第一个地点：");
				scanf("%s",e1);getchar();
				printf("请输入删除的弧的第二个地点：");
				scanf("%s",e2);getchar();
				back=DeleteArc(G[i],e1,e2);
				if(back == 0)
					printf("该弧不存在\n");
				else
					printf("删除成功！\n");
				getchar();break; 
			case 13:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				if(Save(G[i]))
					printf("文件保存成功！\n");
				else
					printf("文件保存失败！\n");
				getchar();break; 
			case 14:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				G[i]=Load(G[i]);
				printf("文件读取成功！\n");
				getchar();break;	
			case 15:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
					getchar();
					break;
				} 	
				start=clock();
				printf("请输入构建网络的起始顶点：");
				scanf("%s",e1);getchar(); 
				back=Minspantree(G[i],e1);
				if(back == -1)
					printf("无此顶点\n");
				finish=clock();
				duration=(double)(finish-start)/CLOCKS_PER_SEC;
				printf("运行时间为%f秒\n",duration); 
				getchar();break;
			case 16:
				system("cls");
				printf("请输入该图的编号（0-19）：");
				scanf("%d",&i);getchar();
				if(G[i] == NULL)
				{
					printf("该图为空图！\n");
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
				printf("该图最少染色数为%d\n",back);
				finish=clock();
				duration=(double)(finish - start)/CLOCKS_PER_SEC;
				printf("运行时间为%f秒\n",duration); 
				getchar();break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
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
		printf("类型错误！\n");
		return NULL;
	}
	T->kind=i;
	printf("请输入图的顶点数:");
	scanf("%d", &T->vexnum); getchar();
	printf("请输入图的边数:");	
	scanf("%d", &T->arcnum); getchar();	
	for (i = 0; i < T->vexnum; i++)
	{
		printf("输入第%d个结点的信息\n", i+1);
		T->vertices[i].num=i;
		printf("名称：");
		scanf("%s",T->vertices[i].name);getchar();
		printf("省会：");
		scanf("%s",T->vertices[i].captial);getchar();
		printf("人口数：");
		scanf("%d",&T->vertices[i].people);getchar();
		printf("电话区号：");
		scanf("%s",T->vertices[i].phone);getchar();
		printf("地理位置：");
		scanf("%s",T->vertices[i].where);getchar();
		T->vertices[i].firstarc = NULL;
	} 
	for (k = 0; k < T->arcnum; k++)
	{
		printf("请输入第%d条弧的权值:",k+1);
		scanf("%d", &weight); getchar();
		printf("请输入弧头:");
		scanf("%s", tou); getchar();
		printf("请输入弧尾:");
		scanf("%s", wei); getchar();
		
		p = (ArcNode*)malloc(sizeof(ArcNode));
		j = LocateVex(T, wei);	
		i = LocateVex(T, tou);
		p->adjvex = j;
		p->Weight = weight;
		p->nextarc = T->vertices[i].firstarc;//插在表头 
		T->vertices[i].firstarc = p;

		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = i;
		q->Weight=weight;
		q->nextarc = T->vertices[j].firstarc; //插在表头
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
	printf("请输入需要修改的选项：1.名字  2.省会  3.人口数 4.电话区号 5.地理位置\n");
	scanf("%d",&e);getchar();
	if(e==1)
	{
		printf("请输入修改后的名字：");
		scanf("%s",G->vertices[i].name);getchar();
		return 1; 
	}
	else if(e==2)
	{
		printf("请输入修改后的省会：");
		scanf("%s",G->vertices[i].captial);getchar();
		return 1;
	}
	else if(e==3)
	{
		printf("请输入修改后的人口数：");
		scanf("%d",&G->vertices[i].people);getchar();
		return 1;
	} 
	else if(e==4)
	{
		printf("请输入修改后的电话区号：");
		scanf("%s",G->vertices[i].phone);getchar();
		return 1;
	} 
	else if(e==5)
	{
		printf("请输入修改后的地理位置：");
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
			printf("请输入改变后的权值：");
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
			printf("编号：%d  地名：%s  省会：%s  人口数：%d  电话区号：%s 地理位置：%s\n",G->vertices[p->adjvex].num,G->vertices[p->adjvex].name,\
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
	printf("所有邻接点信息为\n");
	while (p != NULL)
	{
		printf("编号：%d  地名：%s  省会：%s  人口数：%d  电话区号：%s 地理位置：%s\n",G->vertices[p->adjvex].num,G->vertices[p->adjvex].name,\
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

ALGraph InsertVex(ALGraph T)//插在最后的位置 
{
	printf("请输入插入顶点地名:");
	scanf("%s",T->vertices[T->vexnum].name);getchar();
	printf("请输入插入顶点省会:");
	scanf("%s",T->vertices[T->vexnum].captial);getchar();
	printf("请输入插入顶点人口数:");
	scanf("%d",&T->vertices[T->vexnum].people);getchar();
	printf("请输入插入顶点电话区号:");
	scanf("%s",T->vertices[T->vexnum].phone);getchar(); 
	printf("请输入插入顶点地理位置:");
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
	while (p)//释放所有以ch为头结点的弧 
	{
		pcrs = p;
		p = p->nextarc;
		free(pcrs);
		G->arcnum--;
	}
	
	for (i = j; i < G->vexnum - 1; i++) //所有节点前移一位 
		G->vertices[i] = G->vertices[i + 1];
	G->vexnum--;
	
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->vertices[i].firstarc;
		while (p != NULL)
		{
			if (p->adjvex != j)
			{	
				if (p->adjvex > j)//节点序号改变 
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
		printf("文件打开失败！\n");
		return ERROR;
	}
	fprintf(fp, "结点数： %d\n", T->vexnum);
	fprintf(fp, "弧数： %d\n", T->arcnum);
	fprintf(fp, "图的种类为： %d\n", T->kind);
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
	fgets(line, 250, fp);//读完后续空格 
	sscanf(line, "%*s%d", &arc);
	fgets(line, 250, fp);
	sscanf(line, "%*s%d", &T->kind);//读入字符串但是不赋值 
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
	printf("最小生成树为：\n");
	k=LocateVex(T,v);
	if(k == -1)
		return -1;
	for(j=0;j < T->vexnum;j++)//初始化 
		if(j != k)
		{ 
			strcpy(closedges[j].adjvex,T->vertices[k].name);
			closedges[j].lowcost=Arcweight(T,v,T->vertices[j].name);//不存在弧的话，权值是-1 
		} 
	closedges[k].lowcost=0;
	
	for(i=1;i<T->vexnum;i++)
	{
		min=0;//寻找最小边 
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
		printf("第%d条边:  %s  %s  权值%d\n",i,closedges[minsum].adjvex,T->vertices[minsum].name,min);
		closedges[minsum].lowcost=0;
		for(j=0;j < T->vexnum;j++)
		{
			weight=Arcweight(T,T->vertices[minsum].name,T->vertices[j].name);//同地名代表0
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
                k=k+1;    //处理下一个顶点
        else
        {
            color[k]=0;
            k=k-1;//回溯
        }
    }
    return -1; 
} 
