#include "sellerwindow.h"
#include<iostream>
#include<Windows.h>
#include"usermainwindow.h"
#include"commodity.h"
#include"order.h"

using namespace std;

void seller_return(char userid[7])
{
	cout << endl << "1.�����ϼ����� 2.�����û�������";
	cout << endl << "���������";
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
		cout<<endl<< "��Чѡ��" << endl;
		seller_return(userid);
	}
}

void sellerwindow(char userid[7])
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������" << endl;
	cout << "====================================================================================" << endl;
	cout << endl << "���������";
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
			cout << endl << "����������Ʒ�嵥���£�" << endl;
			fcom->commodity_search(userid);
			seller_return(userid);
			break;
		}
		case(3):
		{                  
			cout << endl;
			fcom->commodity_search(userid);
			cout <<endl<< "�������޸���ƷID��";
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
				cout << endl << "�������¼���ƷID��";
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
		cout << endl << "*********************������ȷ��ʽ���룡�����Զ���ת������������*********************";
		Sleep(2000);
		system("cls");
		sellerwindow(userid);
	}
}