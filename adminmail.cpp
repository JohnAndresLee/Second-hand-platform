#include "adminmail.h"
#include<iostream>
#include"adminmainwindow.h"
#include"messagecontact.h"
#include<Windows.h>
#include<ctime>

using namespace std;

void adminmail_return()
{
	cout << endl << "1.返回上级界面 2.返回管理员主界面";
	cout << endl << "输入操作：";
	char n1[20];
	cin >> n1;
	if (strcmp(n1, "1") == 0)
	{
		adminmail();
	}
	else if (strcmp(n1, "2") == 0)
		adminmain();
	else
	{
		cout << endl << "无效选择！" << endl;
		adminmail_return();
	}
}

void adminunreadmessagedisplay(char adminid[])//显示管理员未读用户留言
{
	messagecontact* fmes = new messagecontact();
	node_message* head =fmes->messageread();
	node_message* p = head;
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->mes.senderid, "admin") != 0 && strcmp(head->mes.receiverid,"admin") == 0 && head->mes.state == false)
		{
			flag = true;
			cout << endl << "====================================================================================" << endl;
			cout << "留言用户ID：" << head->mes.senderid << endl;
			cout << "留言内容：" << head->mes.message << endl;
			cout << "留言时间：" << head->mes.date << endl;
			cout << "====================================================================================" << endl;
			fmes->confirm(head);
			fmes->messagewrite(p);
			char adminid[7] = "admin";
			fmes->sendback(adminid, head->mes.senderid);
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "当前没有未读的用户留言" << endl;
		adminmail_return();
	}
	adminmail_return();
}

void adminhistorymessagedisplay(char adminid[])
{
	messagecontact* fmes = new messagecontact();
	node_message* allhead = fmes->messageread();
	node_message* head =fmes->message_search(adminid,allhead);
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->mes.senderid, "admin") != 0 && strcmp(head->mes.receiverid,"admin") == 0 && head->mes.state == true)
		{
			flag = true;
			cout << endl << "====================================================================================" << endl;
			cout << "留言用户ID：" << head->mes.senderid << endl;
			cout << "留言内容：" << head->mes.message << endl;
			cout << "留言时间：" << head->mes.date << endl;
			cout << "====================================================================================" << endl;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "您暂时还未收到用户的留言" << endl;
		adminmail_return();
	}
	adminmail_return();
}

void adminmailsend()
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.发送给用户 2.查看所有发送记录 3.返回管理员信箱界面" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	cout << endl << "输入操作：";
	cin >> f;
	messagecontact* fmes = new messagecontact();
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			fmes->adminsendmessage();
			break;
		}
		case(2):
		{
			char adminid[6] = { "admin" };
			node_message* allhead = fmes->messageread();
			node_message* head = fmes->message_search(adminid,allhead);
			bool flag = false;
			while (head != NULL)
			{
				if (strcmp(head->mes.senderid, adminid) == 0)
				{
					flag = true;
					cout << endl << "====================================================================================" << endl;
					cout << "留言用户ID：" << head->mes.receiverid << endl;
					cout << "留言内容：" << head->mes.message << endl;
					cout << "留言时间：" << head->mes.date << endl;
					cout << "留言状态：";
					if (head->mes.state)
						cout << "已读" << endl;
					else
						cout << "未读" << endl;
					cout << "====================================================================================" << endl;
				}
				head = head->next;
			}
			if (!flag)
			{
				cout << endl << "您暂时还未发送留言给用户！" << endl;
				adminmail_return();
			}
			adminmail_return();
			break;
		}
		case(3):
		{
			adminmail();
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
		adminmailsend();
	}
	return;
}

void adminmail()
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.查看未读用户留言 2.查看历史用户留言 3.发送留言 4.返回管理员主界面" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	char adminid[6] ="admin";
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
			adminunreadmessagedisplay(adminid);
			break;
		}
		case(2):
		{
			adminhistorymessagedisplay(adminid);
			break;
		}
		case(3):
		{
			adminmailsend();
			break;
		}
		case(4):
		{
			system("cls");
			adminmain();
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
		adminmail();
	}
	return;
}