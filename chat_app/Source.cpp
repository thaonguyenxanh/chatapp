#include"SQLLite.h"
#include"users_management.h"
#include<iostream>
#include"friend_list_management.h"
#include"message_management.h"
#include<conio.h>
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
				cout << "7: Modify friend information" << endl;
				cout << "8: Log out" << endl;
				int a2;
				cout << "choose from 1 to 7" << endl;
				cout << "Enter Ctr_l to display friendlist" << endl;
				cout << "Enter Ctr_R to display all message had not been read : " << endl << endl<<endl;
				char ch;
				cin.ignore();
				ch = getch();



				if (ch == 12) {// ctr_l
					int a= fr.display_friend_list(i);
					int j;
					cout << "Enter 1- " << a << " to send message enter 0 to continue: " << endl;
					cin >> j;
					if (j == 0) {
						continue;
					}
					else
					{
						mm.send_message(i, j);
					}
				}
				else if (ch == 18)//ctr_R
				{
					int count = mm.has_not_been_read();
					int j;
					cout << "Enter 1- " << count << " to reply message enter 0 to continue: " << endl;
					cin.ignore();
					cin >> j;
					if (j == 0) {
						continue;
					}
					else
					{
						mm.send_message(i, j);
					}
				}
				else
				{
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
						fr.modify_friend();
						break;
					case 8:
						return 0;
						break;
					default:
						break;
					}
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