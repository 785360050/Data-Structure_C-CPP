#pragma once

typedef int DataType;

struct SequentialList
{
	DataType* data;
	int length;	//��ǰ��
	int maxsize;
};
typedef struct SequentialList SeqList;
//������maxsize��Ԫ�ؿռ��˳������ر��׵�ַ
//����Ԫ��ֵ��ʼ��Ϊ0
SeqList* SeqList_Init(int maxsize);	
//��������˳���
void SeqList_Destroy(SeqList* List);	
//������˳���List��pos��λ�ò���Ԫ��ֵdata
void SeqList_Insert(SeqList* List, int pos, DataType data);	
//ɾ������List��pos��λ���ϵ�Ԫ�أ�����Ԫ��ֵ
DataType SeqList_Delete(SeqList* List, int pos);
//�޸�����List��pos��λ���ϵ�Ԫ��ֵΪdata
void SeqList_Update(SeqList* List, int pos, DataType data);
//��ʾ˳���ListԪ�ؿռ��ϵ�����Ԫ��
void SeqList_Show(SeqList* List);







