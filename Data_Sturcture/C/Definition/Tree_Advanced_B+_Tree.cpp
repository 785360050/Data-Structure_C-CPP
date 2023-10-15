#include "../API/Tree_Advanced_B+_Tree.h"

#include <iostream>
#include <string>

static bool Element_Greater(int a, int b)
{
	return a - b > 0;
}


BPlus_Node* BPlus_Node_Create_Leaf(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;

	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m + 1] {};
	node->data = new int[m + 1] {};
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

BPlus_Node* BPlus_Node_Create_Branch(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;

	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m + 1] {};
	node->data = nullptr;//�����ڵ㲻������
	if (node->keys == nullptr)
	{
		delete node->keys;
		delete node->data;
		delete node;
		return nullptr;
	}
	node->child = new BPlus_Node * [m + 2] {};///ΪʲôҪ+2
	return node;
}


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

#include <queue>
void BPlus_Tree_Destroy(BPlus_Tree* tree)
{///��α����ͷŽڵ�
	std::queue<BPlus_Node*> queue;
	int i = 0;
	queue.push(tree->root);
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



////���ֲ��� �ҵ�������ָ����key��λ�� ������ڷ���1 ���򷵻�0
////����ҵ�����Ϊ��ֵ��λ�� ���򷵻����ڵ�ֵ��λ��(child��λ��)
//static bool binary_search(int* keys, int key, int left, int right, int* index)
//{
//	int mid;
//	while (left <= right)
//	{
//		mid = (left + right) / 2;
//		if (keys[mid] == key)
//		{
//			*index = mid;
//			return true;
//		}
//		if (Element_Greater(keys[mid], key))
//			right = mid - 1;
//		else
//			left = mid + 1;
//	}
//	*index = left;
//	return false;
//}

///������Ŀ��keyʱ��һ��·�����ӽڵ�
static BPlus_Node* Locate_Child(BPlus_Node* node, int key)
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
static int Locate_Key(BPlus_Node* node, int key)
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
static int Locate_Key_Delete(BPlus_Node* node, int key)
{
	if (!node)
		throw std::runtime_error("Node Unexists");

	for (int i = 0; i < node->count; ++i)
	{
		if (key == node->keys[i])
			return i;
	}
	return -1;
}

//Ԫ�صĲ����Լ����Ѳ���
static void _BPlus_Tree_Insert(BPlus_Tree* tree, BPlus_Node* node, int key, int value)
{
	BPlus_Node* parent;
	int mid;
	int temp;
	int i;

	///�Ȳ��뵽Ҷ�ӽڵ�
	//����ƶ�Ԫ��
	for (i = node->count; i > 0 && Element_Greater(node->keys[i - 1], key); i--)
	{
		node->keys[i] = node->keys[i - 1];
		node->data[i] = node->data[i - 1];
	}
	//������Ԫ��
	node->keys[i] = key;
	node->data[i] = value;
	node->count++;


	///�ڵ����ʱ����
	while (node->count >= tree->max)
	{
		BPlus_Node* sibling;
		// ��������
		mid = node->count / 2;//�м�λ������
		temp = node->keys[mid];//�м�Ԫ��
		/*���ѽ��*/
		if (!node->child)// Ҷ�ӽ�����
		{
			sibling = BPlus_Node_Create_Leaf(tree->max);
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
			sibling = BPlus_Node_Create_Branch(tree->max);
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
			parent = BPlus_Node_Create_Branch(tree->max);
			if (!parent)
				throw std::runtime_error("Parent Create Failed");
			parent->child[0] = node;
			node->parent = parent;
			tree->root = parent;
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


void BPlus_Tree_Insert(BPlus_Tree* tree, int key, int value)
{
	BPlus_Node* node;
	int index;

	///����������(Ҷ��)�ڵ�
	if (!tree->root)
	{
		node = BPlus_Node_Create_Leaf(tree->max);
		if (node == nullptr)
			throw std::runtime_error("Node Create Failed");
		tree->root = node;
	}

	node = tree->root;

	///����������������������������������������������������������������������������������������������������������������
	/// ��λ����Ԫ�ص�λ��
	/// ���ҵ������Ҷ�ӽڵ㣬����Ҷ�ӽڵ����Ҳ���λ������
	///����������������������������������������������������������������������������������������������������������������

	while (node->child)
	{
		node = Locate_Child(node, key);
		if (!node)
			throw std::runtime_error("Node Unexists");
	}

	index = Locate_Key(node, key);
	if (index == -1)
		return;//�Ѿ�����Ԫ����


	///�ҵ�����λ�ú����Ԫ��
	_BPlus_Tree_Insert(tree, node, key, value);
}


//Ҷ�ӽ�������ת ���ҽڵ�ĵ�һ��ֵ�Ƶ���ڵ�
void _bplus_leaf_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
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

	//������ɺ�������ø��ڵ�ֵ��������ԭ����ֵ�����ܱ�����ֵܵ�ĩβԪ��
	node->keys[index] = right->keys[0];

	right->count--;

}

//�ڲ���������ת ���ҽڵ�ĵ�һ��ֵ�Ƶ����ڵ� ���ڵ��Ӧ��ֵ�Ƶ���ڵ�
void _bplus_internal_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];

	left->keys[left->count] = node->keys[index];
	left->child[left->count + 1] = right->child[0];
	left->child[left->count + 1]->parent = left;
	left->count++;

	node->keys[index] = right->keys[0];

	// ���ҽڵ������λ
	for (int i = 0; i < right->count - 1; i++)
		right->keys[i] = right->keys[i + 1];

	for (int i = 0; i < right->count; i++)
		right->child[i] = right->child[i + 1];

	right->count--;
}

//�ϲ����Ԫ�ص����������ӽڵ�,index���ӵ�����ֵ
void _BPlus_Node_merge(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];
	if (!left->child)///�ϲ�Ҷ�ӽڵ�
	{//�ϲ������ӽڵ�

		for (int i = 0; i < right->count; ++i)
		{
			left->keys[left->count + i] = right->keys[i];
			left->data[left->count + i] = right->data[i];
		}

		left->count += right->count;

		///�޸�����Ԫ��
		for (int i = index; i < node->count - 1 ; i++)
			node->keys[i] = node->keys[i + 1];
		node->keys[node->count - 1] = 0;
		//(�ϲ�����ڵ㲻Ӧ��ɾ�ұߵ�������)
		//ɾ����ڵ������(ֱ�Ӹ���) (int i = index�Ƿ�+1��bug)
		for (int i = index + 1; i <= node->count-1; i++)
			node->child[i] = node->child[i + 1];
		node->child[node->count] = nullptr;
		node->count--;

		left->next = right->next;
	}
	else///�ϲ������ڵ�
	{
		//�Ӹ��ڵ�ѷָ�Ԫ��������(���ﲻ��Ҫ���Ǻ���ָ���ƶ�)
		left->keys[left->count] = node->keys[index];
		if (node->count == 1)//�黹���ָ������ڵ�ΪҶ�ӽڵ�ĸ��ڵ�ָ��
			right->child[0]->parent = left;
		left->count++;


		//���ұ�Ԫ�غϲ������
		for (int i = 0; i < right->count; ++i)
		{
			left->keys[left->count + i] = right->keys[i];
			right->keys[i] = 0;
		}

		for (int i = 0; i <= right->count; ++i)
		{
			left->child[left->count + i] = right->child[i];
			right->child[i]->parent = left;
			right->child[i] = nullptr;
		}

		left->count += right->count;
		right->count = 0;

		///�޸ĸ������ڵ�
		//ɾ���ƶ�������key
		for (int i = index; i < node->count - 1; i++)
			node->keys[i] = node->keys[i + 1];
		node->keys[node->count - 1] = 0;

		//�ϲ�������ɾ����ڵ�ĺ�������(ֱ�Ӹ��ǣ�ÿ�θ����Һ���)
		for (int i = index + 1; i <= node->count; i++)
			node->child[i] = node->child[i + 1];
		node->child[node->count] = nullptr;
		node->count--;

		left->next = right->next;
	}

	/*�޸ĸ��ڵ�*/


	/*�ͷ��ҽڵ�*/
	free(right->keys);
	free(right->data);
	free(right->child);
	free(right);
}

//Ҷ�ӽ�������ת
void _bplus_leaf_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];

	for (int i = right->count; i > 0; i--)
	{//����ƶ�����������λ��
		right->keys[i] = right->keys[i - 1];
		right->data[i] = right->data[i - 1];
	}
	right->count++;
	right->keys[0] = left->keys[left->count - 1];
	right->data[0] = left->data[left->count - 1];

	left->count--;
	//node->keys[index] = right->keys[0];
	node->keys[index] = right->keys[0];///parent�����ڵ��Ϊ�ƶ���ǰһ��Ԫ��
}

//�ڲ���������ת ��ڵ�����һ��ֵ�����ڵ� ���ڵ��Ӧ��ֵ���ҽڵ�
void _bplus_internal_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];
	for (int i = right->count; i > 0; i--)
		right->keys[i] = right->keys[i - 1];

	right->keys[0] = node->keys[index];
	for (int i = right->count + 1; i > 0; i--)
		right->child[i] = right->child[i - 1];
	right->child[0] = left->child[left->count];
	right->child[0]->parent = right;
	right->count++;

	node->keys[index] = left->keys[left->count - 1];
	left->count--;
}


///ɾ��Ҷ�ӽڵ�node�ϵĵ�index��Ԫ��
static void _BPlus_Tree_delete(BPlus_Tree* tree, BPlus_Node* node, int index)
{
	BPlus_Node* parent, * sibling;



	///��Ҷ�ӽڵ�ɾ����һ��Ԫ�أ����޸Ķ�Ӧ�����ڵ������ֵ
	if (index == 0 && !node->child && node->parent)
	{
		BPlus_Node* node_index=node->parent;
		int key_target = node->keys[index];
		int i = Locate_Key_Delete(node_index, key_target);
		while (i>=node_index->count||i==-1)
		{//һֱ���ϲ���key���ڵĽڵ�
			node_index = node_index->parent;
			i= Locate_Key_Delete(node_index, key_target);
		}
		//�ҵ��󸲸�����
		node_index->keys[i] = node->keys[1];
		
	}

	///ɾ��Ҷ�ӽ���ָ����ֵ
	//�Ӻ���ǰ����
	for (int i = index; i < node->count - 1; i++)
	{
		node->keys[i] = node->keys[i + 1];
		node->data[i] = node->data[i + 1];
	}
	node->count--;
	node->keys[node->count] = 0;

	parent = node->parent;
	///һ��һ������ά�������ڵ�Ԫ������
	while (node->count < tree->min && parent)
	{
		///��λ����ڸ��ڵ��е�����λ��
		for (index = 0; index <= parent->count && parent->child[index] != node; index++)
			;
		if (index > parent->count)// �����ĸ��ڵ���û�ҵ��������
			throw std::logic_error("No Matching Node but Element Delete Found");
		if (index == 0)///û�����ֵ� ֻ�����ֵ�
		{

			sibling = parent->child[1];
			if (sibling->count > tree->min)///�ֵ��и���Ԫ�أ�������Ԫ���ƹ���(��СԪ��)
			{
				// Ǩ������
				if (!node->child)
					// Ҷ�ӽ���Ǩ��
					_bplus_leaf_left_rotate(parent, 0);
				else
					_bplus_internal_left_rotate(parent, 0);
			}
			else///�ֵ����ڵ㶼û�и���Ԫ��ʱ���ϲ��ֵ�Ϊһ��
				_BPlus_Node_merge(parent, 0);

		}
		else///ֻ�����ֵܡ������߶����ֵܣ�������ֵ���Ԫ��
		{
			sibling = parent->child[index - 1];
			if (sibling->count > tree->min)
			{
				// �����ֵ�Ǩ������
				if (!node->child)
					// Ҷ�ӽ�������ת
					_bplus_leaf_right_rotate(parent, index - 1);
				else
					// �ڲ���������ת
					_bplus_internal_right_rotate(parent, index - 1);
			}
			else///�ϲ��ֵ�
				_BPlus_Node_merge(parent, index - 1);
		}

		node = parent;
		parent = node->parent;
	}


		

	///������ڵ���������Ӻϲ������ϲ���ĺ��ӽڵ���Ϊ�µĸ��ڵ�
	if (tree->root->count == 0 && tree->root->child != nullptr)
	{
		node = tree->root;
		tree->root = node->child[0];

		///ɾ��ͷ�ڵ����պ��ӵĸ��ڵ�
		node->child[0]->parent = nullptr;
		free(node->keys);
		free(node->data);
		free(node->child);
		free(node);
	}
}


void BPlus_Tree_Delete(BPlus_Tree* tree, int key)
{
	BPlus_Node* node = tree->root;
	int index;

	///�Ȳ������ڵ��ҵ�Ҷ�ӣ�����Ŀ��Ԫ���ڽڵ��е�index
	while (node->child)
	{
		node = Locate_Child(node, key);
		if (!node)
			throw std::runtime_error("Node Unexists");
	}

	index = Locate_Key_Delete(node, key);
	if (index == -1)
		return;//�����ڸ�Ԫ��

	///�ҵ�ɾ��λ�ú�ɾ��Ŀ��Ԫ��
	_BPlus_Tree_delete(tree, node, index);

	return;
}



static void Node_Print(BPlus_Node* node)
{
	std::vector<int> temp;
	std::cout << '{';
	///��ȱ������Ԫ��
	for (int i = 0; i < node->count; i++)
	{
		if (i != 0)
			std::cout << ',';
		std::cout << node->keys[i];
		temp.push_back(node->keys[i]);
	}
	std::cout << '}';

	///Details to Debug
//	std::cout << '[';
//	if (!node->child)
//	{
//		std::cout << "Leaf";
//		goto END;
//	}
//	///��ȱ������Ԫ��
//	for (int i = 0; i < node->count; i++)
//	{
//		//if (!node->child)
//		//	break;
//		if (i != 0)
//			std::cout << ',';
//		std::cout << node->child[i]->keys[0];
//		
//		//if (i == 0)
//		//	continue;
//		//if (temp[i-1] != node->child[i]->keys[0])
//		//	throw std::logic_error("Errors Occured");
//	}
//	std::cout << (node->child[node->count] ? "," + std::to_string(node->child[node->count]->keys[0]) : "");
//END:
//	std::cout << ']';
//	std::cout << '('<< (!node->parent ? "Root)" : std::to_string(node->parent->keys[0]) + ")");

	if (node->child)
		return;
	std::cout << '<';
	///��ȱ������Ԫ��
	for (int i = 0; i < node->count; i++)
	{
		if (i != 0)
			std::cout << ',';
		std::cout << node->data[i];
			
	}
	std::cout << '>';
}

static void Traver(BPlus_Node* node)
{
	std::cout << '{';
	///��ȱ������Ԫ��
	for (int i = 0; i < node->count; i++)
	{
		if (i != 0)
			std::cout << ',';
		std::cout << node->keys[i];
	}
	std::cout << '}';
}

#include <vector>
//static void BPlus_Level_Show(BPlus_Node* node, int h)
//{
//	if (node == nullptr)
//		return;
//	if (node->child != nullptr)
//		;	//BPlus_Node_Show(node->child[0], h + 1);
//
//	auto node_current = node;
//	while (node_current->child)
//		node_current = node_current->child[0];
//	while (node_current)
//	{
//		BPlus_Node_printfnode(node_current);
//		std::cout << (node_current->next ? "--->" : "\n");
//		node_current = node_current->next;
//	}
//
//
//
//}
static void BPlus_Level_Show(BPlus_Node* node, int h)
{
	if (node == nullptr)
		return;
	if (node->child != nullptr)
		;	//BPlus_Node_Show(node->child[0], h + 1);

	std::vector<std::vector<BPlus_Node*>> buffer;

	int level = 1;
	buffer.push_back({ node });
	//for (int i = 0; i < node->count; ++i)
	//	level


}


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

int BPlus_Tree_Search(BPlus_Tree* tree, int key)
{
	if (!tree)
		throw std::runtime_error("tree is nullptr");

	auto node = tree->root;
	while (node->child)
	{
		node = Locate_Child(node, key);
		if (!node)
			throw std::runtime_error("Node Unexists");
	}

	//��������������Ѻã������һ��
	int index = Locate_Key_Delete(node, key);
	if (index != -1)
		return node->data[index];
	else
		return -1;
}

void BPlus_Tree_Show(BPlus_Tree* tree)
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
