#pragma once


///δ���
/// �����ڵ��Ҷ�ӽڵ㵽�����������ѣ�������
template <typename KeyType = int, typename DataType = int>
struct BPlus_Node
{
private:
	KeyType* keys{ nullptr };			  // ���� ���max�� ��Сmin��
	BPlus_Node<DataType>* parent{ nullptr };
	int count{ 0 };			  // ��ǰԪ�ظ���
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

		keys = new KeyType[orders]{};///orders�׽ڵ���orders-1��Ԫ��
		if (!keys)
			throw std::runtime_error("Node Create Failed: keys allocated failed");
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
	BPlus_Node_Branch** child{ nullptr }; // �ӽڵ� ���max+1�� ��Сmin+1��
public:
	bool Is_Branch() override final { return true; }
public:
	BPlus_Node_Branch() = delete;
	BPlus_Node_Branch(int orders)
		:BPlus_Node<KeyType, DataType>(orders)
	{
		this->Check_Order_Vaild(orders);

		child = new BPlus_Node * [orders] {};///ΪʲôҪ+2,�ݸ�Ϊ0
		if (!child)
			throw std::runtime_error("Node Create Failed: keys allocated failed");
	}
	~BPlus_Node_Branch()
	{
		delete[] child;
	}

};

template <typename KeyType = int, typename DataType = int>
struct BPlus_Node_Leaf :public BPlus_Node<KeyType, DataType>
{
	DataType* data{ nullptr };		  // ��ʵ����  ���max�� ��Сmin�� �����ڲ���� data��nullptr
	BPlus_Node<DataType>* next{ nullptr };	  // ָ���ֵܽ�� ������Ҷ�ӽ���ʱ�����ֵ
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
			throw std::runtime_error("Node Create Failed: Leaf");
	}
	~BPlus_Node_Leaf()
	{
		delete[] data;
	}

};