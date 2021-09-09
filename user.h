#pragma once

struct userinfo
{
	char userid[7] = {'\0'};
	char username[11] = { '\0' };
	char userkey[21] = { '\0' };
	char contactinfo[21] = { '\0' };
	char address[21] = { '\0' };
	char balance[10] = { '\0' };
	char signdate[11] = { '\0' };
	bool flag = true;
};

struct node_user
{
	userinfo user;
	node_user* next;
};

class fuser
{
public:
	void userwrite(node_user* head);

	bool searchusername(const char* username);

	void usersignin();

	node_user*user_inforead();//读入文件中用户信息

	void user_view();//查询所有用户

	void user_delete(const char*userid);//删除用户

	node_user* user_owninfoview(const char* userid, node_user* head);//查看用户个人信息

	void user_infomanage(char userid[7]);//用户个人信息修改

	void userinfo_change(char userid[7]);

	void userlogin();//用户登录

	void user_contact();//用户的留言功能

	void usernamechange(node_user* head, node_user* p);
	void usercontactchange(node_user* head, node_user* p);
	void useraddresschange(node_user* head, node_user* p);
	void userbalencechange(node_user* head, node_user* p);

	 void labelnumber(char id[7]);
private:
};

