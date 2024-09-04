#pragma once

/// <summary>
/// 索引节点中的元素为每个子节点的末尾元素
/// 定义算法等建议看WikiPidia，详细且有存储图，实现上和教材上有些不一样
/// 运行效果见https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html
///
/// 总结：
/// B+树的叶子是一个链表
/// 索引节点和叶子节点结构不同，但是此处公用一种struct
/// 索引节点之间类似B—树，
/// 但是索引节点与最底层的叶子节点需要注意：每一个索引元素存叶子节点的分割元素(在叶子上出现的)
///		最底层的索引节点只存右孩子首元素key(最左孩子元素key不存)
///		非最底层的索引节点分割元素时，不同于最底层索引节点，需要像B-树一样将分割元素移到上层
///		(这样效果是高层索引元素也一一对应叶子的右孩子首元素key)
///
/// 注：key在同一个实例的叶子节点中中唯一，插入已存在的key无效
/// </summary>

#include <vector>
#include <queue>
#include <optional>

#include "B+_Node.hpp"

/// 索引节点元素，取该元素右子树的最小元素(即分割元素)
template <typename DataType, typename KeyType = int, int order = 5, typename NodeType = Node_BPlus<KeyType, DataType, order>>
class BPlus_Tree
{
public:
	NodeType *root{nullptr};		  /// 根节点

	// size_key ∈ [order/2, order-1] 时B+树稳定
	const int element_max{order - 1}; /// 最大元素个数(平衡后为orders-1，多余的一个用于插入时预留给已经满的节点)
	const int element_min{order / 2}; /// 最少元素个数(默认写死为 orders / 2)
public:
	/// 初始化orders阶的B+树，默认每个节点最少为orders/2 (n阶节点最多有n-1个元素)
	BPlus_Tree() { static_assert(order > 2, "order must be greater than 2"); }
	~BPlus_Tree()
	{ /// 层次遍历释放节点
	  // std::queue<NodeType*> queue;
	  // int i = 0;
	  // queue.push(root);
	  // while (!queue.empty())
	  // {
	  // 	auto node = queue.front();
	  // 	if (node->child)
	  // 		for (int i = 0; i <= node->size_data; ++i)
	  // 			queue.push(node->child[i]);
	  // 	queue.pop();
	  // 	delete node;
	  // 	++i;
	  // }
	  // std::cout << "Node Deleted Count: " << i << std::endl;
	}

private: /// Utilities
	NodeType *_Create_Branch() const { return new NodeType(true); }
	NodeType *_Create_Leaf() const { return new NodeType(false); }

private: /// 元素插入相关
	// 元素的插入以及分裂操作逻辑

	/// 将元素key-value插入到叶子节点node中
	/// <param name="node">一定是叶子节点</param>
	void _Insert(NodeType *node, KeyType key, DataType data)
	{
		/// 先插入到叶子节点
		node->Leaf_Element_Insert(key, data);

		/// 节点过载时分裂
		while (node->size_key > element_max)
		{
			// 拷贝数据
			int mid = node->size_data / 2;		// 中间位置索引
			KeyType split_key = node->key[mid]; // 中间元素

			NodeType *sibling; // 分裂结点
			if (!node->is_branch)
				sibling = node->Overflow_Leaf(); // 叶子结点分裂
			else
			{
				sibling = node->Overflow_Branch(); // 索引结点分裂
				split_key = node->key[node->size_key - 1];
				node->key[node->size_key - 1] = KeyType{};
				--node->size_key;
			}

			/// 被分裂的元素插入父节点
			NodeType *parent = node->parent;
			if (!parent) // 父节点不存在，生成新索引节点(该索引节点为新根节点)
			{
				parent = _Create_Branch();
				if (!parent)
					throw std::runtime_error("Parent Create Failed");
				parent->child[0] = node;
				parent->size_child++;
				node->parent = parent;
				sibling->parent = parent;
				root = parent;
			}

			/// 索引元素插入父节点
			parent->Insert_Overflow_Key(split_key, sibling);

			// 向上继续判断是否父节点需要分裂
			node = parent;
		}
	}

private: /// 辅助显示的操作
	/// 经典回溯实现遍历生成所有树中的节点信息，存入数组
	void _BackTrace_Traverse(std::vector<std::vector<NodeType *>> &buffer, NodeType *node)
	{
		static int level = 0;
		if (!node)
			return;

		buffer[level].push_back(node);
		if (!node->is_branch)
			return;

		for (int i = 0; i < node->size_child; ++i)
		{ // 遍历所有孩子节点，加入对应层的数组中
			level++;
			_BackTrace_Traverse(buffer, node->child[i]);
			level--;
		}
	}
	void _Node_Print(NodeType *node)
	{
		for (int i{}; i < node->size_key; i++)
		{
			std::cout << node->key[i] << " ";
		}
		if (node->is_branch)
		{
			std::cout << "[ ";
			for (int i = 0; i < node->size_child; ++i)
				std::cout << node->child[i]->key[0] << ' ';
			std::cout << ']';
		}
		if (node->parent)
			std::cout << '{' << std::to_string(node->parent->key[0]) << '}';
	}
	/// 将BackTrace_Traverse生成的buffer格式化输出
	void _Print_Tree(std::vector<std::vector<NodeType *>> &buffer, int level)
	{

		/// 以行为单位显示每一层的节点
		for (int i = 0; i < level - 1; ++i)
		{
			/// 索引节点稍微居中一些显示
			for (int j = 0; j < (level - i); ++j)
				std::cout << '\t';

			for (const auto &node : buffer[i]) // 索引节点格式化
			{
				_Node_Print(node);
				std::cout << '\t';
			}
			std::cout << std::endl;
		}

		/// 显示最底层的叶子节点
		auto node = buffer[level - 1][0];
		while (node)
		{
			_Node_Print(node);
			if (node->next)
			{
				std::cout << "-> ";
				node = node->next;
			}
			else
			{
				std::cout << "\n";
				return;
			}
		}
	}

public:
	// 插入元素
	void Element_Insert(KeyType key, DataType element)
	{
		/// 空树创建根(叶子)节点
		if (!root)
		{
			root = _Create_Leaf();
			if (!root)
				throw std::runtime_error("Root Create Failed");
		}

		NodeType *node = root;
		int index;

		/// ————————————————————————————————————————————————————————
		/// 定位插入元素的位置
		/// 先找到插入的叶子节点，再再叶子节点中找插入位置索引
		/// ————————————————————————————————————————————————————————
		while (node->is_branch)
		{
			node = node->Locate_Child(key); /// 修改node到下层节点
			if (!node)
				throw std::runtime_error("Node Unexists");
		}

		if (node->Index_Key(key))
			return; // 已经存在元素了，直接取消插入操作

		/// 找到插入位置后插入元素
		_Insert(node, key, element);
	}

	/// 删除叶子节点node上的第index个元素
	void _Delete(NodeType *node, int index)
	{
		/// 若叶子节点删除最后一个元素，则修改对应索引节点的索引值
		if (index == node->size_key - 1 && node->is_branch && node->parent)
		{
			NodeType *node_index = node->parent;
			int key_target = node->key[index];
			int i = node_index->Index_Key(key_target).value_or(-1);
			while (i >= node_index->size_key || i == -1)
			{ // 一直向上层找key所在的节点
				node_index = node_index->parent;
				i = node_index->Index_Key(key_target).value_or(-1);
			}
			// 找到后覆盖数据
			node_index->key[i] = node->key[1];
		}

		/// 删除叶子结点的指定的值
		node->Leaf_Element_Delete(index);

		NodeType *parent = node->parent;

		/// 一层一层向上维护索引节点元素数量
		while (node->size_key < element_min && parent)
		{
			/// 定位结点在父节点中的索引位置
			auto result = node->Locate_Child_Index();
			if (!result) // 在他的父节点中没找到这个孩子
				throw std::logic_error("No Matching Node but Element Delete Found");
			index = result.value();
			NodeType *sibling{};
			if (index == 0) /// 没有左兄弟 只有右兄弟
			{
				sibling = parent->child[1];
				if (sibling->size_key > element_min) /// 兄弟有富余元素，将富余元素移过来(最小元素)
				{
					if (node->is_branch)
						parent->Branch_Rotate_Left(0);
					else
						parent->Leaf_Rotate_Left(0);
				}
				else /// 兄弟俩节点都没有富余元素时，合并兄弟为一个
					parent->Merge_Neighbour_Child(0);
			}
			else /// 只有左兄弟、或两边都有兄弟，向左边兄弟拿元素
			{
				sibling = parent->child[index - 1];
				if (sibling->size_key > element_min)
				{
					// 从左兄弟迁移数据
					if (node->is_branch)
						parent->Branch_Rotate_Right(index - 1);
					else
						parent->Leaf_Rotate_Right(index - 1);
				}
				else /// 合并兄弟
					parent->Merge_Neighbour_Child(index - 1);
			}

			// 向上层更新
			node = parent;
			parent = node->parent;
		}

		/// 如果根节点的两个孩子合并，将合并后的孩子节点作为新的根节点
		if (root->is_branch and !root->size_key)
		{
			node = root;
			root = node->child[0];

			/// 删除头节点后清空孩子的父节点
			node->child[0]->parent = nullptr;
			delete node;
		}
	}
	// 删除元素
	void Element_Delete(KeyType key)
	{
		NodeType *node = root;

		/// 先查索引节点找到叶子，再找目标元素在节点中的index
		while (node->is_branch)
		{
			node = node->Locate_Child(key);
			if (!node)
				throw std::runtime_error("Node Unexists");
		}

		// index = Locate_Key_Delete(node, key);
		auto index = node->Index_Key(key);
		if (!index)
			return; // 不存在该元素

		/// 找到删除位置后删除目标元素
		_Delete(node, index.value());

		return;
	}

	// 搜索叶子中key所对应的元素数据
	std::optional<DataType> Search(KeyType key)
	{
		auto node = root;
		while (node->is_branch)
		{
			node = node->Locate_Child(key);
			if (!node)
				throw std::runtime_error("Node Unexists");
		}

		auto index = node->Index_Key(key); // std::optional支持与bool转换,有值时为true
		if (index.has_value())
			return node->data[index.value()];
		else
			return std::nullopt;
	}
	// 显示整个树
	void Show(const std::string &info = "")
	{
		auto node = root;
		int level = 1;
		// while (node->child)
		while (node->is_branch)
		{ // 所有叶子节点深度相同
			++level;
			node = node->child[0];
		}

		std::vector<std::vector<NodeType *>> buffer;
		buffer.resize(level);
		_BackTrace_Traverse(buffer, root);

		std::cout << "Tree=======================================" << std::endl;
		_Print_Tree(buffer, level);
		std::cout << "===========================================" << std::endl;
	}
};
