#include "usermainwindow.h"
#include<Windows.h>
#include<cstdio>
#include<iostream>
#include"login.h"
#include"user.h"
#include"buyerwindow.h"
#include"sellerwindow.h"
#include"usermail.h"
#include"messagecontact.h"

using namespace std;

void userinfochange_return(char userid[7])
{
	fuser* function = new fuser();
	cout << endl << "1.�����ϼ����� 2.�����û�������";
	cout << endl << "���������";
	char n1[20];
	cin >> n1;
	if (strcmp(n1, "1") == 0)
	{
		function->user_infomanage(userid);
	}
	else if (strcmp(n1, "2") == 0)
		usermainwindow(userid);
	else
	{
		cout <<endl<< "��Чѡ��" << endl;
		userinfochange_return(userid);
	}
}

void usermenu(char userid[7])
{
	char f[20];
	cout << endl << "�������˵�������";
	cin >> f;
	fuser* userfunction = new fuser();
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0 || strcmp(f, "4") == 0 || strcmp(f, "5") == 0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			login();
			break;
		}
		case(2):
		{
			buyerwindow(userid);
			break;
		}
		case(3):
		{
			sellerwindow(userid);
			break;
		}
		case(4):
		{
			usermail(userid);
			break;
		}
		case(5):
		{
			userfunction->user_infomanage(userid);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		cout << endl << "***********************������ȷ��ʽ���룡�����Զ���ת�����˵�***********************";
		Sleep(2000);
		system("cls");
		usermainwindow(userid);
	}
}

void usermainwindow(char userid[7])
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.ע����¼ 2.������� 3.�������� 4.�û����� 5.������Ϣ����"<<endl;
	cout << "====================================================================================" << endl;
	messagecontact* mes = new messagecontact();
	int i1=mes->unreadmessagecount(userid);
	int i2 = mes->unreadadminmessagecount(userid);
	if (i1 == 0&&i2==0)
	{
		cout << endl << "��ǰ��������Ϣ��"<<endl;
		usermenu(userid);
	}
	else
	{
		cout << endl << "����ǰ��" << i1 << "��δ�����û�����Ϣ" << endl;
		cout << endl << "����ǰ��" << i2 << "��δ���Ĺ���Ա��Ϣ" << endl;
		cout << endl << "1.ǰ���鿴 2.ȫ������" << endl;
		char f1[20];
		cout << endl << "���������";
		cin >> f1;
		if (strcmp(f1, "1") == 0 || strcmp(f1, "2") == 0)
		{
			int cap = f1[0] - 48;
			if (cap == 1)
				mes->unreadmessagedisplay(userid);
			else
			{
				system("cls");
				cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
				cout << "====================================================================================" << endl;
				cout << "1.ע����¼ 2.������� 3.�������� 4.�û����� 5.������Ϣ����" << endl;
				cout << "====================================================================================" << endl;
				usermenu(userid);
			}
		}
		else
		{
			cout << endl << "***********************������ȷ��ʽ���룡�����Զ���ת�����˵�***********************";
			Sleep(2000);
			system("cls");
			usermainwindow(userid);
		}
	}
	return;
}