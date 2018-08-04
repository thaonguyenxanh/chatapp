#include"SQLLite.h"
#include"users_management.h"
#include<iostream>
#include"friend_list_management.h"
#include"message_management.h"
#include<Windows.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


int main(int argc, TCHAR* argv[]) {
	SQLiteDB *pSQLite;
	pSQLite = new SQLiteDB();
	users_management um;
	message_management mm;
	friend_list_management fr;
	//fr.add_friend();

	//while (1)
	//{
	//	//if (GetKeyState(115) == true & 0x800 && GetKeyState(VK_CONTROL) == true & 0x800) {
	//	//	fr.modify_friend();
	//	//}

	//}
	char c;
	while (1)
	{

	}
	//fr.block_user();
	//mm.display_message("duy");
	//mm.send_message();
	//um.sign_up();
	pSQLite->CloseConnection();
	delete pSQLite;
	return 0;
	system("PAUSE");
}