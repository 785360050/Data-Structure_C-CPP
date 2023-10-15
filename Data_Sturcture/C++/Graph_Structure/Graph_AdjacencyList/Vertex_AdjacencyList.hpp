#pragma once


#include "Edge_AdjacencyList.hpp"

template <typename DataType>
struct Vertex_AdjacencyList
{///顶点节点
	int no;//顶点在邻接表中的下标
	std::string name;//顶点名
	DataType* data;//数据元素
	Edge_AdjacencyList* head_edge;//存放边信息
};