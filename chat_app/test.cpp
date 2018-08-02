#include"SQLLite.h"
#include"users_management.h"
#include<iostream>
#include"friend_list_management.h"
#include"message_management.h"
using namespace std;

int main(int argc, TCHAR* argv[]) {
	SQLiteDB *pSQLite;
	pSQLite = new SQLiteDB();
	users_management um;
	message_management mm;
	friend_list_management fr;
	fr.add_friend();
	//fr.block_user();
	//mm.display_message("duy");
	//mm.send_message();
	//um.sign_up();
	pSQLite->CloseConnection();
	delete pSQLite;
	system("PAUSE");
}