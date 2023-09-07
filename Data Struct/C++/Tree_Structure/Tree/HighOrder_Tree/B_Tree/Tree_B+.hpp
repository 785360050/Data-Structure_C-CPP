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
/// 
/// </summary>

template <typename KeyType,typename DataType>
struct BPlus_Node
{
	KeyType* keys;			  // ���� ���max�� ��Сmin��
	DataType* data;		  // ��ʵ����  ���max�� ��Сmin�� �����ڲ���� data��nullptr
	BPlus_Node** child; // �ӽڵ� ���max+1�� ��Сmin+1��
	BPlus_Node* next;	  // ָ���ֵܽ�� ������Ҷ�ӽ���ʱ�����ֵ
	BPlus_Node* parent;
	int count;			  // ��ǰԪ�ظ���
};


///�����ڵ�Ԫ�أ�ȡ��Ԫ������������СԪ��(���ָ�Ԫ��)
template <typename KeyType, typename DataType,size_t Order>
class BPlus_Tree
{
private:
	BPlus_Node* root;
	size_t max;///������
	constexpr size_t min{ max / 2 };///��С����(Ĭ��д��Ϊ max / 2)

public:
	///��ʼ��orders�׵�B+����Ĭ��ÿ���ڵ�����Ϊorders/2   (n�׽ڵ������n-1��Ԫ��)
	BPlus_Tree() = default;
	~BPlus_Tree() = default;
	//BPlus_Tree* BPlus_Tree_Init(int orders);
	//void BPlus_Tree_Destroy(BPlus_Tree* tree);

private:
	//�����µ��ڲ����
	BPlus_Node* Create_Branch();
	//�����µ�Ҷ�ӽ��
	BPlus_Node* Create_Leaf();

public:
	void Element_Insert(KeyType key, DataType element);

	void Element_Delete(KeyType key);

	///����Ҷ����key����Ӧ��Ԫ������
	DataType Search(KeyType key);

	void Show()
	{
		//BPlus_Level_Show(tree->root, 0);

		auto node = tree->root;
		int level = 1;
		while (node->child)
		{//����Ҷ�ӽڵ������ͬ
			++level;
			node = node->child[0];
		}

		std::vector<BPlus_Node*>* buffer = new std::vector<BPlus_Node*>[level];
		BackTrace_Traverse(buffer, tree->root, 0);

		std::cout << "Tree=======================================" << std::endl;
		Print_Tree(buffer, level);
		std::cout << "===========================================" << std::endl;
		delete[] buffer;
	}

};


#include <vector>
std::vector<std::vector<BPlus_Node*>> buffer;
int level = 0;
///����ʵ�ֱ��������������еĽڵ���Ϣ����������
static void BackTrace_Traverse(std::vector<BPlus_Node*>*& buffer, BPlus_Node* node, int level)
{
	if (!node)
		return;

	buffer[level].push_back(node);
	if (!node->child)
		return;

	for (int i = 0; i <= node->count; ++i)
	{//�������к��ӽڵ㣬�����Ӧ���������
		level++;
		//if(i==node->count && !node->child[i])


		BackTrace_Traverse(buffer, node->child[i], level);
		level--;
	}
}

void Print_Tree(std::vector<BPlus_Node*>*& buffer, int level)
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




