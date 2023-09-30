#pragma once

#include <iostream>
#include <queue>
#include <string>


#include "../Graph_Structure.h"
#include "Vertex_AdjacencyList.h"



//邻接表
template <typename DataType, typename ElementType = Vertex_AdjacencyList<DataType>>
struct Graph_AdjacencyList:public Graph_Structure<ElementType,DataType>
{
private:
	bool* state_visited;//访问状态

public:
	Graph_AdjacencyList(bool directed,int num_vertex)
		:Graph_Structure<ElementType, DataType>(directed, num_vertex),
		state_visited{ new bool[num_vertex](false)}
	{
		for (int i = 0; i < num_vertex; i++)
		{
			this->vertex[i].no = i;
			this->vertex[i].head_edge = nullptr;
		}
	}
	~Graph_AdjacencyList()
	{
		delete[] state_visited;
	}

private:
	void Reset_VistedState()
	{
		for (int i = 0; i < this->num_vertex; i++)
			state_visited[i] = false;
	}
	int Index(Vertex_AdjacencyList<DataType> vertex) const
	{
		return std::stoi(vertex.name);
	}
	Edge_AdjacencyList* Create_EdgeNode(int index, int weight)
	{
		return new Edge_AdjacencyList(index, weight);
	}

public:
	//添加图graph中，从x到y的边，权值为weight
	void Graph_Edge_Add(int no_origin, int no_destination, int weight) override
	{
		try
		{
			if (no_origin < 0 || no_origin >= this->num_vertex)
				throw std::runtime_error("Index no_origin is out of range!");
			if (no_destination < 0 || no_destination >= this->num_vertex)
				throw std::runtime_error("Index no_destination is out of range!");
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		Edge_AdjacencyList* node = Create_EdgeNode(no_destination, weight);
		node->next = this->vertex[no_origin].head_edge;///头插法插入新节点
		this->vertex[no_origin].head_edge = node;
		++this->num_edge;
		if (no_origin != no_destination && this->directed == false)
		{///无向图新建插入两个节点
			node = Create_EdgeNode(no_origin, weight);
			node->next = this->vertex[no_destination].head_edge;///头插法插入新节点
			this->vertex[no_destination].head_edge = node;
		}
	}
	void Graph_Edge_Delete(int no_origin, int no_destination) override
	{

	}
	void Graph_Traverse_DFS(int no_vertex) override
	{
		Edge_AdjacencyList* e;
		std::cout << this->vertex[no_vertex].no << ' ';
		state_visited[no_vertex] = true;
		e = this->vertex[no_vertex].head_edge;
		while (e)
		{
			if (state_visited[e->index_vertex] == false)
				Graph_Traverse_DFS(this->vertex[e->index_vertex].no);
			e = e->next;
		}

	}
	void Graph_Traverse_BFS(int no_vertex) override
	{

		Reset_VistedState();
	#define Standard_Queue
	#ifdef Standard_Queue
		std::queue<int> q;
		q.push(no_vertex);
		while (!q.empty())
		{

			int x = q.front();
			std::cout << x << ' ';
			q.pop();
			state_visited[x] = true;
			Edge_AdjacencyList* e = this->vertex[x].head_edge;
			while (e)
			{///下一层全入队
				if (state_visited[e->index_vertex] == false)
				{
					q.push(e->index_vertex);
					state_visited[e->index_vertex] = true;
				}
				e = e->next;
			}
		}
	#endif // Standard_Queue


	}

	void Graph_Show() override
	{
		using namespace std;
		string d = ((this->directed) == true) ? "有向图" : "无向图";
		cout << "顶点数：" << this->num_vertex << endl
			<< "边数：" << this->num_edge << endl
			<< d << endl;
		for (int i = 0; i < this->num_vertex; i++)
		{
			Vertex_AdjacencyList v = this->vertex[i];
			Edge_AdjacencyList* e = v.head_edge;
			cout << v.no << "->";
			while (e)
			{
				cout << this->vertex[e->index_vertex].no << "->";
				e = e->next;
			}
			cout << "NULL\n";
		}
	}

};

















