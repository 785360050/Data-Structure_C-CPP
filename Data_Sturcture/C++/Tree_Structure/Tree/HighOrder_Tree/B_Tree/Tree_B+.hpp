#pragma once



/// <summary>
/// �����ڵ��е�Ԫ��Ϊÿ���ӽڵ��ĩβԪ��
/// �����㷨�Ƚ��鿴WikiPidia����ϸ���д洢ͼ��ʵ���Ϻͽ̲�����Щ��һ��
/// ����Ч����https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html
/// 
/// �ܽ᣺
/// B+����Ҷ����һ������
/// �����ڵ��Ҷ�ӽڵ�ṹ��ͬ�����Ǵ˴�����һ��struct
/// �����ڵ�֮������B������
/// ���������ڵ�����ײ��Ҷ�ӽڵ���Ҫע�⣺ÿһ������Ԫ�ش�Ҷ�ӽڵ�ķָ�Ԫ��(��Ҷ���ϳ��ֵ�)
///		��ײ�������ڵ�ֻ���Һ�����Ԫ��key(������Ԫ��key����)
///		����ײ�������ڵ�ָ�Ԫ��ʱ����ͬ����ײ������ڵ㣬��Ҫ��B-��һ�����ָ�Ԫ���Ƶ��ϲ�
///		(����Ч���Ǹ߲�����Ԫ��Ҳһһ��ӦҶ�ӵ��Һ�����Ԫ��key)
///		
/// ע��key��ͬһ��ʵ����Ҷ�ӽڵ�����Ψһ�������Ѵ��ڵ�key��Ч
/// </summary>

#include <vector>
#include <queue>
#include <optional>

#include "B+_Node.hpp"

///�����ڵ�Ԫ�أ�ȡ��Ԫ������������СԪ��(���ָ�Ԫ��)
template
<
	typename DataType,
	typename KeyType = int,
	int orders = 5
>
class BPlus_Tree
{
public:
	using Node_Type = BPlus_Node<KeyType, DataType>;
private:
	Node_Type* root;	///���ڵ�
	const int element_max{ orders };///���Ԫ�ظ���(ƽ���Ϊorders-1�������һ�����ڲ���ʱԤ�����Ѿ����Ľڵ�)
	const int element_min{ orders / 2 };///����Ԫ�ظ���(Ĭ��д��Ϊ orders / 2)

public:
	///��ʼ��orders�׵�B+����Ĭ��ÿ���ڵ�����Ϊorders/2   (n�׽ڵ������n-1��Ԫ��)
	//BPlus_Tree()
	//{
	//	if(orders<=2)
	//		throw std::logic_error("Invalid Tree Orders: orders <= 2")
	//}
	~BPlus_Tree()
	{///��α����ͷŽڵ�
		std::queue<Node_Type*> queue;
		int i = 0;
		queue.push(root);
		while (!queue.empty())
		{
			auto node = queue.front();
			if (node->child)
				for (int i = 0; i <= node->count; ++i)
					queue.push(node->child[i]);
			queue.pop();
			delete node;
			++i;
		}
		std::cout << "Node Deleted Count: " << i << std::endl;

	}
	 
private: ///Utilities
	//�����µ��ڲ����
	BPlus_Node_Branch<KeyType,DataType>* Create_Branch()
	{
		return new BPlus_Node_Branch(element_max);
	}
	//�����µ�Ҷ�ӽ��
	BPlus_Node_Leaf<KeyType, DataType>* Create_Leaf()
	{
		return new BPlus_Node_Leaf(element_max);
	}
	//�Ƚ�����key�Ĵ�С��a>b=true
	bool Key_Greater(const KeyType a,const KeyType b)
	{
		return a > b;
	}



	/// ���²���key���ڵĽڵ㣬����key���ڵ��²�ڵ�
	Node_Type* Locate_Child(Node_Type* node, int key)
	{
		if (!node)
			throw std::runtime_error("Node Unexists");
		for (int i = 0; i < node->count; i++)
		{
			if (node->keys[i] < key)
				continue;
			if (key < node->keys[i])
				return node->child[i];
			else
				return node->child[i + 1];
		}
		return node->child[node->count];
	}
	///����key��Ҷ�ӽڵ�����λ���������Ѿ�����ʱ����-1
	std::optional<int> Locate_Index_KeyInsert(Node_Type* node, int key)
	{
		if (!node)
			throw std::runtime_error("Node Unexists");

		for (int i = 0; i < node->count; ++i)
		{
			if (node->keys[i] < key)
				continue;
			if (key == node->keys[i])
				return -1;
			if (key < node->keys[i])
				return i - 1;
		}
		return 0;
	}
	///����key��node�е��±꣬�����ڷ���-1
	std::optional<int> Locate_IndexOfKey(Node_Type* node, int key)
	{
		if (!node)
			throw std::runtime_error("Node Unexists");

		for (int i = 0; i < node->count; ++i)
		{
			if (key == node->keys[i])
				return i;
		}
		return std::nullopt;
	}


private:///Ԫ�ز������
	//Ԫ�صĲ����Լ����Ѳ����߼�

	/// <summary>
	/// ��Ԫ��key-value���뵽Ҷ�ӽڵ�node��
	/// </summary>
	/// <param name="node">һ����Ҷ�ӽڵ�</param>
	void _BPlus_Tree_Insert(Node_Type* node, KeyType key, DataType value)
	{
		Node_Type* parent;
		int mid;
		int temp;
		int i;

		///�Ȳ��뵽Ҷ�ӽڵ�
		//����ƶ�Ԫ��
		for (i = node->count; i > 0 && Key_Greater(node->keys[i - 1], key); i--)
		{
			node->keys[i] = node->keys[i - 1];
			node->data[i] = node->data[i - 1];
		}
		//������Ԫ��
		node->keys[i] = key;
		node->data[i] = value;
		node->count++;


		///�ڵ����ʱ����
		while (node->count >= element_max)
		{
			Node_Type* sibling;
			// ��������
			mid = node->count / 2;//�м�λ������
			temp = node->keys[mid];//�м�Ԫ��
			/*���ѽ��*/
			if (!node->child)// Ҷ�ӽ�����
			{
				sibling = Create_Leaf();
				sibling->count = node->count - mid;

				for (int i = 0; i < sibling->count; ++i)
				{//����Ԫ�غ�����
					sibling->keys[i] = node->keys[mid + i];
					sibling->data[i] = node->data[mid + i];
					node->keys[mid + i] = node->data[mid + i] = 0;//�ÿ�
				}

				//����Ҷ�ӵ���ʽ�ڵ�
				sibling->next = node->next;
				node->next = sibling;
			}
			else// ����������
			{///ע�⣺�����ڵ�ķ��ѻ�ѷ��ѽڵ������ƶ������������ӽڵ�һ�����������ĵ�һ��Ԫ��
				sibling = Create_Branch();
				sibling->count = node->count - mid - 1;//����Ԫ�ز����ֵܽڵ�

				/// ���ָ��ȥ�ĺ���ת�����·��ѵ��ֵܽڵ�
				for (int i = 0; i < sibling->count; ++i)
				{//����Ԫ�غ�����
					sibling->keys[i] = node->keys[mid + i + 1];
					sibling->child[i] = node->child[mid + i + 1];
					sibling->child[i]->parent = sibling;

					node->keys[mid + i + 1] = 0;//�ÿ�
					node->child[mid + i + 1] = nullptr;
				}
				//sibling->child[sibling->count] = node->child[node->count];
				sibling->child[sibling->count] = node->child[node->count];
				sibling->child[sibling->count]->parent = sibling;

			}
			node->count = mid;

			///�����ѵ�Ԫ�ز��븸�ڵ�
			parent = node->parent;
			if (!parent)//���ڵ㲻���ڣ������������ڵ�(�������ڵ�Ϊ�¸��ڵ�)
			{
				parent = Create_Branch(element_max);
				if (!parent)
					throw std::runtime_error("Parent Create Failed");
				parent->child[0] = node;
				node->parent = parent;
				root = parent;
			}

			///����Ԫ�ز��븸�ڵ�

			//��һ�������ƶ�Ԫ�أ�һ�߶�λ����λ��
			for (i = parent->count; i > 0 && Element_Greater(parent->keys[i - 1], temp); i--)
			{
				parent->keys[i] = parent->keys[i - 1];
				parent->child[i + 1] = parent->child[i];
			}

			parent->keys[i] = temp;
			if (parent->child[0]->child)//���ӽڵ�Ϊ�����ڵ�
				node->keys[mid] = 0;
			parent->child[i + 1] = sibling;
			parent->count++;

			sibling->parent = parent;

			// ���ϼ����ж��Ƿ񸸽ڵ���Ҫ����
			node = parent;
		}
	}


	

private:///������ʾ�Ĳ���
	//std::vector<std::vector<BPlus_Node*>> buffer;
	///�������ʵ�ֱ��������������еĽڵ���Ϣ����������
	void _BackTrace_Traverse(std::vector<Node_Type*>*& buffer, Node_Type* node, int level)
	{
		static int level = 0;
		if (!node)
			return;

		buffer[level].push_back(node);
		if (!node->child)
			return;

		for (int i = 0; i <= node->count; ++i)
		{//�������к��ӽڵ㣬�����Ӧ���������
			level++;
			BackTrace_Traverse(buffer, node->child[i], level);
			level--;
		}
	}
	///��BackTrace_Traverse���ɵ�buffer��ʽ�����
	void _Print_Tree(std::vector<Node_Type*>*& buffer, int level)
	{

		///����Ϊ��λ��ʾÿһ��Ľڵ�
		for (int i = 0; i < level - 1; ++i)
		{
			///�����ڵ���΢����һЩ��ʾ
			for (int j = 0; j < (level - i); ++j)
				std::cout << '\t';

			for (const auto& node : buffer[i])//�����ڵ��ʽ��
			{
				Node_Print(node);
				std::cout << '\t';
			}
			std::cout << std::endl;
		}

		///��ʾ��ײ��Ҷ�ӽڵ�
		auto node = buffer[level - 1][0];
		while (node)
		{
			Node_Print(node);
			if (node->next)
			{
				std::cout << "->";
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
	//����Ԫ��
	void Element_Insert(KeyType key, DataType element)
	{
		///����������(Ҷ��)�ڵ�
		if (!root)
		{
			root = Create_Leaf(element_max);
			if (root)
				throw std::runtime_error("Root Create Failed");
		}

		Node_Type* node = root;
		int index;

		///����������������������������������������������������������������������������������������������������������������
		/// ��λ����Ԫ�ص�λ��
		/// ���ҵ������Ҷ�ӽڵ㣬����Ҷ�ӽڵ����Ҳ���λ������
		///����������������������������������������������������������������������������������������������������������������

		while (node->child)
		{
			node = Locate_Child(node, key);///�޸�node���²�ڵ�
			if (!node)
				throw std::runtime_error("Node Unexists");
		}

		
		if (Locate_IndexOfKey(node, key))
			return;//�Ѿ�����Ԫ���ˣ�ֱ��ȡ���������


		///�ҵ�����λ�ú����Ԫ��
		_BPlus_Tree_Insert(node, key, element);
	}
	//ɾ��Ԫ��
	void Element_Delete(KeyType key)
	{

	}

	//����Ҷ����key����Ӧ��Ԫ������
	std::optional<DataType> Search(KeyType key)
	{
		auto node = root;
		while (node->child)
		{
			node = Locate_Child(node, key);
			if (!node)
				throw std::runtime_error("Node Unexists");
		}

		auto index = Locate_IndexOfKey(node, key);//std::optional֧����boolת��,��ֵʱΪtrue
		if(index.has_value())
			return node->data[index];
		else
			return std::nullopt;
	}
	//��ʾ������
	void Show(const std::string& info="")
	{
		auto node = root;
		int level = 1;
		//while (node->child)
		while (node->Is_Branch())
		{//����Ҷ�ӽڵ������ͬ
			++level;
			node = dynamic_cast<BPlus_Node_Branch*>(node)->child[0];
		}

		std::vector<Node_Type*>* buffer = new std::vector<Node_Type*>[level];
		_BackTrace_Traverse(buffer, node, 0);

		std::cout << "Tree=======================================" << std::endl;
		_Print_Tree(buffer, level);
		std::cout << "===========================================" << std::endl;
		delete[] buffer;
	}

};






