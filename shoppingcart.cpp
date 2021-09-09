#define _CRT_SECURE_NO_WARNINGS

#include "shoppingcart.h"
#include<iostream>
#include"user.h"
#include"commodity.h"
#include"buyerwindow.h"

using namespace std;

comlist*shopcart_noderead(char list[],comlist*head)
{
	int num = 0;
	int i = 7;
	while (list[i] != '\0')
	{
		comlist* p = new comlist;
		while(num<=5)
			p->comid[num++] = list[i++];
		p->comid[6] = '\0';
		i++;
		if (head == NULL)
		{
			head = p;
			p->next = NULL;
		}
		else
		{
			p->next = head;
			head = p;
		}
		num = 0;
	}
	return head;
}

shopping* shopcart_read()
{
	shopping* shophead = NULL;
	shopping* shoptail = NULL;
	FILE* fp = fopen("shoppingcart.txt", "r");
	char list[200] = {'\0'};
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		if (fscanf(fp, "%s", list) != EOF)
		{
			if (shophead == NULL)
			{
				shopping* p = new shopping;
				comlist* comhead = NULL;
				for (int i = 0; i <= 5; ++i)
					p->userid[i] = list[i];
				p->userid[6] = '\0';
				comhead=shopcart_noderead(list, comhead);
				p->com = comhead;
				shophead = p;
				p->next = NULL;
				shoptail = p;
			}
			else
			{
				shopping* p = new shopping;
				comlist* comhead = NULL;
				 for (int i = 0; i <= 5; ++i)
					p->userid[i] = list[i];
				p->userid[6] = '\0';
				comhead=shopcart_noderead(list, comhead);
				p->com = comhead;
				shoptail->next = p;
				p->next = NULL;
				shoptail = p;
			}
		}
	}
	fclose(fp);
	return shophead;
}

void shopcart_write(shopping*head)
{
	shopping* p = head;
	FILE* fp = fopen("shoppingcart.txt", "w");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	while (head != NULL)
	{
		if (head->com != NULL)
		{
			fprintf(fp, "%s", head->userid);
			while (head->com != NULL)
			{
				fprintf(fp, ",%s", head->com->comid);
				head->com = head->com->next;
			}
			fputc('\n', fp);
		}
		head = head->next;
	}
	fclose(fp);
	return;
}

void shopcart_main(char userid[7],char comid[])//商品购物车//下架或卖出后提示//显示购物车//购物车中直接购买
{
	cout << endl << "加入购物车（y/n）：";
	char choose[20];
	cin >> choose;
	bool flag = false;
	if (strcmp(choose, "y") == 0)
	{
		shopping*head=shopcart_read();
		shopping* a = head;
		while (head != NULL)
		{
			if (strcmp(head->userid, userid) == 0)
			{
				flag = true;
				shopping* temp = head;
				comlist* precom = head->com;
				bool exist = false;
				while (temp->com!= NULL)
				{
					if (strcmp(temp->com->comid, comid) == 0)
					{
						exist = true;
						cout << endl << "该商品已在购物车中！";
						buyer_return(userid);
					}
					temp->com = temp->com->next;
				}
				if (!exist)
				{
					comlist* newcom = new comlist;
					for (int i = 0; i <= 5; ++i)
						newcom->comid[i] = comid[i];
					newcom->comid[6] = '\0';
					newcom->next = precom;
					head->com = newcom;
				}
				break;
			}
			head = head->next;
		}
		if (!flag)
		{
			shopping* p = new shopping;
			comlist* c = new comlist;
			for (int i = 0; i <= 5; ++i)
			{
				p->userid[i] = userid[i];
				c->comid[i] = comid[i];
			}
			p->userid[6] = '\0';
			c->comid[6] = '\0';
			p->com = c;
			p->com->next = NULL;
			p->next = a;
			a = p;
		}
		shopcart_write(a);
		cout << "添加成功！";
		buyer_return(userid);
	}
	else if (strcmp(choose, "n") == 0)
		buyer_return(userid);
	else
	{
		cout << endl << "请以正确的格式输入!";
		shopcart_main(userid,comid);
	}
	return;
}

bool shopcart_display(char userid[])//显示购物车
{
	shopping* head = shopcart_read();
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->userid, userid) == 0)
		{
			node_com* comhead = commodityread();
			node_com* comheadorigin = comhead;
			comlist* p = head->com;
			while (p != NULL)
			{
				while (comhead != NULL)
				{
					if (strcmp(comhead->com.comid, p->comid) == 0)
					{
						if (comhead->com.s == 0)
						{
							flag = true;
							cout << endl << "************************************************************************************" << endl;
							cout << "商品ID：" << comhead->com.comid << endl << "名称：" << comhead->com.comname << endl << "描述：" << comhead->com.description << endl << "上架时间：" << comhead->com.date << endl << "卖家ID：" << comhead->com.sellerid << endl << "商品状态：";
							cout << "销售中" << endl;
							cout << "************************************************************************************" << endl;
						}
						else
						{
							shopcart_delete(userid, p->comid);
						}
					}
					comhead = comhead->next;
				}
				p = p->next;
				comhead = comheadorigin;
			}
			if (!flag)
				return false;
			else
				return true;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "购物车为空，快去添加心仪的商品吧！" << endl;
		return false;
	}
	return true;
}

void shopcart_delete(char userid[],char comid[])
{
		shopping* head = shopcart_read();
		shopping* origin = head;
		bool flag = false;
		while (head != NULL)
		{
			if (strcmp(head->userid, userid) == 0)
			{
				comlist* p = head->com;
				comlist* pre = p;
				if (strcmp(p->comid, comid) == 0 && p->next == NULL)
				{
					flag = true;
					delete p;
					head->com = NULL;
					shopcart_write(origin);
					cout << endl << "商品"<<comid<<"已被移除出购物车！" << endl;
				}
				else
				{
					while (p != NULL)
					{
						if (strcmp(p->comid, comid) == 0)
						{
							flag = true;
							if (p==head->com)
							{
								head->com = p->next;
								delete p;
								shopcart_write(origin);
								cout << endl << "该商品已被移除出购物车！" << endl;
							}
							else
							{
								pre->next = p->next;
								delete p;
								shopcart_write(origin);
								cout << endl << "该商品已被移除出购物车！" << endl;
							}
							break;
						}
						pre = p;
						p = p->next;
					}
				}
				if (!flag)
					cout << endl << "无效操作：该商品不在您的购物车中！" << endl;
			}
			head = head->next;
		}
	
	return;
}
