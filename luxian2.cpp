/*
21.旅游交通线路问题
有一些城镇和公路，由于沿途路况和其他因素的影响，每条旅行线路所需的旅行费用也不同，
要求设计一种数据结构，能够存储各个城镇之间的公路费用与长度（若存在的话），
在此基础上设计相关算法，使得用户任意输入起始城镇名称和终点城镇名称后，
可以给出一条最便宜的线路以及总里程最短的线路，并给出途径的每一个城镇和总共所需的费用和总长度。
*/ 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>//链表相关
#include<math.h>
#include<windows.h>//清屏函数头文件 
#include<limits.h>//无穷大或无穷小相关
#define Error -1;//定义错误信息
#define MVNum 500//城镇最大数 
 
typedef struct ENode {//定义边的结构体
	int v1, v2;//表示顶点（即城镇所在的邻接表的位置的下标）
	char city1[10], city2[10];//顶点/城镇的名称
	int mileage, cost, time;//边的权重:路程、费用、时间（单位为分钟）
}*edge;
 
typedef struct AdjVNode {//定义邻接点的结构体
	int adjv;//邻接点,表示所连接的城镇的位置，也就是下标
	char CityName[10];//表示所连接的城镇名称
	int mileage, cost, time;//边的权重：路程、费用、时间
	struct AdjVNode* Next;//指向下一个邻接点的指针
}*adjoin;
 
typedef struct VNode {//定义顶点表头结点的结构体
	char CityName[10];//顶点数据，即为城镇名称
	adjoin FirstEdge;//边的表头指针
}adjlist[MVNum];
 
typedef struct GNode {//定义图的结构体
	int Nv, Ne;//图的顶点数、边数
	adjlist G;//邻接表
}*graph;
 
typedef int DataType;//定义数据类型
 
typedef struct Queue {//创建队列结构体
	DataType Data;//队列的元素/数据
	struct Queue* Next;//尾指针
}*queue;


queue CreateQ();//创建队列
 
DataType back(queue Q);//返回队列中的最后一个元素
 
bool empty(queue Q);//判断队列是否为空，如果队列空则返回真
 
DataType front(queue Q);//返回队列的第一个元素
 
void pop(queue Q);//删除队列中的第一个元素
 
void push(queue Q, DataType data);//在队列末尾加入一个元素
 
int size(queue Q);//返回队列中元素的个数
 
void show(queue Q);//额外添加，将队列所有元素输出，测试用
 
 
queue CreateQ() {//创建队列
	queue Q = (queue)malloc(sizeof(struct Queue));//创建头节点/开辟空间
	Q->Next = NULL;//头节点空置
	return Q;
}
 
DataType back(queue Q) {//返回队列中的最后一个元素
	if (empty(Q)) return ERROR;//如果队列为空返回错误信息
	queue p = Q->Next;
	while (p->Next)p = p->Next;//找到最后一个元素的位置
	return p->Data;//返回最后一个元素
}
 
bool empty(queue Q) {//判断队列是否为空，如果队列空则返回真
	return Q->Next == NULL;
}
 
DataType front(queue Q) {//返回队列的第一个元素
	if (empty(Q)) return ERROR;//如果队列为空返回错误信息
	return  Q->Next->Data;//否则队列不为空直接返回第一个元素
}
 
void pop(queue Q) {//删除队列中的第一个元素
	if (empty(Q))return;//如果队列为空直接退出
	queue p = Q->Next;//删除第一个元素/结点
	Q->Next = p->Next;
	p->Next = NULL;
	free(p);//将已删除的结点的空间释放
}
 
void push(queue Q,DataType data) {//在队列末尾加入一个元素
	queue p = (queue)malloc(sizeof(struct Queue));//创建结点
	p->Next = NULL;//将准备插入的结点的尾指针指向空
	p->Data = data;//存入数据
	if (Q->Next) {//如果当前队列不为空
		queue q = Q->Next;
		while (q->Next)q = q->Next;
		q->Next = p;//插入结点
	}
	else Q->Next = p;//否则直接将要插入的结点作为第一个结点
}
 
int size(queue Q) {//返回队列中元素的个数
	int count = 0;//开一个变量计数
	queue p = Q->Next;
	while (p)p = p->Next, count++;//计数
	return count;//返回元素个数
}
 
void show(queue Q) {//额外添加，将队列所有元素输出，测试用
	if (empty(Q)) {//如果队列为空直接退出
		printf("队列为空\n");
		return;
	}
	queue p = Q->Next;//遍历输出
	while (p) {
		printf("%d ", p->Data);
		p = p->Next;
	}
	printf("\n");
}

 
//定义/初始化一个图，如果文件中有路线也把路线插入图中
graph CreateG();
 
//判断图是否为空
bool empty(graph G);
 
//在图G中查找城镇名称，如果不存在则返回错误信息ERROR，存在则返回该城镇所在邻接表的下标位置
int Search_CityName(graph G,char city[]);
 
//往图G中插入一条新的路线E
void Insert_Path(graph G, edge E);
 
//将邻接表进行输出，测试用
void show(graph G);
 
//将所有的路线进行输出
void Show_Path(graph G);
 
//将图中的某条路线进行修改
void Modify_Path(graph G,edge E);
 
//将图进行保存,格式为：城市1 城市2 路程 费用 时间
bool Save_File(graph G);
 
//读取文件，将文件中的路线全部输进邻接表中
bool Read_File(graph G);
 
//用该函数来递归查找P数组中的路径
void print_path(graph G, int i, int j);
 
//用Folyd算法生成当前城镇能到达的所有城市
void Floyd_path(graph G, char city[]);
 
//用Folyd算法生成任意两个城镇之间的费用最少的路线
void Floyd_Cost(graph G, char city1[], char city2[]);
 
//用Folyd算法生成任意两个城镇之间的路程最少的路线
void Floyd_Mileage(graph G, char city1[], char city2[]);
 
//用Folyd算法生成任意两个城镇之间的所用时间最少的路线
void Floyd_Time(graph G, char city1[], char city2[]);
 
//用广度优先搜索算法搜索中转站最少的路线，需要用到队列
void Bfs(graph G, char city1[], char city2[]);
 
//将v1到v2的中转站最少的路线打印出来
void Print_Path(graph G, int v1, int v2);
 

 
//定义/初始化一个图
graph CreateG() {
	graph G = (graph)malloc(sizeof(struct GNode));//建立图/开辟空间
	G->Ne = 0;//初始边数为0
	G->Nv = 0;//初始的顶点/城镇数目也为0
	for (int i = 0; i < MVNum; i++)//将图中的全部顶点的表头指针赋为空NULL
		G->G[i].FirstEdge = NULL;
	Read_File(G);//将文件中的路线输入图中
	return G;//将图返回
}
 
//判断图是否为空
bool empty(graph G) {
	return G->Nv == 0;
}
 
//在图G中查找城镇名称，如果不存在则返回错误信息ERROR，存在则返回该城镇所在邻接表的下标位置
int Search_CityName(graph G,char city[]) {
	if (empty(G))return Error;//如果当前图为空，则直接返回错误信息
	for (int i = 0; i < G->Nv; i++) //否则进行查找
		if (strcmp(G->G[i].CityName, city) == 0)return i;//找到了直接返回下标
	return Error;//没找到返回错误信息
}
 
//往图G中插入一条新的路线
void Insert_Path(graph G, edge E) {
	E->v1 = Search_CityName(G, E->city1);//先在原先的邻接表中查找两城镇的位置
	E->v2 = Search_CityName(G, E->city2);
	if (E->v1 == -1)E->v1 = G->Nv++;//没找到就在图中加入新的点，同时图中的顶点数+1
	if (E->v2 == -1)E->v2 = G->Nv++;
	adjoin p = (adjoin)malloc(sizeof(struct AdjVNode));//开辟一个新的邻接点
	p->adjv = E->v2; p->cost = E->cost;//给邻接点赋值：
	p->mileage = E->mileage; p->time = E->time; strcpy(p->CityName, E->city2);
	strcpy(G->G[E->v1].CityName, E->city1);//将城镇名称放入顶点数据
	adjoin s = G->G[E->v1].FirstEdge;//用尾插法将邻接点与邻接表进行连接
	if (s == NULL) {
		p->Next = G->G[E->v1].FirstEdge;
		G->G[E->v1].FirstEdge = p;
	}
	else {
		while (s->Next != NULL)s = s->Next;
		p->Next = s->Next;
		s->Next = p;
	}
	adjoin q = (adjoin)malloc(sizeof(struct AdjVNode));//无向边需要在边的两头都加入邻接点
	q->adjv = E->v1; q->cost = E->cost;//给邻接点赋值
	q->mileage = E->mileage; q->time = E->time; strcpy(q->CityName, E->city1);
	strcpy(G->G[E->v2].CityName, E->city2);//将城镇名称放入顶点数据
	s = G->G[E->v2].FirstEdge;//用尾插法将邻接点与邻接表进行连接
	if (s == NULL) {
		q->Next = G->G[E->v2].FirstEdge;
		G->G[E->v2].FirstEdge = q;
	}
	else {
		while (s->Next != NULL)s = s->Next;
		q->Next = s->Next;
		s->Next = q;
	}
	G->Ne++;//最后图的边的数目+1
}
 
//将邻接表进行输出，测试用
void show(graph G){
	for (int i = 0; i < G->Nv; i++) {
		printf("%s 可以去的城市:", G->G[i].CityName);
		adjoin p = G->G[i].FirstEdge;//将指针指向邻接表的该位置的表头结点的下一个结点
		while (p!=NULL) {
			printf("%s（费用为：%d） ", p->CityName, p->cost);
			p = p->Next;
		}
		printf("\n\n");
	}
}
 
//将图进行保存，格式为：城镇1 城镇2 路程 费用 时间
bool Save_File(graph G) {
	bool vis[MVNum][MVNum] = { false };//开一个布尔类型的二维数组进行标记，防止重复输出相同的路线
    FILE* fpw = fopen("C:\\Users\\fushengqingkong\\Desktop\\design\\data.txt", "w");//以只写的形式打开文本文件
	//若文件不存在则新建，否则，从起始位置开始写入文件，会覆盖文件原来的内容
	if (fpw == NULL)return false;//如果打开文件失败则退出
	for (int i = 0; i < G->Nv; i++) {
		adjoin p = G->G[i].FirstEdge;//将指针指向邻接表的该位置的表头结点的下一个结点
		while (p!=NULL) {
			if (!vis[i][p->adjv] && !vis[p->adjv][i]) {
				fprintf(fpw, "%s %s %d %d %d\n", G->G[i].CityName, p->CityName, p->mileage, p->cost, p->time);
				vis[i][p->adjv] = true;
				vis[p->adjv][i] = true;
			}
			p = p->Next;
		}
	}
	fclose(fpw);//关闭文件指针
	return true;
}
 
//读取文件，将文件中的路线全部输进图G中
bool Read_File(graph G) {
	FILE* fpr = fopen("C:\\Users\\fushengqingkong\\Desktop\\design\\data.txt", "r");
	//以只读的形式打开文本文件，不存在则退出
	edge E = (edge)malloc(sizeof(struct ENode));//给一条边开辟空间，用来进行读取输入
	if (fpr==NULL)return false;//如果文件不存在或文件为空，则退出
	//用while语句将所有的路线都插入图G中
	while (fscanf(fpr, "%s %s %d %d %d", E->city1, E->city2, &E->mileage, &E->cost, &E->time) != EOF) 
		Insert_Path(G, E);//直接将从文件中读出的路线插入图G中，并且不用保存
	fclose(fpr);//关闭文件指针
	return true;
}
 
//将图G中的某条路线进行修改
void Modify_Path(graph G,edge E) {
	E->v1 = Search_CityName(G, E->city1);//先在原先的邻接表中查找两城镇的位置
	E->v2 = Search_CityName(G, E->city2);
	if (E->v1 == -1 || E->v2 == -1) {//如果有一个城镇没有找到对应的邻接表中的位置，说明该路线不存在
		printf("该路线不存在！\n");
		return;
	}
	adjoin p = G->G[E->v1].FirstEdge;//将城镇1所在的邻接表的位置的表头指针赋给p
	while (p!=NULL) {
		if (p->adjv == E->v2) {//用指针p进行遍历查找城镇2
			p->cost = E->cost;//找到后进行数据修改
			p->mileage = E->mileage;
			p->time = E->time;
			break;//找到了直接退出循环
		}
		p = p->Next;//没找到继续找
	}
	p = G->G[E->v2].FirstEdge;//将城镇2所在的邻接表的位置的表头指针赋给p
	while (p!=NULL) {
		if (p->adjv == E->v1) {//用指针p进行遍历查找城镇1
			p->cost = E->cost;//找到后进行数据修改
			p->mileage = E->mileage;
			p->time = E->time;
			break;//找到了直接退出循环
		}
		p = p->Next;//没找到继续找
	}
	Save_File(G);//将修改后的路线进行保存
}
 
//将所有的路线进行输出
void Show_Path(graph G) {
	system("cls");
	printf("-----------------------------------------------------路线总表-----------------------------------------------------------\n");
	printf("________________________________________________________________________________________________________________________\n");
	printf("|%10s\t\t|%10s\t\t|%10s\t\t|%10s\t\t|%10s\t\t|\n", "起点", "终点", "路程(千米)", "费用(元)", "时间(分)");
	printf("________________________________________________________________________________________________________________________\n");
	bool vis[MVNum][MVNum] = { false };//开一个布尔类型的二维数组进行标记，防止重复输出相同的路线
	for (int i = 0; i < G->Nv; i++) {
		adjoin p = G->G[i].FirstEdge;//将指针指向邻接表的该位置的表头结点的下一个结点
		bool flag = false;//定义一个标记用于换行输出
		while (p!=NULL) {
			if (!vis[i][p->adjv] && !vis[p->adjv][i]) {
				//printf("%s到%s(反方向相同) 所需路程：%d 所需路费：%d 所需时间：%d", G->G[i].CityName, p->CityName, p->mileage, p->cost, p->time);
				printf("|%10s\t\t|%10s\t\t|%10d\t\t|%10d\t\t|%10d\t\t|", G->G[i].CityName, p->CityName, p->mileage, p->cost, p->time);
				vis[i][p->adjv] = true;//将路线输出后进行标记
				vis[p->adjv][i] = true;
				flag = true;
			}
			p = p->Next;
			if (flag) {//如果标记变为真，说明有了输出，进行换行
				printf("\n________________________________________________________________________________________________________________________\n");
				flag = false;//重新标记为假
			}
		}
	}
	
}
 
//用矩阵D来保存费用这个权值，用P来保存路径
//开的空间比较大，要用用全局变量，否则在函数内部定义会造成堆栈溢出
long long D[MVNum][MVNum], P[MVNum][MVNum];
 
//用Folyd算法生成当前城镇能到达的所有城镇 
void Floyd_path(graph G, char city[]) {
	int v = -1;
	for (int i = 0; i < G->Nv; i++)//对两个矩阵进行初始化
		if (strcmp(G->G[i].CityName, city) == 0) {
			v = i;
			break;
		}
 
	for (int i = 0; i < G->Nv; i++)//对Path矩阵进行初始化
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
 
	for (int k = 0; k < G->Nv; k++)//floyd算法
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (P[i][k] == 1 && P[k][j] == 1) {
					P[i][j] = 1;
				}
 
	printf("%s 能够到达的所有城镇:", G->G[v].CityName);
	for (int i = 0; i < G->Nv; i++) {
		if (P[v][i] == 1 && v != i)
			printf("%s ", G->G[i].CityName);
	}
	printf("\n\n");
}
 
//用该函数来递归查找P数组中的路径
void print_path(graph G,int i, int j) {
	int k = P[i][j];//找到上一个中转站/顶点（中转城镇）
	if (k == -1)
		//说明没有中转顶点，直接返回
		return;
	print_path(G, i, k);//寻找i和k之间
	printf("%s->", G->G[k].CityName);
	print_path(G, k, j);//寻找k和j之间
	
}
 
//用Folyd算法生成任意两个城镇之间的费用最少的路线
bool Floyd_Cost(graph G, int v1, int v2) {
	
	for(int i=0;i<G->Nv;i++)//对两个矩阵进行初始化
		for (int j = 0; j < G->Nv; j++) {
			if (i == j)D[i][j] = 0;//如果相同说明是同一点
			else D[i][j] = INT_MAX;//否则先全部赋值为无穷大
			P[i][j] = -1;//一开始路径都没有
		}
	for (int i = 0; i < G->Nv; i++) {//记录所有相邻城镇之间的费用
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->cost;//将边上的费用这个权值赋给数组D
			p = p->Next;
		}
	}
	for(int k=0;k<G->Nv;k++)//floyd算法
		for(int i=0;i<G->Nv;i++)
			for(int j=0;j<G->Nv;j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//因为路费不会是负数，所以不用加特判了
					if(i!=j)P[i][j] = k;
				}
	if (D[v1][v2] >= INT_MAX) return false;
	//如果最后的路线总费用大于等定义好的无穷大，那么说明路线不存在
	printf("从 %s 至 %s 花费最小的路线为:%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	print_path(G, v1, v2);
	printf("%s 共花费%d元\n\n", G->G[v2].CityName, D[v1][v2]);
	return true;
}
 
//用Folyd算法生成任意两个城镇之间的路程最少的路线
void Floyd_Mileage(graph G, int v1, int v2) {
	for (int i = 0; i < G->Nv; i++)//对两个矩阵进行初始化
		for (int j = 0; j < G->Nv; j++) {
			if (i == j)D[i][j] = 0;//如果相同说明是同一点
			else D[i][j] = INT_MAX;//否则先全部赋值为无穷大
			P[i][j] = -1;//一开始路径都没有
		}
	for (int i = 0; i < G->Nv; i++) {//记录所有相邻城镇之间的路程
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->mileage;//将边上的费用这个权值赋给数组D
			p = p->Next;
		}
	}
	for (int k = 0; k < G->Nv; k++)//floyd算法
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//因为路程不会是负数，所以不用加特判了
					if (i != j)P[i][j] = k;
				}
	printf("从 %s 至 %s 路程最小的路线为:%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	print_path(G, v1, v2);
	printf("%s 共有%dkm的路程\n\n", G->G[v2].CityName, D[v1][v2]);
}
 
//用Folyd算法生成任意两个城镇之间的所用时间最少的路线
void Floyd_Time(graph G, int v1, int v2) {
	for (int i = 0; i < G->Nv; i++)//对两个矩阵进行初始化
		for (int j = 0; j < G->Nv; j++) {
			if (i == j)D[i][j] = 0;//如果相同说明是同一点
			else D[i][j] = INT_MAX;//否则先全部赋值为无穷大
			P[i][j] = -1;//一开始路径都没有
		}
	for (int i = 0; i < G->Nv; i++) {//记录所有相邻城镇之间的时间
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->time;//将边上的费用这个权值赋给数组D
			p = p->Next;
		}
	}
	for (int k = 0; k < G->Nv; k++)//floyd算法
		for (int i = 0; i < G->Nv; i++)
			for (int j = 0; j < G->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//因为时间不会是负数，所以不用加特判了
					if (i != j)P[i][j] = k;
				}
	printf("从 %s 至 %s 所花时间最少的路线为:%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	print_path(G, v1, v2);
	printf("%s 共需时间%d分钟\n\n", G->G[v2].CityName, D[v1][v2]);
}
 
//下面这三个数组用与Bfs也就是广搜，搜索中转站最少的路线
int d[MVNum] = { 0 }, p[MVNum] = { 0 };
bool vis[MVNum];//用vis数组标记已经遍历过的邻接点
//用数组d来保存路线的长度,用数组P来保存广搜的路径
 
//将v1到v2的中转站最少的路线打印出来,需要先执行Bfs函数
void Print_Path(graph G, int v1, int v2) {
	if (v2 == v1)printf("%s", G->G[v1].CityName);//递归结束标志
	//刚进来时，v1肯定不等于v2，但是因为v1是起点，所以会递归到v1==v2时才会进行输出
	else if (p[v2] == -1)return;
	else {
		Print_Path(G, v1, p[v2]);//这里进行递归，直到v1==v2
		printf("->%s", G->G[v2].CityName);
	}
}
 
//用广度优先搜索算法搜索中转站最少的路线,需要用到队列
void Bfs(graph G, int v1, int v2) {
	printf("从 %s 至 %s 中转站最少的路线为:", G->G[v1].CityName, G->G[v2].CityName);
	memset(vis, false, sizeof vis);//将vis数组全部赋值为false
	memset(p, -1, sizeof p);//将数组p全部赋值为-1，表示没有初始路径
	queue q = CreateQ();//创建一个队列
	push(q, v1);//入队
	vis[v1] = true;//标记
	while (!empty(q)) {//当队列不为空时继续执行
		int v = front(q);//将队头出列
		pop(q);//出队，队头出队后马上将队头删除
		adjoin t = G->G[v].FirstEdge;
		while (t != NULL) {
			if (!vis[t->adjv]) {//如果这个邻接点没有遍历过
				vis[t->adjv] = true;//进行标记
				p[t->adjv] = v;//记录父节点
				d[t->adjv] = d[v] + 1;//中转站+1
				push(q, t->adjv);//入队
			}
			t = t->Next;
		}
	}
	Print_Path(G, v1, v2);//将路径进行打印
	printf(" 中转站的个数为:%d \n\n", d[v2] - 1);
	//输出中转站个数并进行换行，进行-1是因为d[v2]已经将v2也就是终点城镇算进去了
}
 
 
int FindMinDist(graph G, long long dist[], int collected[]) {   //查找未被收入的点中dist最小者
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
 
//用dijkstra算法生成任意两个城镇之间路程最短的路线
void Dijkstra(graph G, int v1, int v2) {
	long long dist[MVNum];
	int S = v1;
	int collected[MVNum], path[MVNum];
	int V, W;
 
	for (int i = 0; i < G->Nv; i++)//对两个矩阵进行初始化
		for (int j = 0; j < G->Nv; j++) {
			if (i == j) D[i][j] = 0;//如果相同说明是同一点
			else D[i][j] = INT_MAX;//否则先全部赋值为无穷大
		}
	for (int i = 0; i < G->Nv; i++) {//记录所有相邻城镇之间的路程
		adjoin p = G->G[i].FirstEdge;
		while (p != NULL) {
			D[i][p->adjv] = p->mileage;//将边上的路程这个权值赋给数组D
			p = p->Next;
		}
	}
 
	for (V = 0; V < G->Nv; V++) {//记录S→V的直达路程到dist中，同时记录父节点
		dist[V] = D[S][V];
		if (dist[V] < INT_MAX)
			path[V] = S;
		else
			path[V] = -1;
		collected[V] = 0;		//0标记未被收入的点
	}
 
	dist[S] = 0;
	collected[S] = 1;			//收入出发点
 
	while (1) {
		V = FindMinDist(G, dist, collected);
		if (V == -1)
			break;
 
		collected[V] = 1;		//收入距离最短的点
		for (W = 0; W < G->Nv; W++) {
			if (collected[W] == 0 && D[V][W] < INT_MAX) {
				if (dist[V] + D[V][W] < dist[W]) {			//刷新dist（距离）和path（父节点）数组
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
	printf("从 %s 至 %s 路程最小的路线为(Dijkstra):%s->", G->G[v1].CityName, G->G[v2].CityName, G->G[v1].CityName);
	while (i > 0) {
		printf("%s->", G->G[P_D[i--]].CityName);
	}
	printf("%s 共有%dkm的路程\n\n", G->G[v2].CityName, dist[v2]);
}


void Welcome();//主菜单界面
 
void Welcome_Print();//打印主菜单界面
 
void Goodbye();//结束程序 
 
void Function_One(graph G);//实现用户的功能1，查询城市路线
 
void Function_Two(graph G);//实现用户的功能2，查询所以路线
 
void Function_Three(graph G);//实现用户的功能3,查询可到达的城镇 
 
void Function_Four(graph G);//实现用户的功能4,修改/更新路线
 
void Function_Five(graph G);//实现用户的功能5，添加新路线
 

//打印主菜单界面
void Welcome_Print() {
	system("cls");//清屏 

	printf("\t\t\t\t**********************************************\n");//界面
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**               欢迎进入！                 **\n");
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**********************************************\n");
	printf("\t\t\t\t**-----------------功能菜单-----------------**\n");
	printf("\t\t\t\t**       查询城镇路线   ----------1         **\n");
	printf("\t\t\t\t**       查询所有路线   ----------2         **\n");
	printf("\t\t\t\t**       查询可到达城镇 ----------3         **\n");
	printf("\t\t\t\t**       修改/更新路线  ----------4         **\n");
	printf("\t\t\t\t**       添加新路线     ----------5         **\n");
	printf("\t\t\t\t**       退出当前系统   ----------0         **\n");
	printf("\t\t\t\t**********************************************\n");
}

//主菜单界面 
void Welcome() {
	//进入操作前先创建一个图，并将文件中的数据输进去
	graph G = CreateG();
	while (1) {//操作需要可以持续进行，用一个死循环
		Welcome_Print();
		printf("请输入你所想查询信息的选项（数字）: ");
		int choice;
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			Function_One(G);//查询城镇路线
			break;
		case 2:
			Function_Two(G);//查询所有路线
			break;
		case 3:
			Function_Three(G);//查询可到达城镇 
			break;
		case 4:
			Function_Four(G);//修改/更新路线
			break;
		case 5:
			Function_Five(G);//加入新的路线
			break;
		case 0:
			Goodbye();
			break;
		}
		printf("是否要继续进行操作？(是：1/否：0)\n");
		scanf("%d", &choice);
		if (choice == 0)Goodbye();
	}
}

//结束程序 
void Goodbye() { 

	system("cls");
	printf("\t\t\t\t**********************************************\n");
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**        欢迎下次使用！~再见！~~           **\n");
	printf("\t\t\t\t**                                          **\n");
	printf("\t\t\t\t**********************************************\n");
	exit(0);
}
 
//实现用户的功能1，查询城镇路线
void Function_One(graph G) {
	char city1[10], city2[10];//开两个数组输入两个城镇名称
	printf("请输入两个城镇的名称（起点和终点）：\n");
	scanf("%s%s", city1, city2);
	int v1 = Search_CityName(G, city1);//在原先的邻接表中查找两城镇的位置
	int v2 = Search_CityName(G, city2);
	if (v1 == -1 || v2 == -1) {//防止重复输出没有路线的信息，在查询之前就先进行判断
		//如果两个城镇中有一个或两个没找到在邻接表中的位置，说明该路线不存在
		printf("抱歉！暂时没有%s到达%s的路线！\n", city1, city2);
		return;
	}
	if (v1 == v2) {
		printf("您已经在该城镇中，无需查找路线！\n");
		return;
	}
	//直接调用已经写好的函数
	if(!Floyd_Cost(G, v1, v2))//费用最少
		printf("抱歉！暂时没有%s到达%s的路线！\n", city1, city2);
	else {
		//Floyd_Mileage(G, v1, v2);//路程最少
		Dijkstra(G, v1, v2);//dijkstra算法，求路程最少的路线，用来测试和与Floy算法比较
		Floyd_Time(G, v1, v2);//时间最少
		Bfs(G, v1, v2);//中转站最少
	}
}
 
//实现用户的功能2，查询所有路线
void Function_Two(graph G) {
	Show_Path(G);
}
 
//实现用户的功能3，查询当前城镇可以到达的城镇 
void Function_Three(graph G) {
	char city[10];
	printf("请输入当前城镇：\n");
	scanf("%s", city);
	int v = Search_CityName(G, city);
	if (v == -1) {
		printf("抱歉！暂时不存在该城镇!\n");
		return;
	}
	Floyd_path(G, city);
}
 
//实现用户的功能4，修改/更新路线
void Function_Four(graph G) {
	printf("请输入更新之后的路线：\n");
	printf("格式为：城镇1 城镇2 路程 费用 时间\n");
	edge E = (edge)malloc(sizeof(struct ENode));
	scanf("%s%s%d%d%d", E->city1, E->city2, &E->mileage, &E->cost, &E->time);
	E->v1 = Search_CityName(G, E->city1);//现在原先的邻接表中查找两城镇的位置
	E->v2 = Search_CityName(G, E->city2);
	if (E->v1 == -1 || E->v2 == -1) {//如果有一个城镇没有找到对应的邻接表中的位置，说明该路线不存在
		printf("该路线不存在！\n");
		return;
	}
	else {
		Modify_Path(G, E);
		printf("修改成功！\n");
	}
}
 
//实现用户的功能5，添加新路线
void Function_Five(graph G) {
	printf("请输入新的路线：\n");
	printf("格式为：城镇1 城镇2 路程 费用 时间\n");
	edge E = (edge)malloc(sizeof(struct ENode));
	scanf("%s%s%d%d%d", E->city1, E->city2, &E->mileage, &E->cost, &E->time);
	Insert_Path(G, E);
	printf("添加路线成功！\n");
	Save_File(G);//输入新的路线之后进行保存
}


int main() {
	
	Welcome();
 
	return 0;
}
