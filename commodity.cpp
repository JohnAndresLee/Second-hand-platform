#define _CRT_SECURE_NO_WARNINGS

#include "commodity.h"
#include<iostream>
#include<cstring>
#include<Windows.h>
#include"adminmainwindow.h"
#include"login.h"
#include<cstdlib>
#include<iomanip>
#include"sellerwindow.h"
#include<iomanip>
#include"buyerwindow.h"
#include"minus.h"
#include"shoppingcart.h"
#include"user.h"
#include"order.h"

using namespace std;

char list[201] = {'\0'};

void noderead(char*list, node_com* p)
{
	int len = strlen(list);
	for (int j = 0;;)
	{
		int temp = 0;
		while (list[j] != ',')
			p->com.comid[temp++] = list[j++];
		p->com.comid[temp] = '\0';
		++j;
		temp = 0;
		while (list[j] != ',')
			p->com.comname[temp++] = list[j++];
		++j;
		p->com.comname[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->com.price[temp++] = list[j++];
		++j;
		p->com.price[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->com.description[temp++] = list[j++];
		++j;
		p->com.description[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->com.sellerid[temp++] = list[j++];
		++j;
		p->com.sellerid[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->com.date[temp++] = list[j++];
		++j;
		p->com.date[temp] = '\0';
		temp = 0;
		char state[10] = { '\0' };
		while (j < len)
			state[temp++] = list[j++];
		if (state[1] == 'n')
			p->com.s = on_sale;
		else if (state[1] == 'f')
			p->com.s = off_shelf;
		else
			p->com.s = sold_out;
		break;
	}
	return;
}

node_com*commodityread()
{
	node_com* head = NULL;
	node_com* tail = NULL;
	FILE* fp = fopen("commodity.txt", "r");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	fscanf(fp, "%s", list);
	while (!feof(fp))
	{
		if (fscanf(fp, "%s", list) != EOF)
		{
			node_com* p = new node_com;
			if (head == NULL)
			{
				noderead(list, p);
				head = p;
			}
			else
			{
				noderead(list, p);
				tail->next = p;
			}
			p->next = NULL;
			tail = p;
		}
	}
	fclose(fp);
	return head;
}

void fcommodity::commoditywrite(node_com*head)
{
	node_com* p = head;
	FILE* fp = fopen("commodity.txt", "w");
	if(fp==NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n","商品ID","名称", "价格", "描述", "卖家ID", "发布日期", "商品状态");
	while (p != NULL)
	{
		fprintf(fp, "%s,%s,%s,%s,%s,%s,",p->com.comid,p->com.comname,p->com.price,p->com.description,p->com.sellerid,p->com.date);
		if (p->com.s == 0)
			fprintf(fp, "%s\n", "onsale");
		else if(p->com.s==1)
			fprintf(fp, "%s\n", "offshelf");
		else 
			fprintf(fp, "%s\n", "soldout");
		p = p->next;
	}
	fclose(fp);
}

bool fcommodity::commodity_search(char userid[])//根据卖家用户ID搜索
{
	node_com* head = commodityread();
	node_com* p = head;
	bool flag = false;
	cout << "====================================================================================" << endl;
	cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(16) << "上架时间"<< setw(14) << "商品状态" <<setw(20)<<"商品描述"<<endl;
	cout << "====================================================================================" << endl;
	while (p != NULL)
	{
		if (strcmp(p->com.sellerid, userid) == 0)
		{		
			cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(17) << p->com.date<<setw(14);
			if (p->com.s == 0)
				cout << "销售中" << left<<setw(20) << p->com.description << endl;
			else if (p->com.s == 1)
				cout << "已下架" << left<<setw(20) << p->com.description << endl;
			else if (p->com.s == 2)
				cout << "已售出" << left<<setw(20) << p->com.description<<endl;
			flag = true;
		}
		p =p->next;
	}
	if (!flag)
	{
		cout << "                             您暂未在本平台发布商品" << endl;
		cout << "====================================================================================" << endl;
		return false;
	}
	cout << "====================================================================================" << endl;
	return true;
}

void fcommodity::commodity_viewall()//查看所有商品
{
	node_com*head=commodityread();
	node_com* p = head;
	cout << endl << "************************************************************************************" << endl;
	cout << left <<setw(10)<< "ID" <<setw(14)<< "名称" << setw(14) << "价格" <<setw(16) << "上架时间" << setw(14) << "卖家ID" << setw(14)<< "商品状态"<<endl;
	cout << "************************************************************************************" << endl;
	if (p == NULL)
		cout << "                           用户暂时还未发布任何商品！"<<endl;
	while(p!=NULL)
	{
		cout<<left<<setw(10)<<p->com.comid <<setw(14)<< p->com.comname <<setw(14)<< p->com.price <<setw(16)<< p->com.date <<setw(14)<< p->com.sellerid <<" ";
		if (p->com.s == 0)
			cout << "销售中"<<endl;
		else if (p->com.s == 1)
			cout << "已下架"<<endl;
		else if (p->com.s == 2)
			cout << "已售出"<<endl;
		p = p->next;
	}
	cout<< "************************************************************************************" << endl;
	return;
}

bool fcommodity::commodity_buyerviewall(char userid[])//买家查看所有商品
{
	node_com* head = commodityread();
	node_com* p = head;
	cout << endl << "************************************************************************************" << endl;
	cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(16) << "上架时间" << setw(14) << "卖家ID" << endl;
	bool flag = false;
	while (p != NULL)
	{
		if (p->com.s == on_sale&&strcmp(p->com.sellerid,userid)!=0)
		{
			cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(16) << p->com.date << setw(14) << p->com.sellerid <<endl;
			flag = true;
		}
		p = p->next;
	}
	if (!flag)
	{
		cout << "				当前没有销售中商品！" << endl;
		cout << "************************************************************************************" << endl;
		return false;
	}
	cout << "************************************************************************************" << endl;
	return true;
}

bool fcommodity::commodity_query(int n,node_com*head,char userid[])//[拓展]根据一定条件查询商品//价格区间//价格排序
{
	if (n == 1)
	{
		node_com* newhead0 = NULL;
		node_com* newtail = NULL;
		while (head != NULL)
		{
			if (head->com.s == on_sale && strcmp(userid, head->com.sellerid) != 0)
			{
				node_com* p = new node_com;
				if (newhead0 == NULL)
				{
					strcpy(p->com.comid,head->com.comid);
					strcpy(p->com.comname, head->com.comname);
					strcpy(p->com.date, head->com.date);
					strcpy(p->com.description, head->com.description);
					strcpy(p->com.price, head->com.price);
					p->com.s=head->com.s;
					strcpy(p->com.sellerid, head->com.sellerid);
					p->next = newhead0;
					newhead0 = p;
				}
				else
				{
					node_com* newhead = newhead0;
					strcpy(p->com.comid, head->com.comid);
					strcpy(p->com.comname, head->com.comname);
					strcpy(p->com.date, head->com.date);
					strcpy(p->com.description, head->com.description);
					strcpy(p->com.price, head->com.price);
					p->com.s = head->com.s;
					strcpy(p->com.sellerid, head->com.sellerid);
					if (judge(p->com.price, newhead0->com.price))
					{
						p->next = newhead0;
						newhead0 = p;
					}
					else
					{
						node_com* pre = newhead;
						while (newhead != NULL)
						{
							if (judge(p->com.price, newhead->com.price))
							{
								pre->next = p;
								p->next = newhead;
								break;
							}
							else
							{
								pre = newhead;
								newhead = newhead->next;
							}
						}
						if (pre->next == NULL)
						{
							pre->next = p;
							p->next = NULL;
						}
					}
				}
			}
			head = head->next;
		}
		node_com* p = newhead0;
		cout << endl << "************************************************************************************" << endl;
		cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(16) << "上架时间" << setw(14) << "卖家ID" << endl;
		while (p!= NULL)
		{
			cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(16) << p->com.date << setw(14) << p->com.sellerid <<endl;
			p = p->next;
		}
		cout << "************************************************************************************" << endl;
		return true;
	}
	else if (n == 2)
	{
		char down[5];
		char up[5];
		cout <<endl<<"请输入您需要设定的价格下限：";
		cin >> down;
		cout <<endl<< "请输入您需要设定的价格上限：";
		cin >> up;
		if (judge(up, down))
		{
			cout << endl << "您所要查询的商品信息如下：";
			cout << endl << "************************************************************************************" << endl;
			cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(16) << "上架时间" << setw(14) << "卖家ID" << endl;
			bool flag = false;
			while (head != NULL)
			{
				if (judge(up, head->com.price) && judge(head->com.price, down) && head->com.s == on_sale && strcmp(userid, head->com.sellerid) != 0)
				{
					flag = true;
					cout << left << setw(10) << head->com.comid << setw(14) << head->com.comname << setw(14) << head->com.price << setw(16) << head->com.date << setw(14) << head->com.sellerid << endl;
				}
				head = head->next;
			}
			if (!flag)
				cout << "				   没有符合您搜索条件的商品！" << endl;
			cout << "************************************************************************************" << endl;
			return flag;
		}
		else
		{
			cout << endl << "上下界输入有误！请重新进行操作"<<endl;
			return false;
		}
	}
	else if (n == 3)
	{
		node_com* newhead0 = NULL;
		node_com* newtail = NULL;
		while (head != NULL)
		{
			if (head->com.s == on_sale && strcmp(userid, head->com.sellerid) != 0)
			{
				node_com* p = new node_com;
				if (newhead0 == NULL)
				{
					strcpy(p->com.comid, head->com.comid);
					strcpy(p->com.comname, head->com.comname);
					strcpy(p->com.date, head->com.date);
					strcpy(p->com.description, head->com.description);
					strcpy(p->com.price, head->com.price);
					p->com.s = head->com.s;
					strcpy(p->com.sellerid, head->com.sellerid);
					p->next = newhead0;
					newhead0 = p;
				}
				else
				{
					node_com* newhead = newhead0;
					strcpy(p->com.comid, head->com.comid);
					strcpy(p->com.comname, head->com.comname);
					strcpy(p->com.date, head->com.date);
					strcpy(p->com.description, head->com.description);
					strcpy(p->com.price, head->com.price);
					p->com.s = head->com.s;
					strcpy(p->com.sellerid, head->com.sellerid);
					if (judge(newhead0->com.price,p->com.price))
					{
						p->next = newhead0;
						newhead0 = p;
					}
					else
					{
						node_com* pre = newhead;
						while (newhead != NULL)
						{
							if (judge(newhead->com.price,p->com.price))
							{
								pre->next = p;
								p->next = newhead;
								break;
							}
							else
							{
								pre = newhead;
								newhead = newhead->next;
							}
						}
						if (pre->next == NULL)
						{
							pre->next = p;
							p->next = NULL;
						}
					}
				}
			}
			head = head->next;
		}
		node_com* p = newhead0;
		cout << endl << "************************************************************************************" << endl;
		cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(16) << "上架时间" << setw(14) << "卖家ID" << endl;
		while (p != NULL)
		{
			cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(16) << p->com.date << setw(14) << p->com.sellerid << endl;
			p = p->next;
		}
		cout << "************************************************************************************" << endl;
		return true;
	}
	return true;
}

void fcommodity::commodity_takeoff(const char* comid,int k,char userid[])//下架商品
{
	node_com* head = commodityread();
	node_com* p = commodity_view(comid, head, k, userid);
		if (p == NULL)
		{
			if (k == 1)
				commodityreturn();
			else
				seller_return(userid);
		}
		else
		{
			if (p->com.s == off_shelf)
			{
				cout << endl << "该商品已下架！无法执行下架操作" << endl;
				if (k == 1)
					commodityreturn();
				else
					seller_return(userid);
			}
			else if (p->com.s == sold_out)
			{
				cout << endl << "该商品已售出！无法执行下架操作" << endl;
				if (k == 1)
					commodityreturn();
				else
					seller_return(userid);
			}
			else
			{
				cout << endl << "您确定要下架该商品吗？";
				cout << endl << "请选择（y/n）：";
				char choose[20];
				cin >> choose;
				bool  flag = true;
				while (flag)
				{
					if (strcmp(choose, "y") == 0)
					{
						p->com.s = off_shelf;
						cout << endl << "下架成功！" << endl;
						commoditywrite(head);
						structdeletecom(head);
						flag = false;
						if (k == 1)
							commodityreturn();
						else
							seller_return(userid);
					}
					else if (strcmp(choose, "n") == 0)
					{
						if (k == 1)
							commodityreturn();
						else
							seller_return(userid);
					}
					else
					{
						cout << endl << "请输入正确的格式!";
						commodity_takeoff(comid, k, userid);
					}
				}
				return;
			}
		}
	return;
}

node_com*fcommodity::commodity_view(const char* comid,node_com*head,int i,char userid[])//查询单个商品
{
	node_com* p = head;
	while(p!=NULL)
	{
		if (strcmp(comid, p->com.comid) == 0)
		{
			if (i == 2 && strcmp(userid, p->com.sellerid) != 0)
			{
				cout << endl << "************************************************************************************" << endl;
						cout << "                          不能对其他用户发布的商品进行该操作！";
				cout << endl << "************************************************************************************" << endl;
				return NULL;
			}
			else
			{
				cout << endl << "************************************************************************************" << endl;
				cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(16) << "上架时间" << setw(14) << "卖家ID" << setw(14) << "商品状态" << endl;
				cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(16) << p->com.date << setw(14) << p->com.sellerid << " ";
				if (p->com.s == 0)
					cout << "销售中" << endl;
				else if (p->com.s == 1)
					cout << "已下架" << endl;
				else if (p->com.s == 2)
					cout << "已售出" << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              没有找到您想搜索的商品！";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
}

node_com* fcommodity::commodity_buyersearchid(const char* comid, node_com* head,char userid[])//查询单个商品
{
	node_com* p = head;
	while (p != NULL)
	{
		if ((strcmp(comid,p->com.comid)==0||strcmp(comid,p->com.comname)==0)&&p->com.s==on_sale)
		{
			if (strcmp(userid, p->com.sellerid) != 0)
			{
				cout << endl << "************************************************************************************" << endl;
				cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(14) << "卖家ID" << endl;
				cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(14) << p->com.sellerid << endl;
				cout << endl << "商品描述：";
				cout << p->com.description << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
			else
			{
				cout <<endl<< "不能在买家界面搜索自己发布的商品哦！具体商品信息可前往卖家界面查看"<<endl;
				return NULL;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              没有找到您想搜索的商品！";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
	
}

bool buyervaguesearch(const char* comname, node_com* head, char userid[])
{
	node_com* p = head;
	bool flag = false;
	while (p != NULL)
	{
		if (p->com.s == on_sale && strcmp(userid, p->com.sellerid) != 0)
		{
			int sim = 0;
			int len = strlen(comname);
			int lencom = strlen(p->com.comname);
			for (int i = 0; i < len; ++i)
			{
				for (int j = 0; j < lencom; ++j)
				{
					if (comname[i] == p->com.comname[j])
					{
						sim++;
						break;
					}
					else if (comname[i] >= 65 && comname[i] <= 90 && p->com.comname[j] == comname[i] + 32)
					{
						sim++;
						break;
					}
					else if (comname[i] >= 97 && comname[i] <= 122 && p->com.comname[j] == comname[i] - 32)
					{
						sim++;
						break;
					}
				}
			}
			if (sim == len)
			{
				flag = true;
				cout << endl << "************************************************************************************" << endl;
				cout << left << setw(10) << "ID" << setw(14) << "名称" << setw(14) << "价格" << setw(14) << "卖家ID" << endl;
				cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(14) << p->com.sellerid << endl;
				cout << endl << "商品描述：";
				cout << p->com.description << endl;
				cout << "************************************************************************************" << endl;
			}
		}
		p = p->next;
	}
	if (!flag)
	{
		cout << endl << "************************************************************************************" << endl;
		cout << "                              没有找到您想搜索的相似商品！";
		cout << endl << "************************************************************************************" << endl;
		return false;
	}
	return true;
}

node_com* fcommodity::commodity_buyerview(const char* comid, node_com * head, char userid[])//查询单个商品
{
	node_com* p = head;
	while (p != NULL)
	{
		if (strcmp(comid, p->com.comid) == 0)
		{
			if (strcmp(userid, p->com.sellerid) == 0)
			{
				cout << endl<< "无法在买家操作界面查询自己的商品信息！"<<endl;
				return p;
			}
			else if (p->com.s == 0)
			{
				cout << endl << "************************************************************************************" << endl;
				cout << "名称：" << p->com.comname << endl << "描述：" << p->com.description << endl << "上架时间：" << p->com.date << endl << "卖家ID：" << p->com.sellerid << endl << "商品状态：";
				cout << "销售中" << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              没有找到您想搜索的商品！";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
}

void fcommodity::commodity_infochange(const char* comid,char userid[])//修改商品信息
{
	node_com* head = commodityread();
	node_com* p = commodity_view(comid, head,2,userid);
	if (p==NULL)
	{
		seller_return(userid);
		return;
	}
	cout << "请输入修改商品属性（1.价格 2.描述）：";
	int n;
	cin >> n;
	if (n == 1)
	{
		cout << "请输入修改后的价格：";
		char price1[10];
		cin >> price1;
		if (price1[0] == '-')
		{
			cout << "商品价格不能为负！"<<endl;
			commodity_infochange(comid,userid);
		}
		cout << endl << "请确认修改后的商品信息！" << endl;
		cout <<endl<<"************************************************************************************" << endl;
		cout << "商品ID：" << p->com.comid << endl << "商品名称：" << p->com.comname << endl << "商品价格：" << price1 << endl << "商品描述：" << p->com.description << endl;
		cout<< "************************************************************************************" << endl;
		commodity_infochangeprice(comid, userid, p, head, price1);
	}
	else if (n == 2)
	{
		cout << "请输入修改后的商品描述：";
		char describe[101] = {'\0'};
		cin >> describe;
		cout << endl << "请确认修改后的商品信息！" << endl;
		cout << endl << "************************************************************************************" << endl;
		cout << "商品ID：" << p->com.comid << endl << "商品名称：" << p->com.comname << endl << "商品价格：" <<p->com.price << endl << "商品描述：" <<describe<< endl;
		cout << "************************************************************************************" << endl;
		commodity_infochangedescribe(comid, userid, p, head, describe);
	}
	else
	{
		cout << endl << "没有对应的商品属性，修改失败！"<<endl;
		seller_return(userid);
	}
	return;
}

void fcommodity::commodity_infochangeprice(const char* comid, char userid[],node_com*p,node_com*head,char price1[])
{
	cout << "确认修改？（y/n）：";
	char choose[20];
	cin >> choose;
	if (strcmp(choose, "y") == 0)
	{
		int len = strlen(price1);
		int i = 0;
		for (; i < len; i++)
			p->com.price[i] = price1[i];
		p->com.price[i] = '\0';
		commoditywrite(head);
		structdeletecom(head);
		cout << endl << "修改成功！" << endl;
		seller_return(userid);
	}
	else if (strcmp(choose, "n") == 0)
		seller_return(userid);
	else
	{
		cout << endl << "请以正确的格式输入！" << endl;
		commodity_infochangeprice(comid, userid, p, head, price1);
	}
	return;
}

void fcommodity::commodity_infochangedescribe(const char* comid, char userid[], node_com* p, node_com* head, char describe[])
{
	cout << "确认修改？（y/n）：";
	char choose[20];
	cin >> choose;
	if (strcmp(choose, "y") == 0)
	{
		int len = strlen(describe);
		int i = 0;
		for (; i < len; i++)
			p->com.description[i] = describe[i];
		p->com.description[i] = '\0';
		commoditywrite(head);
		structdeletecom(head);
		cout << endl << "修改成功！" << endl;
		seller_return(userid);
	}
	else if (strcmp(choose, "n") == 0)
		seller_return(userid);
	else
	{
		cout << endl << "请以正确的格式输入！" << endl;
		commodity_infochangedescribe(comid, userid, p, head, describe);
	}
	return;
}

void fcommodity::commodtity_lauch(char userid[7])//发布商品
{
	char name[11];
	cout << endl << "请输入商品名称：";
	cin >> name;
	cout << endl << "请输入商品金额：";
	char price[10];
	cin >> price;
	if (price[0] == '-')
	{
		cout << "商品金额不能为负数！"<<endl;
		seller_return(userid);
	}
	char describe[101];
	cout << endl << "请输入商品描述：";
	cin >> describe;
	cout << endl << endl << "请确认发布商品的信息无误！";
	cout <<endl<<"************************************************************************************" << endl;
	cout << "商品名称：" << name << endl << "商品金额：" << price << endl << "商品描述：" << describe << endl;
	cout<< "************************************************************************************" << endl;
	lauchconfirm(userid,name,price,describe);
	return;
}
void fcommodity::lauchconfirm(char userid[7],char name[],char price[],char describe[])
{
	cout << endl << "您确认要发布该商品吗（y/n）：";
	char choose[20];
	cin >> choose;
	if (strcmp(choose, "y") == 0)
	{
		node_com* head = commodityread();
		char comid[7] = { '\0' };
		labelnumber(comid,head);

		time_t rawtime;
		struct tm* ptminfo;
		time(&rawtime);
		ptminfo = localtime(&rawtime);

		FILE* fp = fopen("commodity.txt", "a+");
		if (fp == NULL)
		{
			printf("Open Failed\n");
			exit(-1);
		}
		if (head == NULL)
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", "商品ID","名称","价格","描述","卖家ID","上架时间","商品状态");
		fprintf(fp, "%s,%s,%s,%s,%s,%02d-%02d-%02d,%s\n",comid,name,price,describe,userid,ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,"onsale");
		fclose(fp);
		cout << endl << "发布商品成功！" << endl;
	}
	else if (strcmp(choose, "n") == 0)
		seller_return(userid);
	else
	{
		cout << endl << "请以正确的格式输入!";
		lauchconfirm(userid,name, price, describe);
	}
	return;
}
void fcommodity::labelnumber(char comid[7], node_com* head)//为新商品新建ID
{
	if (head == NULL)
	{
		comid[0] = 'M';
		for (int w = 1; w <= 4; ++w)
			comid[w] = '0';
		comid[5] = '1';
		comid[6] = '\0';
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		int i = 5;
		while (head->com.comid[i]== '9')
		{
			comid[i] = '0';
			i--;
		}
		comid[i] = head->com.comid[i] + 1;
		for (int k = i - 1; k >= 0; --k)
			comid[k] = head->com.comid[k];
	}
	return;
}

void fcommodity::commoditydetail(char userid[],char comid[],node_com*find)
{
	if (find == NULL || strcmp(userid, find->com.sellerid) == 0)
		buyer_return(userid);
	else
	{
		if (find != NULL)
		{
			cout << endl << "1.查看卖家信息 2.加入购物车 3.取消";
			cout << endl << "输入操作：";
			char fc[10];
			cin >> fc;
			if (strcmp(fc, "1") == 0)
			{
				cout << "1.查看卖家个人信息 2.查看卖家交易信息 3.取消";
				cout <<endl<< "输入操作：";
				char v[10];
				cin >> v;
				if (strcmp(v, "1") == 0)
				{
					fuser* ffuser = new fuser();
					node_user* p = ffuser->user_inforead();
					while (p != NULL)
					{
						if (p->user.flag)
						{
							if (strcmp(userid, p->user.userid) == 0)
							{
								cout << endl << "************************************************************************************" << endl;
								cout << "用户ID：" << p->user.userid << endl << "用户名：" << p->user.username << endl << "联系方式：" << p->user.contactinfo << endl << "地址：" << p->user.address << endl;
								cout << "************************************************************************************" << endl;
							}
						}
						p = p->next;
					}
					cout << endl << "1.加入购物车 2.返回上级界面 3.返回主界面";
					cout << endl << "输入操作：";
					char v1[10];
					cin >> v1;
					if (strcmp(v1, "1") == 0)
						shopcart_main(userid, comid);
					else if (strcmp(v1, "2") == 0)
						commoditydetail(userid, comid, find);
					else if (strcmp(v1, "3") == 0)
						buyer_return(userid);
				}
				else if (strcmp(v, "2") == 0)
				{
					node_order* orderhead = orderread();
					bool flag = false;
					while (orderhead != NULL)
					{
						if (strcmp(orderhead->order.sellerid, find->com.sellerid) == 0)
						{
							cout << endl << "************************************************************************************";
							cout << endl << left << setw(10) << "订单ID" << setw(10) << "商品ID" << setw(14) << "交易金额" << setw(14) << "交易时间" << setw(10) << "卖家ID";
							cout << endl << left << setw(10) << orderhead->order.orderid << setw(10) << orderhead->order.comid << setw(14) << orderhead->order.trademoney << setw(14) << orderhead->order.time << setw(10) << orderhead->order.sellerid;
							cout << endl << "商品评价：" << orderhead->order.buyerevaluation << endl;
							cout << "买家满意度（满分五分）：" << orderhead->order.sellerscore << endl;
							cout << "************************************************************************************";
							flag = true;
						}
						orderhead = orderhead->next;
					}
					if (!flag)
					{
						cout << endl << "************************************************************************************" << endl;
						cout << "                           该用户暂无卖出商品的订单！";
						cout << endl << "************************************************************************************" << endl;
					}
					cout << endl << "1.加入购物车 2.返回上级界面 3.返回主界面";
					cout << endl << "输入操作：";
					char v1[10];
					cin >> v1;
					if (strcmp(v1, "1") == 0)
						shopcart_main(userid, comid);
					else if (strcmp(v1, "2") == 0)
						commoditydetail(userid, comid, find);
					else if (strcmp(v1, "3") == 0)
						buyer_return(userid);
				}
				else if (strcmp(v, "3") == 0)
					buyer_return(userid);
				else
				{
					cout << endl << "  无效操作！" << endl;
					commoditydetail(userid,comid,find);
				}
			}
			else if (strcmp(fc, "2") == 0)
				shopcart_main(userid, comid);
			else if (strcmp(fc, "3") == 0)
				buyer_return(userid);
			else
			{
				cout << endl << "   无效操作！" << endl;
				buyer_return(userid);
			}
		}
		else
			buyer_return(userid);
	}
	return;
}