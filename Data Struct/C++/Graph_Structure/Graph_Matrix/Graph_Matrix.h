#pragma once

#include <iostream>
#include <queue>
#include <vector>


#include "../Graph_Structure.h"
#include "Vertex_Matrix.h"

//template <typename DataType>
//struct  Graph_Matrix<DataType>::Vertex_Matrix;






//邻接矩阵
template <typename DataType, typename ElementType = Vertex_Matrix<DataType>>
class Graph_Matrix
	:public Graph_Structure<ElementType,DataType>
{///边权值<0表示∞，=0表示不存在,无向图=1表示存在
private:
	bool* state_visited;//访问状态
	Vertex_Matrix<DataType>* vertex;//存放顶点的集合
	int** edge;//邻接矩阵

public:
	Graph_Matrix(bool directed,int num_vertex):
		Graph_Structure<Vertex_Matrix<DataType>,DataType>(directed,num_vertex),
		state_visited{ new bool[num_vertex] {} },
		vertex{new Vertex_Matrix<DataType>[num_vertex]}
	{///初始化num_vertex * num_vertex的矩阵空间，边权值默认为0，num_vertex个空间的顶点集合
		//int(*graph->edge)[num_vertex] = new int[num_vertex][num_vertex];
		edge = new int* [num_vertex];///分配指针数组空间
		for (int i = 0; i < num_vertex; i++)
		{///分配二位数组空间
			vertex[i].name = std::to_string(i);	///初始化顶点集合
			edge[i] = new int[num_vertex] {};
		}
	}
	~Graph_Matrix()
	{
		for (int i = 0; i < this->num_vertex; i++)
			delete[] edge[i];
		delete edge;
		delete state_visited;
	}
private:
	int Index(int x) const
	{
		return x - 1;
	}
	void Visit(const Vertex_Matrix<DataType>& vertex)
	{
		std::cout << vertex.name << ' ';
	}
	//重置访问状态，用于辅助遍历
	void Clear_VistiedState()
	{
		for (int i = 0; i < this->num_vertex; i++)
			state_visited[i] = 0;
	}
	bool CheckEdge_Infinit(int weight)
	{///	<0的边权值视为∞;
		return (weight <= 0) ? true : false;
	}
public:
	void Graph_Show() override
	{
		std::string d = this->directed == true ? "有向图" : "无向图";
		std::cout << "顶点数：" << this->num_vertex << std::endl
			<< "边数：" << this->num_edge << std::endl
			<< d << '\t';
		for (int i = 0; i < this->num_vertex; i++)
			std::cout << i << '\t';
		std::cout << std::endl;
		for (int l = 0; l < this->num_vertex; l++)
		{
			std::cout << l << '\t';
			for (int c = 0; c < this->num_vertex; c++)
				std::cout << edge[l][c] << '\t';
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Graph_Edge_Add(int no_origin, int no_destination, int weight) override
	{
		try
		{
			if (no_origin < 0 || no_origin >= this->num_vertex)
				throw std::exception("Index Origin is out of range!");
			if (no_destination < 0 || no_destination > this->num_vertex)
				throw std::exception("Index Destination is out of range!");
			if (!CheckEdge_Infinit(edge[no_origin][no_destination]))//边存在时候不添加
				throw std::exception("Edge already Existed");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}

		edge[no_origin][no_destination] = weight;//添加从x到y的一条边
		if (this->directed == false)//无向图对称
			edge[no_destination][no_origin] = weight;
		++this->num_edge;
	}
	void Graph_Edge_Delete(int no_origin, int no_destination)
	{
		try
		{
			if (no_origin < 0 || no_origin >= this->num_vertex)
				throw std::exception("Index Origin is out of range!");
			if (no_destination < 0 || no_destination > this->num_vertex)
				throw std::exception("Index Destination is out of range!");
			if (CheckEdge_Infinit(edge[no_origin][no_destination]))//边存在时候不添加
				throw std::exception("Edge is not Existed");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}

		edge[no_origin][no_destination] = 0;//添加从x到y的一条边
		if (this->directed == false)//无向图对称
			edge[no_destination][no_origin] = 0;
		--this->num_edge;
	}
	//static bool History_Visited[maxsize];
	void Graph_Traverse_DFS(int no_vertex) override
	{
		//Clear_VistiedState(graph);///BUG
		Visit(vertex[no_vertex]);
		state_visited[no_vertex] = true;//标记为已访问
		for (int i = 0; i <= this->num_vertex; i++)
		{
			if
			(
				!CheckEdge_Infinit(edge[no_vertex][i]) ///判断存在边
				&&
				!state_visited[i]	///判断未访问
			)
				Graph_Traverse_DFS(i);
		}

	}

	void Graph_Traverse_BFS(int no_vertex) override
	{
		Clear_VistiedState();
	#define Standard_Queue
	#ifdef Standard_Queue
		std::queue<int> q;
		int front;
		q.push(no_vertex);
		while (!q.empty())
		{
			std::cout << q.front() << ' ';
			state_visited[q.front()] = true;
			front = q.front();
			q.pop();
			for (int i = 0; i <= this->num_vertex; i++)
			{
				if (!CheckEdge_Infinit(edge[front][i]) && !state_visited[i])
				{
					q.push(i);
					state_visited[i] = true;
				}
			}
		}
	#endif // Standard_Queue


	}

};





