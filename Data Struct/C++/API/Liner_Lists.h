#pragma once

template <class DataType>
class SeqList
{
public:
	//������maxsize��Ԫ�ؿռ��˳������ر��׵�ַ
	//����Ԫ��ֵ��ʼ��Ϊ0
	SeqList();
	//��˳���List�ĵ�pos��λ���ϲ�������Ԫ��data
	void Insert(SeqList* List, int pos, DataType data);
	//ɾ������List��pos��λ���ϵ�Ԫ�أ�����Ԫ��ֵ
	DataType Delete(SeqList* List, int pos);
	//�޸�����List��pos��λ���ϵ�Ԫ��ֵΪdata
	void Update(SeqList* List, int pos, DataType data);
	//��ʾ˳���ListԪ�ؿռ��ϵ�����Ԫ��
	void Show(SeqList* List);
	//��������˳���
	~SeqList();

	int* data;	//Ԫ��ֵ
	int length;	//��ǰ��
	int MAXSIZE;//�������
};





void test()
{
	LinerLists_SequentialList<int> a;
	a.data
}