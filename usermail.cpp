#include "usermail.h"
#include<iomanip>
#include<iostream>
#include"usermainwindow.h"
#include<Windows.h>
#include"messagecontact.h"

using namespace std;

void mail_return(char userid[7])
{
	cout << endl << "1.返回上级界面 2.返回用户主界面";
	cout << endl << "输入操作：";
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
		cout << endl << "无效选择！" << endl;
		mail_return(userid);
	}
}

void usermail(char userid[7])
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.查看未读留言 2.查看历史留言 3.发送留言 4.返回用户主界面" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	messagecontact* fmes = new messagecontact();
	cout << endl << "输入操作：";
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
		cout << endl << "*********************************请以正确格式输入！*********************************";
		Sleep(2000);
		system("cls");
		usermail(userid);
	}
	return;
}