#pragma once

#include <iostream>
#include <queue>




//邻接矩阵
template <typename DataType>
class Graph_Matrix
{///边权值<0表示∞，=0表示不存在,无向图=1表示存在
private:
	struct Vertex_Matrix
	{//顶点结构体
	public:
		int no;//顶点编号
		//std::string name;//顶点名
		DataType* data;//顶点存放的数据元素
	public:
		//Vertex_Matrix()
	};
private:
	bool directed;//判断是否为有向图
	int num_vertex;//顶点总数;
	int num_edge;//边总数
	bool* state_visited;//访问状态
	Vertex_Matrix* vertex;//存放顶点的集合
	int** edge;//邻接矩阵

public:
	Graph_Matrix(int num_vertex,bool directed ):
		directed{directed},
		num_vertex{num_vertex},
		num_edge{0},
		vertex{new Vertex_Matrix[num_vertex]{} },
		state_visited{ new bool[num_vertex] {} }
	{///初始化num_vertex * num_vertex的矩阵空间，边权值默认为0，num_vertex个空间的顶点集合
		//int(*graph->edge)[num_vertex] = new int[num_vertex][num_vertex];
		edge = new int* [num_vertex];///分配指针数组空间
		for (int i = 0; i < num_vertex; i++)
		{///分配二位数组空间
			vertex[i].no = i;	///初始化顶点集合
			edge[i] = new int[num_vertex];
			for (int c = 0; c < num_vertex; c++)///初始化为全0
				edge[i][c] = 0;
		}
	}
	~Graph_Matrix()
	{
		for (int i = 0; i < num_vertex; i++)
			delete[] edge[i];
		delete edge;
		delete vertex;
		delete state_visited;
	}
private:
	int Index(int x) const
	{
		return x - 1;
	}
	void Visit(const Vertex_Matrix& vertex)
	{
		std::cout << vertex.no << ' ';
	}
	//重置访问状态，用于辅助遍历
	void Clear_VistiedState()
	{
		for (int i = 0; i < num_vertex; i++)
			state_visited[i] = 0;
	}
	bool CheckEdge_Infinit(int weight)
	{///	<0的边权值视为∞;
		return (weight <= 0) ? true : false;
	}
public:
	void Show()
	{
		using namespace std;
		string d = directed == true ? "有向图" : "无向图";
		cout << "顶点数：" << num_vertex << endl
			<< "边数：" << num_edge << endl
			<< d << '\t';
		for (int i = 0; i < num_vertex; i++)
			cout << i << '\t';
		cout << endl;
		for (int l = 0; l < num_vertex; l++)
		{
			cout << l << '\t';
			for (int c = 0; c < num_vertex; c++)
				cout << edge[l][c] << '\t';
			cout << endl;
		}
		std::cout << std::endl;
	}

	void Graph_Edge_Add(int no_origin, int no_destination, int weight)
	{
		try
		{
			if (no_origin < 0 || no_origin >= num_vertex)
				throw std::exception("Index Origin is out of range!");
			if (no_destination < 0 || no_destination > num_vertex)
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
		if (directed == false)//有向图对称
			edge[no_destination][no_origin] = weight;
		++num_edge;
	}

	//static bool History_Visited[maxsize];
	void Graph_Traverse_DFS(int no_vertex)
	{
		//Clear_VistiedState(graph);///BUG
		Visit(vertex[no_vertex]);
		state_visited[no_vertex] = true;//标记为已访问
		for (int i = 0; i <= num_vertex; i++)
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

	void Graph_Traverse_BFS(int no_vertex)
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
			for (int i = 0; i <= num_vertex; i++)
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





