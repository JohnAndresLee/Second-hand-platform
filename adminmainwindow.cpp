#include "adminmainwindow.h"
#include<iostream>
#include"commodity.h"
#include"login.h"
#include"user.h"
#include<Windows.h>
#include<ctime>
#include"order.h"
#include"messagecontact.h"
#include"adminmail.h"

using namespace std;

void structdeletecom(node_com* head)
{
	while (head != NULL)
	{
		node_com* temp = head;
		head = head->next;
		delete temp;
	}
	return;
}

void structdeleteuser(node_user* head)
{
	while (head != NULL)
	{
		node_user* temp = head;
		head = head->next;
		delete temp;
	}
	return;
}

void commodityreturn()
{
	cout << endl << "1.���ع���Ա�˵� 2.ע��" << endl << "���������";
	char n1[20];
	cin >> n1;
	if (strcmp(n1, "1") == 0)
	{
		system("cls");
		adminmain();
	}
	else if (strcmp(n1, "2") == 0)
		login();
	else
	{
		cout<<endl<< "��Чѡ��" << endl;
		commodityreturn();
	}
}

void adminlogin()
{
	cout << "���������Ա������";
	char name[11], key[11];
	cin >> name;
	cout << "���������Ա���룺";
	cin >> key;
	if (strcmp(name, "admin") == 0 && strcmp(key, "12345") == 0)
	{
		cout << "********************************��½�ɹ�!�����Զ���ת*******************************";
		Sleep(2000);
		system("cls");
		adminmain();
	}
	else
	{
		cout << "******************************��¼ʧ�ܣ������ص����˵�******************************" << endl<<endl;
		Sleep(1000);
		login();
	}
}


void adminmenu()
{
	cout << endl << "�������˵�������";
	char f[20];
	cin >> f;
	fcommodity* fcom = new fcommodity();
	fuser* userfunction = new fuser();
	order* forder = new order();
	int n = 0;
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0 || strcmp(f, "4") == 0 || strcmp(f, "5") == 0 || strcmp(f, "6") == 0 || strcmp(f, "7") == 0 || strcmp(f, "8") == 0)
	{
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			fcom->commodity_viewall();
			commodityreturn();
		}
		case(2):
		{
			node_com* p;
			cout << "��������Ʒ���ƣ�";
			char comid[7];
			cin >> comid;
			node_com* head = commodityread();
			char userid[7] = "admin";
			p = fcom->commodity_view(comid, head, 1, userid);
			commodityreturn();
		}
		case(3):
		{
			forder->order_view();
			commodityreturn();
			break;
		}
		case(4):
		{
			userfunction->user_view();
			commodityreturn();
			break;
		}
		case(5):
		{
			cout << endl << "������Ҫɾ�����û�ID��";
			char userid[7];
			cin >> userid;
			userfunction->user_delete(userid);
			break;
		}
		case(6):
		{
			cout << endl << "���������е���Ʒ��Ϣ���£�";
			char adminid[7] = "admin";
			fcom->commodity_buyerviewall(adminid);
			cout << endl << "�������¼���ƷID��";
			char comid[7];
			cin >> comid;
			char userid[7] = "admin";
			fcom->commodity_takeoff(comid, 1, userid);
			break;
		}
		case(7):
		{
			adminmail();
			break;
		}
		case(8):
		{
			login();
			break;
		}
		default:
			break;
		}
	}
	else
	{
		cout << endl << "*********************������ȷ��ʽ���룡�����Զ���ת������Ա�˵�*********************";
		Sleep(2000);
		system("cls");
		adminmain();
	}
	return;
}

void adminmain()
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��=============================================" << endl; 
	cout << "==================================================================================================" << endl;
	cout << "1.�鿴������Ʒ 2.������Ʒ 3.�鿴���ж��� 4.�鿴�����û� 5.ɾ���û� 6.�¼���Ʒ 7.����Ա���� 8.ע�� " << endl;
	cout << "==================================================================================================" << endl;
	messagecontact* mes = new messagecontact();
	char adminid[6] = { "admin" };
	int i = mes->unreadmessagecount(adminid);
	if (i == 0)
	{
		cout << endl << "��ǰ��������Ϣ��" << endl;
		adminmenu();
	}
	else
	{
		cout << endl << "����ǰ��" << i << "��δ�����û�����Ϣ" << endl;
		cout << endl << "1.ǰ���鿴 2.ȫ������" << endl;
		char f1[20];
		cout << endl << "���������";
		cin >> f1;
		if (strcmp(f1, "1") == 0 || strcmp(f1, "2") == 0)
		{
			int cap = f1[0] - 48;
			if (cap == 1)
				adminmail();
			else
			{
				system("cls");
				cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��=============================================" << endl;
				cout << "==================================================================================================" << endl;
				cout << "1.�鿴������Ʒ 2.������Ʒ 3.�鿴���ж��� 4.�鿴�����û� 5.ɾ���û� 6.�¼���Ʒ 7.����Ա���� 8.ע�� " << endl;
				cout << "==================================================================================================" << endl;
				adminmenu();
			}
		}
		else
		{
			cout << endl << "***********************������ȷ��ʽ���룡�����Զ���ת�����˵�***********************";
			Sleep(2000);
			system("cls");
			adminmain();
		}
	}
}
