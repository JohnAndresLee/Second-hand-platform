#pragma once
struct comlist
{
	char comid[7];
	comlist* next;
};

struct shopping
{
	char userid[7];
	comlist*com;
	shopping* next;
};

void shopcart_main(char userid[7], char comid[]);//购物车功能的主函数

void shopcart_write(shopping* head);//将各用户购物车信息写入文件

shopping* shopcart_read();//从文件中读取各用户购物车信息
comlist*shopcart_noderead(char list[], comlist* head);

void shopcart_delete(char userid[], char comid[]);//将商品移除购物车

bool shopcart_display(char userid[]);//显示购物车的功能
