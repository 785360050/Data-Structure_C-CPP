#pragma once

/// 使用一个结构同时表示叶子和节点，leaf区分索引节点和叶子节点
template <typename KeyType, typename DataType, int order = 5>
class Node_BPlus
{
public:
	bool is_branch{false}; /// 标记是否为叶节点
public:
	Node_BPlus *parent{nullptr};
	KeyType key[order]; // 最多branch-1个元素
	int size_key;		/// key数组当前元素个数
public:
	/// ============================================================================================================
	/// 		Index Node
	/// ============================================================================================================
	Node_BPlus *child[order + 1]; /// 索引指针。(末尾冗余一个，缓存待调整的元素。注：算法基于该特性)
	int size_child;				  /// 当前索引指针个数
public:
	/// ============================================================================================================
	/// 		Leaf
	/// ============================================================================================================
	Node_BPlus *next{nullptr};
	DataType data[order]; /// 数据数组
	int size_data;		  /// 数据个数

public:
	Node_BPlus() = default;
	Node_BPlus(bool is_branch) : is_branch(is_branch) {}

public:
	// 定位key在节点中的下标，不存在时返回maxsize值
	std::optional<int> Index_Key(KeyType key)
	{
		for (int i{}; i < size_key; ++i)
		{
			if (this->key[i] == key)
				return i;
			else if (this->key[i] > key)
				return std::nullopt;
		}
		return std::nullopt;
	}

public:
	void Key_Append(KeyType key) { this->key[size_key++] = key; }
	void Child_Append(Node_BPlus *child) { this->child[size_child++] = child; }
	void Data_Append(DataType data) { this->data[size_data++] = data; }

	void Leaf_Element_Insert(KeyType key, DataType data)
	{ /// 先插入到叶子节点
		// 向后移动元素
		int i;
		for (i = this->size_data; i > 0 && key < this->key[i - 1]; i--) // 写死为升序排序
		{
			this->key[i] = this->key[i - 1];
			this->data[i] = this->data[i - 1];
		}
		// 插入新元素
		this->key[i] = key;
		this->size_key++;
		this->data[i] = data;
		this->size_data++;
	}
	/// 删除叶子结点的指定的元素
	void Leaf_Element_Delete(int index)
	{
		// 从后往前覆盖
		for (int i = index; i < this->size_key - 1; i++)
		{
			key[i] = key[i + 1];
			data[i] = data[i + 1];
		}
		size_key--;
		key[size_key] = KeyType{};
	}

	/// 向下层找key所在的节点，返回key所在的下层节点
	Node_BPlus *Locate_Child(int key)
	{
		for (int i = 0; i < size_key; i++)
		{
			if (this->key[i] < key)
				continue;
			if (key <= this->key[i])
				return child[i]; // 左孩子
			else
				return child[i + 1]; // 右孩子
		}
		// 索引节点的key数量比所有叶子节点数量少1
		return child[size_key];
	}

	std::optional<int> Locate_Child_Index()
	{
		/// 定位结点在父节点中的索引位置
		int index = 0;
		while (index <= parent->size_key)
		{
			if (parent->child[index] == this)
				return index;
			index++;
		}
		return std::nullopt;
	}
	Node_BPlus *Overflow_Leaf()
	{
		auto mid = size_data / 2;
		auto sibling = new Node_BPlus(false);

		for (int i = 0; i < mid; ++i) // 拷贝元素和数据
		{
			sibling->key[i] = this->key[mid + i + 1]; // 分割元素的后一个元素开始
			this->key[mid + i + 1] = KeyType{};		  // 置空
			--size_key;
			++sibling->size_key;

			sibling->data[i] = this->data[mid + i + 1];
			this->data[mid + i + 1] = DataType{}; // 置空
			--size_data;
			++sibling->size_data;
		}

		// 插入叶子的链式节点
		sibling->next = this->next;
		this->next = sibling;
		return sibling;
	}

	Node_BPlus *Overflow_Branch()
	{ /// 注意：索引节点的分裂会把分裂节点向上移动，而不是像子节点一样存右子树的第一个元素
		auto mid = this->size_key / 2;
		auto sibling = new Node_BPlus(true);
		// sibling->size_key = this->size_key - mid - 1; // 分裂元素不给兄弟节点

		/// 将分割出去的孩子转交给新分裂的兄弟节点
		for (int i = 0; i < mid; ++i)
		{ // 拷贝元素和数据
			sibling->key[i] = this->key[mid + i + 1];
			this->key[mid + i + 1] = KeyType{}; // 置空
			++sibling->size_key;
			--this->size_key;

			sibling->child[i] = this->child[mid + i + 1];
			this->child[mid + i + 1] = nullptr;
			sibling->child[i]->parent = sibling;
			--this->size_child;
			++sibling->size_child;
		}

		// 移动末尾的叶子结点到兄弟节点
		sibling->child[sibling->size_child] = this->child[this->size_child + 1];
		this->child[this->size_child + 1] = nullptr;
		--this->size_child;
		sibling->child[sibling->size_child]->parent = sibling;
		++sibling->size_child;

		return sibling;
	}

	void Insert_Overflow_Key(KeyType split_key, Node_BPlus *sibling)
	{
		auto mid = this->size_data / 2;
		// 先一边往后移动元素，一边定位插入位置
		int i{this->size_key};
		while (i > 0 and split_key < this->key[i - 1])
		{
			this->key[i] = this->key[i - 1];
			this->child[i + 1] = this->child[i];
			i--;
		}

		this->key[i] = split_key;
		++size_key;
		child[i + 1] = sibling;
		sibling->parent = this;
		++size_child;

		return;
	}

	// 内部结点的左旋转 把右节点的第一个值移到父节点 父节点对应的值移到左节点
	void Branch_Rotate_Left(int left_child_index)
	{
		auto parent = this; // 当前节点作为父节点，控制左右孩子旋转

		Node_BPlus *left = parent->child[left_child_index];
		Node_BPlus *right = parent->child[left_child_index + 1];
		left->key[left->size_key] = parent->key[left_child_index];
		left->child[left->size_key + 1] = right->child[0];
		left->child[left->size_key + 1]->parent = left;
		left->size_key++;
		left->size_child++;

		parent->key[left_child_index] = right->key[0];

		// 对右节点进行移位
		for (int i = 0; i < right->size_key - 1; i++)
			right->key[i] = right->key[i + 1];
		right->size_key--;
		right->key[right->size_key] = KeyType{};

		for (int i = 0; i < right->size_child; i++)
			right->child[i] = right->child[i + 1];
		right->size_child--;
		// 此处无需置空，移动的时候多遍历一次，利用末尾冗余的空指针覆盖
	}

	// 叶子结点的左旋转 把右节点的第一个值移到左节点
	void Leaf_Rotate_Left(int left_child_index)
	{
		auto parent = this; // 当前节点作为父节点，控制左右孩子旋转

		Node_BPlus *left = parent->child[left_child_index];
		Node_BPlus *right = parent->child[left_child_index + 1];
		left->key[left->size_key] = right->key[0];
		left->data[left->size_key] = right->data[0];
		left->size_key++;

		// 右兄弟的收个元素被移动到左兄弟的最后一个位置，所以更新父节点索引key
		parent->key[left_child_index] = right->key[0];

		// 对右节点进行移位
		for (int i = 0; i < right->size_key - 1; i++)
		{
			right->key[i] = right->key[i + 1];
			right->data[i] = right->data[i + 1];
		}
		right->size_key--;
	}

	// 合并结点元素的左右两个子节点,index左孩子的索引值
	void Merge_Neighbour_Child(int left_child_index)
	{
		auto parent = this; // 当前节点作为父节点，控制左右孩子旋转

		Node_BPlus *left = parent->child[left_child_index];
		Node_BPlus *right = parent->child[left_child_index + 1];
		if (!left->is_branch) /// 合并叶子节点
		{
			// 合并到左子节点
			for (int i = 0; i < right->size_key; ++i)
			{
				left->key[left->size_key + i] = right->key[i];
				left->data[left->size_key + i] = right->data[i];
			}
			left->size_key += right->size_key;

			/// 修改索引元素
			for (int i = left_child_index; i < parent->size_key - 1; i++)
				parent->key[i] = parent->key[i + 1];
			parent->key[parent->size_key - 1] = KeyType{};
			--parent->size_key;

			//(合并到左节点不应该删右边的索引吗？)
			// 删除左节点的索引(直接覆盖) (int i = index是否+1有bug)
			for (int i = left_child_index + 1; i < parent->size_child; i++)
				parent->child[i] = parent->child[i + 1];
			parent->size_child--;

			left->next = right->next;
		}
		else /// 合并索引节点
		{
			// 从父节点把分割元素移下来(这里不需要考虑孩子指针移动)
			left->key[left->size_key] = parent->key[left_child_index];
			if (parent->size_key == 1) // 归还被分割索引节点为叶子节点的父节点指向
				right->child[0]->parent = left;
			left->size_key++;

			// 把右边元素合并到左边
			for (int i{}, right_key_size{right->size_key}; i < right_key_size; ++i)
			{
				left->key[left->size_key] = right->key[i];
				++left->size_key;
				right->key[i] = KeyType{};
				--right->size_key;
			}
			for (int i{}, right_child_size{right->size_child}; i < right_child_size; ++i)
			{
				left->child[left->size_child] = right->child[i];
				++left->size_child;
				right->child[i]->parent = left;
				right->child[i] = nullptr;
				--right->size_child;
			}

			/// 修改父索引节点
			// 删除移动下来的key
			for (int i{left_child_index}; i < parent->size_key - 1; i++)
			{
				parent->key[i] = parent->key[i + 1];
				--parent->size_key;
			}
			parent->size_key--;
			parent->key[parent->size_key] = KeyType{}; // 末尾置空

			// 合并索引后，删除夫节点的孩子索引(直接覆盖，每次覆盖右孩子)
			for (int i{left_child_index + 1}, child_size{parent->size_child}; i < child_size; i++)
				parent->child[i] = parent->child[i + 1];
			--parent->size_child;
			parent->child[parent->size_child] = nullptr;

			/// ============================================================================================================
			/// 		此处不要处理删除父节点，移动后会统一处理删除
			/// ============================================================================================================
		}
		// 删除多余的右节点
		delete right;
	}

	// 叶子结点的右旋转
	void Leaf_Rotate_Right(int left_child_index)
	{
		auto parent = this; // 当前节点作为父节点，控制左右孩子旋转
		Node_BPlus *left = parent->child[left_child_index];
		Node_BPlus *right = parent->child[left_child_index + 1];

		for (int i = right->size_key; i > 0; i--)
		{ // 向后移动，留出插入位置
			right->key[i] = right->key[i - 1];
			right->data[i] = right->data[i - 1];
		}
		right->size_key++;
		right->key[0] = left->key[left->size_key - 1];
		right->data[0] = left->data[left->size_key - 1];

		left->size_key--;
		// parent->key[left_child_index] = right->key[0];
		parent->key[left_child_index] = right->key[0]; /// parent索引节点改为移动的前一个元素
	}

	// 内部结点的右旋转 左节点的最后一个值到父节点 父节点对应的值到右节点
	void Branch_Rotate_Right(int left_child_index)
	{
		auto parent = this; // 当前节点作为父节点，控制左右孩子旋转
		Node_BPlus *left = parent->child[left_child_index];
		Node_BPlus *right = parent->child[left_child_index + 1];
		for (int i = right->size_key; i > 0; i--)
			right->key[i] = right->key[i - 1];

		right->key[0] = parent->key[left_child_index];
		for (int i = right->size_key + 1; i > 0; i--)
			right->child[i] = right->child[i - 1];
		right->child[0] = left->child[left->size_key];
		right->child[0]->parent = right;
		right->size_key++;

		parent->key[left_child_index] = left->key[left->size_key - 1];
		left->size_key--;
	}
};
