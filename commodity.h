#pragma once
enum state
{
	on_sale,
	off_shelf,
	sold_out
};

struct commodity
{
	char comid[7];
	char comname[21];
	char price[10];
	char description[101];
	char sellerid[7];
	char date[11];
	state s;
};

struct node_com
{
	commodity com;
	node_com* next;
};


class fcommodity
{
public:
	void commoditywrite(node_com* head);

	void commodity_viewall();//查看所有商品

	bool commodity_search(char userid[]);

	bool commodity_buyerviewall(char userid[]);

	bool commodity_query(int n, node_com* head,char userid[]);//[拓展]根据一定条件查询商品/n为操作选择

	void commodity_takeoff(const char* comid,int k,char userid[]);//下架商品

	node_com*commodity_view(const char*comid, node_com* head,int i,char userid[]);//查询单个商品
	node_com* commodity_buyerview(const char* comid, node_com* head,char userid[]);
	node_com* commodity_buyersearchid(const char* comname, node_com* head,char userid[]);

	void commodity_infochange(const char* comid,char userid[]);//修改商品信息
	void commodity_infochangeprice(const char* comid, char userid[], node_com* p, node_com* head, char price1[]);
	void commodity_infochangedescribe(const char* comid, char userid[], node_com* p, node_com* head, char describe[]);

	void commodtity_lauch(char userid[7]);//发布商品
	void lauchconfirm(char userid[7], char name[], char price[], char desribe[]);
	void labelnumber(char comid[7],node_com*head);
//拓展功能函数

	void commodity_evaluation(const char* comid);//商品评价

	void commoditydetail(char userid[], char comid[], node_com* find);

private:

};

node_com* commodityread();

bool buyervaguesearch(const char* comname, node_com* head, char userid[]);