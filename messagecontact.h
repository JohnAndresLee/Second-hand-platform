#pragma once
struct message
{
	char senderid[7];
	char receiverid[7];
	char date[20];
	char message[201];
	bool state;//标记已读消息和未读消息
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
	node_message* messageread();//对文件中所有留言信息的读取
	void messagewrite(node_message* head);//将留言写入文件中

	node_message*message_search(char userid[7],node_message*head);

	int unreadmessagecount(char userid[7]);//对用户未读信息的计数
	int unreadadminmessagecount(char userid[7]);

	void usersendmessage(char userid[7]);//用户发送信息
	void sendback(char userid[], char receiver[]);//未读信息的回复

	void adminsendmessage();//管理员发出的信息

	void unreadmessagedisplay(char userid[7]);

	void confirm(node_message* head);

	void historymessagedisplay(char userid[7]);
};

