#pragma once
#include <iostream>
#include "Global Variables.h"



struct Graph_matrix_Vertex
{
	int no;//顶点编号
	std::string name;//顶点名
	DataType* data;//顶点存放的数据元素
};
typedef Graph_matrix_Vertex Vertex_Matrix;

struct Graph_matrix
{///边权值<0表示∞，=0表示不存在,无向图=1表示存在
	bool directed;//判断是否为有向图
	int num_vertex;//顶点总数;
	int num_edge;//边总数
	Vertex_Matrix vertex[maxsize];//存放顶点的集合
	int edge[maxsize][maxsize];//邻接矩阵
};


//初始化邻接矩阵
void Graph_Init(Graph_matrix* graph, int num, std::string name, bool directed, int edgeweight);
//添加边(已存在时不添加)
void Graph_Edge_Add(Graph_matrix* graph, int x, int y, int w);










