#pragma once
#include"user.h"
#include"commodity.h"

struct orderinfo
{
	char orderid[7];
	char comid[7];
	char trademoney[10];
	char time[11];
	char sellerid[7];
	char buyerid[7];
	char buyerevaluation[50];
	char sellerscore[5];
};

struct node_order
{
	orderinfo order;
	node_order* next;
};

node_order* orderread();

class order
{
public:
	void orderwrite(node_order* head);

	void labelnumber(char orderid[7], node_order* head);//为新订单新建ID

	void order_formation(char userid[],node_com*p,node_com*head,node_user*user,node_user*seller);

	void order_view();//查看所有订单

	void order_buyeridquery(char buyerid[]);//查询买家的订单

	void order_selleridquery(char sellerid[]);//查询卖家的订单

	void order_evaluate(char buyerid[], node_order* order);//对订单进行评价
private:

};

