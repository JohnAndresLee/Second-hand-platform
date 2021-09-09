#define _CRT_SECURE_NO_WARNINGS

#include"login.h"
#include<iostream>
#include<cstring>
#include<ctime>
#include<windows.h>
#include<cstdlib>
#include<cstring>
#include"adminmainwindow.h"
#include"commodity.h"
#include"user.h"

using namespace std;



void login()
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！==============================="<<endl;
	cout << "====================================================================================" << endl;
	cout << "1.用户登录 2.用户注册 3.管理员登录 4.退出程序"<<endl;
	cout<< "====================================================================================" << endl;
	fuser* userfunction = new fuser();
	cout << endl << "输入操作：";
	char f[20];
	cin >> f;
	int n = 0;
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0 || strcmp(f, "4") == 0)
	{
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			userfunction->userlogin();
			break;
		}
		case(2):
		{
			userfunction->usersignin();
			break;
		}
		case(3):
		{
			adminlogin();
			break;
		}
		case(4):
		{
			exit(0);
		}
		default:
			break;
		}
	}
	else
	{
		cout << endl << "*********************请以正确格式输入！即将重新跳转至登录主界面*********************";
		Sleep(2000);
		system("cls");
		login();
	}
}