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
	//fr.add_friend();
	//fr.block_user();
	//mm.display_message("duy");
	//mm.send_message();
	//um.sign_up();

	while (1)
	{
		cout << "1: Sign up. " << endl;
		cout << "2: Sign in" << endl;
		int i;
		int a1;
		cout << "type 1 to sign up, 2 to sign in" << endl;
		cin >> a1;
		switch (a1)
		{
		case 1:
			um.sign_up();
			break;
		case 2:
			i = um.login();
			while (((i) != 0))
			{
				cout << "1: Display all my messages" << endl;
				cout << "2: Display all my messages with: " << endl;

				cout << "3: Send message" << endl;
				cout << "4: Add new friend" << endl;
				cout << "5: Display all of my friend list" << endl;
				cout << "6: Block" << endl;
				cout << "7: Log out" << endl;
				int a2;
				cout << "choose from 1 to 7" << endl;
				cin >> a2;
				switch (a2)
				{
				case 1:
					mm.display_all_message(i);
					break;
				case 2:
					mm.display_message();
					break;
				case 3:
					mm.send_message();
					break;
				case 4:
					fr.add_friend();
					break;
				case 5:
					fr.display_friend_list(i);	
					break;
				case 6:
					fr.block_user();
					break;
				case 7:
					return 0;
					break;
				default:
					break;
				}
			}
		default:
			break;
		}
	}
	pSQLite->CloseConnection();
	delete pSQLite;
	system("PAUSE");
	
 }