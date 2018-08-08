#pragma once
#include"users.h"
#include"SQLLite.h"
#include<iostream>
#include<tchar.h>
#include<sstream>
using namespace std;
class users_management:public users
{

	users user;
	int check_user(string username);
	string address = user.get_address();
	string email = user.get_email();
	string password = user.get_password();
public:
	SQLiteDB * pSQLite = new SQLiteDB();
	int login();
	int sign_up();
	void log_out();
public:
	users_management();
	~users_management();
};



inline int users_management::check_user(string username)
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

inline int users_management::login()
{
	string usename, password;
	cout << "input your username: " << endl;
	cin.ignore();
	getline(cin, usename);
	cout << "Input your password: " << endl;
	//cin.ignore();
	getline(cin, password);
	string query = " select * from users where users.username like '" + usename + "' and users.passwords like '" + password + "';";
	int i = 0;
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
		return -1;
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
	if (i == 0) {
		cout << "error" << endl;
	}
	else
	{
		cout << "log in successfully!" << endl;
		return i;
	}
}

inline int users_management::sign_up()
{
	string username;
	string fullname;
	string address;
	string email;
	string password;
	string tempt_password;
	while (1)
	{
	tryagain:
		cout << "Username: " << endl;
		cin.ignore();  
		getline(cin, username);
		for (int j = 0; j < username.length(); j++)
		{
			if (username[j] == ' ') {
				cout << "user name doesnot have sqace" << endl;
				goto tryagain;
			}

		}
		int i = 0;
		string query = "select *from users where users.username= '" + username + "';";
		if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
			cout << "Unable to connect database" << endl;
			cout << pSQLite->GetLastError().c_str() << endl;
		}
		else
		{
			i = check_user(username);
			if (i) {
				cout << "username: " << username << " has existed" << endl;
				continue;
			}
			else {
				cout << "password: " << endl;
				getline(cin, password);
				cout << "Enter your password again: " << endl;
				getline(cin, tempt_password);
				if (password != tempt_password) {
					cout << "Fail!" << endl;
					continue;
				}
				cout << "Full name: " << endl;
				getline(cin, fullname);
				cout << "address: " << endl;
				getline(cin, address);
				cout << "email: " << endl;
				getline(cin, email);
				user.fullname = fullname;
				user.username = username;
				user.set_address(address);
				user.set_email(email);
				user.set_password(password);
				string query = "insert into users(username,passwords,fullname,address,Emails) values('" + user.username + "','" + password + "','" + user.fullname + "','" + address + "','" + email + "');";
				int rc = pSQLite->Excute(query.c_str());
				if (rc == 0) {
					cout << pSQLite->GetLastError();
				}
			}
		}	
	}
	return 0;
}

inline void users_management::log_out()
{
	pSQLite = new SQLiteDB();
	delete pSQLite;
}

users_management::users_management()
{
}


users_management::~users_management()
{
	delete pSQLite;
}
