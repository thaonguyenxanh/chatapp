#pragma once
#include<iostream>
#include<string>
#include<ctime>
#pragma warning(disable : 4996)
using namespace std;
class message
{

	int id, sender, receiver;
	string content;
	time_t time_now = time(0);
	char *time_c;
public:
	int get_id()const { return this->id;}
	void set_sender(int sender) { this->sender = sender;}
	int get_sender()const { return this->sender; }
	void set_receiver(int receiver) { this->receiver = receiver; }
	int get_receiver()const { return this->receiver; }
	void set_content(string content) { this->content = content; }
	string	 get_content()const { return this->content; }
	void set_time(char *time_c) {
		time_c = ctime(&time_now);
		this->time_c = time_c;
	}
	char *get_time_c()const { return this->time_c; }

public:
	message();
	message(int id, int sender, int receiver, string content, char *time_c): id(0),sender(0),receiver(0),content(""),time_c('\0'){};
	~message();
};



message::message()
{
}


message::~message()
{
}
