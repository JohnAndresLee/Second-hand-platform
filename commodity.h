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

	void commodity_viewall();//�鿴������Ʒ

	bool commodity_search(char userid[]);

	bool commodity_buyerviewall(char userid[]);

	bool commodity_query(int n, node_com* head,char userid[]);//[��չ]����һ��������ѯ��Ʒ/nΪ����ѡ��

	void commodity_takeoff(const char* comid,int k,char userid[]);//�¼���Ʒ

	node_com*commodity_view(const char*comid, node_com* head,int i,char userid[]);//��ѯ������Ʒ
	node_com* commodity_buyerview(const char* comid, node_com* head,char userid[]);
	node_com* commodity_buyersearchid(const char* comname, node_com* head,char userid[]);

	void commodity_infochange(const char* comid,char userid[]);//�޸���Ʒ��Ϣ
	void commodity_infochangeprice(const char* comid, char userid[], node_com* p, node_com* head, char price1[]);
	void commodity_infochangedescribe(const char* comid, char userid[], node_com* p, node_com* head, char describe[]);

	void commodtity_lauch(char userid[7]);//������Ʒ
	void lauchconfirm(char userid[7], char name[], char price[], char desribe[]);
	void labelnumber(char comid[7],node_com*head);
//��չ���ܺ���

	void commodity_evaluation(const char* comid);//��Ʒ����

	void commoditydetail(char userid[], char comid[], node_com* find);

private:

};

node_com* commodityread();

bool buyervaguesearch(const char* comname, node_com* head, char userid[]);