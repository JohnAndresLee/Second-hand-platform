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
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n","????ID","????", "????", "????", "????ID", "????????", "????????");
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

bool fcommodity::commodity_search(char userid[])//????????????ID????
{
	node_com* head = commodityread();
	node_com* p = head;
	bool flag = false;
	cout << "====================================================================================" << endl;
	cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(16) << "????????"<< setw(14) << "????????" <<setw(20)<<"????????"<<endl;
	cout << "====================================================================================" << endl;
	while (p != NULL)
	{
		if (strcmp(p->com.sellerid, userid) == 0)
		{		
			cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(17) << p->com.date<<setw(14);
			if (p->com.s == 0)
				cout << "??????" << left<<setw(20) << p->com.description << endl;
			else if (p->com.s == 1)
				cout << "??????" << left<<setw(20) << p->com.description << endl;
			else if (p->com.s == 2)
				cout << "??????" << left<<setw(20) << p->com.description<<endl;
			flag = true;
		}
		p =p->next;
	}
	if (!flag)
	{
		cout << "                             ??????????????????????" << endl;
		cout << "====================================================================================" << endl;
		return false;
	}
	cout << "====================================================================================" << endl;
	return true;
}

void fcommodity::commodity_viewall()//????????????
{
	node_com*head=commodityread();
	node_com* p = head;
	cout << endl << "************************************************************************************" << endl;
	cout << left <<setw(10)<< "ID" <<setw(14)<< "????" << setw(14) << "????" <<setw(16) << "????????" << setw(14) << "????ID" << setw(14)<< "????????"<<endl;
	cout << "************************************************************************************" << endl;
	if (p == NULL)
		cout << "                           ??????????????????????????"<<endl;
	while(p!=NULL)
	{
		cout<<left<<setw(10)<<p->com.comid <<setw(14)<< p->com.comname <<setw(14)<< p->com.price <<setw(16)<< p->com.date <<setw(14)<< p->com.sellerid <<" ";
		if (p->com.s == 0)
			cout << "??????"<<endl;
		else if (p->com.s == 1)
			cout << "??????"<<endl;
		else if (p->com.s == 2)
			cout << "??????"<<endl;
		p = p->next;
	}
	cout<< "************************************************************************************" << endl;
	return;
}

bool fcommodity::commodity_buyerviewall(char userid[])//????????????????
{
	node_com* head = commodityread();
	node_com* p = head;
	cout << endl << "************************************************************************************" << endl;
	cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(16) << "????????" << setw(14) << "????ID" << endl;
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
		cout << "				????????????????????" << endl;
		cout << "************************************************************************************" << endl;
		return false;
	}
	cout << "************************************************************************************" << endl;
	return true;
}

bool fcommodity::commodity_query(int n,node_com*head,char userid[])//[????]????????????????????//????????//????????
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
		cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(16) << "????????" << setw(14) << "????ID" << endl;
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
		cout <<endl<<"????????????????????????????";
		cin >> down;
		cout <<endl<< "????????????????????????????";
		cin >> up;
		if (judge(up, down))
		{
			cout << endl << "??????????????????????????";
			cout << endl << "************************************************************************************" << endl;
			cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(16) << "????????" << setw(14) << "????ID" << endl;
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
				cout << "				   ??????????????????????????" << endl;
			cout << "************************************************************************************" << endl;
			return flag;
		}
		else
		{
			cout << endl << "??????????????????????????????"<<endl;
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
		cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(16) << "????????" << setw(14) << "????ID" << endl;
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

void fcommodity::commodity_takeoff(const char* comid,int k,char userid[])//????????
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
				cout << endl << "??????????????????????????????" << endl;
				if (k == 1)
					commodityreturn();
				else
					seller_return(userid);
			}
			else if (p->com.s == sold_out)
			{
				cout << endl << "??????????????????????????????" << endl;
				if (k == 1)
					commodityreturn();
				else
					seller_return(userid);
			}
			else
			{
				cout << endl << "??????????????????????";
				cout << endl << "????????y/n????";
				char choose[20];
				cin >> choose;
				bool  flag = true;
				while (flag)
				{
					if (strcmp(choose, "y") == 0)
					{
						p->com.s = off_shelf;
						cout << endl << "??????????" << endl;
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
						cout << endl << "????????????????!";
						commodity_takeoff(comid, k, userid);
					}
				}
				return;
			}
		}
	return;
}

node_com*fcommodity::commodity_view(const char* comid,node_com*head,int i,char userid[])//????????????
{
	node_com* p = head;
	while(p!=NULL)
	{
		if (strcmp(comid, p->com.comid) == 0)
		{
			if (i == 2 && strcmp(userid, p->com.sellerid) != 0)
			{
				cout << endl << "************************************************************************************" << endl;
						cout << "                          ????????????????????????????????????";
				cout << endl << "************************************************************************************" << endl;
				return NULL;
			}
			else
			{
				cout << endl << "************************************************************************************" << endl;
				cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(16) << "????????" << setw(14) << "????ID" << setw(14) << "????????" << endl;
				cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(16) << p->com.date << setw(14) << p->com.sellerid << " ";
				if (p->com.s == 0)
					cout << "??????" << endl;
				else if (p->com.s == 1)
					cout << "??????" << endl;
				else if (p->com.s == 2)
					cout << "??????" << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              ????????????????????????";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
}

node_com* fcommodity::commodity_buyersearchid(const char* comid, node_com* head,char userid[])//????????????
{
	node_com* p = head;
	while (p != NULL)
	{
		if ((strcmp(comid,p->com.comid)==0||strcmp(comid,p->com.comname)==0)&&p->com.s==on_sale)
		{
			if (strcmp(userid, p->com.sellerid) != 0)
			{
				cout << endl << "************************************************************************************" << endl;
				cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(14) << "????ID" << endl;
				cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(14) << p->com.sellerid << endl;
				cout << endl << "??????????";
				cout << p->com.description << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
			else
			{
				cout <<endl<< "??????????????????????????????????????????????????????????????????"<<endl;
				return NULL;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              ????????????????????????";
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
				cout << left << setw(10) << "ID" << setw(14) << "????" << setw(14) << "????" << setw(14) << "????ID" << endl;
				cout << left << setw(10) << p->com.comid << setw(14) << p->com.comname << setw(14) << p->com.price << setw(14) << p->com.sellerid << endl;
				cout << endl << "??????????";
				cout << p->com.description << endl;
				cout << "************************************************************************************" << endl;
			}
		}
		p = p->next;
	}
	if (!flag)
	{
		cout << endl << "************************************************************************************" << endl;
		cout << "                              ????????????????????????????";
		cout << endl << "************************************************************************************" << endl;
		return false;
	}
	return true;
}

node_com* fcommodity::commodity_buyerview(const char* comid, node_com * head, char userid[])//????????????
{
	node_com* p = head;
	while (p != NULL)
	{
		if (strcmp(comid, p->com.comid) == 0)
		{
			if (strcmp(userid, p->com.sellerid) == 0)
			{
				cout << endl<< "??????????????????????????????????????"<<endl;
				return p;
			}
			else if (p->com.s == 0)
			{
				cout << endl << "************************************************************************************" << endl;
				cout << "??????" << p->com.comname << endl << "??????" << p->com.description << endl << "??????????" << p->com.date << endl << "????ID??" << p->com.sellerid << endl << "??????????";
				cout << "??????" << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              ????????????????????????";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
}

void fcommodity::commodity_infochange(const char* comid,char userid[])//????????????
{
	node_com* head = commodityread();
	node_com* p = commodity_view(comid, head,2,userid);
	if (p==NULL)
	{
		seller_return(userid);
		return;
	}
	cout << "????????????????????1.???? 2.????????";
	int n;
	cin >> n;
	if (n == 1)
	{
		cout << "????????????????????";
		char price1[10];
		cin >> price1;
		if (price1[0] == '-')
		{
			cout << "??????????????????"<<endl;
			commodity_infochange(comid,userid);
		}
		cout << endl << "????????????????????????" << endl;
		cout <<endl<<"************************************************************************************" << endl;
		cout << "????ID??" << p->com.comid << endl << "??????????" << p->com.comname << endl << "??????????" << price1 << endl << "??????????" << p->com.description << endl;
		cout<< "************************************************************************************" << endl;
		commodity_infochangeprice(comid, userid, p, head, price1);
	}
	else if (n == 2)
	{
		cout << "????????????????????????";
		char describe[101] = {'\0'};
		cin >> describe;
		cout << endl << "????????????????????????" << endl;
		cout << endl << "************************************************************************************" << endl;
		cout << "????ID??" << p->com.comid << endl << "??????????" << p->com.comname << endl << "??????????" <<p->com.price << endl << "??????????" <<describe<< endl;
		cout << "************************************************************************************" << endl;
		commodity_infochangedescribe(comid, userid, p, head, describe);
	}
	else
	{
		cout << endl << "??????????????????????????????"<<endl;
		seller_return(userid);
	}
	return;
}

void fcommodity::commodity_infochangeprice(const char* comid, char userid[],node_com*p,node_com*head,char price1[])
{
	cout << "????????????y/n????";
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
		cout << endl << "??????????" << endl;
		seller_return(userid);
	}
	else if (strcmp(choose, "n") == 0)
		seller_return(userid);
	else
	{
		cout << endl << "????????????????????" << endl;
		commodity_infochangeprice(comid, userid, p, head, price1);
	}
	return;
}

void fcommodity::commodity_infochangedescribe(const char* comid, char userid[], node_com* p, node_com* head, char describe[])
{
	cout << "????????????y/n????";
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
		cout << endl << "??????????" << endl;
		seller_return(userid);
	}
	else if (strcmp(choose, "n") == 0)
		seller_return(userid);
	else
	{
		cout << endl << "????????????????????" << endl;
		commodity_infochangedescribe(comid, userid, p, head, describe);
	}
	return;
}

void fcommodity::commodtity_lauch(char userid[7])//????????
{
	char name[11];
	cout << endl << "????????????????";
	cin >> name;
	cout << endl << "????????????????";
	char price[10];
	cin >> price;
	if (price[0] == '-')
	{
		cout << "????????????????????"<<endl;
		seller_return(userid);
	}
	char describe[101];
	cout << endl << "????????????????";
	cin >> describe;
	cout << endl << endl << "??????????????????????????";
	cout <<endl<<"************************************************************************************" << endl;
	cout << "??????????" << name << endl << "??????????" << price << endl << "??????????" << describe << endl;
	cout<< "************************************************************************************" << endl;
	lauchconfirm(userid,name,price,describe);
	return;
}
void fcommodity::lauchconfirm(char userid[7],char name[],char price[],char describe[])
{
	cout << endl << "??????????????????????y/n????";
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
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", "????ID","????","????","????","????ID","????????","????????");
		fprintf(fp, "%s,%s,%s,%s,%s,%02d-%02d-%02d,%s\n",comid,name,price,describe,userid,ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,"onsale");
		fclose(fp);
		cout << endl << "??????????????" << endl;
	}
	else if (strcmp(choose, "n") == 0)
		seller_return(userid);
	else
	{
		cout << endl << "??????????????????!";
		lauchconfirm(userid,name, price, describe);
	}
	return;
}
void fcommodity::labelnumber(char comid[7], node_com* head)//????????????ID
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
			cout << endl << "1.???????????? 2.?????????? 3.????";
			cout << endl << "??????????";
			char fc[10];
			cin >> fc;
			if (strcmp(fc, "1") == 0)
			{
				cout << "1.???????????????? 2.???????????????? 3.????";
				cout <<endl<< "??????????";
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
								cout << "????ID??" << p->user.userid << endl << "????????" << p->user.username << endl << "??????????" << p->user.contactinfo << endl << "??????" << p->user.address << endl;
								cout << "************************************************************************************" << endl;
							}
						}
						p = p->next;
					}
					cout << endl << "1.?????????? 2.???????????? 3.??????????";
					cout << endl << "??????????";
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
							cout << endl << left << setw(10) << "????ID" << setw(10) << "????ID" << setw(14) << "????????" << setw(14) << "????????" << setw(10) << "????ID";
							cout << endl << left << setw(10) << orderhead->order.orderid << setw(10) << orderhead->order.comid << setw(14) << orderhead->order.trademoney << setw(14) << orderhead->order.time << setw(10) << orderhead->order.sellerid;
							cout << endl << "??????????" << orderhead->order.buyerevaluation << endl;
							cout << "????????????????????????" << orderhead->order.sellerscore << endl;
							cout << "************************************************************************************";
							flag = true;
						}
						orderhead = orderhead->next;
					}
					if (!flag)
					{
						cout << endl << "************************************************************************************" << endl;
						cout << "                           ??????????????????????????";
						cout << endl << "************************************************************************************" << endl;
					}
					cout << endl << "1.?????????? 2.???????????? 3.??????????";
					cout << endl << "??????????";
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
					cout << endl << "  ??????????" << endl;
					commoditydetail(userid,comid,find);
				}
			}
			else if (strcmp(fc, "2") == 0)
				shopcart_main(userid, comid);
			else if (strcmp(fc, "3") == 0)
				buyer_return(userid);
			else
			{
				cout << endl << "   ??????????" << endl;
				buyer_return(userid);
			}
		}
		else
			buyer_return(userid);
	}
	return;
}