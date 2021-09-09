#define _CRT_SECURE_NO_WARNINGS

#include "user.h"
#include<iostream>
#include"adminmainwindow.h"
#include"login.h"
#include<Windows.h>
#include<cstdio>
#include<ctime>
#include"usermainwindow.h"
#include"plus.h"
#include<iomanip>
#include"commodity.h"

using namespace std;

void noderead(char* list, node_user* p)
{
	int len = strlen(list);
	for (int j = 0;;)
	{
		int temp = 0;
		while (list[j] != ',')
			p->user.userid[temp++]= list[j++];
		p->user.userid[temp] = '\0';
		++j;
		temp = 0;
		while (list[j] != ',')
			p->user.username[temp++] = list[j++];
		++j;
		p->user.username[temp] = '\0';
		if (strcmp(p->user.username, "NULL") == 0)
		{
			p->user.flag = false;
			break;
		}
		else
		{
			temp = 0;
			while (list[j] != ',')
				p->user.userkey[temp++] = list[j++];
			++j;
			p->user.userkey[temp] = '\0';
			temp = 0;
			while (list[j] != ',')
				p->user.contactinfo[temp++] = list[j++];
			++j;
			p->user.contactinfo[temp] = '\0';
			temp = 0;
			while (list[j] != ',')
				p->user.address[temp++] = list[j++];
			++j;
			p->user.address[temp] = '\0';
			temp = 0;
			while (list[j] != ',')
				p->user.balance[temp++] = list[j++];
			++j;
			p->user.balance[temp] = '\0';
			temp = 0;
			while (list[j] != '\0')
				p->user.signdate[temp++] = list[j++];
			++j;
			p->user.signdate[temp] = '\0';
			break;
		}
	}
	return;
}

void fuser::userwrite(node_user*head)
{
	node_user* p = head;
	FILE* fp = fopen("user.txt", "w");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n","用户ID","用户名","密码","联系方式", "地址","钱包余额","注册时间");
	while (p != NULL)
	{
		if(p->user.flag)
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", p->user.userid, p->user.username,p->user.userkey,p->user.contactinfo, p->user.address, p->user.balance,p->user.signdate);
		else
			fprintf(fp, "%s,%s\n", p->user.userid, "NULL");
		p = p->next;
	}
	fclose(fp);
}

void fuser::usersignin()
{
	cout <<endl<<"请输入用户名：";
	char name[11] = { '\0' }, key1[21] = { '\0' }, key2[21] = {'\0'};
	cin >> name;
	if (searchusername(name)&&strcmp(name,"NULL")!=0&&strcmp(name, "admin") != 0)
	{
		cout << endl<<"请输入密码：";
		cin >> key1;
		cout <<endl<< "请确认密码：";
		cin >> key2;
		if (strcmp(key1, key2) == 0)
		{
			char userid[7] = {'\0'};
			labelnumber(userid);
			
			time_t rawtime;
			struct tm* ptminfo;
			time(&rawtime);
			ptminfo = localtime(&rawtime);

			FILE* fp = fopen("user.txt", "a+");
			if (fp == NULL)
			{
				printf("Open Failed\n");
				exit(-1);
			}
			if (user_inforead() == NULL)
				fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", "用户ID", "用户名", "密码", "联系方式", "地址", "钱包余额", "注册时间");
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%02d-%02d-%02d\n",userid,name, key1,"NULL", "NULL", "0.0", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday);
			fclose(fp);
			cout << "***************************注册成功！即将重新返回登录界面***************************"<<endl;
			Sleep(2000);
			login();
		}
		else
		{
			cout << "密码输入不一致，请重新注册";
			usersignin();
		}
	}
	else
	{
		cout << endl << "*****************************该用户名已被注册，请重新输入！*****************************"<<endl;
		usersignin();
	}
}

node_user* fuser::user_inforead()//读入文件中用户信息
{
	node_user* head = NULL;
	node_user* tail = NULL;
	FILE* fp = fopen("user.txt", "r");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	char list[200];
	fscanf(fp, "%s", list);
	while (!feof(fp))
	{
		if (fscanf(fp, "%s", list) != EOF)
		{
			node_user* p = new node_user;
			if (head == NULL)
			{
				noderead(list, p);
				head = p;
			}
			else
			{
				noderead(list, p);
				tail->next = p;
			}
			p->next = NULL;
			tail = p;
		}
	}
	fclose(fp);
	return head;
}


bool fuser::searchusername(const char* username)
{
	node_user* head = user_inforead();
	while (head != NULL)
	{
		if (strcmp(head->user.username, username) == 0)
			return false;
		head = head->next;
	}
	return true;
}

void fuser::user_view()//查询所有用户
{
	node_user* head = user_inforead();
	node_user* p = head;
	cout << endl << "************************************************************************************" << endl;
	cout <<left<<setw(10)<<"用户ID" <<setw(14)<< "用户名" <<setw(24)<< "联系方式" << setw(24) << "地址" << setw(10) << "钱包余额"<<endl;
	while (p != NULL)
	{
		if (p->user.flag)		
			cout <<left<<setw(10)<<p->user.userid <<setw(14)<< p->user.username <<setw(24)<< p->user.contactinfo <<setw(24) << p->user.address <<setw(10)<< p->user.balance<< endl;
		p = p->next;
	}
	cout << "************************************************************************************" << endl;
}

void fuser::user_delete(const char* userid)//删除用户
{
		node_user* head = user_inforead();
		node_user* p = user_owninfoview(userid, head);
		if (p == NULL)
		{
			commodityreturn();
		}
		else
		{
			cout << endl << "确认要删除该用户吗：" << endl;
				cout << endl << "请选择（y/n）：";
				char choose[20];
				cin >> choose;
				bool  flag = true;
				while (flag)
				{
					if (strcmp(choose, "y") == 0)
					{
						p->user.flag = false;
						cout << endl << "删除成功！" << endl;
						node_com* comhead = commodityread();
						node_com* p = comhead;
						while (p != NULL)
						{
							if (strcmp(p->com.sellerid, userid) == 0 && p->com.s == on_sale)
								p->com.s = off_shelf;
							p = p->next;
						}
						fcommodity* fcom = new fcommodity();
						fcom->commoditywrite(comhead);
						userwrite(head);
						structdeleteuser(head);
						flag = false;
					}
					else if (strcmp(choose, "n") == 0)
						commodityreturn();
					else
					{
						cout <<endl<< "请输入正确的格式!";
						user_delete(userid);
					}
				}
				commodityreturn();
		}
}

node_user*fuser::user_owninfoview(const char*userid,node_user* head)//查看用户个人信息
{
	node_user* p = head;
	while (p != NULL)
	{
		if (p->user.flag)
		{
			if (strcmp(userid, p->user.userid) == 0)
			{
				cout << endl << "************************************************************************************" << endl;
				cout << "用户名：" << p->user.username << endl << "联系方式：" << p->user.contactinfo << endl << "地址：" << p->user.address << endl << "钱包余额：" << p->user.balance << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              没有找到您想搜索的用户！";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
}

void fuser::labelnumber(char id[7])//为新用户新建ID
{
	node_user* head = user_inforead();
	if (head == NULL)
	{
		id[0] = 'U';
		for (int w = 1; w <= 4; ++w)
			id[w] ='0';
		id[5] = '1';
		id[6] = '\0';
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		int i = 5;
		while (head->user.userid[i] == '9')
		{
			id[i] = '0';
			i--;
		}
		id[i] = head->user.userid[i] + 1;
		for (int k = i - 1; k >= 0; --k)
			id[k] = head->user.userid[k];
	}
	return;
}

void fuser::userlogin()
{
	cout << "请输入用户名：";
	char name[11], keyinput[21];
	cin >> name;
	cout << "请输入密码：";
	cin >> keyinput;
	node_user* head = user_inforead();
	node_user* p = head;
	bool flag = false;
	while (p != NULL)
	{
		if (p->user.flag)
		{
			if (strcmp(name, p->user.username) == 0)
			{
				
				if (strcmp(keyinput, p->user.userkey) == 0)
				{
					cout << "*************************登陆成功！即将自动跳转到用户主界面*************************";
					flag = true;
					Sleep(2000);
					usermainwindow(p->user.userid);
				}
				else
				{
					cout << "*************************用户名或密码错误！即将回到登录界面*************************" << endl;
					flag = true;
					Sleep(2000);
					login();
				}
			}
		}
		p = p->next;
	}
	if (!flag)
	{
		cout << "***************************该用户不存在！即将回到登录界面***************************" << endl;
		Sleep(2000);
		login();
	}
	return;
}

void fuser::user_infomanage(char userid[7])//用户个人信息修改
{
	system("cls");
	cout << "===============================欢迎使用二手交易平台！===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.返回用户主界面 2.修改信息 3.查看信息 4.充值" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
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
			usermainwindow(userid);
			break;
		}
		case(2):
		{
			userinfo_change(userid);
			userinfochange_return(userid);
			break;
		}
		case(3):
		{
			node_user* head = user_inforead();
			node_user* p = user_owninfoview(userid, head);
			userinfochange_return(userid);
			break;
		}
		case(4):
		{
			node_user* head = user_inforead();
			node_user* p = user_owninfoview(userid, head);
			userbalencechange(head, p);
			userinfochange_return(userid);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		cout << endl << "*******************************请以正确格式重新输入！*******************************";
		Sleep(2000);
		system("cls");
		user_infomanage(userid);
	}
}




void fuser::userinfo_change(char userid[7])
{
	node_user* head = user_inforead();
	node_user* p = user_owninfoview(userid, head);
	cout << endl << "请输入修改的属性（1.用户名 2.联系方式 3.地址）:";
	char f[20];
	cout << endl << "输入操作：";
	cin >> f;
	fuser* userfunction = new fuser();
	if (strcmp(f, "1") == 0 || strcmp(f, "2") == 0 || strcmp(f, "3") == 0)
	{
		int n;
		n = f[0] - 48;
		switch (n)
		{
		case(1):
		{
			usernamechange(head, p);
			break;
		}
		case(2):
		{
			usercontactchange(head, p);
			break;
		}
		case(3):
		{
			useraddresschange(head,p);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		cout << endl << "**********************请以正确格式输入！即将自动跳转至上级界面**********************";
		Sleep(2000);
		user_infomanage(userid);
	}
}
void fuser::usernamechange(node_user*head,node_user*p)
{
	fuser* f = new fuser();
	cout << endl << "请输入修改后的用户名：";
	char newname[11];
	cin >> newname;
	if (f->searchusername(newname))
	{
		int i = 0;
		while (newname[i] != '\0')
		{
			p->user.username[i] = newname[i];
			i++;
		}
		p->user.username[i] = '\0';
		cout << "修改成功！"<<endl;
		userwrite(head);
	}
	else
	{
		cout << "该用户名已被注册，请重新输入！"<<endl;
		usernamechange(head, p);
	}
}
void fuser::usercontactchange(node_user* head, node_user* p)
{
	fuser* f = new fuser();
	cout << endl << "请输入修改后的联系方式：";
	char newcontact[21];
	cin >> newcontact;
	int i = 0;
	while (newcontact[i] != '\0')
	{
		p->user.contactinfo[i] = newcontact[i];
		i++;
	}
	p->user.contactinfo[i] = '\0';
	cout <<endl<< "修改成功！"<<endl;
	userwrite(head);
}
void fuser::useraddresschange(node_user* head, node_user* p)
{
	fuser* f = new fuser();
	cout << endl << "请输入修改后的联系方式：";
	char newaddress[21];
	cin >> newaddress;
	int i = 0;
	while (newaddress[i] != '\0')
	{
		p->user.address[i] = newaddress[i];
		i++;
	}
	p->user.address[i] = '\0';
	cout << endl << "修改成功！"<<endl;
	userwrite(head);
}

void fuser::userbalencechange(node_user* head, node_user* p)
{
	fuser* f = new fuser();
	cout << endl << "请输入充值数目：";
	char balence[10];
	cin >> balence;
	if (balence[0] == '-')
	{
		cout << "充值金额不能为负！"<<endl;
		userbalencechange(head, p);
	}
	else
	{
		char newbalence[10];
		fplus(balence, p->user.balance, newbalence);
		int i = 0;
		while (newbalence[i] != '\0')
		{
			p->user.balance[i] = newbalence[i];
			i++;
		}
		p->user.balance[i] = '\0';
		cout << endl << "修改成功！" << endl;
		userwrite(head);
	}
}

void fuser::user_contact()//用户的留言功能
{

}