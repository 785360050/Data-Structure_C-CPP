#include "../API/Graph_matrix.h"

static int Index(int x)
{
	return x - 1;
}

void Graph_Init
(
	Graph_matrix* graph, 
	int edgenum, 
	std::string name, 
	bool directed, 
	int edgeweight
)
{///初始化maxsize*maxsize的矩阵空间，边权值为edgeweigt，maxsize的顶点集合空间
	graph->directed = directed;
	graph->num_edge = 0;
	graph->num_vertex = edgenum;
	memset(graph->vertex, 0, sizeof(graph->vertex));//顶点集合置空
	memset(graph->edge, 0, sizeof(int) * maxsize * maxsize);
	char n = 'A';
	for (int i = 0; i < edgenum; i++)
	{
		graph->vertex[i].no = i;
		graph->vertex[i].name = n + 1;
		for (int column = 0; column < edgenum; column++)
			graph->edge[i][column] = edgeweight;
	}
}

static bool CheckExist_Edge(int weight)
{///	<0的边权值视为∞;
	if (weight < 0)
		return false;
	return true;
}
void Graph_Edge_Add(Graph_matrix* graph, int x, int y, int weight)
{
	try
	{
		if (Index(x) < 0 || Index(x) >= graph->num_vertex)
			throw 1;
		if (Index(y) < 0 || Index(y) >= graph->num_vertex)
			throw 2;
		if (CheckExist_Edge(graph->edge[x][y]))//边存在时候不添加
			throw 3;
	}
	catch (int a)
	{
		if (a == 1)
		{
			std::cout << "Index X is out of range!" << std::endl;
			return;
		}
		if (a == 2)
		{
			std::cout << "Index Y is out of range!" << std::endl;
			return;
		}
		if (a == 3)
		{
			std::cout << "Edge already Existed"<< std::endl;
			return;
		}
	}
	
	graph->edge[x][y] = weight;//添加从x到y的一条边
	if(graph->directed==true)//有向图对称
		graph->edge[y][x] = weight;
	graph->num_edge++;
}






