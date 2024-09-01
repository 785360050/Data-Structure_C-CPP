#pragma once

#include <iostream>
#include <optional>

#include "B_Node.hpp"

/// ————————————————————————————————
///  默认B树节点元素个数最少为 1/2阶数(向下取值)
///		最多为 阶数-1
/// ————————————————————————————————


/// ============================================================================================================
/// N阶B树节点在调整后最多有 N-1个元素，最少有 N/2个元素
/// 元素和孩子指针数组各多分配一个单位空间(N,N+1)，用于缓存被分割的元素
/// ============================================================================================================
template <typename KeyType, typename ElementType, int order=5>
struct B_Node
{
	static constexpr   int npos{order};    // key数组中非法的下标
	KeyType     key[order]{};       /// 存放关键字 ///order-1个元素用于存储，最后一个元素空间用于预存,如插入时预存分割元素
	int         size{};             /// 节点当前key个数
	ElementType element[order]{};   /// 存放元素
	B_Node      *child[order+1]{};  /// 存放指针索引
	B_Node      *parent{nullptr};   /// 父节点
public:
	B_Node()
	{
		static_assert(order > 2, "order must be greater than 2");
	}
	~B_Node()
	{
		// 不负责删除子树
	}

public:
	/// 索引指针下标 与 key下标 互转
	static constexpr int _Left_Child(int key_index) { return key_index; } // key下标转左孩子指针下标
	static constexpr int _Right_Child(int key_index) { return ++key_index; } // key下标转右孩子指针下标
	static constexpr int _Left_Child_Parent(int position) { return position; } // 左孩子下标转父节点key下标
	static constexpr int _Right_Child_Parent(int position) { return --position; } // 右孩子下标转父节点key下标

public:
	// 定位key在节点中的位置
	int Locate_Key(KeyType key)
	{ /// 返回元素值为key的下标位置，失败时返回第一个比key大的元素位置，找其左指针
		// static_assert(node);
		int i{};
		while (i < size)
		{
			if (this->key[i] >= key )
				return i;
			++i;
		}
		return i; // 返回第一个比key大的元素位置，用于后续向下层节点查找
	}

	// 以mid为下标，将mid后所有元素移动到新节点
	// 原有位置置为NULL
	// 重置分割位置元素值，并返回该元素值
	std::pair<KeyType, B_Node *> Split(int mid)
	{
		B_Node *sp = new B_Node; /// 新建同层分裂节点

		// int guard = node->size == order ? node->size+1 : node->size;
		for (int i = mid + 1, j = 0; i < size; i++, j++)
		{ /// 将分割元素的后面所有元素移动到新节点
			sp->key[j] = this->key[i];
			sp->child[j] = this->child[i];
			/// 清空原位置
			key[i] = KeyType{};
			child[i] = KeyType{};
		}
		sp->size = this->size - mid - 1; /// 一半分裂出去，非奇数order时可能有bug
		if (this->size == order)
		{ /// 补丁：用于添加到满父节点后，最后一个索引指针不移动给新节点
			sp->child[sp->size] = this->child[size];
			this->child[size] = NULL;
		}
		sp->parent = this->parent;

		for (int i = 0; i <= sp->size; i++)
		{ /// 将原来的指针索引交给分裂的节点(更新分裂节点的下层parent指针)
			if (sp->child[i])
				sp->child[i]->parent = sp;
		}

		/// 将分割元素返回
		KeyType element = key[mid];
		key[mid] = KeyType{};
		size = mid;

		return {element, sp};
	}

	// /// 插入节点
	// void Insert_Element(int pos,const KeyType& key,const ElementType& element)
	// { 
	// 	if (node->size != branch-1)
	// 	{ /// 插入到末尾元素位置不后移，直接覆盖
	// 		for (int i{node.size-1}; i >= pos; --i)
	// 		{ /// 顺序表元素后移插入
	// 			node->key[i] = node->key[i - 1];
	// 			node->child[i + 1] = node->child[i];
	// 		}
	// 	}
	// 	node->key[pos] = key;
	// 	node->child[pos] = child;
	// 	if (child)
	// 		child->parent = node;
	// 	++node->size;
	// }
};


/// @brief
/// @tparam KeyType 排序用的key类型
/// @tparam ElementType 元素类型
/// @tparam order 阶数
/// @tparam NodeType 节点类型
template <typename KeyType, typename ElementType, int order, typename NodeType = B_Node<KeyType, bool, order>>
struct Tree_Advanced_B
{ /// 回溯法实现插入删除

public:
	NodeType *root{nullptr}; /// 根节点
	int count{};			 // 元素数量

public:
	~Tree_Advanced_B()
	{
		std::cout << "删除B树节点个数:" << count << std::endl;
		if (!root)
			return;
		for (int i = 0; i < order; i++)
		{
			delete root->child[i];
			--count;
		}
	}

private:
	// B树调整
	void Restore(NodeType *node)
	{
		NodeType *parent, *brother_left, *brother_right;
		parent = node->parent;
		if (parent)
		{					/// 父节点存在
			int i_index; /// 指向调整节点的索引指针
			for (i_index = 0; i_index <= parent->size; ++i_index)
			{ /// 遍历父节点中的索引指针,以找到左右兄弟节点
				if (parent->child[i_index] == node)
					break;
			}
			/// parent->child[i_index] 指向当前节点
			brother_left = i_index > 0 ? parent->child[i_index - 1] : nullptr;
			brother_right = i_index <= parent->size ? parent->child[i_index + 1] : nullptr;

			if (brother_left && brother_left->size > order / 2)
			{ /// 左兄弟有多余元素，则从左兄弟借元素
				/// 从左兄弟借元素 = 从父节点借小元素(逻辑前驱) + 父节点从左节点借最大的元素(逻辑前驱)
				for (int i = node->size; i > 0; --i)
				{ /// 后移元素，留出第一个位置，存放父节点中借的元素
					node->key[i] = node->key[i - 1];
					node->child[i] = node->child[i - 1];
				}
				/// 存放父节点中借的元素
				int parent_key_index = NodeType::_Right_Child_Parent(i_index);
				node->key[0] = parent->key[parent_key_index];

				/// 父节点从左兄弟借最后一个元素
				parent->key[parent_key_index] = brother_left->key[brother_left->size - 1];

				brother_left->key[brother_left->size - 1]=KeyType{};
				/// 调整长度
				--brother_left->size;
				++node->size;
			}
			else if (brother_right && brother_right->size > order / 2)
			{ /// 右兄弟有多余元素，则从右兄弟借
				/// 从右兄弟借元素 = 从父节点借大元素(逻辑后继) + 父节点从右兄弟借最小元素(逻辑后继)

				/// 先把父元素移下来，放节点末尾
				node->key[node->size] = parent->key[i_index]; /// index_right_to_position(i_index)+1
				if (node->child[node->size])
					node->child[node->size]->parent = node;

				/// 再把右兄弟的第一个元素移上来(逻辑后继)
				parent->key[i_index] = brother_right->key[0];

				for (int i = 0; i < brother_right->size; ++i)
				{ /// 右兄弟被抽走一个元素，前移一格
					brother_right->key[i] = brother_right->key[i + 1];
					brother_right->child[i] = brother_right->child[i + 1];
				}
				brother_right->child[brother_right->size + 1] = nullptr;
				/// 调整长度
				++node->size;
				--brother_right->size;
			}
			else
			{ /// 左右兄弟都无法借元素，只能合并
				if (brother_left)
				{ /// 调整节点与左兄弟合并
					/// 合并 = 从父节点移动分割元素到左兄弟 + 当前节点元素都移到左节点

					int position_smaller_element = NodeType::_Right_Child_Parent(i_index);

					/// 从父节点移下分割元素
					brother_left->key[brother_left->size] = parent->key[position_smaller_element];
					++brother_left->size;

					for (int i = position_smaller_element; i < parent->size; ++i)
					{ /// 左移动父节点元素，补齐空位
						parent->key[i] = parent->key[i + 1];
						parent->child[i + 1] = parent->child[i + 2];
					}
					--parent->size;
					parent->key[parent->size] = KeyType{};
					parent->child[parent->size + 1] = nullptr;

					for (int i = 0; i < node->size; ++i)
					{ /// 把调整节点的元素和索引指针都移动给左兄弟
						brother_left->key[brother_left->size + i] = node->key[i];
						brother_left->child[brother_left->size + i + 1] = node->child[i + 1];
						if (brother_left->child[brother_left->size + i + 1])
							brother_left->child[brother_left->size + i + 1]->parent = brother_left;
					} /// 补齐缺少移动的第一个索引
					brother_left->child[brother_left->size] = node->child[0];
					if (brother_left->child[brother_left->size])
						brother_left->child[brother_left->size]->parent = brother_left;
					brother_left->size += node->size;
					delete node;

					if (root == parent)
					{ /// 如果此时父节点为根，则当父节点没有关键字时才调整
						if (parent->size == 0)
						{
							for (int i = 0; i <= parent->size; ++i)
							{
								if (parent->child[i])
								{
									root = parent->child[i];
									root->parent = nullptr;
									delete parent;
									break;
								}
							}
						}
					}
					else
					{ /// 如果父节点不为根，则需要判断是否需要重新调整
						if (parent->size < order / 2)
							Restore(parent);
					}
				}
				else if (brother_right)
				{ /// 调整节点与右兄弟合并
					/// 合并 = 从父节点移动分割元素(逻辑后继)到左兄弟 + 右兄弟元素都移到调整节点

					int position_bigger_element = NodeType::_Left_Child_Parent(i_index);

					/// 从父节点移下分割元素
					node->key[node->size] = parent->key[position_bigger_element];
					++node->size;

					for (int i = position_bigger_element; i < parent->size; ++i)
					{ /// 左移动父节点元素，补齐空位
						parent->key[i] = parent->key[i + 1];
						parent->child[i + 1] = parent->child[i + 2];
					}
					parent->child[parent->size + 1] = nullptr;
					parent->key[parent->size] = KeyType{};
					--parent->size;

					for (int i = 0; i < brother_right->size; ++i)
					{ /// 把右兄弟元素和索引指针移到调整节点
						node->key[node->size + i] = brother_right->key[i];
						node->child[node->size + i + 1] = brother_right->child[i + 1];
						if (node->child[node->size + i + 1])
							node->child[node->size + i + 1]->parent = node;
					} /// 补齐缺少移动的第一个索引
					node->child[node->size + 1] = brother_right->child[0];
					if (node->child[node->size + 1])
						node->child[node->size + 1]->parent = node;
					node->size += brother_right->size;
					delete brother_right;

					if (root == parent)
					{ /// 如果此时父节点为根，则当父节点没有关键字时才调整
						if (parent->size == 0)
						{
							for (int i = 0; i <= parent->size; ++i)
							{
								if (parent->child[i])
								{
									root = parent->child[i];
									delete parent;
									root->parent = nullptr;
									break;
								}
							}
						}
					}
					else
					{ /// 如果父节点不为根，则需要判断是否需要重新调整
						if (parent->size < order / 2)
							Restore(parent);
					}
				}
				else
				{ /// 左右兄弟都不存在，合并当前元素到根节点
					for (int i = 0; i > node->size; ++i)
					{
						if (node->child[i])
						{
							root = node->child[i];
							root->parent = nullptr;
							break;
						}
					}
				}
			}
		}
		else
		{ /// 父节点不存在，即为根节点，合并并减少一层树的高度
			NodeType *del;
			for (int i = 0; i <= node->size; ++i)
				if (node->child[i + 1])
				{
					del = node;
					node = node->child[i + 1];
					del->child[i] = nullptr;
					delete del;
					break;
				}
			root = node;
			root->parent = nullptr;
		}
	}
	void Delete(NodeType *node, int position)
	{								   /// 删除node节点中下标为Position的元素
		if (node->child[position + 1]) /// 若元素存在右指针，则非叶节点
		{							   /// 删除非叶节点
			/// 用逻辑后继节点代替(父节点元素代替，父节点用右子树第一个代替)
			NodeType *leaf = node;
			if (leaf)
			{ /// 右孩子的第一个叶子元素(循环定位)
				leaf = leaf->child[position + 1];
				while (leaf->child[0])
					leaf = leaf->child[0];
				node->key[position] = leaf->key[0];
			}
			Delete(leaf, 0); /// 删除逻辑后继
		}
		else
		{ /// 删除叶节点

			for (int i = position; i < node->size; ++i)
			{									 /// 直接删除
				node->key[i] = node->key[i + 1]; /// 因为key末尾预留，且插入时置为0，所以可以直接从后覆盖前，且不考虑越界
				node->child[i] = node->child[i + 1];
			}
			--node->size;
			if (node->size < order / 2) /// 阈值可自定义
				Restore(node);		/// 调整B树
		}
	}

public:
	NodeType *Create_Node() { return new NodeType; }

	struct Result
	{
		bool tag;		 /// 查找是否成功
		int pos;		 /// 查到的key元素下标索引(parent_node->key[pos])	失败时为NULL
		NodeType *index; /// 查到的key所在节点的指针索引	失败时为父节点
	};

	// 查找
	Result B_Tree_Search(KeyType key)
	{
		NodeType *precursor = nullptr; /// 父节点索引
		NodeType *current = root;	   /// 当前节点索引
		int pos = 0;				   /// 节点中的位置下标
		bool tag{false};			   /// 标记查找状态
		while (current && !tag)
		{ /// 搜索当前节点是否存在目标key
			pos = current->Locate_Key(key);
			if (pos < current->size && current->key[pos] == key)
				/// 查找成功
				tag = true;
			else
			{ /// 查找失败
				precursor = current;
				current = current->child[pos]; /// 向下层节点找key(大值的左指针)
			}
		}

		Result result; /// 生成结果
		if (tag)
		{ /// 查找成功(树中存在值为key的节点元素)
			result.tag = true;
			result.index = current;
			result.pos = pos;
		}
		else
		{
			result.tag = false;
			result.index = precursor;
			result.pos = pos;
		}
		return result;
	}

	std::optional<ElementType &> operator[](KeyType key)
	{
		if (!root)
			return std::nullopt;

		NodeType node = root;
		int index_key = node.Locate_Key(key);
		while (node && node.key[index_key] != key)
		{
			if (index_key == NodeType::npos)
			{
				if (!node.child)
					return std::nullopt;
				else
				{
					int index_child = (key > node.key[index_key] ? NodeType::_Right_Child(index_key) : NodeType::_Left_Child(index_key));
					node = node.child[index_child];
					continue;
				}
			}
			else
				return node.element[index_key];
		}
	}

	// 插入元素
	void Element_Insert(KeyType key, ElementType element = ElementType{})
	{
		/// 定位待插入节点及下标位置
		Result res = B_Tree_Search(key);
		if (res.tag == true)
			// if (res != std::nullopt)
			throw std::logic_error("Insert Failed: key exsisted");

		NodeType *node = res.index; /// 元素插入的节点，此处因为Result搜索失败，所以返回查找节点的父节点声明为parent(即插入节点)
		int pos_node = res.pos;	/// 元素插入的节点的下标索引pos位置插入元素key(pos=第一个大元素的下标位置)
		NodeType *child = nullptr;	/// 分裂的新节点

		bool loop = true;		  /// 控制插入的while大循环,完成后控制退出
		bool root_new = false;	  /// 控制分裂时，是否需要新建上层节点
		KeyType key_insert = key; /// 插入的key

		if (node) /// 插入目标节点存在时
		{
			while (!root_new)
			{	  /// key插入当前节点
				// node.Insert_Element(pos_node, key_insert, element);
				{ /// 插入节点
				  
				  	/// 插入到末尾元素位置不后移，直接覆盖
					for (int i{node->size-1}; i >= pos_node; --i)
					{ /// 顺序表元素后移插入
						node->key[i] = node->key[i - 1];
						node->child[i + 1] = node->child[i];
					}
					node->key[pos_node] = key_insert;
					node->child[pos_node+1] = child;
					if (child)
						child->parent = node;
					++node->size;
				}
				/// 插入后判断是否分裂
				if (node->size < order)
					break;
				else
				{								/// 节点满，分裂
					int pos_mid = order / 2; /// 分裂为上层节点
					/// 分割满节点为两个节点，返回待插入的key
					std::pair<KeyType, NodeType *> pair = node->Split(pos_mid);
					key_insert = pair.first;
					child = pair.second;
					if (node->parent)
					{ /// 上层节点存在时，key插入到上层节点parent中
						node = node->parent;
						pos_node=node->Locate_Key(key_insert);
					}
					else
						root_new = true; /// 需要新建上层节点
				}
			}
		}
		else /// 插入目标节点不存在时(即空树时)
		{
			root = Create_Node(); /// 创建上层节点
			root->key[0] = key;
			++root->size;
		}
		if (root_new)
		{
			NodeType *root = Create_Node(); /// 创建上层节点
			this->root = root;
			root->key[0] = key_insert;
			root->child[0] = node;
			root->child[1] = child;
			node->parent = root;
			child->parent = root;
			root->size++;
		}
		count++;
	}

	// 删除值为key的元素
	void Element_Delete(KeyType key)
	{
		Result result = B_Tree_Search(key);
		if (result.tag)
		{ /// result查找key成功时，返回key所在的节点和下标
			Delete(result.index, result.pos);
			--count;
		}
		else
			throw std::logic_error("Delete Failed: key not exsisted");
	}
	// 中序遍历
	void Traverse_Inorder(NodeType *node)
	{
		if (node)
		{
			for (int i = 0; i < node->size; ++i)
			{
				if (node->child[i]) /// 感觉多余
					Traverse_Inorder(node->child[i]);
				/// ——————————————————————————————————递归分割
				std::cout << node->key[i] << ' ';
			} /// 补齐缺少的最后一个索引
			Traverse_Inorder(node->child[node->size]);
		}
	}

	/// 中序遍历并显示信息
	void B_Tree_Show(std::string string)
	{
		std::cout << string << std::endl;
		Traverse_Inorder(root);
		std::cout << std::endl;
	}
};
