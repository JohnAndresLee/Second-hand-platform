#pragma once
struct comlist
{
	char comid[7];
	comlist* next;
};

struct shopping
{
	char userid[7];
	comlist*com;
	shopping* next;
};

void shopcart_main(char userid[7], char comid[]);//���ﳵ���ܵ�������

void shopcart_write(shopping* head);//�����û����ﳵ��Ϣд���ļ�

shopping* shopcart_read();//���ļ��ж�ȡ���û����ﳵ��Ϣ
comlist*shopcart_noderead(char list[], comlist* head);

void shopcart_delete(char userid[], char comid[]);//����Ʒ�Ƴ����ﳵ

bool shopcart_display(char userid[]);//��ʾ���ﳵ�Ĺ���
