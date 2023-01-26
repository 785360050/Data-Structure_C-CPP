#pragma once

#include <iostream>
#include <queue>





//邻接表
template <typename DataType>
struct Graph_AdjacencyList
{
private:
	struct Edge_AdjacencyList
	{///邻接表的边(弧)
		int index_vertex;//顶点的下标索引
		int weight;//边权重
		Edge_AdjacencyList* next;
	public:
		Edge_AdjacencyList(int index, int weight)
			:index_vertex{ index }, weight{ weight }, next{ nullptr } {};
	};

	struct Vertex_AdjacencyList
	{///顶点节点
		int no;//顶点在邻接表中的下标
		std::string name;//顶点名
		DataType* data;//数据元素
		Edge_AdjacencyList* head_edge;//存放边信息
	};

private:
	bool directed;
	int num_vertex;
	int num_edge;
	bool* state_visited;//访问状态
	Vertex_AdjacencyList* vertex;//顶点数组

public:
	Graph_AdjacencyList(int num_vertex, bool directed):
		directed{ directed },
		num_vertex{ num_vertex },
		num_edge{0},
		state_visited{ new bool[num_vertex](false)},
		vertex{ new Vertex_AdjacencyList[num_vertex] }
	{
		for (int i = 0; i < num_vertex; i++)
		{
			vertex[i].no = i;
			//graph->vertex[i].name = 'A' + i;
			vertex[i].head_edge = nullptr;
		}
	}
	~Graph_AdjacencyList()
	{
		delete[] state_visited;
		delete[] vertex;
	}

private:
	void Reset_VistedState()
	{
		for (int i = 0; i < num_vertex; i++)
			state_visited[i] = false;
	}
	int Index(Vertex_AdjacencyList vertex) const
	{
		return vertex.no;
	}
	Edge_AdjacencyList* Create_EdgeNode(int index, int weight)
	{
		return new Edge_AdjacencyList(index, weight);
	}

public:
	//添加图graph中，从x到y的边，权值为weight
	void Graph_Edge_Add(int no_origin, int no_destination, int weight)
	{
		try
		{
			if (no_origin < 0 || no_origin >= num_vertex)
				throw std::exception("Index no_origin is out of range!");
			if (no_destination < 0 || no_destination >= num_vertex)
				throw std::exception("Index no_destination is out of range!");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		Edge_AdjacencyList* node = Create_EdgeNode(no_destination, weight);
		node->next = vertex[no_origin].head_edge;///头插法插入新节点
		vertex[no_origin].head_edge = node;
		++num_edge;
		if (no_origin != no_destination && directed == false)
		{///无向图新建插入两个节点
			node = Create_EdgeNode(no_origin, weight);
			node->next = vertex[no_destination].head_edge;///头插法插入新节点
			vertex[no_destination].head_edge = node;
		}
	}
	void Graph_Traverse_DFS(int no_vertex)
	{
		Edge_AdjacencyList* e;
		std::cout << vertex[no_vertex].no << ' ';
		state_visited[no_vertex] = true;
		e = vertex[no_vertex].head_edge;
		while (e)
		{
			if (state_visited[e->index_vertex] == false)
				Graph_Traverse_DFS(vertex[e->index_vertex].no);
			e = e->next;
		}

	}
	void Graph_Traverse_BFS(int no_vertex)
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
			Edge_AdjacencyList* e = vertex[x].head_edge;
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

	void Graph_Show()
	{
		using namespace std;
		string d = directed == true ? "有向图" : "无向图";
		cout << "顶点数：" << num_vertex << endl
			<< "边数：" << num_edge << endl
			<< d << endl;
		for (int i = 0; i < num_vertex; i++)
		{
			Vertex_AdjacencyList v = vertex[i];
			Edge_AdjacencyList* e = v.head_edge;
			cout << v.no << "->";
			while (e)
			{
				cout << vertex[e->index_vertex].no << "->";
				e = e->next;
			}
			cout << "NULL\n";
		}
	}

};

















