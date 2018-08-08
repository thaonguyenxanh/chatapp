#pragma once
#include<iostream>
#include<string>
#include"message.h"
#include"SQLLite.h"
#include"users_management.h"
#include<tchar.h>
#include<ctime>
using namespace std;

class message_management:public message
{
public:
	message msg;
	SQLiteDB *pSQLite = new SQLiteDB();
	users_management um;
	int id = msg.get_id(); 
	int sender = msg.get_sender();
	int receiver= msg.get_receiver();
	string content= msg.get_content();
	char *time_c=msg.get_time_c();

public:
	int check_user(string username);
	int check_friend(int friend_id);
	void display_all_message(int id);
	void display_message();
	void display_all_read_msg();
	int has_not_been_read();
	void send_message();
	void send_message(int user1, int user2);
	
public:
	message_management();
	~message_management();
};



inline int message_management::check_user(string username)
{
	int i = 0;
	string query = "select * from users where users.username= '" + username + "';";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		IResult *res = pSQLite->ExcuteSelect(query.c_str());
		if (!res) {
			cout << "Error: " << pSQLite->GetLastError().c_str();
		}
		else
		{
			while (res->Next())
			{
				i = (int)res->ColomnData(0);
				const char* a = res->ColomnData(0);
				stringstream strValue;
				strValue << a;
				strValue >> i;
			}
			res->Release();
			if (!i) {
				cout << "no one has user name: " << username << endl;
				return 0;
			}
			else
			{
				return i;
			}
		}
	}
}

inline int message_management::check_friend(int friend_id)
{
	string query = " select * from friend_list,users where users.id = " + to_string(friend_id) + " and users.id= friend_list.user2 or users.id= friend_list.user1;";
	int j = 0;
	IResult *res1 = pSQLite->ExcuteSelect(query.c_str());
	if (!res1) {
		cout << "Error: " << pSQLite->GetLastError().c_str();
		return 0;
	}
	else
	{
		while (res1->Next())
		{
			j = (int)res1->ColomnData(0);
			const char* a = res1->ColomnData(0);
			stringstream strValue;
			strValue << a;
			strValue >> j;
		}
		res1->Release();
		return 1;
	}
}

inline void message_management::display_all_message(int id)
{
	string query = "select message.id,message.receiver,message.sender,message.contents,message.time from message, users where users.id= " + to_string(id) + " and (message.receiver= users.id or message.sender= users.id);";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		IResult *res = pSQLite->ExcuteSelect(query.c_str());
		if (!res)
		{
			cout << "Error: " << pSQLite->GetLastError().c_str();
			cout << endl;
		}
		else
		{
			int i = res->GetColumnCount();
			for (int k = 0; k < i; k++)
			{
				printf("%s\t\t", res->NextColomnName(k));
			}
			cout << endl;
			while (res->Next())
			{
				for (int k = 0; k < i; k++)
				{
					printf("%s\t\t", res->ColomnData(k));
				}
				cout << endl;
			}
		}
		res->Release();
	}

}

inline void message_management::display_message()
{
	string username;
	cout << "Type username you wanna display all msg: " << endl;
	cin.ignore();
	getline(cin, username);
	string query = "select distinct message.id,message.receiver,message.sender,message.contents,message.time from message, users where (message.receiver=(select message.id from message, users where users.username= '" + username + "' or message.sender=(select message.id from message, users where users.username= '" + username + "')) and (message.receiver= users.id or message.sender= users.id));";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{

		IResult *res = pSQLite->ExcuteSelect(query.c_str());
		if (!res)
		{
			cout << "Error: " << pSQLite->GetLastError().c_str();
			cout << endl;
		}
		else
		{
			int i = res->GetColumnCount();
			for (int k = 0; k < i; k++)
			{
				printf("%s\t", res->NextColomnName(k));
			}
			cout << endl;
			while (res->Next())
			{
				for (int k = 0; k < i; k++)
				{
					printf("%s\t", res->ColomnData(k));

				}
				cout << endl;
			}
		}
		res->Release();
	}
}

inline void message_management::display_all_read_msg()
{
	string query = "select distinct message.id,message.receiver,message.sender,message.contents,message.time from message, users where message.status= 0;";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		IResult *res = pSQLite->ExcuteSelect(query.c_str());
		if (!res)
		{
			cout << "Error: " << pSQLite->GetLastError().c_str();
			cout << endl;
		}
		else
		{
			int i = res->GetColumnCount();
			for (int k = 0; k < i; k++)
			{
				printf("%s\t", res->NextColomnName(k));
			}
			cout << endl;
			while (res->Next())
			{
				for (int k = 0; k < i; k++)
				{
					printf("%s\t", res->ColomnData(k));
				}
				cout << endl;
			}
		}
		res->Release();
	}
}

	inline int message_management::has_not_been_read()
{
	int count = 0;
	string query = "select distinct message.id, message.receiver, message.sender, message.contents, message.time from message, users where message.status= 1;";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		IResult *res = pSQLite->ExcuteSelect(query.c_str());
		if (!res)
		{
			cout << "Error: " << pSQLite->GetLastError().c_str();
			cout << endl;
		}
		else
		{
			int i = res->GetColumnCount();
			for (int k = 0; k < i; k++)
			{
				printf("%s\t", res->NextColomnName(k));
			}
			cout << endl;
			while (res->Next())
			{
				for (int k = 0; k < i; k++)
				{
					printf("%s\t", res->ColomnData(k));

				}
				count++;
				cout << endl;
			}
		}
		res->Release();
	}
	return count;
}

inline void message_management::send_message()
{
	string contents;
	string username;
	message msg;
again:
	cout << "Enter user name to send message: " << endl;
	cin.ignore();
	getline(cin, username);
	int i = 0;;
	string query = "select *from users where users.username= '" + username + "';";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		i = check_user(username);
		if (!i) {
			cout << "no one has user name: " << username << endl;
			goto again;
		}
		else {
			cout << "Enter something that's so sweet to send " << username << endl;
			getline(cin, content);
			time_t time_now = time(0);
			char *t = ctime(&time_now);
			t[strlen(t) - 1] = '\0';

			string query2 = "insert into message(sender,receiver,contents,time) values(" + to_string(i) + ",(select distinct users.id from users where users.username= '" + username + "'),'" + content + "', '" + t + "');";
			bool a = pSQLite->isConnected();
			if (!a) {
				cout << "database is disconnected!" << endl;
			}
			else
			{
				int rc = pSQLite->Excute(query2.c_str());
				if (rc > 0) {
					cout << "sent successfully!" << endl;
				}
				else
				{
					string err = pSQLite->GetLastError().c_str();
					cout << err << endl;
				}
			}
		}
		/*IResult *res = pSQLite->ExcuteSelect(query.c_str());
		if (!res) {
			cout << "Error: " << pSQLite->GetLastError().c_str();
		}
		else
		{
			while (res->Next())
			{
				i = (int)res->ColomnData(0);
				const char* a = res->ColomnData(0);
				stringstream strValue;
				strValue << a;
				strValue >> i;
			}
		}
		res->Release();*/
		
	}
}

inline void message_management::send_message(int user1, int user2)
{
	time_t time_now = time(0);
	char *t = ctime(&time_now);
	t[strlen(t) - 1] = '\0';
	string content;
	cout << "type something that's sweet to your friend" << endl;
	cin.ignore();
	getline(cin, content);
	string query2 = "insert into message(sender,receiver,contents,time) values(" + to_string(user1) + "," + to_string(user2) + ",'" + content + "', '" + t + "');";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		int i = 0;
		int rc = pSQLite->Excute(query2.c_str());
		if (rc > 0) {
			cout << "sent successfully!" << endl;
		}
		else
		{
			string err = pSQLite->GetLastError().c_str();
			cout << err << endl;
		}
	}
}

message_management::message_management()
{
}


message_management::~message_management()
{
	delete pSQLite;
}
