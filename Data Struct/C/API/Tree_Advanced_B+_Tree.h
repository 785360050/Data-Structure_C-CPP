#pragma once


struct BPlus_Node
{
	int* keys;			  // ���� ���max�� ��Сmin��
	int* data;		  // ��ʵ����  ���max�� ��Сmin�� �����ڲ���� data��nullptr
	BPlus_Node** child; // �ӽڵ� ���max+1�� ��Сmin+1��
	BPlus_Node* next;	  // ָ���ֵܽ�� ������Ҷ�ӽ���ʱ�����ֵ
	BPlus_Node* parent;
	int count;			  // ��ǰԪ�ظ���
};


struct BPlus_Tree
{
	BPlus_Node* root;
	int max;///������
	int min;///��С����(Ĭ��д��Ϊ max / 2)
};



#include <iostream>

int item_cmp(int a,int b)
{return a-b;}


///��ʼ��orders�׵�B+����Ĭ��ÿ���ڵ�����Ϊorders/2
BPlus_Tree* BPlus_Tree_Init(int orders)
{
	BPlus_Tree* tree = new BPlus_Tree;
	if (!tree)
		return nullptr;
	tree->root = nullptr;
	tree->max = orders;
	tree->min = orders / 2;
	return tree;
}


/*
���ֲ��� �ҵ�������ָ����key��λ�� ������ڷ���1 ���򷵻�0
����ҵ�����Ϊ��ֵ��λ�� ���򷵻����ڵ�ֵ��λ��(child��λ��)
*/
int binary_search(int* keys, int key, int left, int right, int* index)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (item_cmp(keys[mid], key) > 0)
			right = mid - 1;
		else if (item_cmp(keys[mid], key) < 0)
			left = mid + 1;
		else
		{
			*index = mid;
			return 1;
		}
	}
	*index = left;
	return 0;
}

//�����µ�Ҷ�ӽ��
BPlus_Node* BPlus_Node_Create_Leaf(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;
	
	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m+1];
	node->data = new int[m+1];
	if (node->keys == nullptr || node->data == nullptr)
	{
		delete node->keys;
		delete node->data;
		delete node;
		return nullptr;
	}
	node->child = nullptr;
	return node;
}

//�����µ��ڲ����
BPlus_Node* BPlus_Node_Create_Branch(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;

	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m + 1];
	node->data = nullptr;
	if (node->keys == nullptr || node->data == nullptr)
	{
		delete node->keys;
		delete node->data;
		delete node;
		return nullptr;
	}
	node->child = new BPlus_Node[m+2];
	return node;
}

//Ԫ�صĲ����Լ����Ѳ���
int _BPlus_Tree_Insert(BPlus_Tree* tree, BPlus_Node* node, int key, int value)
{
	BPlus_Node* parent, node2;
	int mid;
	int temp;
	int i;
	/*�Ȳ���Ҷ�ӽ��*/
	for (i = node->count; i > 0 && item_cmp(node->keys[i - 1], key) > 0; i--)
	{
		node->keys[i] = node->keys[i - 1];
		node->data[i] = node->data[i - 1];
	}
	node->keys[i] = key;
	node->data[i] = value;
	node->count++;
	while (node->count > tree->max)
	{
		/*���ѽ��*/
		if (node->child == nullptr)
		{
			// Ҷ�ӽ�����
			node2 = BPlus_Node_new_leaf(tree->max);
		}
		else
		{
			// �ڲ�������
			node2 = BPlus_Node_new_internal(tree->max);
		}
		if (node2 == nullptr)
		{
			return 0;
		}
		// ��������
		mid = node->count / 2;
		temp = node->keys[mid];
		if (node->child == nullptr)
		{
			node2->count = node->count - mid;
			memcpy(node2->keys, node->keys + mid, sizeof(int) * (node2->count));
			memcpy(node2->data, node->data + mid, sizeof(int) * (node2->count));
			node2->next = node->next;
			node->next = node2;
		}
		else
		{

			node2->count = node->count - mid - 1;

			memcpy(node2->keys, node->keys + mid + 1, sizeof(int) * (node2->count));
			memcpy(node2->child, node->child + mid + 1, sizeof(BPlus_Node*) * (node->count - mid));

			// �������ø�ָ��
			for (int i = 0; i <= node2->count; i++)
			{
				node2->child[i]->parent = node2;
			}
		}

		node->count = mid;

		/*���븸�ڵ�*/
		parent = node->parent;
		if (parent == nullptr)
		{
			// ����һ���µĸ��ڵ�
			parent = BPlus_Node_new_internal(tree->max);
			if (parent == nullptr)
			{
				return 0;
			}
			parent->child[0] = node;
			node->parent = parent;
			tree->root = parent;
		}

		/*�������� ������*/
		for (i = parent->count; i > 0 && item_cmp(parent->keys[i - 1], temp) > 0; i--)
		{
			parent->keys[i] = parent->keys[i - 1];
			parent->child[i + 1] = parent->child[i];
		}

		parent->keys[i] = temp;
		parent->child[i + 1] = node2;
		parent->count++;

		node2->parent = parent;

		// ���� ���ϼ����ж�
		node = parent;
	}
	return 1;
}

int BPlus_Tree_Insert(BPlus_Tree* tree, int key, int value)
{
	BPlus_Node* node;
	int ret, index;
	if (tree->root == nullptr)
	{
		node = BPlus_Node_Create_Leaf(tree->max);
		if (node == nullptr)
			return 0;
		tree->root = node;
	}

	node = tree->root;
	// ����Ҷ�ӽ��
	while (node->child != nullptr)
	{
		ret = binary_search(node->keys, key, 0, node->count - 1, &index);
		if (ret == 1)
			index++;
		node = node->child[index];
	}

	ret = binary_search(node->keys, key, 0, node->count - 1, &index);
	if (ret == 1)
		// �������Ѿ�������
		return 0;
	_BPlus_Tree_Insert(tree, node, key, value);
	return 1;
}

void BPlus_Node_printfnode(int* key, int h)
{
	for (int i = 0; i < h; i++)
		std::cout << "   ";
	if (key == nullptr)
		std::cout << "\n";
	else
		std::cout << *key<<std::endl;
}

void BPlus_Node_Show(BPlus_Node* node, int h)
{
	if (node == nullptr)
		return;
	if (node->child != nullptr)
		BPlus_Node_Show(node->child[0], h + 1);
	for (int i = 0; i < node->count; i++)
	{
		BPlus_Node_printfnode(&node->keys[i], h);
		if (node->child != nullptr)
			BPlus_Node_Show(node->child[i + 1], h + 1);
	}
}

void BPlus_Tree_Show(BPlus_Tree* tree)
{
	BPlus_Node_Show(tree->root, 0);
}


//Ҷ�ӽ�������ת ���ҽڵ�ĵ�һ��ֵ�Ƶ���ڵ�
void _bplus_leaf_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, right;
	left = node->child[index];
	right = node->child[index + 1];
	left->keys[left->count] = right->keys[0];
	left->data[left->count] = right->data[0];
	left->count++;

	// ���ҽڵ������λ
	for (int i = 0; i < right->count - 1; i++)
	{
		right->keys[i] = right->keys[i + 1];
		right->data[i] = right->data[i + 1];
	}

	right->count--;

	node->keys[index] = right->keys[0];
}

//�ڲ���������ת ���ҽڵ�ĵ�һ��ֵ�Ƶ����ڵ� ���ڵ��Ӧ��ֵ�Ƶ���ڵ�
void _bplus_internal_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, *right;
	left = node->child[index];
	right = node->child[index + 1];

	left->keys[left->count] = node->keys[index];
	left->child[left->count + 1] = right->child[0];
	left->count++;

	node->keys[index] = right->keys[0];

	// ���ҽڵ������λ
	for (int i = 0; i < right->count - 1; i++)
		right->keys[i] = right->keys[i + 1];

	for (int i = 0; i < right->count; i++)
		right->child[i] = right->child[i + 1];

	right->count--;
}

//�ϲ����Ԫ�ص����������ӽڵ�
void _BPlus_Node_merge(BPlus_Node* node, int index)
{
	BPlus_Node* left, right;
	left = node->child[index];
	right = node->child[index + 1];
	if (left->child != nullptr)
	{
		/*�޸����ӽڵ�*/
		left->keys[left->count] = node->keys[index];
		memcpy(left->keys + left->count + 1, right->keys, sizeof(int) * (right->count));

		for (int i = 0; i <= right->count; i++)
		{
			right->child[i]->parent = left;
			left->child[left->count + i + 1] = right->child[i];
		}

		left->count = left->count + right->count + 1;
	}
	else
	{
		memcpy(left->keys + left->count, right->keys, sizeof(int) * (right->count));
		memcpy(left->data + left->count, right->data, sizeof(int) * (right->count));

		left->count = left->count + right->count;
	}

	/*�޸ĸ��ڵ�*/
	for (int i = index; i < node->count - 1; i++)
		node->keys[i] = node->keys[i + 1];

	for (int i = index + 1; i < node->count; i++)
		node->child[i] = node->child[i + 1];
	node->count--;

	/*�ͷ��ҽڵ�*/
	free(right->keys);
	free(right->data);
	free(right->child);
	free(right);
}

//Ҷ�ӽ�������ת
void _bplus_leaf_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, right;
	left = node->child[index];
	right = node->child[index + 1];

	for (int i = right->count; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
		right->data[i] = right->data[i - 1];
	}
	right->count++;
	right->keys[0] = left->keys[left->count - 1];
	right->data[0] = left->data[left->count - 1];

	left->count--;
	node->keys[index] = right->keys[0];
}

//�ڲ���������ת ��ڵ�����һ��ֵ�����ڵ� ���ڵ��Ӧ��ֵ���ҽڵ�
void _bplus_internal_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, right;
	left = node->child[index];
	right = node->child[index + 1];
	for (int i = right->count; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
	}
	right->keys[0] = node->keys[index];
	for (int i = right->count + 1; i > 0; i--)
	{
		right->child[i] = right->child[i - 1];
	}
	right->child[0] = left->child[left->count];
	right->count++;

	node->keys[index] = left->keys[left->count - 1];
	left->count--;
}


void _BPlus_Tree_delete(BPlus_Tree* tree, BPlus_Node* node, int index)
{
	BPlus_Node* parent, sibling;
	/*��ɾ��Ҷ�ӽ���ָ����ֵ*/
	for (int i = index; i < node->count - 1; i++)
	{
		node->keys[i] = node->keys[i + 1];
		node->data[i] = node->data[i + 1];
	}
	node->count--;
	parent = node->parent;
	while (node->count < tree->min && parent != nullptr)
	{
		/*Ѱ�ҵ���ǰ����ڸ��ڵ㵱�е�λ��*/
		for (index = 0; index <= parent->count && parent->child[index] != node; index++)
			;
		if (index > parent->count)// �����ĸ��ڵ���û�ҵ��������
			return;
		if (index == 0)
		{
			// ����ǵ�һ�����  û�����ֵ� ֻ�����ֵ�
			sibling = parent->child[1];
			if (sibling->count > tree->min)
			{
				// Ǩ������
				if (node->child == nullptr)
					// Ҷ�ӽ���Ǩ��
					_bplus_leaf_left_rotate(parent, 0);
				else
					_bplus_internal_left_rotate(parent, 0);
			}
			else
				/*�ϲ��ֵ�*/
				_BPlus_Node_merge(parent, 0);
		}
		else
		{
			/*
			�������Ǹ����еĵ�index���ӽڵ㣬�ֵ��ǵ�index - 1
			�м�ķָ�Ԫ���Ǹ��ڵ��еĵ�index - 1��Ԫ��
			*/
			sibling = parent->child[index - 1];
			if (sibling->count > tree->min)
			{
				// �����ֵ�Ǩ������
				if (node->child == nullptr)
					// Ҷ�ӽ�������ת
					_bplus_leaf_right_rotate(parent, index - 1);
				else
					// �ڲ���������ת
					_bplus_internal_right_rotate(parent, index - 1);
			}
			else
				/*�ϲ��ֵ�*/
				_BPlus_Node_merge(parent, index - 1);
		}

		node = parent;
		parent = node->parent;
	}

	if (tree->root->count == 0 && tree->root->child != nullptr)
	{
		node = tree->root;
		tree->root = node->child[0];
		free(node->keys);
		free(node->data);
		free(node->child);
		free(node);
	}
}

void BPlus_Tree_Delete(BPlus_Tree* tree, int key)
{
	BPlus_Node* node = tree->root;
	int ret = 0, index;
	/*�Ȳ��ҵ�Ҷ��*/
	while (node->child != nullptr)
	{
		ret = binary_search(node->keys, key, 0, node->count - 1, &index);
		if (ret == 1)
			index++;
		node = node->child[index];
	}
	ret = binary_search(node->keys, key, 0, node->count - 1, &index);
	if (ret == 0)
		return;

	_BPlus_Tree_delete(tree, node, index);

	return;
}
