#define _CRT_SECURE_NO_WARNINGS

#include "order.h"
#include<iostream>
#include"buyerwindow.h"
#include"commodity.h"
#include"user.h"
#include"minus.h"
#include"plus.h"
#include<iomanip>

using namespace std;

void noderead(char* list, node_order* p)
{
	int len = strlen(list);
	int j = 0;
		int temp = 0;
		while (list[j] != ',')
			p->order.orderid[temp++] = list[j++];
		p->order.orderid[temp] = '\0';
		++j;
		temp = 0;
		while (list[j] != ',')
			p->order.comid[temp++] = list[j++];
		++j;
		p->order.comid[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->order.trademoney[temp++] = list[j++];
		++j;
		p->order.trademoney[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->order.time[temp++] = list[j++];
		++j;
		p->order.time[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->order.sellerid[temp++] = list[j++];
		++j;
		p->order.sellerid[temp] = '\0';
		temp = 0;
		while (list[j] != ',')
			p->order.buyerid[temp++] = list[j++];
		++j;
		p->order.buyerid[temp] = '\0';
		temp = 0;

		while (list[j] != ',')
			p->order.buyerevaluation[temp++] = list[j++];
		++j;
		p->order.buyerevaluation[temp] = '\0';
		temp = 0;
		while (list[j] != '\0')
			p->order.sellerscore[temp++] = list[j++];
		++j;
		p->order.sellerscore[temp] = '\0';
		temp = 0;
	return;
}

node_order* orderread()
{
	node_order* head = NULL;
	node_order* tail = NULL;
	FILE* fp = fopen("order.txt", "r");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	char list[201];
	fscanf(fp, "%s", list);
	while (!feof(fp))
	{
		if (fscanf(fp, "%s", list) != EOF)
		{
			node_order* p = new node_order;
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

void order::orderwrite(node_order* head)
{
	node_order* p = head;
	FILE* fp = fopen("order.txt", "w");
	if (fp == NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", "????ID", "????ID", "????????", "????????", "????ID", "????ID","????????","????????");
	while (p != NULL)
	{
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", p->order.orderid, p->order.comid, p->order.trademoney, p->order.time, p->order.sellerid, p->order.buyerid,p->order.buyerevaluation,p->order.sellerscore);
		p = p->next;
	}
	fclose(fp);
}

void order::order_formation(char userid[], node_com* p, node_com* head,node_user*user, node_user* seller)
{
	if (judge(user->user.balance, p->com.price))
	{
		cout << endl << "????????????????????????y/n????";
		char choose[20];
		cin >> choose;
		if (strcmp(choose, "y") == 0)
		{
			p->com.s = sold_out;
			char balence[10];		
			char balenceseller[10];
			fminus(user->user.balance, p->com.price,balence);	
			fplus(seller->user.balance, p->com.price, balenceseller);
			int i = 0;
			while (balence[i] != '\0')
			{
				user->user.balance[i] = balence[i];
				i++;
			}
			user->user.balance[i] = '\0';
			i = 0;
			while (balence[i] != '\0')
			{
				seller->user.balance[i] = balenceseller[i];
				i++;
			}
			seller->user.balance[i] = '\0';

			char orderid[7] = { '\0' };
			node_order*orderhead=orderread();
			labelnumber(orderid, orderhead);

			time_t rawtime;
			struct tm* ptminfo;
			time(&rawtime);
			ptminfo = localtime(&rawtime);

			FILE* fp = fopen("order.txt", "a+");
			if (fp == NULL)
			{
				printf("Open Failed\n");
				exit(-1); 
			}
			if (orderread() == NULL)
				fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", "????ID", "????ID", "????????", "????????", "????ID", "????ID", "????????", "????????");
			fprintf(fp, "%s,%s,%s,%02d-%02d-%02d,%s,%s,%s,%s\n", orderid,p->com.comid,p->com.price,ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,seller->user.userid,user->user.userid,"NULL","NULL");
			fclose(fp);

			cout << endl << endl << "************************************************************************************";
			cout << endl<<"??????????";
			cout << endl << "??????????"<< ptminfo->tm_year + 1900<<"-"<<ptminfo->tm_mon + 1<<"-"<<ptminfo->tm_mday;
			cout << endl << "??????????" << p->com.price;
			cout << endl << "??????????????????";
			cout << endl << "??????"<<user->user.balance;
			cout << endl << "************************************************************************************";
			return;
		}
		else if (strcmp(choose, "n") == 0)
			buyer_return(userid);
		else
		{
			cout << endl << "????????????????!";
			order_formation(userid, p, head, user,seller);
		}
	}
	else
	{
		cout << endl << endl << "************************************************************************************";
		cout << endl << "??????????";
		cout << endl<<"??????????????????";
		cout <<endl<< "????????????????????????????????????????";
		cout <<endl << "************************************************************************************";
		buyer_return(userid);
	}
	return;
}

void order::labelnumber(char orderid[7], node_order* head)//????????????ID
{
	if (head == NULL)
	{
		orderid[0] = 'T';
		for (int w = 1; w <= 4; ++w)
			orderid[w] = '0';
		orderid[5] = '1';
		orderid[6] = '\0';
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		int i = 5;
		while (head->order.orderid[i]== '9')
		{
			orderid[i] = '0';
			i--;
		}
		orderid[i] = head->order.orderid[i] + 1;
		for (int k = i - 1; k >= 0; --k)
			orderid[k] = head->order.orderid[k];
	}
	return;
}


void order::order_view()//????????????
{
	node_order*head = orderread();
	cout<<endl << "************************************************************************************";
	if (head == NULL)
		cout<<endl<< "                               ????????????????????"<<endl;
	else
	{
		cout << endl <<left<<setw(10)<<"????ID" <<setw(10)<< "????ID" <<setw(14)<< "????????" <<setw(14)<< "????????" << setw(10) << "????ID" <<setw(10)<< "????ID"<<setw(10)<<"????????";
		while (head != NULL)
		{
			cout << endl << left<<setw(10)<<head->order.orderid << setw(10)<< head->order.comid <<setw(14) << head->order.trademoney <<setw(14) << head->order.time <<setw(10)<< head->order.sellerid <<setw(10)<< head->order.buyerid<<head->order.sellerscore;
			head = head->next;
		}
	}
	cout<<endl<<"************************************************************************************";
	return;
}

void order::order_buyeridquery(char buyid[])//??????????????
{
	node_order* head = orderread();
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->order.buyerid, buyid) == 0)
		{
			cout << endl << "************************************************************************************";
			cout << endl << left << setw(10) << "????ID" << setw(10) << "????ID" << setw(14) << "????????" << setw(14) << "????????" << setw(10) << "????ID" << setw(10) << "????ID";
			cout << endl << left << setw(10) << head->order.orderid << setw(10) << head->order.comid << setw(14) << head->order.trademoney << setw(14) << head->order.time << setw(10) << head->order.sellerid << setw(10) << head->order.buyerid;
			cout << endl << "??????????" << head->order.buyerevaluation << endl;
			cout << "????????????????????????" << head->order.sellerscore << endl;
			cout<< "************************************************************************************";
			flag = true;
		}	
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "************************************************************************************";
		cout<< "                              ??????????????????????";
		cout << endl << "************************************************************************************" << endl;
	}
	return;
}

void order::order_evaluate(char buyerid[],node_order*order)
{
	cout << endl << "??????????????????????????5??????";
	char score[5];
	cin >> score;
	if (strcmp(score, "0") == 0 || strcmp(score, "1") == 0 || strcmp(score, "2") == 0 || strcmp(score, "3") == 0 || strcmp(score, "4") == 0 || strcmp(score, "5") == 0)
	{
		int j= 0;
		while (score[j] != '\0')
		{
			order->order.sellerscore[j] = score[j];
			j++;
		}
		order->order.sellerscore[j] = '\0';
	}
	else
	{
		cout << endl << "??????5????????????????";
		order_evaluate(buyerid,order);
	}
	cout << endl << "????????????????????????????";
	char evaluate[50];
	cin >> evaluate;
	int i = 0;
	while (evaluate[i] != '\0')
	{
		order->order.buyerevaluation[i] = evaluate[i];
		++i;
	}
	order->order.buyerevaluation[i] = '\0';
	cout <<endl<<"??????????????????????????";
	char score0[5];
	cin >> score0;
	while(strcmp(score0, "0") != 0&&strcmp(score0, "1") != 0&&strcmp(score0, "2") != 0&&strcmp(score0, "3") != 0&&strcmp(score0, "4") != 0&&strcmp(score0, "5") != 0)
	{
		cout << endl << "??????5????????????????";
		cin >> score0;
	}
	cout << endl << "????????????????????????????????????????????????"<<endl;
	
}

void order::order_selleridquery(char sellerid[])//??????????????
{
	node_order* head = orderread();
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->order.sellerid, sellerid) == 0)
		{
			cout << endl << "************************************************************************************";
			cout << endl << left << setw(10) << "????ID" << setw(10) << "????ID" << setw(14) << "????????" << setw(14) << "????????" << setw(10) << "????ID" << setw(10) << "????ID";
			cout << endl << left << setw(10) << head->order.orderid << setw(10) << head->order.comid << setw(14) << head->order.trademoney << setw(14) << head->order.time << setw(10) << head->order.sellerid << setw(10) << head->order.buyerid;
			cout << endl << "??????????" << head->order.buyerevaluation<<endl;
			cout << "????????????????????????" << head->order.sellerscore<<endl;
			cout<< "************************************************************************************";
			flag = true;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "************************************************************************************" << endl;
		cout<< "                                ????????????????????";
		cout << endl << "************************************************************************************" << endl;
	}
	return;

}