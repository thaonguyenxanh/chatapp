#pragma once
#include<iostream>
#include<string>
#include"SQLLite.h"
#include<ctime>
#include"friend_list.h"
#include<sstream>
#include<vector>
#pragma warning(disable:4996)
using namespace std;
class friend_list_management: public friend_list
{
public:
	SQLiteDB * pSQLite = new SQLiteDB();
	friend_list fr;
	int id = fr.get_id();
	int user1 = fr.get_user1();
	int user2 = fr.get_user2();
	bool blocked = fr.get_status();
	unsigned int period = fr.get_period();
	void add_friend();
	int display_friend_list(int id);
	void block_user();
	void modify_friend();
	void rich_view(int id);
public:
	friend_list_management();
	~friend_list_management();
};



inline void friend_list_management::add_friend()
{
again:
	string username;
	int i = 0;
	cout << "Input username you want to add to your friendlist: " << endl;
	cin.ignore();
	getline(cin, username);
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
			res->Release();
			if (!i) {
				cout << "no one has user name: " << username << endl;
				goto again;
			}
			else
			{
				string query = " select * from friend_list,users where users.id = " + to_string(i) + " and users.id= friend_list.user2;";
				int j = 0;
				IResult *res1 = pSQLite->ExcuteSelect(query.c_str());
				if (!res1) {
					cout << "Error: " << pSQLite->GetLastError().c_str();
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
				}
				if (j) {
					cout << "username :" << username << " had been your friend" << endl;
				}
				else
				{
					time_t now;
					struct tm newyear;
					double seconds;

					time(&now);  /* get current time; same as: now = time(NULL)  */

					newyear = *localtime(&now);

					newyear.tm_hour = 0; newyear.tm_min = 0; newyear.tm_sec = 0;
					newyear.tm_mon = 0;  newyear.tm_mday = 1;

					seconds = difftime(now, mktime(&newyear));//from 2000s

					string query2 = "insert into friend_list(user1, user2, period) values(" + to_string(i) + ",(select users.id from users where users.username= '" + username + "')," + to_string((unsigned int)seconds) + ");";
					bool a = pSQLite->isConnected();
					if (!a) {
						cout << "database disconnected!" << endl;
					}
					else
					{

						int rc = pSQLite->Excute(query2.c_str());
						a = pSQLite->isConnected();
						if (rc > 0) {
							cout << "add friend successfully!" << endl;
						}
						else
						{
							string err = pSQLite->GetLastError().c_str();
							cout << err << endl;
						}
					}
				}
			}
		}

	}

	
}

inline int friend_list_management::display_friend_list(int id)
{
	int count = 0;
	string query = "select friend_list.id, friend_list.user2, friend_list.period from friend_list, users where users.id= " + to_string(id) + " and (users.id= friend_list.user1) and friend_list.blocked =1;";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		IResult *res2 = pSQLite->ExcuteSelect(query.c_str());
		if (!res2)
		{
			cout << "Error: " << pSQLite->GetLastError().c_str();
			cout << endl;
		}
		else
		{
			int i = res2->GetColumnCount();
			for (int k = 0; k < i; k++)
			{
				printf("%s\t", res2->NextColomnName(k));
			}
			cout << endl;
			while (res2->Next())
			{
				for (int k = 0; k < i; k++)
				{
					printf("%s\t", res2->ColomnData(k));
					
				}
				count++;
				cout << endl;
			}
		}	
		res2->Release();

	}
	return count;
}

inline void friend_list_management::block_user()
{
	int i = 0;
	again:
	string username;
	cin.ignore();
	cout << "type user name who you wanna block!" << endl;
	getline(cin, username);
	string query2 = " select * from friend_list,users where users.username like '" + username + "' and users.id= friend_list.user2;";
	string query = "update friend_list set blocked= 0 where friend_list.user2= (select users.id from users where users.username= '"+username+"');";
	if (!pSQLite->OpenConnection("chatapp.db", "C:\\Users\\8570w\\source\\repos\\chat_app\\chat_app\\")) {
		cout << "Unable to connect database" << endl;
		cout << pSQLite->GetLastError().c_str() << endl;
	}
	else
	{
		IResult *res = pSQLite->ExcuteSelect(query2.c_str());
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
		}
	}
	if (!i) {
		cout << "no one has user name: " << username << endl;
		goto again;
	}
	else
	{
		int rc = pSQLite->Excute(query.c_str());
		if (rc > 0) {
			cout << "Block success!" << endl;
		}
		else {
			cout << pSQLite->GetLastError().c_str();
			cout << endl;
		}
	}
	pSQLite->CloseConnection();
}

inline void friend_list_management::modify_friend()	
{
	string fr_name;
	int i = 0;
again:
	cout << "Type your friend name to modify information: " << endl;
	cin.ignore();
	getline(cin, fr_name);
	string query = "select users.id from users where users.username= '" + fr_name + "';";
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
		}
		string full_name;
		string address;
		string email;
		cout << "type new full name: " << endl;
		getline(cin, full_name);
		cout << "type new  address: " << endl;
		getline(cin, address);
		cout << "Type new email: " << endl;
		getline(cin, email);
		string query2 = "update users set fullname= '" + full_name + "' , address= '" + address + "' , Emails= '" + email + "' where users.id= " + to_string(i) + ";";
		if (!i) {
			cout << "no one has user name: " << fr_name << endl;
			goto again;
		}
		else
		{
			int rc = pSQLite->Excute(query2.c_str());
			if (rc > 0) {
				cout << "Modify success!" << endl;
			}
			else {
				cout << pSQLite->GetLastError().c_str();
				cout << endl;
			}
		}
	}

}

inline void friend_list_management::rich_view(int id)
{
	vector<string> address;
	string query = "select distinct users.address from users, friend_list where friend_list.user1= users.id or friend_list.user2= users.id and users.id= "+to_string(id)+";";
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
			int i = res->GetColumnCount();
			while (res->Next())
			{
				for (int k = 0; k < i; k++)
				{
					const char *addr = res->ColomnData(k);
					string addr2 = addr;
					address.push_back(addr2);
				}
				cout << endl;
			}
			vector<string>::iterator it;
			for ( it = address.begin(); it != address.end(); it++)
			{
				cout <<"\t\t\t\t"<< *it << endl;
				string query2= "select distinct users.username from users, friend_list where friend_list.user1 = users.id or friend_list.user2 = users.id and users.address = '" + *it + "' and users.id = "+ to_string(id)+"; ";
				IResult *res2 = pSQLite->ExcuteSelect(query2.c_str());
				if (!res2) {
					cout << "Error: " << pSQLite->GetLastError().c_str();
					cout << endl;
				}
				else
				{
					int j = res2->GetColumnCount();
					while (res2->Next())
					{
						for (int e = 0; e < j; e++)
						{
							printf("%s\n", res2->ColomnData(e));
						}
						cout << endl;
					}
					res2->Release();
				}

			}
		}
		res->Release();
	}
}

friend_list_management::friend_list_management()
{
}


friend_list_management::~friend_list_management()
{
	delete pSQLite;
}
