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
	cout << endl << "1.返回上级界面 2.返回用户主界面";
	cout << endl << "输入操作：";
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
		cout <<endl<< "无效选择！" << endl;
		userinfochange_return(userid);
	}
}

void usermenu(char userid[7])
{
	char f[20];
	cout << endl << "输入主菜单操作：";
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
		cout << endl << "***********************请以正确格式输入！即将自动跳转至主菜单***********************";
		Sleep(2000);
		system("cls");
		usermainwindow(userid);
	}
}

void usermainwindow(char userid[7])
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.注销登录 2.我是买家 3.我是卖家 4.用户信箱 5.个人信息管理"<<endl;
	cout << "====================================================================================" << endl;
	messagecontact* mes = new messagecontact();
	int i1=mes->unreadmessagecount(userid);
	int i2 = mes->unreadadminmessagecount(userid);
	if (i1 == 0&&i2==0)
	{
		cout << endl << "当前暂无新消息！"<<endl;
		usermenu(userid);
	}
	else
	{
		cout << endl << "您当前有" << i1 << "条未读的用户新消息" << endl;
		cout << endl << "您当前有" << i2 << "条未读的管理员消息" << endl;
		cout << endl << "1.前往查看 2.全部忽略" << endl;
		char f1[20];
		cout << endl << "输入操作：";
		cin >> f1;
		if (strcmp(f1, "1") == 0 || strcmp(f1, "2") == 0)
		{
			int cap = f1[0] - 48;
			if (cap == 1)
				mes->unreadmessagedisplay(userid);
			else
			{
				system("cls");
				cout << "===============================欢迎使用二手交易平台！===============================" << endl;
				cout << "====================================================================================" << endl;
				cout << "1.注销登录 2.我是买家 3.我是卖家 4.用户信箱 5.个人信息管理" << endl;
				cout << "====================================================================================" << endl;
				usermenu(userid);
			}
		}
		else
		{
			cout << endl << "***********************请以正确格式输入！即将自动跳转至主菜单***********************";
			Sleep(2000);
			system("cls");
			usermainwindow(userid);
		}
	}
	return;
}