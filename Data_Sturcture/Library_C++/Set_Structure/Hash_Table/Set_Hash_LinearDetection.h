#pragma once





//线性探测法解决冲突
template <typename DataType>
class HashList
{
private:
	DataType* data;
	int length;
	int maxsize;
public:
	HashList(int maxsize = 20)
		:length{ 0 }, maxsize{ maxsize }, data{ new DataType[maxsize]{} } {};
	HashList()
	{
		if(data)
			delete[] data;
	}

private:

public:
	//哈希函数：除留余数法
	int HashFunction_Remain(int size, int key) const
	{
		return key % size;
	}

	//冲突函数：开放定址法-线性探测法
	int CollisionFuction_OpenAddressing_LinerProbing(int index, int key) const
	{
		return (index + 1) % maxsize;
	}

	void HashList_Insert(int key)
	{
		try
		{
			if (length >= maxsize)
				throw std::runtime_error("Insert Failed: Hash List is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		int index = HashFunction_Remain(maxsize, key);
		while (data[index] != NULL)
		{
			index = CollisionFuction_OpenAddressing_LinerProbing(index, key);
		}
		data[index] = key;
		length++;
	}

	int HashList_Locate(int key)
	{
		int index = HashFunction_Remain(maxsize, key);
		int t = 1;
		while (data[index] != key && t < length)
		{
			index = CollisionFuction_OpenAddressing_LinerProbing(index, key);
			t++;
		}
		return (data[index] == key) ? index : NULL;
	}

	void HashList_Show()
	{
		std::cout
			<< "Length:" << length << std::endl
			<< "Maxsize:" << maxsize << std::endl;
		for (int i = 0; i < maxsize; i++)
			std::cout << data[i] << ' ';
		std::cout << std::endl;
	}

};


//void HashList_Init(HashList* list, int maxsize);
//
////哈希函数：除留余数法
//int HashFunction_Remain(int size, int key);
//
////冲突函数：开放定址法-线性探测法
//int CollisionFuction_OpenAddressing_LinerProbing(const HashList* list, int index, int key);
//
//void HashList_Insert(HashList* list, int key);
//
////查找元素key的下标
//int HashList_Locate(const HashList* const list, int key);
//
//void HashList_Destroy(HashList* list);
//
//void HashList_Show(const HashList* const list);