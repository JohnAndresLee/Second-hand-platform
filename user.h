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

	node_user*user_inforead();//�����ļ����û���Ϣ

	void user_view();//��ѯ�����û�

	void user_delete(const char*userid);//ɾ���û�

	node_user* user_owninfoview(const char* userid, node_user* head);//�鿴�û�������Ϣ

	void user_infomanage(char userid[7]);//�û�������Ϣ�޸�

	void userinfo_change(char userid[7]);

	void userlogin();//�û���¼

	void user_contact();//�û������Թ���

	void usernamechange(node_user* head, node_user* p);
	void usercontactchange(node_user* head, node_user* p);
	void useraddresschange(node_user* head, node_user* p);
	void userbalencechange(node_user* head, node_user* p);

	 void labelnumber(char id[7]);
private:
};

