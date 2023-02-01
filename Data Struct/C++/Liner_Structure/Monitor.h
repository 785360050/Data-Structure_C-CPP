//#pragma once
//
//#include <iostream>
//#include "../Monitor.h"
//#include "Liner_Structure_ADT.h"
//#include "Liner_List/Liner_List_Sequential/Liner_List_Sequential.h"
//
//template<typename DataType>
//class Liner_List_Monitor :public Monitor
//{
//private:
//	Liner_List<DataType>* list;
//public:
//	Liner_List_Monitor(const Liner_List<DataType>& list)
//		:list{ list } {};
//	virtual void List_Show(const std::string& string) = 0;
//};
//
//
//template<typename DataType>
//class Sequential_List_Monitor :public Liner_List_Monitor<DataType>
//{
//public:
//	Sequential_List_Monitor(const Sequential_List<DataType>& list) :
//		Liner_List_Monitor<DataType>(list) {};
//	//显示线性表所有信息
//	void List_Show(const std::string& string)
//	{
//		std::cout << string << std::endl
//			<< "[Length/Maxsize]:\n"
//			<< " [" << this->list->Show() << '/' << maxsize << ']' << std::endl
//			<< "Head->";
//		for (int index = 0; index < maxsize; index++)
//			std::cout << '[' << index << ':' << head[index] << "]-";
//		std::cout << "End\n";
//	}
//};
//
//template <typename DataType>
//void List_Show(const Sequential_List<DataType>& list,const std::string& string)
//{
//	std::cout << string << std::endl
//		<< "[Length/Maxsize]:\n"
//		<< " [" << list.List_GetLength() << '/' << list.List_Get_Maxsize() << ']' << std::endl
//		<< "Head->";
//	for (int index = 0; index < list.List_Get_Maxsize(); index++)
//		std::cout << '[' << index << ':' << list.head[index] << "]-";
//	std::cout << "End\n";
//}
//
//
//
//
