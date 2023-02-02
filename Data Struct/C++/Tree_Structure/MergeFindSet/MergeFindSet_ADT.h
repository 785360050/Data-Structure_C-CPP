#pragma once








template <typename DataType>
class MergeFindSet_ADT
{
protected:
	virtual ~MergeFindSet_ADT() = default;
public:
	//判断查并集set中，元素x,y是否再同一个集合中
	virtual bool Find(DataType x, DataType y) = 0;
	//合并查并集set中元素x,y到同一集合中(x加入y的组)
	virtual void Merge(DataType x, DataType y) = 0;
	//显示整个查并集
	virtual void Show() = 0;
};