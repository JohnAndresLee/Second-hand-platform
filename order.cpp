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
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", "订单ID", "商品ID", "交易金额", "交易时间", "卖家ID", "买家ID","买家评论","卖家得分");
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
		cout << endl << "您确定要购买此商品吗？（y/n）：";
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
				fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", "订单ID", "商品ID", "交易金额", "交易时间", "卖家ID", "买家ID", "买家评论", "卖家得分");
			fprintf(fp, "%s,%s,%s,%02d-%02d-%02d,%s,%s,%s,%s\n", orderid,p->com.comid,p->com.price,ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,seller->user.userid,user->user.userid,"NULL","NULL");
			fclose(fp);

			cout << endl << endl << "************************************************************************************";
			cout << endl<<"交易提醒！";
			cout << endl << "交易时间："<< ptminfo->tm_year + 1900<<"-"<<ptminfo->tm_mon + 1<<"-"<<ptminfo->tm_mday;
			cout << endl << "交易金额：" << p->com.price;
			cout << endl << "交易状态：交易成功";
			cout << endl << "余额："<<user->user.balance;
			cout << endl << "************************************************************************************";
			return;
		}
		else if (strcmp(choose, "n") == 0)
			buyer_return(userid);
		else
		{
			cout << endl << "请输入正确的格式!";
			order_formation(userid, p, head, user,seller);
		}
	}
	else
	{
		cout << endl << endl << "************************************************************************************";
		cout << endl << "交易提醒！";
		cout << endl<<"交易状态：交易失败";
		cout <<endl<< "失败原因：余额不足！请至个人中心进行充值";
		cout <<endl << "************************************************************************************";
		buyer_return(userid);
	}
	return;
}

void order::labelnumber(char orderid[7], node_order* head)//为新订单新建ID
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


void order::order_view()//查看所有订单
{
	node_order*head = orderread();
	cout<<endl << "************************************************************************************";
	if (head == NULL)
		cout<<endl<< "                               本平台暂无订单信息！"<<endl;
	else
	{
		cout << endl <<left<<setw(10)<<"订单ID" <<setw(10)<< "商品ID" <<setw(14)<< "交易金额" <<setw(14)<< "交易时间" << setw(10) << "卖家ID" <<setw(10)<< "买家ID"<<setw(10)<<"买家评分";
		while (head != NULL)
		{
			cout << endl << left<<setw(10)<<head->order.orderid << setw(10)<< head->order.comid <<setw(14) << head->order.trademoney <<setw(14) << head->order.time <<setw(10)<< head->order.sellerid <<setw(10)<< head->order.buyerid<<head->order.sellerscore;
			head = head->next;
		}
	}
	cout<<endl<<"************************************************************************************";
	return;
}

void order::order_buyeridquery(char buyid[])//查询买家的订单
{
	node_order* head = orderread();
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->order.buyerid, buyid) == 0)
		{
			cout << endl << "************************************************************************************";
			cout << endl << left << setw(10) << "订单ID" << setw(10) << "商品ID" << setw(14) << "交易金额" << setw(14) << "交易时间" << setw(10) << "卖家ID" << setw(10) << "买家ID";
			cout << endl << left << setw(10) << head->order.orderid << setw(10) << head->order.comid << setw(14) << head->order.trademoney << setw(14) << head->order.time << setw(10) << head->order.sellerid << setw(10) << head->order.buyerid;
			cout << endl << "商品评价：" << head->order.buyerevaluation << endl;
			cout << "买家满意度（满分五分）：" << head->order.sellerscore << endl;
			cout<< "************************************************************************************";
			flag = true;
		}	
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "************************************************************************************";
		cout<< "                              您暂无购买商品的订单！";
		cout << endl << "************************************************************************************" << endl;
	}
	return;
}

void order::order_evaluate(char buyerid[],node_order*order)
{
	cout << endl << "请为该商品的卖家评分（满分5分）：";
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
		cout << endl << "请输入5以内的非负整数！";
		order_evaluate(buyerid,order);
	}
	cout << endl << "请输入您对本次该商品的评价：";
	char evaluate[50];
	cin >> evaluate;
	int i = 0;
	while (evaluate[i] != '\0')
	{
		order->order.buyerevaluation[i] = evaluate[i];
		++i;
	}
	order->order.buyerevaluation[i] = '\0';
	cout <<endl<<"请对本平台提供的服务打分：";
	char score0[5];
	cin >> score0;
	while(strcmp(score0, "0") != 0&&strcmp(score0, "1") != 0&&strcmp(score0, "2") != 0&&strcmp(score0, "3") != 0&&strcmp(score0, "4") != 0&&strcmp(score0, "5") != 0)
	{
		cout << endl << "请输入5以内的非负整数！";
		cin >> score0;
	}
	cout << endl << "感谢您此次的评价，您的评价是我们不断提高的动力！"<<endl;
	
}

void order::order_selleridquery(char sellerid[])//查询卖家的订单
{
	node_order* head = orderread();
	bool flag = false;
	while (head != NULL)
	{
		if (strcmp(head->order.sellerid, sellerid) == 0)
		{
			cout << endl << "************************************************************************************";
			cout << endl << left << setw(10) << "订单ID" << setw(10) << "商品ID" << setw(14) << "交易金额" << setw(14) << "交易时间" << setw(10) << "卖家ID" << setw(10) << "买家ID";
			cout << endl << left << setw(10) << head->order.orderid << setw(10) << head->order.comid << setw(14) << head->order.trademoney << setw(14) << head->order.time << setw(10) << head->order.sellerid << setw(10) << head->order.buyerid;
			cout << endl << "商品评价：" << head->order.buyerevaluation<<endl;
			cout << "买家满意度（满分五分）：" << head->order.sellerscore<<endl;
			cout<< "************************************************************************************";
			flag = true;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << endl << "************************************************************************************" << endl;
		cout<< "                                暂无卖出商品的订单！";
		cout << endl << "************************************************************************************" << endl;
	}
	return;

}