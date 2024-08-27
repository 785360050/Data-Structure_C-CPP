#pragma once

#include "../../Painter/Painter.hpp"


#include "../../Data_Sturcture/C++/Linear_Structure/Linear_List/Link_List/Skip_List.hpp"

template<typename NodeType>
struct Serialized_Container
{
	std::vector<std::vector<NodeType*>> container;
	Serialized_Container(int level)
	{
		container.resize(level);
	}
};

namespace Adapter
{
	struct Skip_List:public Storage::Skip_List<int,0.5f>
	{
		std::vector<Node *> Get_Storage(){return this->header;}
		Node * Get_Tail(){return this->tail;}
		int Get_Current_Level(){return this->level;}
		std::map<size_t, Node *> Get_Search_Path(){return this->search_path;}

		template<typename NodeType>
		using Serialized_Container=std::vector<std::vector<NodeType*>>;
		Serialized_Container<Node> Get_Container()
		{
			Serialized_Container<Node> container(this->level);
			for (Node *node = header[0]; node; node = node->next[0])
			{
				for(int level{};level<this->level;++level)
				{
					if(level<=node->level)
					{
						container[level].push_back(node);
					}
					else
						container[level].push_back(nullptr);

				}
			}
			return container;
		}



	};
};


namespace Painter
{

	class Skip_List : public Painter::Painter
	{
		Adapter::Skip_List skip_list;
	public:
		Skip_List();
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	};
}

#include "../Structure.hpp"


namespace View
{
	class Skip_List : public Structure
	{
		Painter::Skip_List painter;

	public:
		Skip_List()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}

	public: // interactions
		// void Element_Push();
		// void Element_Pop();
		// void Element_Get_Top();
		// void Is_Empty();
		// void Get_Size();
		// void Clear()   ;

		void Config_Operations() override;
	};
}
