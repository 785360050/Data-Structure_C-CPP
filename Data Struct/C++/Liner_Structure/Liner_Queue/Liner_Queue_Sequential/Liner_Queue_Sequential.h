#pragma once


#include <iostream>

#include "../Liner_Queue_ADT.h"


//#define full1	///用标记为判断队满
//#define full2	///用少存一个单位的元素判断队满

#ifdef full1
template<typename DataType>
struct Sequence_Queue:public Queue<DataType>
{///使用少存一个元素空间实现队列判断满
private:
	int front;
	int rear;
	int length;
	int maxsize;
	DataType* element;
public:///Redundancy
	Sequence_Queue()
	{
		front = rear = length = maxsize = 0;
		element = nullptr;
	}

public:
	//初始化队列
	void Queue_Init(int maxsize) override
	{//初始化为0
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		element = new DataType[maxsize + 1];
		memset(element, 0, sizeof(DataType) * (maxsize + 1) );
		this->maxsize = maxsize;
	}
	//销毁队列
	void Queue_Destroy() override
	{
		try
		{
			if (!element)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is not exsist" << std::endl;
			return;
		}
		delete[] element;
		element = nullptr;
	}
	//清空队列
	void Queue_Clear() override
	{
		//for (int i = 0; i < maxsize; i++)
		//	element[i] = 0;
		memset(element, 0, sizeof(DataType) * (maxsize + 1));
		length = front = rear = 0;
	}
	//判断是否队空
	bool Queue_CheckEmpty() override
	{
		if (length==0)
			return true;
		return false;
	}
	//返回队列长度(元素个数)
	int Queue_Length() override
	{
		return length;
	}
	//返回队头
	DataType Queue_GetHead() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		return element[front];
	}
	//显示整个队列信息
	void Queue_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:"<< " [" << length << '/' << maxsize << ']' << std::endl
			<< "[Front/Rear/Redundancy]: [" << front << '/' << rear << '/' << rear + maxsize << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < maxsize+1; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	//元素入队
	void Element_Enqueue(DataType element) override
	{
		try
		{
			if (Queue_CheckFull())
				throw 0;
			if (!this->element)
				throw 1;
		}
		catch (bool x)
		{
			if (x==1)
				std::cout << "SeqQueue is not exist" << std::endl;
			if (x == 0)
				std::cout << "Queue is Full" << std::endl;
			return;
		}
		this->element[rear] = element;
		rear = (rear + 1) % maxsize;
		length++;
	}
	//元素出队
	DataType Element_Dequeue() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return NULL;
		}
		DataType x = element[front];
		element[front] = 0;
		front = (front + 1) % Index(maxsize);
		length--;
		return x;
	}
private:
	bool Queue_CheckFull()
	{
		if ((rear + 1) % maxsize == front)
			return true;
		return false;
	}
	int Index(int x)
	{
		return x - 1;
	}
};
#endif // full1

#ifdef full2

template<typename DataType>
struct Sequence_Queue :public Queue<DataType>
{///使用少存一个元素空间实现队列判断满
private:
	int front; int rear;
	int length;	int maxsize;
	bool full;
	DataType* element;
public:
	Sequence_Queue()
	{
		front = rear = length = maxsize = full = 0;
		element = nullptr;
	}

public:
	//初始化队列
	void Queue_Init(int maxsize) override
	{//初始化为0
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		element = new DataType[maxsize];
		for (int i = 0; i < maxsize; i++)
			element[i] = 0;
		this->maxsize = maxsize;
	}
	//销毁队列
	void Queue_Destroy() override
	{
		try
		{
			if (!element)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is not exsist" << std::endl;
			return;
		}
		delete[] element;
		element = nullptr;
	}
	//清空队列
	void Queue_Clear() override
	{
		memset(element, 0, sizeof(DataType) * maxsize);
		length = front = rear = full = 0;
	}
	//判断是否队空
	bool Queue_CheckEmpty() override
	{
		if (full == true)
			return false;
		if (length > 0)
			return false;
		return true;
	}
	//返回队列长度(元素个数)
	int Queue_Length() override
	{
		return length;
	}
	//返回队头
	DataType Queue_GetHead() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		return element[front];
	}
	//显示整个队列信息
	void Queue_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]=" << "[" << length << '/' << maxsize << ']' << std::endl
			<< "[Front/Rear]=[" << front << '/' << rear << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	//元素入队
	void Element_Enqueue(DataType element) override
	{
		try
		{
			if (Queue_CheckFull())
				throw 0;
			if (!element)
				throw 1;
		}
		catch (bool x)
		{
			if (x == 1)
				std::cout << "SeqQueue is not exist" << std::endl;
			if (x == 0)
				std::cout << "Queue is Full" << std::endl;
			return;
		}
		this->element[rear] = element;
		rear = (rear + 1) % maxsize;
		length++;

		if (Queue_CheckFull())
			full = true;
	}
	//元素出队
	DataType Element_Dequeue() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return NULL;
		}
		DataType x = element[front];
		element[front] = 0;
		front = (front + 1) % maxsize;
		length--;
		
		if (!Queue_CheckFull())
			full = false;
		return x;
	}
private:
	bool Queue_CheckFull()
	{
		if (length == maxsize )
			return true;
		return false;
	}
	int Index(int x)
	{
		return x - 1;
	}
};

#endif // full2

template<typename DataType>
struct Sequence_Queue :public Queue<DataType>
{///使用少存一个元素空间实现队列判断满
protected:
	int front;
	int rear;
	int length;
	int maxsize;
	DataType* element;
protected:
	virtual bool Queue_CheckFull()
	{return (rear + 1) % (maxsize + 1) == front ? true : false; }
	int Index(int x) const
	{return x - 1;}
public:///Redundancy
	Sequence_Queue()
		:front{ 0 }, rear{ 0 }, length{ 0 }, maxsize{ 0 }, element{ nullptr } {};
	Sequence_Queue(int maxsize)
		:Sequence_Queue()
	{
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		element = new DataType[maxsize + 1]{};//初始化为0
		this->maxsize = maxsize;
	}
	virtual ~Sequence_Queue()
	{
		if (element)
		{
			delete[] element;
			element = nullptr;
			std::cout << "Sequence_Queue Destroyed" << std::endl;
		}
	}
public:
	//清空队列
	void Queue_Clear() override
	{
		//for (int i = 0; i < maxsize; i++)
		//	element[i] = 0;
		memset(element, 0, sizeof(DataType) * (maxsize));
		length = front = rear = 0;
	}
	//判断是否队空
	bool Queue_CheckEmpty() override
	{return length == 0 ? true : false;}
	//返回队列长度(元素个数)
	int Queue_Length() override
	{return length;}
	//返回队头
	DataType Queue_GetHead() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		return element[front];
	}
	//显示整个队列信息
	virtual void Queue_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:" << " [" << length << '/' << maxsize << ']' << std::endl
			<< "[Front/Rear/Redundancy]: [" << front << '/' << rear << '/' << rear + maxsize << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < maxsize + 1; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	//元素入队
	virtual void Element_Enqueue(DataType element) override
	{
		try
		{
			if (this->element==nullptr)
				throw std::exception("SeqQueue is not exist");
			if (Queue_CheckFull())
				throw std::exception("Enqueue Failed: Queue is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->element[rear] = element;
		rear = (rear + 1) % maxsize;
		length++;
	}
	//元素出队
	virtual DataType Element_Dequeue() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return NULL;
		}
		DataType x = element[front];
		element[front] = 0;
		front = (front + 1) % Index(maxsize);
		--length;
		return x;
	}

};


template<typename DataType>
struct Sequence_Queue_Tag :public Sequence_Queue<DataType>
{///使用少存一个元素空间实现队列判断满
private:
	bool full;
private:
	bool Queue_CheckFull() override final
	{return full;}
public:
	Sequence_Queue_Tag()
		:Sequence_Queue<DataType>(), full{false} {};
	Sequence_Queue_Tag(int maxsize)
		:Sequence_Queue<DataType>()
	{
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		this->element = new DataType[maxsize]{};//初始化为0
		this->maxsize = maxsize;
		full = false;
	}
	~Sequence_Queue_Tag() override
	{
		try
		{
			if (!this->element)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is not exsist" << std::endl;
			return;
		}
		delete[] this->element;
		this->element = nullptr;
		std::cout << "Sequence_Queue_Tag Destroyed" << std::endl;
	}
public:
	void Queue_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]=" << "[" << this->length << '/' << this->maxsize << ']' << std::endl
			<< "[Front/Rear]=[" << this->front << '/' << this->rear << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < this->maxsize; index++)
			std::cout << '[' << index << ':' << this->element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	void Element_Enqueue(DataType element) override
	{
		try
		{
			if (this->element == nullptr)
				throw std::exception("SeqQueue is not exist");
			if (Queue_CheckFull())
				throw std::exception("Enqueue Failed: Queue is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->element[this->rear] = element;
		this->rear = (this->rear + 1) % this->maxsize;
		this->length++;

		if (Queue_CheckFull())
			full = true;
	}
	DataType Element_Dequeue() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return NULL;
		}
		DataType x = this->element[this->front];
		this->element[this->front] = 0;
		this->front = (this->front + 1) % this->maxsize;
		this->length--;
		
		if (!Queue_CheckFull())
			full = false;
		return x;
	}
};




