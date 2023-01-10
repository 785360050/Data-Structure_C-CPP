#pragma once

#include <iostream>

template <typename DataType>
class Base
{
public:
	DataType x;
	DataType y;
	Base() :x{ 0 }, y{ 0 } {};
	Base(int x, int y) :x{ x }, y{ y } {};
};


template <typename DataType>
class Derive :public Base<DataType>
{
public:
	//Derive() :Base<DataType>();
	//Derive(int x, int y) :Base<DataType>(x, y);
	Derive()
	{
		this->x=0;
		this->y=0;
	}
	Derive(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

void main()
{
	Derive<int> d(1, 2);
	std::cout << d.x << ' ' << d.y << std::endl;
	Base<int> b(3, 4);
	std::cout << b.x << ' ' << b.y << std::endl;
}