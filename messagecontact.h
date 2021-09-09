#pragma once
struct message
{
	char senderid[7];
	char receiverid[7];
	char date[20];
	char message[201];
	bool state;//����Ѷ���Ϣ��δ����Ϣ
};

struct node_message
{
	message mes;
	node_message* next;
};

void smessage(char userid[], char receiver[]);

class messagecontact
{
public:
	node_message* messageread();//���ļ�������������Ϣ�Ķ�ȡ
	void messagewrite(node_message* head);//������д���ļ���

	node_message*message_search(char userid[7],node_message*head);

	int unreadmessagecount(char userid[7]);//���û�δ����Ϣ�ļ���
	int unreadadminmessagecount(char userid[7]);

	void usersendmessage(char userid[7]);//�û�������Ϣ
	void sendback(char userid[], char receiver[]);//δ����Ϣ�Ļظ�

	void adminsendmessage();//����Ա��������Ϣ

	void unreadmessagedisplay(char userid[7]);

	void confirm(node_message* head);

	void historymessagedisplay(char userid[7]);
};

