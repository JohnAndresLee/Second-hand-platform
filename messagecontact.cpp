#define _CRT_SECURE_NO_WARNINGS

#include "messagecontact.h"
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include"usermail.h"
#include"user.h"
#include<ctime>
#include"adminmail.h"

using namespace std;

void noderead(char* list, node_message* p)
{
	int len = strlen(list);
	int j = 0;
	int temp = 0;
	while (list[j] != ',')
		p->mes.senderid[temp++] = list[j++];
	p->mes.senderid[temp] = '\0';
	++j;
	temp = 0;
	while (list[j] != ',')
		p->mes.receiverid[temp++] = list[j++];
	p->mes.receiverid[temp] = '\0';
	++j;
	temp = 0;
	if (list[j] == '1')
		p->mes.state = true;//已读
	else
		p->mes.state = false;
	j+=2;
	while (list[j] != ',')
		p->mes.date[temp++] = list[j++];
	p->mes.date[temp] = '\0';
	++j;
	temp = 0;
	while (list[j] != '\0')
		p->mes.message[temp++] = list[j++];
	++j;
	p->mes.message[temp] = '\0';
	temp = 0;
	return;
}

node_message* messagecontact::messageread()
{
	node_message* head = NULL;
	FILE* fp = fopen("message.txt", "r");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	char list[240];
	while (!feof(fp))
	{
		if (fscanf(fp, "%s", list) != EOF)
		{
			node_message* p = new node_message;
			if (head == NULL)
			{
				noderead(list, p);
				head = p;
				head->next = NULL;
			}
			else
			{
				noderead(list, p);
				p->next = head;
				head = p;
			}
		}
	}
	fclose(fp);
	return head;
}

void messagecontact::messagewrite(node_message*head)//读入全部后的全部覆盖输出
{
	node_message* p = head;
	FILE* fp = fopen("message.txt", "w");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	while (p != NULL)
	{
		fprintf(fp, "%s,%s,",p->mes.senderid,p->mes.receiverid);
		if (p->mes.state)
			fprintf(fp, "%s,", "1");
		else
			fprintf(fp, "%s,", "0");
		fprintf(fp, "%s,%s\n", p->mes.date, p->mes.message);
		p = p->next;
	}
	fclose(fp);
	return;
}

node_message* messagecontact::message_search(char userid[7],node_message*head)
{
	node_message* usermailhead = NULL;
	node_message* usermailtail = NULL;
	while (head != NULL)
	{
		if (strcmp(head->mes.senderid, userid) == 0 || strcmp(head->mes.receiverid, userid) == 0)
		{
			node_message* p = new node_message;
			p->mes = head->mes;
			if (usermailhead == NULL)
				usermailhead = p;
			else
				usermailtail->next = p;
			p->next = NULL;
			usermailtail = p;
		}
		head = head->next;
	}
	return usermailhead;
}

void smessage(char userid[],char receiver[])
{
	cout << endl << "请输入您要发送的留言：";
	char message[201];
	cin >> message;

	time_t rawtime;
	struct tm* ptminfo;
	time(&rawtime);
	ptminfo = localtime(&rawtime);

	FILE* fp = fopen("message.txt", "a+");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s,%s,%02d-%02d-%02d-%02d:%02d,%s\n", userid, receiver, "0", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, message);
	fclose(fp);
	cout << endl << "发送成功！";
	return;
}

int messagecontact::unreadmessagecount(char userid[7])//未读的用户留言，不算管理员发送的信息
{
	node_message* head = messageread();
	node_message* counthead =message_search(userid,head);
	int num = 0;
	while (counthead != NULL)
	{
		if (strcmp(counthead->mes.senderid,"admin")!=0&&strcmp(counthead->mes.receiverid, userid) == 0 && counthead->mes.state == false)
			num++;
		counthead = counthead->next;
	}
	return num;
}

int messagecontact::unreadadminmessagecount(char userid[7])//未读的管理员留言
{
	node_message* head = messageread();
	node_message* counthead = message_search(userid,head);
	int num = 0;
	while (counthead != NULL)
	{
		if (strcmp(counthead->mes.senderid, "admin")== 0 && strcmp(counthead->mes.receiverid, userid) == 0 && counthead->mes.state == false)
			num++;
		counthead = counthead->next;
	}
	return num;
}

void messagecontact::usersendmessage(char userid[7])
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.发送给用户 2.发送给管理员 3.查看所有发送记录 4.返回用户信箱界面" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	cout << endl << "输入操作：";
	cin >> f;
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0|| strcmp(f, "4") == 0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			fuser* user = new fuser();
			cout << endl << "请输入您要留言的用户ID：";
			char receiver[20] = { '\0' };
			cin >> receiver;
			if (strcmp(receiver, userid) == 0)
			{
				cout << endl << "不能对自己进行留言功能！即将重新回到发送留言界面";
				Sleep(2000);
				usersendmessage(userid);
			}
			else
			{
				node_user* userhead = user->user_inforead();
				bool userexist = false;
				while (userhead != NULL)
				{
					if (strcmp(userhead->user.userid, receiver) == 0 && strcmp(userhead->user.username, "NULL") != 0)
					{
						userexist = true;
						break;
					}
					userhead = userhead->next;
				}
				if (!userexist)
				{
					cout << endl << "该用户不存在！即将重新回到发送留言界面";
					Sleep(2000);
					usersendmessage(userid);
				}
				else
				{
					smessage(userid, receiver);
					mail_return(userid);
				}
			}
		}
		case(2):
		{
			char receiver[10] = "admin";
			smessage(userid, receiver);
			mail_return(userid);
		}
		case(3):
		{
			node_message* allhead = messageread();
			node_message* head =message_search(userid,allhead);
			bool flag = false;
				while (head != NULL)
				{
					if (strcmp(head->mes.senderid, userid) == 0)
					{
						flag = true;
						cout << endl << "====================================================================================" << endl;
						cout << "留言用户ID：" << head->mes.receiverid<< endl;
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
					cout << endl << "您暂时还未发送留言给其他用户！" << endl;
					mail_return(userid);
				}
				mail_return(userid);
			break;
		}
		case(4):
		{
			usermail(userid);
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
		usersendmessage(userid);
	}
	return;
}

void messagecontact::adminsendmessage()//管理员发出的信息
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.发送给特定用户 2.发送给全体用户 3.取消发送" << endl;
	cout << "====================================================================================" << endl;
	fuser* user = new fuser();
	cout <<endl<< "输入操作：";
	char n1[20];
	cin >> n1;
	node_user* userhead = user->user_inforead();
	if (strcmp(n1, "1") == 0)
	{
		cout << endl << "请输入您要留言的用户ID：";
		char receiver[20] = { '\0' };
		cin >> receiver;
		bool userexist = false;
		while (userhead != NULL)
		{
			if (strcmp(userhead->user.userid, receiver) == 0)
			{
				if (strcmp(userhead->user.username, "NULL") != 0)
				{
					userexist = true;
					break;
				}
				else
					break;
			}
			userhead = userhead->next;
		}
		if (!userexist)
		{
			cout << endl << "该用户不存在！即将重新回到发送留言界面";
			Sleep(2000);
			adminsendmessage();
		}
		else
		{
			char adminname[10] = "admin";
			smessage(adminname, receiver);
			adminmail_return();
		}
	}
	else if (strcmp(n1, "2") == 0)
	{
		cout << endl << "请输入您要发送的留言：";
		char message[201];
		cin >> message;

		time_t rawtime;
		struct tm* ptminfo;
		time(&rawtime);
		ptminfo = localtime(&rawtime);

		FILE* fp = fopen("message.txt", "a+");
		if (fp == NULL)
		{
			printf("Open Failed\n");
			exit(-1);
		}
		while (userhead != NULL)
		{
			if(strcmp(userhead->user.username,"NULL")!=0)
				fprintf(fp, "%s,%s,%s,%02d-%02d-%02d-%02d:%02d,%s\n", "admin", userhead->user.userid, "0", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, message);
			userhead = userhead->next;
		}
		fclose(fp);
		cout << endl << "发送成功！";
		adminmail_return();
	}
	else if (strcmp(n1, "3") == 0)
	{
		adminmailsend();
	}
	else
	{
		cout << endl << "无效选择！" << endl;
		adminsendmessage();
	}
	return;
}

void messagecontact::confirm(node_message*head)
{
	cout << endl << "确认已读吗？（y/n）：";
	char choose[20];
	cin >> choose;
	if (strcmp(choose, "y") == 0)
		head->mes.state = true;
	else if (strcmp(choose, "n") == 0)
		head->mes.state = false;
	else
	{
		cout << endl << "请以正确的格式输入！" << endl;
		confirm(head);
	}
	return;
}

void messagecontact::sendback(char userid[],char receiver[])
{
	cout << endl << "需要回复该留言吗？（y/n）：";
	char choose[20];
	cin >> choose;
	if (strcmp(choose, "y") == 0)
	{
		smessage(userid, receiver);
		return;
	}
	else if (strcmp(choose, "n") == 0)
		return;
	else
	{
		cout << endl << "请以正确的格式输入！" << endl;
		sendback(userid,receiver);
	}
	return;
}

void messagecontact::unreadmessagedisplay(char userid[7])
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.查看未读用户留言 2.查看未读系统留言 3.返回用户信箱界面" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	cout << endl << "输入操作：";
	cin >> f;
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			node_message* head =messageread();
			node_message* p = head;
			bool flag = false;
			while (head != NULL)
			{
				if (strcmp(head->mes.senderid, "admin") != 0 && strcmp(head->mes.receiverid, userid) == 0&&head->mes.state==false)
				{
		
					flag = true;
					cout << endl << "====================================================================================" << endl;
					cout << "留言用户ID：" << head->mes.senderid << endl;
					cout << "留言内容：" << head->mes.message << endl;
					cout << "留言时间：" << head->mes.date << endl;
					cout << "====================================================================================" << endl;
					confirm(head);
					messagewrite(p);
					sendback(userid, head->mes.senderid);
				}
				head = head->next;
			}
			if (!flag)
			{
				cout << endl << "当前没有未读的其他用户留言" << endl;
				mail_return(userid);
			}
			mail_return(userid);
			break;
		}
		case(2):
		{
			node_message* allhead = messageread();
			node_message* p = allhead;
			bool flag = false;
			while (allhead != NULL)
			{
				if (strcmp(allhead->mes.senderid, "admin") == 0 && strcmp(allhead->mes.receiverid, userid) == 0 && allhead->mes.state ==false)
				{
					flag = true;
					cout << endl << "====================================================================================" << endl;
					cout << "管理员系统留言：" << "from admin" << endl;
					cout << "留言内容：" << allhead->mes.message << endl;
					cout << "留言时间：" << allhead->mes.date << endl;
					cout << "====================================================================================" << endl;
					confirm(allhead);
					messagewrite(p);
					char adminid[7] = "admin";
					sendback(userid,adminid);
				}
				allhead = allhead->next;
			}
			if (!flag)
			{
				cout << endl << "当前没有未读的管理员系统留言" << endl;
				mail_return(userid);
			}
			mail_return(userid);
			break;
		}
		case(3):
		{
			usermail(userid);
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
		unreadmessagedisplay(userid);
	}
	return;
}

void messagecontact::historymessagedisplay(char userid[7])
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.查看所有已读用户留言 2.查看所有已读系统留言 3.返回用户信箱界面" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
	cout << endl << "输入操作：";
	cin >> f;
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") ==0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			node_message* allhead = messageread();
			node_message* head = message_search(userid,allhead);
			bool flag = false;
				while (head != NULL)
				{
					if (strcmp(head->mes.senderid,"admin")!= 0&&strcmp(head->mes.receiverid, userid) == 0&&head->mes.state==true)
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
				cout << endl << "您暂时还未收到其他用户的留言" << endl;
				mail_return(userid);
			}
				mail_return(userid);
			break;
		}
		case(2):
		{
			node_message* allhead = messageread();
			node_message* head = message_search(userid,allhead);
			bool flag = false;
			while (head != NULL)
			{
				if (strcmp(head->mes.senderid, "admin")== 0 &&strcmp(head->mes.receiverid, userid) == 0&& head->mes.state == true)
				{
					flag = true;
					cout << endl << "====================================================================================" << endl;
					cout << "管理员系统留言：" <<"from admin"<< endl;
					cout << "留言内容：" << head->mes.message << endl;
					cout << "留言时间：" << head->mes.date << endl;
					cout << "====================================================================================" << endl;
				}
				head = head->next;
			}
			if (!flag)
			{
				cout << endl << "您暂时还未收到管理员系统的留言" << endl;
				mail_return(userid);
			}
			mail_return(userid);
			break;
		}
		case(3):
		{
			usermail(userid);
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
		historymessagedisplay(userid);
	}
	return;
}