#pragma once
#include<iostream>
#include<string>
using namespace std;
class friend_list
{
	int id, user1, user2;
	bool blocked;
	unsigned int period;
public:
	unsigned int get_period()const { return this->period; }
	void set_period(unsigned int period) { this->period = period; }
	int get_id()const { return this->id; }
	void set_user1(int user1) { this->user1 = user1; }
	int get_user1()const { return this->user1; }
	void set_user2(int user2) { this->user2 = user2; }
	int get_user2() { return this->user2; }
	void set_status(bool blocked) { this->blocked = blocked; }
	bool get_status()const { return this->blocked; }
public:
	friend_list();
	friend_list(int id, int user1, int user2, bool blocked) : id(0), user1(0), user2(0), blocked(false) {};
	~friend_list();
};



friend_list::friend_list()
{
}


friend_list::~friend_list()
{
}
