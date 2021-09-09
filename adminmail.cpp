#include "adminmail.h"
#include<iostream>
#include"adminmainwindow.h"
#include"messagecontact.h"
#include<Windows.h>
#include<ctime>

using namespace std;

void adminmail_return()
{
	cout << endl << "1.�����ϼ����� 2.���ع���Ա������";
	cout << endl << "���������";
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
		cout << endl << "��Чѡ��" << endl;
		adminmail_return();
	}
}

void adminunreadmessagedisplay(char adminid[])//��ʾ����Աδ���û�����
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
			cout << "�����û�ID��" << head->mes.senderid << endl;
			cout << "�������ݣ�" << head->mes.message << endl;
			cout << "����ʱ�䣺" << head->mes.date << endl;
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
		cout << endl << "��ǰû��δ�����û�����" << endl;
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
			cout << "�����û�ID��" << head->mes.senderid << endl;
			cout << "�������ݣ�" << head->mes.message << endl;
			cout << "����ʱ�䣺" << head->mes.date << endl;
			cout << "====================================================================================" << endl;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "����ʱ��δ�յ��û�������" << endl;
		adminmail_return();
	}
	adminmail_return();
}

void adminmailsend()
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.���͸��û� 2.�鿴���з��ͼ�¼ 3.���ع���Ա�������" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	cout << endl << "���������";
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
					cout << "�����û�ID��" << head->mes.receiverid << endl;
					cout << "�������ݣ�" << head->mes.message << endl;
					cout << "����ʱ�䣺" << head->mes.date << endl;
					cout << "����״̬��";
					if (head->mes.state)
						cout << "�Ѷ�" << endl;
					else
						cout << "δ��" << endl;
					cout << "====================================================================================" << endl;
				}
				head = head->next;
			}
			if (!flag)
			{
				cout << endl << "����ʱ��δ�������Ը��û���" << endl;
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
		cout << endl << "*********************************������ȷ��ʽ���룡*********************************";
		Sleep(2000);
		system("cls");
		adminmailsend();
	}
	return;
}

void adminmail()
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.�鿴δ���û����� 2.�鿴��ʷ�û����� 3.�������� 4.���ع���Ա������" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	char adminid[6] ="admin";
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
		cout << endl << "*********************************������ȷ��ʽ���룡*********************************";
		Sleep(2000);
		system("cls");
		adminmail();
	}
	return;
}