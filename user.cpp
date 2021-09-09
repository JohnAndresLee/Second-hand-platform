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
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n","�û�ID","�û���","����","��ϵ��ʽ", "��ַ","Ǯ�����","ע��ʱ��");
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
	cout <<endl<<"�������û�����";
	char name[11] = { '\0' }, key1[21] = { '\0' }, key2[21] = {'\0'};
	cin >> name;
	if (searchusername(name)&&strcmp(name,"NULL")!=0&&strcmp(name, "admin") != 0)
	{
		cout << endl<<"���������룺";
		cin >> key1;
		cout <<endl<< "��ȷ�����룺";
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
				fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", "�û�ID", "�û���", "����", "��ϵ��ʽ", "��ַ", "Ǯ�����", "ע��ʱ��");
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%02d-%02d-%02d\n",userid,name, key1,"NULL", "NULL", "0.0", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday);
			fclose(fp);
			cout << "***************************ע��ɹ����������·��ص�¼����***************************"<<endl;
			Sleep(2000);
			login();
		}
		else
		{
			cout << "�������벻һ�£�������ע��";
			usersignin();
		}
	}
	else
	{
		cout << endl << "*****************************���û����ѱ�ע�ᣬ���������룡*****************************"<<endl;
		usersignin();
	}
}

node_user* fuser::user_inforead()//�����ļ����û���Ϣ
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

void fuser::user_view()//��ѯ�����û�
{
	node_user* head = user_inforead();
	node_user* p = head;
	cout << endl << "************************************************************************************" << endl;
	cout <<left<<setw(10)<<"�û�ID" <<setw(14)<< "�û���" <<setw(24)<< "��ϵ��ʽ" << setw(24) << "��ַ" << setw(10) << "Ǯ�����"<<endl;
	while (p != NULL)
	{
		if (p->user.flag)		
			cout <<left<<setw(10)<<p->user.userid <<setw(14)<< p->user.username <<setw(24)<< p->user.contactinfo <<setw(24) << p->user.address <<setw(10)<< p->user.balance<< endl;
		p = p->next;
	}
	cout << "************************************************************************************" << endl;
}

void fuser::user_delete(const char* userid)//ɾ���û�
{
		node_user* head = user_inforead();
		node_user* p = user_owninfoview(userid, head);
		if (p == NULL)
		{
			commodityreturn();
		}
		else
		{
			cout << endl << "ȷ��Ҫɾ�����û���" << endl;
				cout << endl << "��ѡ��y/n����";
				char choose[20];
				cin >> choose;
				bool  flag = true;
				while (flag)
				{
					if (strcmp(choose, "y") == 0)
					{
						p->user.flag = false;
						cout << endl << "ɾ���ɹ���" << endl;
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
						cout <<endl<< "��������ȷ�ĸ�ʽ!";
						user_delete(userid);
					}
				}
				commodityreturn();
		}
}

node_user*fuser::user_owninfoview(const char*userid,node_user* head)//�鿴�û�������Ϣ
{
	node_user* p = head;
	while (p != NULL)
	{
		if (p->user.flag)
		{
			if (strcmp(userid, p->user.userid) == 0)
			{
				cout << endl << "************************************************************************************" << endl;
				cout << "�û�����" << p->user.username << endl << "��ϵ��ʽ��" << p->user.contactinfo << endl << "��ַ��" << p->user.address << endl << "Ǯ����" << p->user.balance << endl;
				cout << "************************************************************************************" << endl;
				return p;
			}
		}
		p = p->next;
	}
	cout << endl << "************************************************************************************" << endl;
	cout << "                              û���ҵ������������û���";
	cout << endl << "************************************************************************************" << endl;
	return NULL;
}

void fuser::labelnumber(char id[7])//Ϊ���û��½�ID
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
	cout << "�������û�����";
	char name[11], keyinput[21];
	cin >> name;
	cout << "���������룺";
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
					cout << "*************************��½�ɹ��������Զ���ת���û�������*************************";
					flag = true;
					Sleep(2000);
					usermainwindow(p->user.userid);
				}
				else
				{
					cout << "*************************�û�����������󣡼����ص���¼����*************************" << endl;
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
		cout << "***************************���û������ڣ������ص���¼����***************************" << endl;
		Sleep(2000);
		login();
	}
	return;
}

void fuser::user_infomanage(char userid[7])//�û�������Ϣ�޸�
{
	system("cls");
	cout << "===============================��ӭʹ�ö��ֽ���ƽ̨��===============================" << endl;
	cout << "====================================================================================" << endl;
	cout << "1.�����û������� 2.�޸���Ϣ 3.�鿴��Ϣ 4.��ֵ" << endl;
	cout << "====================================================================================" << endl;
	char f[20];
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
		cout << endl << "*******************************������ȷ��ʽ�������룡*******************************";
		Sleep(2000);
		system("cls");
		user_infomanage(userid);
	}
}




void fuser::userinfo_change(char userid[7])
{
	node_user* head = user_inforead();
	node_user* p = user_owninfoview(userid, head);
	cout << endl << "�������޸ĵ����ԣ�1.�û��� 2.��ϵ��ʽ 3.��ַ��:";
	char f[20];
	cout << endl << "���������";
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
		cout << endl << "**********************������ȷ��ʽ���룡�����Զ���ת���ϼ�����**********************";
		Sleep(2000);
		user_infomanage(userid);
	}
}
void fuser::usernamechange(node_user*head,node_user*p)
{
	fuser* f = new fuser();
	cout << endl << "�������޸ĺ���û�����";
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
		cout << "�޸ĳɹ���"<<endl;
		userwrite(head);
	}
	else
	{
		cout << "���û����ѱ�ע�ᣬ���������룡"<<endl;
		usernamechange(head, p);
	}
}
void fuser::usercontactchange(node_user* head, node_user* p)
{
	fuser* f = new fuser();
	cout << endl << "�������޸ĺ����ϵ��ʽ��";
	char newcontact[21];
	cin >> newcontact;
	int i = 0;
	while (newcontact[i] != '\0')
	{
		p->user.contactinfo[i] = newcontact[i];
		i++;
	}
	p->user.contactinfo[i] = '\0';
	cout <<endl<< "�޸ĳɹ���"<<endl;
	userwrite(head);
}
void fuser::useraddresschange(node_user* head, node_user* p)
{
	fuser* f = new fuser();
	cout << endl << "�������޸ĺ����ϵ��ʽ��";
	char newaddress[21];
	cin >> newaddress;
	int i = 0;
	while (newaddress[i] != '\0')
	{
		p->user.address[i] = newaddress[i];
		i++;
	}
	p->user.address[i] = '\0';
	cout << endl << "�޸ĳɹ���"<<endl;
	userwrite(head);
}

void fuser::userbalencechange(node_user* head, node_user* p)
{
	fuser* f = new fuser();
	cout << endl << "�������ֵ��Ŀ��";
	char balence[10];
	cin >> balence;
	if (balence[0] == '-')
	{
		cout << "��ֵ����Ϊ����"<<endl;
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
		cout << endl << "�޸ĳɹ���" << endl;
		userwrite(head);
	}
}

void fuser::user_contact()//�û������Թ���
{

}