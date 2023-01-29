#pragma once







template <typename ElementType,typename DataType>
class Graph_Structure
{
protected:
	bool directed;			///否为有向图
	int num_edge;			///边总数
	int num_vertex;			///顶点总数
	ElementType* vertex;	///顶点集合

public:
	Graph_Structure(bool directed, int num_vertex)
		:directed(directed), num_vertex(num_vertex),num_edge(0), vertex(new ElementType[num_vertex]) {};
	virtual ~Graph_Structure()
	{
		delete[] vertex;
	}

public:
	//添加边(已存在时不添加)
	virtual void Graph_Edge_Add(int no_origin, int no_destination, int weight) = 0;
	virtual void Graph_Edge_Delete(int no_origin, int no_destination) = 0;
	//显示邻接矩阵
	virtual void Graph_Show() = 0;
	//广度优先遍历
	virtual void Graph_Traverse_DFS(int no_vertex_start) = 0;
	//深度优先遍历
	virtual void Graph_Traverse_BFS(int no_vertex_start) = 0;

};