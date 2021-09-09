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
	cout << endl << "1.返回管理员菜单 2.注销" << endl << "输入操作：";
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
		cout<<endl<< "无效选择！" << endl;
		commodityreturn();
	}
}

void adminlogin()
{
	cout << "请输入管理员姓名：";
	char name[11], key[11];
	cin >> name;
	cout << "请输入管理员密码：";
	cin >> key;
	if (strcmp(name, "admin") == 0 && strcmp(key, "12345") == 0)
	{
		cout << "********************************登陆成功!即将自动跳转*******************************";
		Sleep(2000);
		system("cls");
		adminmain();
	}
	else
	{
		cout << "******************************登录失败！即将回到主菜单******************************" << endl<<endl;
		Sleep(1000);
		login();
	}
}


void adminmenu()
{
	cout << endl << "输入主菜单操作：";
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
			cout << "请输入商品名称：";
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
			cout << endl << "请输入要删除的用户ID：";
			char userid[7];
			cin >> userid;
			userfunction->user_delete(userid);
			break;
		}
		case(6):
		{
			cout << endl << "所有销售中的商品信息如下：";
			char adminid[7] = "admin";
			fcom->commodity_buyerviewall(adminid);
			cout << endl << "请输入下架商品ID：";
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
		cout << endl << "*********************请以正确格式输入！即将自动跳转至管理员菜单*********************";
		Sleep(2000);
		system("cls");
		adminmain();
	}
	return;
}

void adminmain()
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！=============================================" << endl; 
	cout << "==================================================================================================" << endl;
	cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.管理员信箱 8.注销 " << endl;
	cout << "==================================================================================================" << endl;
	messagecontact* mes = new messagecontact();
	char adminid[6] = { "admin" };
	int i = mes->unreadmessagecount(adminid);
	if (i == 0)
	{
		cout << endl << "当前暂无新消息！" << endl;
		adminmenu();
	}
	else
	{
		cout << endl << "您当前有" << i << "条未读的用户新消息" << endl;
		cout << endl << "1.前往查看 2.全部忽略" << endl;
		char f1[20];
		cout << endl << "输入操作：";
		cin >> f1;
		if (strcmp(f1, "1") == 0 || strcmp(f1, "2") == 0)
		{
			int cap = f1[0] - 48;
			if (cap == 1)
				adminmail();
			else
			{
				system("cls");
				cout << "===============================欢迎使用二手交易平台！=============================================" << endl;
				cout << "==================================================================================================" << endl;
				cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.管理员信箱 8.注销 " << endl;
				cout << "==================================================================================================" << endl;
				adminmenu();
			}
		}
		else
		{
			cout << endl << "***********************请以正确格式输入！即将自动跳转至主菜单***********************";
			Sleep(2000);
			system("cls");
			adminmain();
		}
	}
}
