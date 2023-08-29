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

struct BPlus_Node
{
	int* keys;			  // ���� ���max�� ��Сmin��
	int* data;		  // ��ʵ����  ���max�� ��Сmin�� �����ڲ���� data��nullptr
	BPlus_Node** child; // �ӽڵ� ���max+1�� ��Сmin+1��
	BPlus_Node* next;	  // ָ���ֵܽ�� ������Ҷ�ӽ���ʱ�����ֵ
	BPlus_Node* parent;
	int count;			  // ��ǰԪ�ظ���
};


///�����ڵ�Ԫ�أ�ȡ��Ԫ������������СԪ��(���ָ�Ԫ��)
struct BPlus_Tree
{
	BPlus_Node* root;
	int max;///������
	int min;///��С����(Ĭ��д��Ϊ max / 2)
};







///��ʼ��orders�׵�B+����Ĭ��ÿ���ڵ�����Ϊorders/2   (n�׽ڵ������n-1��Ԫ��)
BPlus_Tree* BPlus_Tree_Init(int orders);

void BPlus_Tree_Destroy(BPlus_Tree* tree);


//�����µ�Ҷ�ӽ��
BPlus_Node* BPlus_Node_Create_Leaf(int m);

//�����µ��ڲ����
BPlus_Node* BPlus_Node_Create_Branch(int m);


void BPlus_Tree_Insert(BPlus_Tree* tree, int key, int value);






void BPlus_Tree_Delete(BPlus_Tree* tree, int key);


void BPlus_Tree_Show(BPlus_Tree* tree);