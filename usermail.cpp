#include "usermail.h"
#include<iomanip>
#include<iostream>
#include"usermainwindow.h"
#include<Windows.h>
#include"messagecontact.h"

using namespace std;

void mail_return(char userid[7])
{
	cout << endl << "1.�����ϼ����� 2.�����û�������";
	cout << endl << "���������";
	char n1[20];
	cin >> n1;
	if (strcmp(n1, "1") == 0)
	{
		usermail(userid);
	}
	else if (strcmp(n1, "2") == 0)
		usermainwindow(userid);
	else
	{
		cout << endl << "��Чѡ��" << endl;
		mail_return(userid);
	}
}

void usermail(char userid[7])
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.�鿴δ������ 2.�鿴��ʷ���� 3.�������� 4.�����û�������" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	messagecontact* fmes = new messagecontact();
	cout << endl << "���������";
	cin >> f;
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0 || strcmp(f, "4") == 0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			fmes->unreadmessagedisplay(userid);
			break;
		}
		case(2):
		{
			fmes->historymessagedisplay(userid);
			break;
		}
		case(3):
		{
			fmes->usersendmessage(userid);
			break;
		}
		case(4):
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
		cout << endl << "*********************************������ȷ��ʽ���룡*********************************";
		Sleep(2000);
		system("cls");
		usermail(userid);
	}
	return;
}