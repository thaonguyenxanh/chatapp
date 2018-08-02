#pragma once
#include<iostream>
#include<string>
using namespace std;

class users
{
public:
	int id;
	string username;
	string fullname;
	int message_id;
	int friend_list_id;
private:

	string address;
	string email;
	string password;
public:
	void set_address(string address) { this->address = address; }
	string get_address()const { return this->address; }
	void set_email(string email) { this->email = email; }
	string get_email() const { return this->email; }
	void set_password(string password) { this->password = password; }
	string get_password()const { return this->password; }


public:
	users();
	users(int id, string username, string fullname, int message_id, int friend_list_id, string address, string email, string password) :id(0), fullname(""), message_id(0), friend_list_id(0), address(""), email(""), password("") {}

	~users();
};

inline users::users()
{
}

users::~users()
{
}

