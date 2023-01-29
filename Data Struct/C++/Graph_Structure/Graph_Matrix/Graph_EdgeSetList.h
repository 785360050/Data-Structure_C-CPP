#pragma once

#include <iostream>
#include "../Graph_Structure.h"

template <typename DataType>
class Graph_EdgeSet:public Graph_Structure<DataType,DataType>
{
private:
	struct Graph_EdgeSet_Edge
	{
		int no_source;
		int no_destination;
		int weight;
	};
private:
	Graph_EdgeSet_Edge* edge;//存放边的数组(顺序表实现)

public:
	Graph_EdgeSet(bool directed, int num_vertex)
		:Graph_Structure<DataType, DataType>(directed, num_vertex),
		edge(new Graph_EdgeSet_Edge[num_vertex * (num_vertex - 1)])///n个顶点最多有n(n-1)条边
	{};
	//释放边集数组空间
	~Graph_EdgeSet()
	{
		delete[] edge;
	}

public:
	//添加边(已存在时不添加)
	void Graph_Edge_Add(int no_origin, int no_destination, int weight)
	{///无向图仅储存两个记录
		try
		{
			for (int i = 0; i < this->num_edge; ++i)
			{
				if (edge->no_source == no_origin && edge->no_destination == no_destination)
					throw std::exception("Graph Edge Add Failed : Edge already exisited!");
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		///边集数组的添加、删除边，不必满足有序，连续

		edge[this->num_edge].no_source = no_origin;
		edge[this->num_edge].no_destination = no_destination;
		edge[this->num_edge].weight = weight;
		++this->num_edge;
		if (this->directed == false)
		{
			edge[this->num_edge].no_source = no_destination;
			edge[this->num_edge].no_destination = no_origin;
			edge[this->num_edge].weight = weight;
			++this->num_edge;
		}

	}
	void Graph_Edge_Delete(int no_origin, int no_destination)
	{
		//try
		//{
		//	for (int i = 0; i < num_edge; ++i)
		//	{
		//		if (edge[i].no_source == no_origin && edge[i].no_destination == no_destination)
		//			throw std::exception("Edge Delete Failed: Edge is not exist!");
		//	}
		//}
		//catch (const std::exception& e)
		//{
		//	std::cout << e.what() << std::endl;
		//	return;
		//}
		//int num_edge = num_edge;
		//if (!directed)
		//	num_edge /= 2;
		for (int i = 0; i < this->num_edge; ++i)
		{
			if (edge[i].no_source == no_origin && edge[i].no_destination == no_destination)
			{
				for (int p = i; p < this->num_edge; ++p)
					edge[p] = edge[p + 1];
				--this->num_edge;
				edge[this->num_edge - 1].no_source = NULL;
				edge[this->num_edge - 1].no_destination = NULL;
				edge[this->num_edge - 1].weight = NULL;

				if (this->directed == false)
					Graph_Edge_Delete(no_destination, no_origin);
				return;
			}
		}
	}
	void Graph_Show()
	{
		int num_edge = this->num_edge;
		if (!this->directed)
			num_edge /= 2;
		std::cout << (this->directed ? "有向图" : "无向图") << std::endl;
		std::cout << " [顶点数 : 边数] " << this->num_vertex << ':' << num_edge << std::endl;
		std::cout << "index [source:destination:weight]" << std::endl;
		for (int i = 0; i < num_edge; ++i)
			std::cout << i << " ["
			<< edge[i].no_source << ':'
			<< edge[i].no_destination << ':'
			<< edge[i].weight << ']' << std::endl;

	}
	void Graph_Traverse_DFS(int no_vertex_start) override
	{

	}
	void Graph_Traverse_BFS(int no_vertex_start) override
	{

	}
};









