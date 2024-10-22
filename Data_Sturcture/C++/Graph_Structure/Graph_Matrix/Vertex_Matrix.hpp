#pragma once

#include <string>

template <typename DataType>
struct Vertex_Matrix
{//顶点结构体
public:
	//int no;//顶点编号
	std::string name;		///顶点名
	DataType data{};			///顶点存放的数据元素
public:
	Vertex_Matrix()=default;
	Vertex_Matrix(std::string name, DataType data)
		: name(name), data(data) {};
};



