#pragma once

#include <iostream>
#include "../Graph_Structure.hpp"
#include <set>
#include <queue>
#include <stack>

template <typename DataType>
class Graph_EdgeSet:public Graph_Structure<DataType,DataType>
{
private:
	struct Graph_EdgeSet_Edge
	{
		int no_source;
		int no_destination;
		int weight;
		bool operator==(const Graph_EdgeSet_Edge& other)
		{
			return this->no_source == other.no_source &&
				this->no_destination == other.no_destination &&
				this->weight == other.weight;
		}
	};
private:
	Graph_EdgeSet_Edge* edge;//存放边的数组(顺序表实现)
	std::pair<Graph_EdgeSet_Edge, bool>* visit_state;
public:
	Graph_EdgeSet(bool directed, int num_vertex)
		:Graph_Structure<DataType, DataType>(directed, num_vertex),
		edge(new Graph_EdgeSet_Edge[num_vertex * (num_vertex - 1)]),
		visit_state(nullptr)
		///n个顶点最多有n(n-1)条边
	{};
	//释放边集数组空间
	~Graph_EdgeSet()
	{
		delete[] edge;
	}

private:
	int Find(Graph_EdgeSet_Edge edge)
	{///返回边在数组中的下标
		for (int i = 0; i < this->num_edge; ++i)
		{
			if (visit_state[i].first == edge)
				return i;
		}
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
					throw std::runtime_error("Graph Edge Add Failed : Edge already exisited!");
			}
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		///边集数组的添加、删除边，不必满足有序，连续

		edge[this->num_edge].no_source = no_origin;
		edge[this->num_edge].no_destination = no_destination;
		edge[this->num_edge].weight = weight;
		++this->num_edge;
	}
	void Graph_Edge_Delete(int no_origin, int no_destination)
	{
		//try
		//{
		//	for (int i = 0; i < num_edge; ++i)
		//	{
		//		if (edge[i].no_source == no_origin && edge[i].no_destination == no_destination)
		//			throw std::runtime_error("Edge Delete Failed: Edge is not exist!");
		//	}
		//}
		//catch (const std::runtime_error& e)
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
		//int num_edge = this->num_edge;
		//if (!this->directed)
		//	num_edge /= 2;
		std::cout << (this->directed ? "有向图" : "无向图") << std::endl;
		std::cout << " [顶点数 : 边数] " << this->num_vertex << ':' << this->num_edge << std::endl;
		std::cout << "index [source:destination:weight]" << std::endl;
		for (int i = 0; i < this->num_edge; ++i)
			std::cout << i << " ["
			<< edge[i].no_source << ':'
			<< edge[i].no_destination << ':'
			<< edge[i].weight << ']' << std::endl;

	}
	//TODO Unfinished
	void Graph_Traverse_DFS(int no_vertex_start) override
	{

		std::stack<Graph_EdgeSet_Edge> stack;			///存放顶点dst
		std::set<int> visit_vertex;		///顶点访问记录
		visit_state ///边访问记录
			= new std::pair<Graph_EdgeSet_Edge, bool>[this->num_edge];

		for (int i = 0; i < this->num_edge; ++i)
		{///初始化记录
			visit_state[i].first = edge[i];
			visit_state[i].second = false;
			if (edge[i].no_source == no_vertex_start || edge[i].no_destination == no_vertex_start)
			{
				stack.push(edge[i]);
				visit_state[i].second = true;
			}
		}
		std::cout << no_vertex_start << ' ';
		visit_vertex.emplace(no_vertex_start);

		while (!stack.empty())
		{
			static bool reverse = false;
			Graph_EdgeSet_Edge edge = stack.top();
			auto src = !reverse ? edge.no_source : edge.no_destination;
			auto dst = !reverse ? edge.no_destination : edge.no_source;
			visit_state[Find(edge)].second = true;
			stack.pop();
			if (visit_vertex.find(dst) == visit_vertex.end())
			{///输出未访问过的顶点
				std::cout << dst << ' ';
				visit_vertex.emplace(dst);
			}
			for (int i = 0; i < this->num_edge; ++i)
			{///将输出顶点相关的边入栈
				if
				(
					visit_state[Find(this->edge[i])].second == false	///判断未访问过
					&&
					(this->edge[i].no_source == dst || this->edge[i].no_destination == dst)
				)
				{
					stack.push(this->edge[i]);
					visit_state[i].second = true;
					reverse == (this->edge[i].no_destination == dst) ? false : true;
				}
			}
		}
		delete[] visit_state;
	}

	
	//TODO Unfinished
	void Graph_Traverse_BFS(int no_vertex_start) override
	{
		std::queue<Graph_EdgeSet_Edge> queue;
		std::set<int> visit_vertex;
		visit_state = new std::pair<Graph_EdgeSet_Edge, bool>[this->num_edge];
		
		for (int i = 0; i < this->num_edge; ++i)
		{///初始化遍历队列
			visit_state[i].first = edge[i];
			visit_state[i].second = false;
			if (edge[i].no_source == no_vertex_start || edge[i].no_destination == no_vertex_start)
			{
				queue.push(edge[i]);
				visit_state[i].second = true;
			}
		}
		std::cout << no_vertex_start << ' ';
		visit_vertex.emplace(no_vertex_start);
		
		while (!queue.empty())
		{
			static bool reverse = false;
			Graph_EdgeSet_Edge edge = queue.front();
			auto src = !reverse ? edge.no_source : edge.no_destination;
			auto dst = !reverse ? edge.no_destination : edge.no_source;
			visit_state[Find(edge)].second = true;
			queue.pop();
			if (visit_vertex.find(dst) == visit_vertex.end())
			{
				std::cout << dst << ' ';
				visit_vertex.emplace(dst);
			}
			for (int i = 0; i < this->num_edge; ++i)
			{
				if
				(
					visit_state[Find(this->edge[i])].second == false	///判断未访问过
					&&
					(this->edge[i].no_source == dst || this->edge[i].no_destination == dst)
				)
				{
					queue.push(this->edge[i]);
					visit_state[i].second = true;
					reverse == (this->edge[i].no_destination == dst) ? false : true;
				}
			}
		}
		
		delete[] visit_state;
	}
};









