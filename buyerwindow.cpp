#include "buyerwindow.h"
#include<iostream>
#include<Windows.h>
#include"usermainwindow.h"
#include"commodity.h"
#include"order.h"
#include"user.h"
#include"shoppingcart.h"
#include"messagecontact.h"
#include<iomanip>

using namespace std;

void buyfunc(char userid[], node_com* p, node_com* ph, node_com* head);

void commoditymoredetail(char userid[],node_com*headorigin)
{
	fcommodity* fcom = new fcommodity();
	cout << endl << "1.�˽���Ʒ������Ϣ 2.ֱ�ӹ��� 3.ȡ��";
	cout << endl << "���������";
	char temp[20];
	cin >> temp;
	if (strcmp(temp, "1") == 0)
	{
		cout << endl << "����������鿴����ƷID��";
		char comid[7];
		cin >> comid;
		node_com* head = commodityread();
		node_com* find = fcom->commodity_buyerview(comid, head, userid);
		fcom->commoditydetail(userid, comid, find);
	}
	else if (strcmp(temp, "2") == 0)
	{
		cout << endl << "��������ƷID��";
		char comid[7];
		cin >> comid;
		node_com* head = commodityread();
		node_com* ph = head;
		node_com* p = fcom->commodity_buyerview(comid, head, userid);
		if (p == NULL || strcmp(userid, p->com.sellerid) == 0)
			buyer_return(userid);
		else
		{
			buyfunc(userid, p, ph, head);
			buyer_return(userid);
		}
	}
	else if (strcmp(temp, "3") == 0)
		buyer_return(userid);
	else
	{
		cout << endl << "��Ч������";
		buyer_return(userid);
	}
}

void buyer_return(char userid[7])
{
	cout << endl << "1.�����ϼ����� 2.�����û�������";
	cout << endl << "���������";
	char n1[20];
	cin >> n1;
	if (strcmp(n1, "1") == 0)
	{
		buyerwindow(userid);
	}
	else if (strcmp(n1, "2") == 0)
		usermainwindow(userid);
	else
	{
		cout<<endl<< "��Чѡ��" << endl;
		buyer_return(userid);
	}
}

void buyfunc(char userid[],node_com*p,node_com*ph,node_com*head)
{
	fcommodity* fcom = new fcommodity();
	order* forder = new order();
	fuser* ffuser = new fuser();
	node_user* userhead = ffuser->user_inforead();
	node_user* puser = userhead;
	node_user* seller = userhead;
	while (userhead != NULL)
	{
		if (strcmp(userhead->user.userid, userid) == 0)
			break;
		else
			userhead = userhead->next;
	}
	while (seller != NULL)
	{
		if (strcmp(seller->user.userid, p->com.sellerid) == 0)
			break;
		else
			seller = seller->next;
	}
	forder->order_formation(userid, p, head, userhead, seller);
	ffuser->userwrite(puser);
	fcom->commoditywrite(ph);
}

void buyerwindow(char userid[7])
{
	system("cls");
	cout << "===========================================��ӭʹ�ö��ֽ���ƽ̨��===========================================" << endl;
	cout << "============================================================================================================" << endl;
	cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�鿴���ﳵ 7.�������� 8.����������" << endl;
	cout << "============================================================================================================" << endl;
	cout << endl << "���������";
	char f[20];
	cin >> f;
	int n = 0;
	fcommodity* fcom =new fcommodity();
	order* forder = new order();
	fuser* ffuser = new fuser();
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0 || strcmp(f, "4") == 0 || strcmp(f, "5") == 0 || strcmp(f, "6") == 0 || strcmp(f, "7") == 0 || strcmp(f, "8") == 0)
	{
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			if (fcom->commodity_buyerviewall(userid))
			{
				node_com* head = commodityread();
				cout << endl << "1.��������Ʒ�۸������� 2.��������Ʒ�۸��������� 3.ȡ��";
				cout << endl << "���������";
				char n[20];
				cin >> n;
				if (strcmp(n, "1") == 0)
				{
					fcom->commodity_query(1, head, userid);
					buyer_return(userid);
				}
				else if (strcmp(n, "2") == 0)
				{
					fcom->commodity_query(3, head, userid);
					buyer_return(userid);
				}
				else if (strcmp(n, "3") == 0)
					buyer_return(userid);
				else
				{
					cout << endl << "��Чѡ��" << endl;
					buyer_return(userid);
				}
			}
			else
				buyer_return(userid);
			break;
		}
		case(2):
		{
			if(!fcom->commodity_buyerviewall(userid))
				buyer_return(userid);
			else
			{
				cout << endl << "��������ƷID��";
				char comid[7];
				cin >> comid;
				node_com* head = commodityread();
				node_com* ph = head;
				node_com* p = fcom->commodity_buyerview(comid, head,userid);
				if (p==NULL||strcmp(userid, p->com.sellerid) == 0)
				{
					buyer_return(userid);
					break;
				}
				else
				{
					buyfunc(userid, p, ph, head);
					buyer_return(userid);
				}
			}
			break;
		}
		case(3):
		{
			cout << endl << "������������ʽ��1.��ȷ���� 2.ģ������ 3.�۸��������� 4.����ID������Ʒ 5.ȡ��";
			cout << endl << "�����������";
			char n[20];
			cin >> n;
			if (strcmp(n, "1") == 0)
			{
				cout << "��������ƷID�����ƣ�";
				char comid[11];
				cin >> comid;
				node_com* head = commodityread();
				node_com* temp = fcom->commodity_buyersearchid(comid, head, userid);
				if (temp != NULL)
				{
					cout << endl << "1.��ϵ���� 2.���빺�ﳵ 3.ȡ��";
					cout << endl << "�����������" << endl;
					char n[20];
					cin >> n;
					if (strcmp(n, "1") == 0)
					{
						smessage(userid, temp->com.sellerid);
						shopcart_main(userid, temp->com.comid);
					}
					else if (strcmp(n, "2") == 0)
						shopcart_main(userid, comid);
					else if (strcmp(n, "3") == 0)
						buyer_return(userid);
					else
					{
						cout << endl << "��Чѡ��" << endl;
						buyer_return(userid);
					}
				}
				buyer_return(userid);
			}
			else if (strcmp(n, "2") == 0)
			{
				cout << "����������Ҫ��ѯ����Ʒ��";
				char comname[20];
				cin >> comname;
				node_com* head = commodityread();
				bool s = buyervaguesearch(comname, head, userid);
				if (!s)
					buyer_return(userid);
				else
				{
					cout << endl << "����������鿴����ƷID��";
					char comid[7];
					cin >> comid;
					node_com* head = commodityread();
					node_com* find = fcom->commodity_buyerview(comid, head, userid);
					if (find == NULL || strcmp(userid, find->com.sellerid) == 0)
					{
						buyer_return(userid);
						break;
					}
					else
					{
						if (find != NULL)
							shopcart_main(userid, comid);
						else
							buyer_return(userid);
					}
				}
			}
			else if (strcmp(n, "3") == 0)
			{
				node_com* headorigin = commodityread();
				node_com* head = headorigin;
				if (fcom->commodity_query(2, head, userid))
				{
					commoditymoredetail(userid,headorigin);
					break;
				}
				else
					buyer_return(userid);
			}
			else if (strcmp(n, "4") == 0)
			{
				cout << "��������Ҫ����������ID��";
				char sellerid[20];
				cin >> sellerid;
				if (strcmp(sellerid, userid) == 0)
				{
					cout <<endl<<"��������ҽ�����Լ�����Ʒ�������أ�" << endl;
					buyer_return(userid);
				}
				else
				{
					node_com* comhead = commodityread();
					node_com* headorigin = comhead;
					node_user* userhead = ffuser->user_inforead();
					bool flag = false;
					while (userhead != NULL)
					{
						if (userhead->user.flag && strcmp(userhead->user.userid, sellerid) == 0)
						{
							flag = true;
							break;
						}
						userhead = userhead->next;
					}
					if (flag)
					{
						cout << endl << "************************************************************************************" << endl;
						cout << left << setw(10) << "ID" << setw(14) << "����" << setw(14) << "�۸�" << setw(16) << "�ϼ�ʱ��" << setw(14) << "����ID" << endl;
						bool flag2 = false;
						while (comhead != NULL)
						{
							if (comhead->com.s == on_sale && strcmp(comhead->com.sellerid, sellerid) == 0)
							{
								flag2 = true;
								cout << left << setw(10) << comhead->com.comid << setw(14) << comhead->com.comname << setw(14) << comhead->com.price << setw(16) << comhead->com.date << setw(14) << comhead->com.sellerid << endl;
							}
							comhead = comhead->next;
						}
						if (!flag2)
						{
							cout << "              ���û����������е���Ʒ��";
							cout << "************************************************************************************" << endl;
							buyer_return(userid);
						}
						else
						{
							cout << "************************************************************************************" << endl;
							commoditymoredetail(userid, headorigin);
							return;
						}
					}
					else
					{
						cout << endl << "���û������ڣ��������������" << endl;
						buyer_return(userid);
					}
				}
			}
			else if (strcmp(n, "5") == 0)
				buyer_return(userid);
			else
			{
				cout << endl << "��Чѡ��" << endl;
				buyer_return(userid);
			}
			break;
		}
		case(4):
		{
			forder->order_buyeridquery(userid);
			buyer_return(userid);
		}
		case(5):
		{
			fcom->commodity_buyerviewall(userid);
			cout << endl << "����������鿴����ƷID��";
			char comid[7];
			cin >> comid;
			node_com* head = commodityread();
			node_com* find = fcom->commodity_buyerview(comid, head, userid);
			fcom->commoditydetail(userid,comid,find);
			break;
		}
		case(6):
		{
			bool s=shopcart_display(userid);
			if (s)
			{
				cout << endl << "1.������Ʒ 2.����Ʒ�Ƴ����ﳵ 3.����" << endl;
				cout << endl << "���������";
				char f[20];
				cin >> f;
				if (strcmp(f, "1") == 0)
				{
					cout << endl << "��������ƷID��";
					char comid[7];
					cin >> comid;
					node_com* head = commodityread();
					node_com* ph = head;
					node_com* p = fcom->commodity_buyerview(comid, head, userid);
					if (p == NULL || strcmp(userid, p->com.sellerid) == 0)
					{
						buyer_return(userid);
						break;
					}
					else
					{
						buyfunc(userid, p, ph, head);
						buyer_return(userid);
					}
				}
				else if (strcmp(f, "2") == 0)
				{
					cout << "��������Ҫ�Ƴ�����ƷID��";
					char comid[20];
					cin >> comid;
					cout << "��ȷ��Ҫ����Ʒ" << comid << "�Ƴ����ﳵ�𣿣�y/n����";
					char choose[20];
					cin >> choose;
					if (strcmp(choose, "y") == 0)
					{
						shopcart_delete(userid, comid);
						buyer_return(userid);
					}
					else if (strcmp(choose, "n") == 0)
						buyer_return(userid);
					else
					{
						cout << endl << "������ȷ�ĸ�ʽ����!";
						buyer_return(userid);
					}
				}
				else if (strcmp(f, "3") == 0)
					buyer_return(userid);
				else
				{
					cout << "������ȷ��ʽ���룡";
					buyer_return(userid);
				}
			}
			else
				buyer_return(userid);
			break;
		}
		case(7):
		{
			node_order* head = orderread();
			node_order* p = head;
			bool flag = false;
			while (p != NULL)
			{
				if (strcmp(p->order.buyerid, userid) == 0 && strcmp(p->order.sellerscore, "NULL") == 0)
				{
					flag = true;
					cout << endl << "************************************************************************************" << endl;
					cout <<"����ID��"<<p->order.orderid<<endl<< "��ƷID��" << p->order.comid << endl << "����ʱ�䣺" << p->order.time << endl << "���׽�" << p->order.trademoney << endl;
					cout<< "����ID��" << p->order.sellerid<<endl;					
					cout << "************************************************************************************" << endl;
					forder->order_evaluate(userid, p);
				}
				p = p->next;
			}
			if (!flag)
			{
				cout << "��ǰ���������۵���Ʒ��";
				buyer_return(userid);
			}
			else
			{
				forder->orderwrite(head);
				buyer_return(userid);
			}
			break;
		}
		case(8):
		{
			usermainwindow(userid);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		cout << endl << "*********************������ȷ��ʽ���룡�����Զ���ת�����������*********************";
		Sleep(2000);
		system("cls");
		buyerwindow(userid);
	}
}