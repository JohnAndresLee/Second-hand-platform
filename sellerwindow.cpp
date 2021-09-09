#include "sellerwindow.h"
#include<iostream>
#include<Windows.h>
#include"usermainwindow.h"
#include"commodity.h"
#include"order.h"

using namespace std;

void seller_return(char userid[7])
{
	cout << endl << "1.返回上级界面 2.返回用户主界面";
	cout << endl << "输入操作：";
	char n1[20];
	cin >> n1;
	if (strcmp(n1, "1") == 0)
	{
		sellerwindow(userid);
	}
	else if (strcmp(n1, "2") == 0)
		usermainwindow(userid);
	else
	{
		cout<<endl<< "无效选择！" << endl;
		seller_return(userid);
	}
}

void sellerwindow(char userid[7])
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
	cout << "====================================================================================" << endl;
	cout << endl << "输入操作：";
	char f[20];
	cin >> f;
	int n = 0;
	fcommodity* fcom = new fcommodity();
	order* forder = new order();
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0 || strcmp(f, "4") == 0 || strcmp(f, "5") == 0 || strcmp(f, "6") == 0)
	{
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			fcom->commodtity_lauch(userid);
			seller_return(userid); 
			break;
		}
		case(2):
		{
			cout << endl << "您发布的商品清单如下：" << endl;
			fcom->commodity_search(userid);
			seller_return(userid);
			break;
		}
		case(3):
		{                  
			cout << endl;
			fcom->commodity_search(userid);
			cout <<endl<< "请输入修改商品ID：";
			char comid[7];
			cin >> comid;
			fcom->commodity_infochange(comid, userid);
			break;
		}
		case(4):
		{
			if (!fcom->commodity_search(userid))
			{
				seller_return(userid);
				break;
			}
			else
			{
				cout << endl << "请输入下架商品ID：";
				char comid[7];
				cin >> comid;
				fcom->commodity_takeoff(comid, 2, userid);
			}
			break;
		}
		case(5):
		{
			forder->order_selleridquery(userid);
			seller_return(userid);
		}
		case(6):
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
		cout << endl << "*********************请以正确格式输入！即将自动跳转至卖家主界面*********************";
		Sleep(2000);
		system("cls");
		sellerwindow(userid);
	}
}