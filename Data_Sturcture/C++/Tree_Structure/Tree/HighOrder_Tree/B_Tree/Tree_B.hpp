#pragma once

#include <iostream>
#include <optional>

#include "B_Node.hpp"

/// ————————————————————————————————
///  默认B树节点元素个数最少为 1/2阶数(向下取值)
///		最多为 阶数-1
/// ————————————————————————————————

template 
<
	typename KeyType,								 // 排序用的key类型
	typename ElementType,								 // 元素类型
	size_t order									 // 阶数
	// typename NodeType = B_Node<KeyType, bool, order> // 节点类型
>
struct Tree_Advanced_B
{ /// 回溯法实现插入删除
public:
protected:
	struct B_Node
	{
		const size_t npos{order};//key数组中非法的下标
		KeyType storage_key[order]{}; /// 存放关键字 ///order-1个元素用于存储，最后一个元素空间用于预存,如插入时预存分割元素
		size_t size{};				  /// 节点当前key个数
		ElementType storage_element[order]{}; /// 存放元素
		B_Node *storage_child[order]{}; /// 存放指针索引
		B_Node *parent{nullptr};	  /// 父节点
	public:
		B_Node(int order)
		{
			static_assert(order > 2, "order must be greater than 2");
		}

	public:
		/// 索引指针下标 与 key下标 互转
		constexpr size_t _Left_Child(size_t key_index) { return key_index; }
		constexpr size_t _Right_Child(size_t key_index) { return ++key_index; }
		constexpr size_t _Left_Child_Parent(size_t position) { return position; }
		constexpr size_t _Right_Child_Parent(size_t position) { return --position; }

	public:
		// 定位key在节点中的位置
		size_t _Locate_Key(KeyType key)
		{ /// 返回元素值为key的下标位置，失败时返回第一个比key大的元素位置，找其左指针
			static_assert(node);
			for (size_t i = 0; i < order; i++)
				if (storage_key[i] == key)
					return i;
			return npos;
		}

		// 以mid为下标，将mid后所有元素移动到新节点
		// 原有位置置为NULL
		// 重置分割位置元素值，并返回该元素值
		std::pair<KeyType, NodeType *> Split(size_t mid)
		{
			NodeType *sp = new NodeType; /// 新建同层分裂节点

			// size_t guard = node->length == node->order ? node->length+1 : node->length;
			for (size_t i = mid + 1, j = 0; i < node->size; i++, j++)
			{ /// 将分割元素的后面所有元素移动到新节点
				sp->key[j] = node->key[i];
				sp->index[j] = node->index[i];
				/// 清空原位置
				node->key[i] = KeyType{};
				node->index[i] = KeyType{};
			}
			sp->size = size - mid - 1; /// 一半分裂出去，非奇数node->order时可能有bug
			if (node->length == node->order)
			{ /// 补丁：用于添加到满父节点后，最后一个索引指针不移动给新节点
				sp->index[sp->length] = node->index[node->length];
				node->index[node->length] = NULL;
			}
			sp->parent = node->parent;

			for (size_t i = 0; i <= sp->length; i++)
			{ /// 将原来的指针索引交给分裂的节点(更新分裂节点的下层parent指针)
				if (sp->index[i])
					sp->index[i]->parent = sp;
			}
			node->length = mid;

			/// 将分割元素返回
			size_t element = node->key[mid];
			node->key[mid] = KeyType{};

			return {element, sp};
		}
	};


public:
	template <typename KeyType, typename ElementType, size_t order>
	using NodeType = B_Node<KeyType, ElementType, order>;
public:
	NodeType *root{nullptr}; /// 根节点
	size_t count{};//元素数量

public:
	// 初始化B树
	//  Tree_Advanced_B(size_t order)
	//  	:order{ order }, count{ 0 }, root{ nullptr } {};
	~Tree_Advanced_B()
	{
		std::cout << "删除B树节点个数:" << count << std::endl;
		if (root)
			for (size_t i = 0; i < order; i++)
				Destroy(root->index[i]);
	}

private:
	void Destroy(NodeType *node)
	{
		if (node)
		{
			for (size_t i = 0; i < order; ++i)
			{
				if (node->index[i])
					Destroy(node->index[i]);
			}
			delete[] node->key;
			delete node;
			count--;
		}
	}

	

	// B树调整
	void RestoreBTree(NodeType *node)
	{
		NodeType *parent, *brother_left, *brother_right;
		parent = node->parent;
		if (parent)
		{				 /// 父节点存在
			size_t i_index; /// 指向调整节点的索引指针
			for (i_index = 0; i_index <= parent->length; ++i_index)
			{ /// 遍历父节点中的索引指针,以找到左右兄弟节点
				if (parent->index[i_index] == node)
					break;
			}
			/// parent->index[i_index] 指向当前节点
			brother_left = i_index > 0 ? parent->index[i_index - 1] : nullptr;
			brother_right = i_index <= parent->length ? parent->index[i_index + 1] : nullptr;

			if (brother_left && brother_left->length > node->order / 2)
			{ /// 左兄弟有多余元素，则从左兄弟借元素
				/// 从左兄弟借元素 = 从父节点借小元素(逻辑前驱) + 父节点从左节点借最大的元素(逻辑前驱)
				for (size_t i = node->length; i > 0; --i)
				{ /// 后移元素，留出第一个位置，存放父节点中借的元素
					node->key[i] = node->key[i - 1];
					node->index[i] = node->index[i - 1];
				}
				/// 存放父节点中借的元素
				node->key[0] = parent->key[index_right_to_position(i_index)];

				/// 父节点从左兄弟借最后一个元素
				parent->key[index_right_to_position(i_index)] = brother_left->key[brother_left->length - 1];
				/// 调整长度
				--brother_left->length;
				++node->length;
			}
			else if (brother_right && brother_right->length > node->order / 2)
			{ /// 右兄弟有多余元素，则从右兄弟借
				/// 从右兄弟借元素 = 从父节点借大元素(逻辑后继) + 父节点从右兄弟借最小元素(逻辑后继)

				/// 先把父元素移下来，放节点末尾
				node->key[node->length] = parent->key[i_index]; /// index_right_to_position(i_index)+1
				if (node->index[node->length])
					node->index[node->length]->parent = node;

				/// 再把右兄弟的第一个元素移上来(逻辑后继)
				parent->key[i_index] = brother_right->key[0];

				for (size_t i = 0; i < brother_right->length; ++i)
				{ /// 右兄弟被抽走一个元素，前移一格
					brother_right->key[i] = brother_right->key[i + 1];
					brother_right->index[i] = brother_right->index[i + 1];
				}
				brother_right->index[brother_right->length + 1] = nullptr;
				/// 调整长度
				++node->length;
				--brother_right->length;
			}
			else
			{ /// 左右兄弟都无法借元素，只能合并
				if (brother_left)
				{ /// 调整节点与左兄弟合并
					/// 合并 = 从父节点移动分割元素到左兄弟 + 当前节点元素都移到左节点

					size_t position_smaller_element = index_right_to_position(i_index);

					/// 从父节点移下分割元素
					brother_left->key[brother_left->length] = parent->key[position_smaller_element];
					++brother_left->length;

					for (size_t i = position_smaller_element; i < parent->length; ++i)
					{ /// 左移动父节点元素，补齐空位
						parent->key[i] = parent->key[i + 1];
						parent->index[i + 1] = parent->index[i + 2];
					}
					--parent->length;
					parent->key[parent->length] = NULL;
					parent->index[parent->length + 1] = nullptr;

					for (size_t i = 0; i < node->length; ++i)
					{ /// 把调整节点的元素和索引指针都移动给左兄弟
						brother_left->key[brother_left->length + i] = node->key[i];
						brother_left->index[brother_left->length + i + 1] = node->index[i + 1];
						if (brother_left->index[brother_left->length + i + 1])
							brother_left->index[brother_left->length + i + 1]->parent = brother_left;
					} /// 补齐缺少移动的第一个索引
					brother_left->index[brother_left->length] = node->index[0];
					brother_left->length += node->length;
					delete node;

					if (root == parent)
					{ /// 如果此时父节点为根，则当父节点没有关键字时才调整
						if (parent->length == 0)
						{
							NodeType *del = parent;
							for (size_t i = 0; i <= parent->length; ++i)
							{
								if (parent->index[i])
								{
									root = parent->index[i];
									delete del;
									break;
								}
								root->parent = NULL;
							}
						}
					}
					else
					{ /// 如果父节点不为根，则需要判断是否需要重新调整
						if (parent->length < order / 2)
							RestoreBTree(parent);
					}
				}
				else if (brother_right)
				{ /// 调整节点与右兄弟合并
					/// 合并 = 从父节点移动分割元素(逻辑后继)到左兄弟 + 右兄弟元素都移到调整节点

					size_t position_bigger_element = index_right_to_position(i_index) + 1;

					/// 从父节点移下分割元素
					node->key[node->length] = parent->key[position_bigger_element];
					++node->length;

					for (size_t i = position_bigger_element; i < parent->length; ++i)
					{ /// 左移动父节点元素，补齐空位
						parent->key[i] = parent->key[i + 1];
						parent->index[i + 1] = parent->index[i + 2];
					}
					parent->index[parent->length + 1] = nullptr;
					parent->key[parent->length] = NULL;
					--parent->length;

					for (size_t i = 0; i < brother_right->length; ++i)
					{ /// 把右兄弟元素和索引指针移到调整节点
						node->key[node->length + i] = brother_right->key[i];
						node->index[node->length + i + 1] = brother_right->index[i + 1];
						if (node->index[node->length + i + 1])
							node->index[node->length + i + 1]->parent = node;
					} /// 补齐缺少移动的第一个索引
					node->index[node->length + 1] = brother_right->index[0];
					node->length += brother_right->length;
					delete brother_right;

					if (root == parent)
					{ /// 如果此时父节点为根，则当父节点没有关键字时才调整
						if (parent->length == 0)
						{
							NodeType *del = parent;
							for (size_t i = 0; i <= parent->length; ++i)
							{
								if (parent->index[i])
								{
									root = parent->index[i];
									delete del;
									break;
								}
								root->parent = NULL;
							}
						}
					}
					else
					{ /// 如果父节点不为根，则需要判断是否需要重新调整
						if (parent->length < order / 2)
							RestoreBTree(parent);
					}
				}
				else
				{ /// 左右兄弟都不存在，合并当前元素到根节点
					for (size_t i = 0; i > node->length; ++i)
					{
						if (node->index[i])
						{
							root = node->index[i];
							break;
						}
					}
					root->parent = nullptr;
				}
			}
		}
		else
		{ /// 父节点不存在，即为根节点，合并并减少一层树的高度
			NodeType *del;
			for (size_t i = 0; i <= node->length; ++i)
				if (node->index[i + 1])
				{
					del = node;
					node = node->index[i + 1];
					del->index[i] = nullptr;
					delete del;
					break;
				}
			root = node;
			root->parent = nullptr;
		}
	}
	void Delete(NodeType *node, size_t position)
	{								   /// 删除node节点中下标为Position的元素
		if (node->index[position + 1]) /// 若元素存在右指针，则非叶节点
		{							   /// 删除非叶节点
			/// 用逻辑后继节点代替(父节点元素代替，父节点用右子树第一个代替)
			NodeType *leaf = node;
			if (leaf)
			{ /// 右孩子的第一个叶子元素(循环定位)
				leaf = leaf->index[position + 1];
				while (leaf->index[0])
					leaf = leaf->index[0];
				node->key[position] = leaf->key[0];
			}
			Delete(leaf, 0); /// 删除逻辑后继
		}
		else
		{ /// 删除叶节点

			for (size_t i = position; i < node->length; ++i)
			{									 /// 直接删除
				node->key[i] = node->key[i + 1]; /// 因为key末尾预留，且插入时置为0，所以可以直接从后覆盖前，且不考虑越界
				node->index[i] = node->index[i + 1];
			}
			--node->length;
			if (node->length < node->order / 2) /// 阈值可自定义
				RestoreBTree(node);				/// 调整B树
		}
	}

public:
	struct Result
	{
		bool tag;		 /// 查找是否成功
		size_t pos;		 /// 查到的key元素下标索引(parent_node->key[pos])	失败时为NULL
		NodeType *index; /// 查到的key所在节点的指针索引	失败时为父节点
	};

	// 查找
	Result B_Tree_Search(size_t key)
	{
		NodeType *precursor = nullptr; /// 父节点索引
		NodeType *current = root;	   /// 当前节点索引
		size_t pos = 0;				   /// 节点中的位置下标
		bool tag{false};			   /// 标记查找状态
		while (current && !tag)
		{ /// 搜索当前节点是否存在目标key
			pos = current->_Locate_Key(key);
			if (pos < current->length && current->key[pos] == key)
				/// 查找成功
				tag = true;
			else
			{ /// 查找失败
				precursor = current;
				current = current->index[pos]; /// 向下层节点找key(大值的左指针)
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

	std::optional<DataType &> operator[](size_t key)
	{
		if(!root)
			return std::nullopt;

		NodeType node = root;
		size_t index_key = node.Locate_Key(key);
		while (node && node.key[index_key] != key)
		{
			if (index == npos)
			{
				if (!node.child)
					return std::nullopt;
				else
				{
					size_t index_child = key > node.key[index] ? _Right_Child(index) : _Left_Child(index);
					node = node.child[index_child];
					continue;
				}
			}
			else
				return node.element[index_key];
		}

	}

	// 插入元素
	void Insert(KeyType key,ElementType element)
	{
		/// 定位待插入节点及下标位置
		Result res = B_Tree_Search(key);
		// if (res.tag == true)
		if (res != std::nullopt)
			throw std::logic_error("Insert Failed: key exsisted");

		NodeType *node = res.index; /// 元素插入的节点，此处因为Result搜索失败，所以返回查找节点的父节点声明为parent(即插入节点)
		size_t pos_node = res.pos;		/// 元素插入的节点的下标索引pos位置插入元素key(pos=第一个大元素的下标位置)
		NodeType *child = nullptr;	/// 分裂的新节点

		bool loop = true;	   /// 控制插入的while大循环,完成后控制退出
		bool root_new = false; /// 控制分裂时，是否需要新建上层节点
		size_t key_insert = key;  /// 插入的key

		if (node) /// 插入目标节点存在时
		{ 
			while (!root_new)
			{	  /// key插入当前节点
				{ /// 插入节点
					size_t i = node->length;
					if (i != node->length)
					{ /// 插入到末尾元素位置不后移，直接覆盖
						for (i; i >= pos_node; --i)
						{ /// 顺序表元素后移插入
							node->key[i] = node->key[i - 1];
							node->index[i + 1] = node->index[i];
						}
					}
					node->key[pos_node] = key_insert;
					node->index[pos_node + 1] = child;
					if (child)
						child->parent = node;
					++node->length;
				}
				/// 插入后判断是否分裂
				if (node->length < order)
					break;
				else
				{							 /// 节点满，分裂
					size_t pos_mid = order / 2; /// 分裂为上层节点
					std::pair<size_t, NodeType *> pair;
					/// 分割满节点为两个节点，返回待插入的key
					pair = split(node, pos_mid);
					key_insert = pair.first;
					child = pair.second;
					if (node->parent)
					{ /// 上层节点存在时，key插入到上层节点parent中
						node = node->parent;
						pos_node = B_Tree_Node_Locate(node, key_insert);
					}
					else
						root_new = true; /// 需要新建上层节点
				}
			}
		}
		else /// 插入目标节点不存在时(即空树时)
		{
			root = new NodeType; /// 创建上层节点
			r->key[0] = key;
			++r->length;
		}
		if (root_new)
		{
			NodeType *root = B_Tree_Create_Node(order); /// 创建上层节点
			this->root = root;
			root->key[0] = key_insert;
			root->index[0] = node;
			root->index[1] = child;
			node->parent = root;
			child->parent = root;
			root->length++;
		}
		count++;
	}

	// 删除值为key的元素
	void Delete(size_t key)
	{
		Result result = B_Tree_Search(key);
		if (result.tag)
		{ /// result查找key成功时，返回key所在的节点和下标
			Delete(result.index, result.pos);
			--count;
		}
		else
			std::cout << "key is not exist" << std::endl;
	}
	// 中序遍历
	void Traverse_Inorder(NodeType *node)
	{
		if (node)
		{
			for (size_t i = 0; i < node->length; ++i)
			{
				if (node->index[i]) /// 感觉多余
					B_Tree_Traverse_Inorder(node->index[i]);
				/// ——————————————————————————————————递归分割
				std::cout << node->key[i] << ' ';
			} /// 补齐缺少的最后一个索引
			B_Tree_Traverse_Inorder(node->index[node->length]);
		}
	}

	/// 中序遍历并显示信息
	void B_Tree_Show(std::string string)
	{
		std::cout << string << std::endl;
		B_Tree_Traverse_Inorder(root);
		std::cout << std::endl;
	}
};
