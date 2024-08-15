#include "Binary_Tree.hpp"


#include <QStack>

//创建二叉树
void CreateBTNode(BTNode * & root,QString binaryTreeBracketNotationString)
{
	root = nullptr;
	enum class processTreeType//当前字符处理的类型
	{
		leftChildTree,
		rightChildTree,
		noChildTree
	};
	processTreeType nowNodeProcessTreeType{processTreeType::noChildTree};

	BTNode * currentNode{nullptr};//当前创建的结点
	QStack<BTNode*> stack;
	for(const auto & element : binaryTreeBracketNotationString)
	{
		if(element == '(')//表示一棵左子树的开始,即将前面刚创建的结点作为双亲结点进栈
		{
			stack.push(currentNode);
			nowNodeProcessTreeType = processTreeType::leftChildTree;
		}
		else if(element == ')')//表示一棵子树的结束
		{
			stack.pop();
		}
		else if(element == ',')//表示一棵右子树的开始
		{
			nowNodeProcessTreeType = processTreeType::rightChildTree;
		}
		else//字母，说明应该创建一个结点
		{
			currentNode = new BTNode;
			currentNode->data = element;

			if(!root)
				root = currentNode;
			else
			{
				switch (nowNodeProcessTreeType)
				{
					case processTreeType::leftChildTree:stack.top()->lchild = currentNode;break;
					case processTreeType::rightChildTree:stack.top()->rchild = currentNode;break;
					case processTreeType::noChildTree:;break;
				}
			}
		}
	}
}

Painter::Binary_Tree::Binary_Tree()
{
	QString binaryTreeBracketNotationString = "A(B(D(M(N,),G(W(,H),))),C(E,F(P,Z(,K(Y,)))))";
	CreateBTNode(root,binaryTreeBracketNotationString);
}

//递归销毁二叉树
void DestroyBT(BTNode * & node)
{
	if (!node)
		return;
	else
	{
		DestroyBT(node->lchild);
		DestroyBT(node->rchild);
		delete node;
		node = nullptr;
	}
}
Painter::Binary_Tree::~Binary_Tree(){DestroyBT(root);}



#include <QPen>
#include <QPainter>
void Painter::Binary_Tree::drawNode(BTNode * node,QPainter & painter,QPoint dataCircleCenter)
{
	static QPoint offsetPoint{20,20};
	// static QPen whitePen{Qt::white,5};
	QRect rect = QRect(dataCircleCenter - offsetPoint,dataCircleCenter + offsetPoint);

	if(node->lchild)
	{
		painter.drawLine(rect.center(),dataCircleCenter + QPoint(-60,60));
		drawNode(node->lchild,painter,dataCircleCenter + QPoint(-60,60));
	}

	if(node->rchild)
	{
		painter.drawLine(rect.center(),dataCircleCenter + QPoint(60,60));
		drawNode(node->rchild,painter,dataCircleCenter + QPoint(60,60));
	}

	painter.save();
	painter.setBrush(Qt::gray);
	painter.setPen({Qt::white,5});
	painter.drawEllipse(rect);
	painter.setPen(QPen(Qt::black,5));
	painter.drawText(rect,Qt::AlignCenter,node->data);
	painter.restore();
}



void Painter::Binary_Tree::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	static QFont font{"Cascadia Code",18};
	// QPaintDevice
	// QPainter painter{view};
	painter->setFont(font);
	painter->setRenderHint(QPainter::Antialiasing,true);
	drawNode(root,*painter,QPoint(0,-200));
}
