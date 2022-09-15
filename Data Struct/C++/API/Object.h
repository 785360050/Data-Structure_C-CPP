#pragma once

class DataStructure
{
public:
private:
	//Liner_Structure;
	//Tree;
	//Graph;
};

class Liner_Structure :public DataStructure
{
	virtual void Init();
	virtual void Destroy();
	virtual void Clear();
	virtual void CheckEmpty();
	virtual void GetLength();
	virtual void LocateElement();
	virtual void PriorElement();
	virtual void NextElement();
	virtual void InsertElement();
	virtual void DeleteElement();
	virtual void Traverse();

};///precursor node

class Tree :public DataStructure
{

};

class Graph :public DataStructure
{

};




