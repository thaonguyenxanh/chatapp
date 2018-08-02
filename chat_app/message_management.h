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
	void display_all_message(int id);
	void display_message();
	void send_message();
public:
	message_management();
	~message_management();
};



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
		pSQLite->CloseConnection();
	}

}

inline void message_management::display_message()
{
	string username;
	cout << "Type username you wanna display all msg: " << endl;
	cin.ignore();
	getline(cin, username);
	string query = "select distinct message.id,message.receiver,message.sender,message.contents,message.time from message, users where message.receiver=(select message.id from message, users where users.username= '" + username + "' and (message.receiver= users.id));";
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
		pSQLite->CloseConnection();
	}
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
		}
		res->Release();
	}
	if (!i) {
		cout << "no one has user name: " << username << endl;
		goto again;
	}
	else {
		cout << "Enter something that's so sweet to send " << username << endl;
		getline(cin, content);
		time_t time_now = time(0);
		char *t = ctime(&time_now);
		t[strlen(t)-1] = '\0';
			
		string query2 = "insert into message(sender,receiver,contents,time) values("+to_string(i)+",(select distinct users.id from users where users.username= '" + username + "'),'" + content + "', '" + t + "');";
		bool a =pSQLite->isConnected();
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
				cout << err<<endl;
			}
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
