#pragma once


#include "Edge_AdjacencyList.hpp"

template <typename DataType>
struct Vertex_AdjacencyList
{///顶点节点
	int no;//顶点在邻接表中的下标
	std::string name;//顶点名
	DataType* data{};//数据元素
	Edge_AdjacencyList* head_edge;//存放边信息
};

#include <map>
namespace Refactor
{
	template <typename DataType>
	struct Vertex_AdjacencyList
	{ /// 顶点节点
	public:
		std::string name; // 顶点名
		DataType data{}; // 数据元素
		std::map<std::string,int> head_edge;  // 存放边信息 <vertex_name,weight>
	public:
		bool operator==(const Vertex_AdjacencyList &vertex) const { return this->name == vertex.name; }
	public:
		Vertex_AdjacencyList() = default;
		Vertex_AdjacencyList(std::string name, DataType data):name{name},data{data} {};

		void Edge_Add(const std::string &vertex_destination, int weight)
		{
			head_edge.insert({vertex_destination, weight});
		}
		void Edge_Delete(const std::string &vertex_destination)
		{
			head_edge.erase(vertex_destination);
		}
	};
}