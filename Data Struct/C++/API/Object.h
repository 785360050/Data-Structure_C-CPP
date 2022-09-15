#pragma once

class DataStructure
{
public:
private:
	Liner_Structure;
	Tree;
	Graph;
};

class Liner_Structure :public DataStructure
{
	void Init();
	void Destroy();
	void Clear();
	void CheckEmpty();
	void GetLength();
	void LocateElement();
	void PriorElement();
	void NextElement();
	void InsertElement();
	void DeleteElement();
	void Traverse();

};///precursor node

class Tree :public DataStructure
{

};

class Graph :public DataStructure
{

};




