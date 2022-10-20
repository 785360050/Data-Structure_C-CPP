#pragma once

#include <iostream>
#include <stack>
#include "../API/Graph_AdjacencyList.h"

static void show(const int* indegree)
{
	for (int i = 0; i < 6; i++)
		std::cout << indegree[i] << ' ';
	std::cout << std::endl;
}

void TopoSort(AdjacencyList* graph)
{
#define Standard_Stack
#ifdef Standard_Stack
	std::stack<int> s;	//缓存入度为0的点，用队列也行
	int* indegree = new int[graph->num_vertex];//记录入度
	memset(indegree, 0, sizeof(int) * graph->num_vertex);
	for (int i = 0; i < graph->num_vertex; i++)
	{//初始化入度表
		if (graph->vertex[i].head_edge)
		{
			AdjacencyList_Edge* temp = graph->vertex[i].head_edge;
			while (temp)
			{///跟新一个顶点的入度总和
				indegree[temp->index_vertex]++;
				temp = temp->next;
			}
		}
	}
	
	for (int i = 0; i < graph->num_vertex; i++)
		if (indegree[i] == 0)///遍历入度表，将入度为0的顶点入栈缓存
			s.push(i);
	
	int no;
	int count=0;///统计拓扑排序结果顶点数，不等于图顶点数时表明有环
	while (!s.empty())
	{
		no = s.top();
		s.pop();
		std::cout << no << ' ';///以输出方式显示拓扑排序结果
		count++;
		AdjacencyList_Edge* temp = graph->vertex[no].head_edge;
		while (temp)
		{///遍历已访问的顶点的邻接表，出现的顶点入度-1，更新后后若为0，则入栈缓存
			indegree[temp->index_vertex]--;
			if (indegree[temp->index_vertex] == 0)
				s.push(temp->index_vertex);
			temp = temp->next;
		}
	}
	delete[] indegree;
	if (count == graph->num_vertex)
		std::cout << "Topo Sort Succeeded" << std::endl;
	else
		std::cout << "Topo Sort Faild: Cycle exisit" << std::endl;

#endif // Standard_Stack

}





