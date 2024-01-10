/*
21.���ν�ͨ��·����
��һЩ����͹�·��������;·�����������ص�Ӱ�죬ÿ��������·��������з���Ҳ��ͬ��
Ҫ�����һ�����ݽṹ���ܹ��洢��������֮��Ĺ�·�����볤�ȣ������ڵĻ�����
�ڴ˻������������㷨��ʹ���û�����������ʼ�������ƺ��յ�������ƺ�
���Ը���һ������˵���·�Լ��������̵���·��������;����ÿһ��������ܹ�����ķ��ú��ܳ��ȡ�
*/ 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>//�������
#include<math.h>
#include<windows.h>//��������ͷ�ļ� 
#include<limits.h>//����������С���
#define Error -1;//���������Ϣ
#define MVNum 500//��������� 
 
typedef struct ENode {//����ߵĽṹ��
	int v1, v2;//��ʾ���㣨���������ڵ��ڽӱ��λ�õ��±꣩
	char city1[10], city2[10];//����/���������
	int mileage, cost, time;//�ߵ�Ȩ��:·�̡����á�ʱ�䣨��λΪ���ӣ�
}*edge;
 
typedef struct AdjVNode {//�����ڽӵ�Ľṹ��
	int adjv;//�ڽӵ�,��ʾ�����ӵĳ����λ�ã�Ҳ�����±�
	char CityName[10];//��ʾ�����ӵĳ�������
	int mileage, cost, time;//�ߵ�Ȩ�أ�·�̡����á�ʱ��
	struct AdjVNode* Next;//ָ����һ���ڽӵ��ָ��
}*adjoin;
 
typedef struct VNode {//���嶥���ͷ���Ľṹ��
	char CityName[10];//�������ݣ���Ϊ��������
	adjoin FirstEdge;//�ߵı�ͷָ��
}adjlist[MVNum];
 
typedef struct GNode {//����ͼ�Ľṹ��
	int Nv, Ne;//ͼ�Ķ�����������
	adjlist G;//�ڽӱ�
}*graph;
 
typedef int DataType;//������������
 
typedef struct Queue {//�������нṹ��
	DataType Data;//���е�Ԫ��/����
	struct Queue* Next;//βָ��
}*queue;


queue CreateQ();//��������
 
DataType back(queue Q);//���ض����е����һ��Ԫ��
 
bool empty(queue Q);//�ж϶����Ƿ�Ϊ�գ�������п��򷵻���
 
DataType front(queue Q);//���ض��еĵ�һ��Ԫ��
 
void pop(queue Q);//ɾ�������еĵ�һ��Ԫ��
 
void push(queue Q, DataType data);//�ڶ���ĩβ����һ��Ԫ��
 
int size(queue Q);//���ض�����Ԫ�صĸ���
 
void show(queue Q);//������ӣ�����������Ԫ�������������
 
 
queue CreateQ() {//��������
	queue Q = (queue)malloc(sizeof(struct Queue));//����ͷ�ڵ�/���ٿռ�
	Q->Next = NULL;//ͷ�ڵ����
	return Q;
}
 
DataType back(queue Q) {//���ض����е����һ��Ԫ��
	if (empty(Q)) return ERROR;//�������Ϊ�շ��ش�����Ϣ
	queue p = Q->Next;
	while (p->Next)p = p->Next;//�ҵ����һ��Ԫ�ص�λ��
	return p->Data;//�������һ��Ԫ��
}
 
bool empty(queue Q) {//�ж϶����Ƿ�Ϊ�գ�������п��򷵻���
	return Q->Next == NULL;
}
 
DataType front(queue Q) {//���ض��еĵ�һ��Ԫ��
	if (empty(Q)) return ERROR;//�������Ϊ�շ��ش�����Ϣ
	return  Q->Next->Data;//������в�Ϊ��ֱ�ӷ��ص�һ��Ԫ��
}
 
void pop(queue Q) {//ɾ�������еĵ�һ��Ԫ��
	if (empty(Q))return;//�������Ϊ��ֱ���˳�
	queue p = Q->Next;//ɾ����һ��Ԫ��/���
	Q->Next = p->Next;
	p->Next = NULL;
	free(p);//����ɾ���Ľ��Ŀռ��ͷ�
}
 
void push(queue Q,DataType data) {//�ڶ���ĩβ����һ��Ԫ��
	queue p = (queue)malloc(sizeof(struct Queue));//�������
	p->Next = NULL;//��׼������Ľ���βָ��ָ���
	p->Data = data;//��������
	if (Q->Next) {//�����ǰ���в�Ϊ��
		queue q = Q->Next;
		while (q->Next)q = q->Next;
		q->Next = p;//������
	}
	else Q->Next = p;//����ֱ�ӽ�Ҫ����Ľ����Ϊ��һ�����
}
 
int size(queue Q) {//���ض�����Ԫ�صĸ���
	int count = 0;//��һ����������
	queue p = Q->Next;
	while (p)p = p->Next, count++;//����
	return count;//����Ԫ�ظ���
}
 
void show(queue Q) {//������ӣ�����������Ԫ�������������
	if (empty(Q)) {//�������Ϊ��ֱ���˳�
		printf("����Ϊ��\n");
		return;
	}
	queue p = Q->Next;//�������
	while (p) {
		printf("%d ", p->Data);
		p = p->Next;
	}
	printf("\n");
}

 
//����/��ʼ��һ��ͼ������ļ�����·��Ҳ��·�߲���ͼ��
graph CreateG();
 
//�ж�ͼ�Ƿ�Ϊ��
bool empty(graph G);
 
//��ͼG�в��ҳ������ƣ�����������򷵻ش�����ϢERROR�������򷵻ظó��������ڽӱ���±�λ��
int Search_CityName(graph G,char city[]);
 
//��ͼG�в���һ���µ�·��E
void Insert_Path(graph G, edge E);
 
//���ڽӱ���������������
void show(graph G);
 
//�����е�·�߽������
void Show_Path(graph G);
 
//��ͼ�е�ĳ��·�߽����޸�
void Modify_Path(graph G,edge E);
 
//��ͼ���б���,��ʽΪ������1 ����2 ·�� ���� ʱ��
bool Save_File(graph G);
 
//��ȡ�ļ������ļ��е�·��ȫ������ڽӱ���
bool Read_File(graph G);
 
//�øú������ݹ����P�����е�·��
void print_path(graph G, int i, int j);
 
//��Folyd�㷨���ɵ�ǰ�����ܵ�������г���
void Floyd_path(graph G, char city[]);
 
//��Folyd�㷨����������������֮��ķ������ٵ�·��
void Floyd_Cost(graph G, char city1[], char city2[]);
 
//��Folyd�㷨����������������֮���·�����ٵ�·��
void Floyd_Mileage(graph G, char city1[], char city2[]);
 
//��Folyd�㷨����������������֮�������ʱ�����ٵ�·��
void Floyd_Time(graph G, char city1[], char city2[]);
 
//�ù�����������㷨������תվ���ٵ�·�ߣ���Ҫ�õ�����
void Bfs(graph G, char city1[], char city2[]);
 
//��v1��v2����תվ���ٵ�·�ߴ�ӡ����
void Print_Path(graph G, int v1, int v2);
 

 
//����/��ʼ��һ��ͼ
graph CreateG() {
	graph G = (graph)malloc(sizeof(struct GNode));//����ͼ/���ٿռ�
	G->Ne = 0;//��ʼ����Ϊ0
	G->Nv = 0;//��ʼ�Ķ���/������ĿҲΪ0
	for (int i = 0; i < MVNum; i++)//��ͼ�е�ȫ������ı�ͷָ�븳Ϊ��NULL
		G->G[i].FirstEdge = NULL;
	Read_File(G);//���ļ��е�·������ͼ��
	return G;//��ͼ����
}
 
//�ж�ͼ�Ƿ�Ϊ��
bool empty(graph G) {
	return G->Nv == 0;
}
 
//��ͼG�в��ҳ������ƣ�����������򷵻ش�����ϢERROR�������򷵻ظó��������ڽӱ���±�λ��
int Search_CityName(graph G,char city[]) {
	if (empty(G))return Error;//�����ǰͼΪ�գ���ֱ�ӷ��ش�����Ϣ
	for (int i = 0; i < G->Nv; i++) //������в���
		if (strcmp(G->G[i].CityName, city) == 0)return i;//�ҵ���ֱ�ӷ����±�
	return Error;//û�ҵ����ش�����Ϣ
}
 
//��ͼG�в���һ���µ�·��
void Insert_Path(graph G, edge E) {
	E->v1 = Search_CityName(G, E->city1);//����ԭ�ȵ��ڽӱ��в����������λ��
	E->v2 = Search_CityName(G, E->city2);
	if (E->v1 == -1)E->v1 = G->Nv++;//û�ҵ�����ͼ�м����µĵ㣬ͬʱͼ�еĶ�����+1
	if (E->v2 == -1)E->v2 = G->Nv++;
	adjoin p = (adjoin)malloc(sizeof(struct AdjVNode));//����һ���µ��ڽӵ�
	p->adjv = E->v2; p->cost = E->cost;//���ڽӵ㸳ֵ��
	p->mileage = E->mileage; p->time = E->time; strcpy(p->CityName, E->city2);
	strcpy(G->G[E->v1].CityName, E->city1);//���������Ʒ��붥������
	adjoin s = G->G[E->v1].FirstEdge;//��β�巨���ڽӵ����ڽӱ��������
	if (s == NULL) {
		p->Next = G->G[E->v1].FirstEdge;
		G->G[E->v1].FirstEdge = p;
	}
	else {
		while (s->Next != NULL)s = s->Next;
		p->Next = s->Next;
		s->Next = p;
	}
	adjoin q = (adjoin)malloc(sizeof(struct AdjVNode));//�������Ҫ�ڱߵ���ͷ�������ڽӵ�
	q->adjv = E->v1; q->cost = E->cost;//���ڽӵ㸳ֵ
	q->mileage = E->mileage; q->time = E->time; strcpy(q->CityName, E->city1);
	strcpy(G->G[E->v2].CityName, E->city2);//���������Ʒ��붥������
	s = G->G[E->v2].FirstEdge;//��β�巨���ڽӵ����ڽӱ��������
	if (s == NULL) {
		q->Next = G->G[E->v2].FirstEdge;
		G->G[E->v2].FirstEdge = q;
	}
	else {
		while (s->Next != NULL)s = s->Next;
		q->Next = s->Next;
		s->Next = q;
	}
	G->Ne++;//���ͼ�ıߵ���Ŀ+1
}
 
//���ڽӱ���������������
void show(graph G){
	for (int i = 0; i < G->Nv; i++) {
		printf("%s ����ȥ�ĳ���:", G->G[i].CityName);
		adjoin p = G->G[i].FirstEdge;//��ָ��ָ���ڽӱ�ĸ�λ�õı�ͷ������һ�����
		while (p!=NULL) {
			printf("%s������Ϊ��%d�� ", p->CityName, p->cost);
			p = p->Next;
		}
		printf("\n\n");
	}
}
 
//��ͼ���б��棬��ʽΪ������1 ����2 ·�� ���� ʱ��
bool Save_File(graph G) {
	bool vis[MVNum][MVNum] = { false };//��һ���������͵Ķ�ά������б�ǣ���ֹ�ظ������ͬ��·��
    FILE* fpw = fopen("C:\\Users\\fushengqingkong\\Desktop\\design\\data.txt", "w");//��ֻд����ʽ���ı��ļ�
	//���ļ����������½������򣬴���ʼλ�ÿ�ʼд���ļ����Ḳ���ļ�ԭ��������
	if (fpw == NULL)return false;//������ļ�ʧ�����˳�
	for (int i = 0; i < G->Nv; i++) {
		adjoin p = G->G[i].FirstEdge;//��ָ��ָ���ڽӱ�ĸ�λ�õı�ͷ������һ�����
		while (p!=NULL) {
			if (!vis[i][p->adjv] && !vis[p->adjv][i]) {
				fprintf(fpw, "%s %s %d %d %d\n", G->G[i].CityName, p->CityName, p->mileage, p->cost, p->time);
				vis[i][p->adjv] = true;
				vis[p->adjv][i] = true;
			}
			p = p->Next;
		}
	}
	fclose(fpw);//�ر��ļ�ָ��
	return true;
}
 
//��ȡ�ļ������ļ��е�·��ȫ�����ͼG��
bool Read_File(graph G) {
	FILE* fpr = fopen("C:\\Users\\fushengqingkong\\Desktop\\design\\data.txt", "r");
	//��ֻ������ʽ���ı��ļ������������˳�
	edge E = (edge)malloc(sizeof(struct ENode));//��һ���߿��ٿռ䣬�������ж�ȡ����
	if (fpr==NULL)return false;//����ļ������ڻ��ļ�Ϊ�գ����˳�
	//��while��佫���е�·�߶�����ͼG��
	while (fscanf(fpr, "%s %s %d %d %d", E->city1, E->city2, &E->mileage, &E->cost, &E->time) != EOF) 
		Insert_Path(G, E);//ֱ�ӽ����ļ��ж�����·�߲���ͼG�У����Ҳ��ñ���
	fclose(fpr);//�ر��ļ�ָ��
	return true;
}
 
//��ͼG�е�ĳ��·�߽����޸�
void Modify_Path(graph G,edge E) {
	E->v1 = Search_CityName(G, E->city1);//����ԭ�ȵ��ڽӱ��в����������λ��
	E->v2 = Search_CityName(G, E->city2);
	if (E->v1 == -1 || E->v2 == -1) {//�����һ������û���ҵ���Ӧ���ڽӱ��е�λ�ã�˵����·�߲�����
		printf("��·�߲����ڣ�\n");
		return;
	}
	adjoin p = G->G[E->v1].FirstEdge;//������1���ڵ��ڽӱ��λ�õı�ͷָ�븳��p
	while (p!=NULL) {
		if (p->adjv == E->v2) {//��ָ��p���б������ҳ���2
			p->cost = E->cost;//�ҵ�����������޸�
			p->mileage = E->mileage;
			p->time = E->time;
			break;//�ҵ���ֱ���˳�ѭ��
		}
		p = p->Next;//û�ҵ�������
	}
	p = G->G[E->v2].FirstEdge;//������2���ڵ��ڽӱ��λ�õı�ͷָ�븳��p
	while (p!=NULL) {
		if (p->adjv == E->v1) {//��ָ��p���б������ҳ���1
			p->cost = E->cost;//�ҵ�����������޸�
			p->mileage = E->mileage;
			p->time = E->time;
			break;//�ҵ���ֱ���˳�ѭ��
		}
		p = p->Next;//û�ҵ�������
	}
	Save_File(G);//���޸ĺ��·�߽��б���
}
 
//�����е�·�߽������
void Show_Path(graph G) {
	system("cls");
	printf("-----------------------------------------------------·���ܱ�-----------------------------------------------------------\n");
	printf("________________________________________________________________________________________________________________________\n");
	printf("|%10s\t\t|%10s\t\t|%10s\t\t|%10s\t\t|%10s\t\t|\n", "���", "�յ�", "·��(ǧ��)", "����(Ԫ)", "ʱ��(��)");
	printf("________________________________________________________________________________________________________________________\n");
	bool vis[MVNum][MVNum] = { false };//��һ���������͵Ķ�ά������б�ǣ���ֹ�ظ������ͬ��·��
	for (int i = 0; i < G->Nv; i++) {
		adjoin p = G->G[i].FirstEdge;//��ָ��ָ���ڽӱ�ĸ�λ�õı�ͷ������һ�����
		bool flag = false;//����һ��������ڻ������
		while (p!=NULL) {
			if (!vis[i][p->adjv] && !vis[p->adjv][i]) {
				//printf("%s��%s(��������ͬ) ����·�̣�%d ����·�ѣ�%d ����ʱ�䣺%d", G->G[i].CityName, p->CityName, p->mileage, p->cost, p->time);
				printf("|%10s\t\t|%10s\t\t|%10d\t\t|%10d\t\t|%10d\t\t|", G->G[i].CityName, p->CityName, p->mileage, p->cost, p->time);
				vis[i][p->adjv] = true;//��·���������б��
				vis[p->adjv][i] = true;
				flag = true;
			}
			p = p->Next;
			if (flag) {//�����Ǳ�Ϊ�棬˵��������������л���
				printf("\n________________________________________________________________________________________________________________________\n");
				flag = false;//���±��Ϊ��
			}
		}
	}
	
}
 
//�þ���D������������Ȩֵ����P������·��
//���Ŀռ�Ƚϴ�Ҫ����ȫ�ֱ����������ں����ڲ��������ɶ�ջ���
long long D[MVNum][MVNum], P[MVNum][MVNum];
 
//��Folyd�㷨���ɵ�ǰ�����ܵ�������г��� 
void Floyd_path(graph G, char city[]) {
	int v = -1;
	for (int i = 0; i < G->Nv; i++)//������������г�ʼ��
		if (strcmp(G->G[i].CityName, city) == 0) {
			v = i;
			break;
		}
 
	for (int i = 0; i < G->Nv; i++)//��Path������г�ʼ��
		for (int j = 0; j < G->Nv; j++) {
			P[i][j] = -1;//
		}
	//memset(P,-1,sizeof P);
	for (int i = 0; i < G->Nv; i++) {
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			P[i][p->adjv] = 1;
			P[p->adjv][i] = 1;
			p = p->Next;
		}
	}
 
	for (int k = 0; k < G->Nv; k++)//floyd�㷨
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (P[i][k] == 1 && P[k][j] == 1) {
					P[i][j] = 1;
				}
 
	printf("%s �ܹ���������г���:", G->G[v].CityName);
	for (int i = 0; i < G->Nv; i++) {
		if (P[v][i] == 1 && v != i)
			printf("%s ", G->G[i].CityName);
	}
	printf("\n\n");
}
 
//�øú������ݹ����P�����е�·��
void print_path(graph G,int i, int j) {
	int k = P[i][j];//�ҵ���һ����תվ/���㣨��ת����
	if (k == -1)
		//˵��û����ת���㣬ֱ�ӷ���
		return;
	print_path(G, i, k);//Ѱ��i��k֮��
	printf("%s->", G->G[k].CityName);
	print_path(G, k, j);//Ѱ��k��j֮��
	
}
 
//��Folyd�㷨����������������֮��ķ������ٵ�·��
bool Floyd_Cost(graph G, int v1, int v2) {
	
	for(int i=0;i<G->Nv;i++)//������������г�ʼ��
		for (int j = 0; j < G->Nv; j++) {
			if (i == j)D[i][j] = 0;//�����ͬ˵����ͬһ��
			else D[i][j] = INT_MAX;//������ȫ����ֵΪ�����
			P[i][j] = -1;//һ��ʼ·����û��
		}
	for (int i = 0; i < G->Nv; i++) {//��¼�������ڳ���֮��ķ���
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->cost;//�����ϵķ������Ȩֵ��������D
			p = p->Next;
		}
	}
	for(int k=0;k<G->Nv;k++)//floyd�㷨
		for(int i=0;i<G->Nv;i++)
			for(int j=0;j<G->Nv;j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//��Ϊ·�Ѳ����Ǹ��������Բ��ü�������
					if(i!=j)P[i][j] = k;
				}
	if (D[v1][v2] >= INT_MAX) return false;
	//�������·���ܷ��ô��ڵȶ���õ��������ô˵��·�߲�����
	printf("�� %s �� %s ������С��·��Ϊ:%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	print_path(G, v1, v2);
	printf("%s ������%dԪ\n\n", G->G[v2].CityName, D[v1][v2]);
	return true;
}
 
//��Folyd�㷨����������������֮���·�����ٵ�·��
void Floyd_Mileage(graph G, int v1, int v2) {
	for (int i = 0; i < G->Nv; i++)//������������г�ʼ��
		for (int j = 0; j < G->Nv; j++) {
			if (i == j)D[i][j] = 0;//�����ͬ˵����ͬһ��
			else D[i][j] = INT_MAX;//������ȫ����ֵΪ�����
			P[i][j] = -1;//һ��ʼ·����û��
		}
	for (int i = 0; i < G->Nv; i++) {//��¼�������ڳ���֮���·��
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->mileage;//�����ϵķ������Ȩֵ��������D
			p = p->Next;
		}
	}
	for (int k = 0; k < G->Nv; k++)//floyd�㷨
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//��Ϊ·�̲����Ǹ��������Բ��ü�������
					if (i != j)P[i][j] = k;
				}
	printf("�� %s �� %s ·����С��·��Ϊ:%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	print_path(G, v1, v2);
	printf("%s ����%dkm��·��\n\n", G->G[v2].CityName, D[v1][v2]);
}
 
//��Folyd�㷨����������������֮�������ʱ�����ٵ�·��
void Floyd_Time(graph G, int v1, int v2) {
	for (int i = 0; i < G->Nv; i++)//������������г�ʼ��
		for (int j = 0; j < G->Nv; j++) {
			if (i == j)D[i][j] = 0;//�����ͬ˵����ͬһ��
			else D[i][j] = INT_MAX;//������ȫ����ֵΪ�����
			P[i][j] = -1;//һ��ʼ·����û��
		}
	for (int i = 0; i < G->Nv; i++) {//��¼�������ڳ���֮���ʱ��
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->time;//�����ϵķ������Ȩֵ��������D
			p = p->Next;
		}
	}
	for (int k = 0; k < G->Nv; k++)//floyd�㷨
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//��Ϊʱ�䲻���Ǹ��������Բ��ü�������
					if (i != j)P[i][j] = k;
				}
	printf("�� %s �� %s ����ʱ�����ٵ�·��Ϊ:%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	print_path(G, v1, v2);
	printf("%s ����ʱ��%d����\n\n", G->G[v2].CityName, D[v1][v2]);
}
 
//������������������BfsҲ���ǹ��ѣ�������תվ���ٵ�·��
int d[MVNum] = { 0 }, p[MVNum] = { 0 };
bool vis[MVNum];//��vis�������Ѿ����������ڽӵ�
//������d������·�ߵĳ���,������P��������ѵ�·��
 
//��v1��v2����תվ���ٵ�·�ߴ�ӡ����,��Ҫ��ִ��Bfs����
void Print_Path(graph G, int v1, int v2) {
	if (v2 == v1)printf("%s", G->G[v1].CityName);//�ݹ������־
	//�ս���ʱ��v1�϶�������v2��������Ϊv1����㣬���Ի�ݹ鵽v1==v2ʱ�Ż�������
	else if (p[v2] == -1)return;
	else {
		Print_Path(G, v1, p[v2]);//������еݹ飬ֱ��v1==v2
		printf("->%s", G->G[v2].CityName);
	}
}
 
//�ù�����������㷨������תվ���ٵ�·��,��Ҫ�õ�����
void Bfs(graph G, int v1, int v2) {
	printf("�� %s �� %s ��תվ���ٵ�·��Ϊ:", G->G[v1].CityName, G->G[v2].CityName);
	memset(vis, false, sizeof vis);//��vis����ȫ����ֵΪfalse
	memset(p, -1, sizeof p);//������pȫ����ֵΪ-1����ʾû�г�ʼ·��
	queue q = CreateQ();//����һ������
	push(q, v1);//���
	vis[v1] = true;//���
	while (!empty(q)) {//�����в�Ϊ��ʱ����ִ��
		int v = front(q);//����ͷ����
		pop(q);//���ӣ���ͷ���Ӻ����Ͻ���ͷɾ��
		adjoin t = G->G[v].FirstEdge;
		while (t != NULL) {
			if (!vis[t->adjv]) {//�������ڽӵ�û�б�����
				vis[t->adjv] = true;//���б��
				p[t->adjv] = v;//��¼���ڵ�
				d[t->adjv] = d[v] + 1;//��תվ+1
				push(q, t->adjv);//���
			}
			t = t->Next;
		}
	}
	Print_Path(G, v1, v2);//��·�����д�ӡ
	printf(" ��תվ�ĸ���Ϊ:%d \n\n", d[v2] - 1);
	//�����תվ���������л��У�����-1����Ϊd[v2]�Ѿ���v2Ҳ�����յ�������ȥ��
}
 
 
int FindMinDist(graph G, long long dist[], int collected[]) {   //����δ������ĵ���dist��С��
	int MinV, V;
	long long MinDist = INT_MAX;
	for (V = 0; V < G->Nv; V++) {
		if (collected[V] == 0 && dist[V] < MinDist) {
			MinDist = dist[V];
			MinV = V;
		}
	}
 
	if (MinDist < INT_MAX) {
		return MinV;
	}
	else {
		return -1;
	}
}
 
//��dijkstra�㷨����������������֮��·����̵�·��
void Dijkstra(graph G, int v1, int v2) {
	long long dist[MVNum];
	int S = v1;
	int collected[MVNum], path[MVNum];
	int V, W;
 
	for (int i = 0; i < G->Nv; i++)//������������г�ʼ��
		for (int j = 0; j < G->Nv; j++) {
			if (i == j) D[i][j] = 0;//�����ͬ˵����ͬһ��
			else D[i][j] = INT_MAX;//������ȫ����ֵΪ�����
		}
	for (int i = 0; i < G->Nv; i++) {//��¼�������ڳ���֮���·��
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->mileage;//�����ϵ�·�����Ȩֵ��������D
			p = p->Next;
		}
	}
 
	for (V = 0; V < G->Nv; V++) {//��¼S��V��ֱ��·�̵�dist�У�ͬʱ��¼���ڵ�
		dist[V] = D[S][V];
		if (dist[V] < INT_MAX)
			path[V] = S;
		else
			path[V] = -1;
		collected[V] = 0;		//0���δ������ĵ�
	}
 
	dist[S] = 0;
	collected[S] = 1;			//���������
 
	while (1) {
		V = FindMinDist(G, dist, collected);
		if (V == -1)
			break;
 
		collected[V] = 1;		//���������̵ĵ�
		for (W = 0; W < G->Nv; W++) {
			if (collected[W] == 0 && D[V][W] < INT_MAX) {
				if (dist[V] + D[V][W] < dist[W]) {			//ˢ��dist�����룩��path�����ڵ㣩����
					dist[W] = dist[V] + D[V][W];
					path[W] = V;
				}
			}
		}
	}
 
	int P_D[MVNum];
	int i = 0;
	P_D[i] = v2;
	int vx = v2;
	while (P_D[i] != v1) {
		vx = path[vx];
		P_D[++i] = vx;
	}
	i--;
	printf("�� %s �� %s ·����С��·��Ϊ(Dijkstra):%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	while (i > 0) {
		printf("%s->", G->G[P_D[i--]].CityName);
	}
	printf("%s ����%dkm��·��\n\n", G->G[v2].CityName, dist[v2]);
}


void Welcome();//���˵�����
 
void Welcome_Print();//��ӡ���˵�����
 
void Goodbye();//�������� 
 
void Function_One(graph G);//ʵ���û��Ĺ���1����ѯ����·��
 
void Function_Two(graph G);//ʵ���û��Ĺ���2����ѯ����·��
 
void Function_Three(graph G);//ʵ���û��Ĺ���3,��ѯ�ɵ���ĳ��� 
 
void Function_Four(graph G);//ʵ���û��Ĺ���4,�޸�/����·��
 
void Function_Five(graph G);//ʵ���û��Ĺ���5�������·��
 

//��ӡ���˵�����
void Welcome_Print() {
	system("cls");//���� 

	printf("\t\t\t\t**********************************************\n");//����
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**               ��ӭ���룡                 **\n");
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**********************************************\n");
	printf("\t\t\t\t**-----------------���ܲ˵�-----------------**\n");
	printf("\t\t\t\t**       ��ѯ����·��   ----------1         **\n");
	printf("\t\t\t\t**       ��ѯ����·��   ----------2         **\n");
	printf("\t\t\t\t**       ��ѯ�ɵ������ ----------3         **\n");
	printf("\t\t\t\t**       �޸�/����·��  ----------4         **\n");
	printf("\t\t\t\t**       �����·��     ----------5         **\n");
	printf("\t\t\t\t**       �˳���ǰϵͳ   ----------0         **\n");
	printf("\t\t\t\t**********************************************\n");
}

//���˵����� 
void Welcome() {
	//�������ǰ�ȴ���һ��ͼ�������ļ��е��������ȥ
	graph G = CreateG();
	while (1) {//������Ҫ���Գ������У���һ����ѭ��
		Welcome_Print();
		printf("�������������ѯ��Ϣ��ѡ����֣�: ");
		int choice;
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			Function_One(G);//��ѯ����·��
			break;
		case 2:
			Function_Two(G);//��ѯ����·��
			break;
		case 3:
			Function_Three(G);//��ѯ�ɵ������ 
			break;
		case 4:
			Function_Four(G);//�޸�/����·��
			break;
		case 5:
			Function_Five(G);//�����µ�·��
			break;
		case 0:
			Goodbye();
			break;
		}
		printf("�Ƿ�Ҫ�������в�����(�ǣ�1/��0)\n");
		scanf("%d", &choice);
		if (choice == 0)Goodbye();
	}
}

//�������� 
void Goodbye() { 

	system("cls");
	printf("\t\t\t\t**********************************************\n");
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**        ��ӭ�´�ʹ�ã�~�ټ���~~           **\n");
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**********************************************\n");
	exit(0);
}
 
//ʵ���û��Ĺ���1����ѯ����·��
void Function_One(graph G) {
	char city1[10], city2[10];//��������������������������
	printf("������������������ƣ������յ㣩��\n");
	scanf("%s%s", city1, city2);
	int v1 = Search_CityName(G, city1);//��ԭ�ȵ��ڽӱ��в����������λ��
	int v2 = Search_CityName(G, city2);
	if (v1 == -1 || v2 == -1) {//��ֹ�ظ����û��·�ߵ���Ϣ���ڲ�ѯ֮ǰ���Ƚ����ж�
		//���������������һ��������û�ҵ����ڽӱ��е�λ�ã�˵����·�߲�����
		printf("��Ǹ����ʱû��%s����%s��·�ߣ�\n", city1, city2);
		return;
	}
	if (v1 == v2) {
		printf("���Ѿ��ڸó����У��������·�ߣ�\n");
		return;
	}
	//ֱ�ӵ����Ѿ�д�õĺ���
	if(!Floyd_Cost(G, v1, v2))//��������
		printf("��Ǹ����ʱû��%s����%s��·�ߣ�\n", city1, city2);
	else {
		//Floyd_Mileage(G, v1, v2);//·������
		Dijkstra(G, v1, v2);//dijkstra�㷨����·�����ٵ�·�ߣ��������Ժ���Floy�㷨�Ƚ�
		Floyd_Time(G, v1, v2);//ʱ������
		Bfs(G, v1, v2);//��תվ����
	}
}
 
//ʵ���û��Ĺ���2����ѯ����·��
void Function_Two(graph G) {
	Show_Path(G);
}
 
//ʵ���û��Ĺ���3����ѯ��ǰ������Ե���ĳ��� 
void Function_Three(graph G) {
	char city[10];
	printf("�����뵱ǰ����\n");
	scanf("%s", city);
	int v = Search_CityName(G, city);
	if (v == -1) {
		printf("��Ǹ����ʱ�����ڸó���!\n");
		return;
	}
	Floyd_path(G, city);
}
 
//ʵ���û��Ĺ���4���޸�/����·��
void Function_Four(graph G) {
	printf("���������֮���·�ߣ�\n");
	printf("��ʽΪ������1 ����2 ·�� ���� ʱ��\n");
	edge E = (edge)malloc(sizeof(struct ENode));
	scanf("%s%s%d%d%d", E->city1, E->city2, &E->mileage, &E->cost, &E->time);
	E->v1 = Search_CityName(G, E->city1);//����ԭ�ȵ��ڽӱ��в����������λ��
	E->v2 = Search_CityName(G, E->city2);
	if (E->v1 == -1 || E->v2 == -1) {//�����һ������û���ҵ���Ӧ���ڽӱ��е�λ�ã�˵����·�߲�����
		printf("��·�߲����ڣ�\n");
		return;
	}
	else {
		Modify_Path(G, E);
		printf("�޸ĳɹ���\n");
	}
}
 
//ʵ���û��Ĺ���5�������·��
void Function_Five(graph G) {
	printf("�������µ�·�ߣ�\n");
	printf("��ʽΪ������1 ����2 ·�� ���� ʱ��\n");
	edge E = (edge)malloc(sizeof(struct ENode));
	scanf("%s%s%d%d%d", E->city1, E->city2, &E->mileage, &E->cost, &E->time);
	Insert_Path(G, E);
	printf("���·�߳ɹ���\n");
	Save_File(G);//�����µ�·��֮����б���
}


int main() {
	
	Welcome();
 
	return 0;
}
