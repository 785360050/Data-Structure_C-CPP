#pragma once


///未完成
/// 索引节点和叶子节点到底如何区分最佳，待考虑
template <typename KeyType = int, typename DataType = int>
struct BPlus_Node
{
private:
	KeyType* keys{ nullptr };			  // 主键 最大max个 最小min个
	BPlus_Node<DataType>* parent{ nullptr };
	int count{ 0 };			  // 当前元素个数
protected:
	void Check_Order_Vaild(int orders)
	{
		if (orders <= 0)
			throw std::logic_error("BPlus_Node Constructed Failed: orders <= 0");
	}
public:
	BPlus_Node() = delete;
	BPlus_Node(int orders)
	{
		Check_Order_Vaild(orders);

		keys = new KeyType[orders]{};///orders阶节点有orders-1个元素
		if (!keys)
			throw std::exception("Node Create Failed: keys allocated failed");
	}
	~BPlus_Node()
	{
		delete[] keys;
	}
public:
	virtual bool Is_Child(){ return false; }
	virtual bool Is_Branch(){ return false; }
};

template <typename KeyType = int, typename DataType = int>
struct BPlus_Node_Branch :public BPlus_Node<KeyType, DataType>
{
private:
	BPlus_Node_Branch** child{ nullptr }; // 子节点 最大max+1个 最小min+1个
public:
	bool Is_Branch() override final { return true; }
public:
	BPlus_Node_Branch() = delete;
	BPlus_Node_Branch(int orders)
		:BPlus_Node<KeyType, DataType>(orders)
	{
		this->Check_Order_Vaild(orders);

		child = new BPlus_Node * [orders] {};///为什么要+2,暂改为0
		if (!child)
			throw std::exception("Node Create Failed: keys allocated failed");
	}
	~BPlus_Node_Branch()
	{
		delete[] child;
	}

};

template <typename KeyType = int, typename DataType = int>
struct BPlus_Node_Leaf :public BPlus_Node<KeyType, DataType>
{
	DataType* data{ nullptr };		  // 真实数据  最大max个 最小min个 对于内部结点 data是nullptr
	BPlus_Node<DataType>* next{ nullptr };	  // 指向兄弟结点 仅仅是叶子结点的时候才有值
public:
	bool Is_Child() override final { return false; }
public:
	BPlus_Node_Leaf() = delete;
	BPlus_Node_Leaf(int orders, BPlus_Node_Leaf<KeyType, DataType>* next = nullptr)
		:BPlus_Node<KeyType, DataType>(orders), next{ next }
	{
		this->Check_Order_Vaild(orders);

		data = new DataType[orders]{};
		if (!data)
			throw std::exception("Node Create Failed: Leaf");
	}
	~BPlus_Node_Leaf()
	{
		delete[] data;
	}

};