#pragma once

#include <iostream>
#include <queue>
#include <string>


#include "../Graph_Structure.hpp"
#include "Vertex_AdjacencyList.hpp"



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


#include <map>
namespace Storage
{
	//邻接表
	template <typename DataType, bool directed, typename VertexType = Refactor::Vertex_AdjacencyList<DataType>>
	struct Graph_AdjacencyList : Logic::Graph_Structure<DataType,VertexType, directed>
	{
	private:
		// bool *state_visited{new bool[num_vertex](false)}; // 访问状态
		std::map<std::string, VertexType> vertex_set; /// 顶点集合 <name,vertex>

	public:
		Graph_AdjacencyList() : Logic::Graph_Structure<DataType,VertexType, directed>() {}
		~Graph_AdjacencyList() {}

	// private:
	// 	void Reset_VistedState()
	// 	{
	// 		for (int i = 0; i < this->num_vertex; i++)
	// 			state_visited[i] = false;
	// 	}

	public:
		// 添加图graph中，从x到y的边，权值为weight
		void Vertex_Add(const std::string& name, DataType data) override
		{
			// vertex_set.insert({vertex.name, std::forward<VertexType>(vertex)});
			vertex_set.insert({name,{name, data}});
			++this->num_vertex;
		}
		void Vertex_Delete(const std::string &name) override
		{
			vertex_set.erase(name);
			--this->num_vertex;
		}
		void Edge_Add(const std::string &vertex_origin, const std::string &vertex_destination, int weight) override
		{
			if (!vertex_set.contains(vertex_origin))
				throw std::runtime_error("Vertex_origin not in the graph!");
			if (!vertex_set.contains(vertex_destination))
				throw std::runtime_error("Vertex_origin not in the graph!");

			// this->vertex[vertex_origin.name].Add_Edge(no_destination, weight);
			vertex_set[vertex_origin].Edge_Add(vertex_destination, weight);
			++this->num_edge;
			if (vertex_origin != vertex_destination && directed == false) /// 无向图新建插入两个节点
				vertex_set[vertex_destination].Edge_Add(vertex_origin, weight);
		}
		void Edge_Delete(const std::string &vertex_origin, const std::string &vertex_destination) override
		{
			if (!vertex_set.contains(vertex_origin))
				throw std::runtime_error("Vertex_origin is not in the graph!");
			if (!vertex_set.contains(vertex_destination))
				throw std::runtime_error("vertex_destination is not in the graph!");

			vertex_set[vertex_origin].Edge_Delete(vertex_destination);
			--this->num_edge;
			if (vertex_origin != vertex_destination && directed == false) /// 无向图新建插入两个节点
				vertex_set[vertex_destination].Edge_Delete(vertex_origin);
		}

		// void Traverse_DFS(int no_vertex) override
		// {
		// 	Edge_AdjacencyList* e;
		// 	std::cout << this->vertex[no_vertex].no << ' ';
		// 	state_visited[no_vertex] = true;
		// 	e = this->vertex[no_vertex].head_edge;
		// 	while (e)
		// 	{
		// 		if (state_visited[e->index_vertex] == false)
		// 			Graph_Traverse_DFS(this->vertex[e->index_vertex].no);
		// 		e = e->next;
		// 	}

		// }
		// void Traverse_BFS(int no_vertex) override
		// {

		// 	Reset_VistedState();
		// 	std::queue<int> q;
		// 	q.push(no_vertex);
		// 	while (!q.empty())
		// 	{

		// 		int x = q.front();
		// 		std::cout << x << ' ';
		// 		q.pop();
		// 		state_visited[x] = true;
		// 		Edge_AdjacencyList* e = this->vertex[x].head_edge;
		// 		while (e)
		// 		{///下一层全入队
		// 			if (state_visited[e->index_vertex] == false)
		// 			{
		// 				q.push(e->index_vertex);
		// 				state_visited[e->index_vertex] = true;
		// 			}
		// 			e = e->next;
		// 		}
		// 	}

		// }

		void Show() override
		{
			using namespace std;
			string d = (directed == true) ? "有向图" : "无向图";
			cout << "顶点数：" << this->num_vertex << endl
				 << "边数：" << this->num_edge << endl
				 << d << endl;
			// for (int i = 0; i < this->num_vertex; i++)
			// {
			// 	VertexType v = vertex_set[std::to_string(i)];
			// 	// Refactor::Vertex_AdjacencyList<DataType>::Edge e = v.head_edge;
			// 	// cout << v.no << "->";
			// 	// while (!e.empty())
			// 	// {
			// 	// 	cout << vertex_set[e.index_vertex].no << "->";
			// 	// 	e = e.next;
			// 	// }
			// 	cout << "NULL\n";
			// }
			
			for (const auto& vertex: vertex_set) 
			{
				cout << '[' << vertex.first<<']' << "->";
				for (const auto& edge: vertex.second.head_edge)
					cout << edge.first << "->";
				cout << "NULL\n";
			}
		}

};
}














