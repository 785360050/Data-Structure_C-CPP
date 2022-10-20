#pragma once
#include <iostream>
#include "Global Variables.h"


//顶点结构体
struct Graph_matrix_Vertex
{
	int no;//顶点编号
	//std::string name;//顶点名
	DataType* data;//顶点存放的数据元素
};
typedef Graph_matrix_Vertex Vertex_Matrix;
//邻接矩阵
struct Graph_matrix
{///边权值<0表示∞，=0表示不存在,无向图=1表示存在
	bool directed;//判断是否为有向图
	int num_vertex;//顶点总数;
	int num_edge;//边总数
	bool* state_visited;//访问状态
	Vertex_Matrix* vertex;//存放顶点的集合
	int** edge;//邻接矩阵
};

//检查是边权值否为∞
bool CheckEdge_Infinit(int weight);

//初始化邻接矩阵
void Graph_Init(Graph_matrix* graph, int num_vertex, bool directed);
//释放邻接矩阵空间
void Graph_Destroy(Graph_matrix* graph);
//添加边(已存在时不添加)
void Graph_Edge_Add(Graph_matrix* graph, int no_origin, int no_destination, int w);
//显示邻接矩阵
void Graph_Show_Matrix(Graph_matrix* graph);

//广度优先遍历
void Graph_Traverse_DFS(Graph_matrix* graph, int no_vertex);
//深度优先遍历
void Graph_Traverse_BFS(Graph_matrix* graph, int no_vertex);







