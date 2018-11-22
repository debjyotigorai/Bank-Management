//BANK MANAGEMENT SOFTWARE
//This program is created by Debjyoti Gorai for school investigatory project and for sole purposes in 2018.
//This program is owned solely by Debjyoti Gorai.
//Editing the program is not allowed. Read the about section of the program for more details.

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <direct.h>

using namespace std;

char * crypt_pass()
{
	char password[100];
	int i = 0;
    char a;
    while(1)
    {
        a=getch();
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
        {
            password[i]=a;
            ++i;
            cout << "*";
        }
        if(a=='@'||a=='#'||a=='?'||a==' '||a=='%'||a=='!'||a=='-'||a=='_'||a=='$'||a=='&'||a=='^'||a=='*')
        {
        	password[i]=a;
        	++i;
        	cout << "*";
		}
        if(a=='\b'&&i>=1)
        {
            cout << "\b \b";
            --i;
        }
        if(a=='\r')
        {
            password[i]='\0';
            break;
        }
    }
    return password;
}

char * crypt_pin()
{
	char pin[4];
	int i=0;
	char a;
	while(1)
	{
		a=getch();
		if (a>='0'&&a<='9')
		{
			pin[i]=a;
            ++i;
            cout << "X";
		}
		if(a=='\b'&&i>=1)
        {
            cout << "\b \b";
            --i;
        }
        if(a=='\r')
        {
            pin[i]='\0';
            break;
        }
		
	}
	return pin;
}

void format_transaction()
{
	Sleep (200);
	cout << "\nTransaction in progress ";
	for (int i=0; i<=10; i++)
	{
		Sleep (200);
		cout << "> ";
	}
}

class BANK_BRANCH
{
	double branch_code;
	char branch_name[50], branch_address[100];
	public:
		void create_branch()
		{
			cout << "\nEnter 4 digit branch code: ";
			cin >> branch_code;
			cout << "\nEnter branch name: ";
			cin.sync();
			cin.getline(branch_name, 50);
			cout << "\nEnter branch address: ";
			cin.sync();
			cin.getline(branch_address, 100);
		}
		double return_branch_code()
		{
			return branch_code;
		}
		void view_branch()
		{
			cout << "\nBranch Code: " << branch_code
				 << "\nBranch Name: " << branch_name
				 << "\nBranch Address: " << branch_address;
		}
		int search_bcode(double bcode)
		{
			int flag=0;
			fstream fin("bank_branch.dat", ios::in);
			if(fin)
			{
				BANK_BRANCH bb;
				while(!fin.eof())
				{
					fin.read((char *)&bb, sizeof(bb));
					if(bb.return_branch_code()==bcode)
					{
						flag=1;
						break;
					}
				}
				if (flag==1)
				{
					fin.close();
				}
				else
				{
					char ch;
					fin.close();
					cout << "\nYou have entered a wrong branch code."
						 << "\nIf you don't know search it instead by pressing Y : ";
					cin >> ch;
					if (ch=='Y'||ch=='y')
					{
						view_branch();
						return 2;
					}
				}
				return 1;
			}
			else
			{
				cout << "\nNo bank branch exists.";
				return 0;
			}
		}	
};

class account_holder
{
	char username[100], password[100], question[200], answer[100], status;
	double bank_code, accno;
	public: 
		double return_bank_code()
		{
			return bank_code;
		}
		double return_accno()
		{
			return accno;
		}
		char * return_question()
		{
			return question;
		}
		char * return_answer()
		{
			return answer;
		}
		char return_status()
		{
			return status;
		}
		char * return_username()
		{
			return username;
		}
		char * return_password()
		{
			return password;
		}
		void change_status_N()
		{
			status='N';
		}
		void change_status_Y()
		{
			status='Y';
		}
		void gen_accno()
		{
			int flag=0;
			srand(time(NULL));
			accno=(rand() % (1000000-100000)) + 100000;
			fstream fobj("account_holder.dat", ios::in);
			account_holder ah;
			if (fobj)
			{
				while(!fobj.eof())
				{
					fobj.read((char *)&ah, sizeof(ah));
					if(accno==ah.return_accno())
					{
						flag=1;
						break;
					}
				}
				if (flag==1)
				{
					fobj.close();
					gen_accno();
				}
				else if(flag==0)
				{
					fobj.close();
				}
			}
			fobj.close();
		}
		int creation_2()
		{
			menu:
			int flag=0, sf;
			cout << "\nACCOUNT CREATION: ";
			cout << "\nEnter bank code: ";
			cin >> bank_code;
			BANK_BRANCH bb;
			sf=bb.search_bcode(bank_code);
			if (sf==1)
			{
				gen_accno();
				cout << "\nCreate a username: ";
				cin.sync();
				cin.getline(username, 100);
				fstream fin("account_holder.dat", ios::in);
				if(fin)
				{
					while(!fin.eof())
					{
						account_holder temp;
						fin.read((char *)&temp, sizeof(temp));
						if(strcmp(temp.return_username(), username)==0)
						{
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
				{
					cout << "\nThe username already exists. Create a different one.";
					goto menu;
				}
				else
				{
					cout << "\nCreate a password: ";
					cin.sync();
					strcpy(password, crypt_pass());
					status='Y';
					cout << "\n\nEnter a security question: ";
					cin.sync();
					cin.getline(question, 200);
					cout << "\nChoose a answer for your question: ";
					cin.sync();
					cin.getline(answer, 100);
				}
				return sf;
			}
			else if(sf==2)
			{
				sf=1;
				goto menu;
			}
			else if(sf==0)
				return sf;
		}
			
	/*void achview()
	{
		cout << "\nusername: " << username
		     << "\npassword: " << password
		     << "\nstatus: " << status
		     << "\nquestion: " << question
		     << "\nanswer: " << answer;
	}*/
};

class account_creation_view
{
	char name[100], email[100], address[100], guardian_name[100], phoneno[20];
	double birth_year, balance, acv_branch_code, accno;
	public:
		void creation()
		{
			cout << "\nPERSONAL DETAILS: ";
			cout << "\nEnter name: ";
			cin.sync();
			cin.getline(name, 100);
			cout << "\nEnter year of birth: ";
			cin >> birth_year;
			cout << "\nEnter residential address: ";
			cin.sync();
			cin.getline(address, 100);
			cout << "\nEnter your's father/ mother's name: ";
			cin.sync();
			cin.getline(guardian_name, 100);
			cout << "\nEnter your phone number: ";
			cin.sync();
			cin.getline(phoneno, 20);
			cout << "\nEnter your email address: ";
			cin.sync();
			cin.getline(email, 100);	
		}
		void creation_part()
		{
			cout << "\nEnter your deposit balance: ";
			cin >> balance;
			cout << "\n....ACCOUNT CREATION SUCCESSFULL....";
		}
		void view()
		{
			cout << "\nACCOUNT DETAILS: "
			     << "\nBank branch code : " << acv_branch_code
			     << "\nAccount number: " << accno
			     << "\nCurrent balance: Rs. " << balance;
			cout << "\nPERSONAL DETAILS:"
			     << "\nName: " << name
			     << "\nYear of birth: " << birth_year
			     << "\nGuardian's name: " << guardian_name
			     << "\nAddress: " << address
			     << "\nPhone number: " << phoneno
			     << "\nEmail: " << email;
		}
		void edit()
		{
			edit_lb:
			int choose;
			cout << "\nEditing Menu: "
				 << "\n1. Edit name."
				 << "\n2. Edit email."
				 << "\n3. Edit address."
				 << "\n4. Edit guardian name."
				 << "\n5. Edit phone number."
				 << "\n6. Edit birth year."
				 << "\n7. Done."
				 << "\nEnter correct choice: ";
			cin >> choose;
			switch (choose)
			{
				case 1: cout << "\nEnter new name: ";
						cin.sync();
						cin.getline(name, 100);
						goto edit_lb;
				case 2: cout << "\nEnter your email address: ";
						cin.sync();
						cin.getline(email, 100);
						goto edit_lb;
				case 3: cout << "\nEnter residential address: ";
						cin.sync();
						cin.getline(address, 100);
						goto edit_lb;
				case 4: cout << "\nEnter your's father/ mother's name: ";
						cin.sync();
						cin.getline(guardian_name, 100);
						goto edit_lb;
				case 5: cout << "\nEnter your phone number: ";
						cin.sync();
						cin.getline(phoneno, 20);
						goto edit_lb;
				case 6: cout << "\nEnter year of birth: ";
						cin >> birth_year;
						goto edit_lb;
				case 7: cout << "\n....Updating Done....";
						break;
				default: cout << "\nWrong choice entered. Try again.";
						 goto edit_lb;	
			}
		}
		double return_balance()
		{
			return balance;
		}
		void enter_balance(int new_bal)
		{
			balance=new_bal;
		}
		double return_accno()
		{
			return accno;
		}
		double return_acv_b_code()
		{
			return acv_branch_code;
		}
		void enter_acv_bcode(double b_code)
		{
			acv_branch_code=b_code;
		}
		void enter_accno(double a_code)
		{
			accno=a_code;
		}
};

void close_account(char username[])
{
	account_holder ah;
	int pos;
	fstream fobj("account_holder.dat", ios::in|ios::out);
	while(!fobj.eof())
	{
		pos=fobj.tellg();
		fobj.read((char *)&ah, sizeof(ah));
		if (strcmp(username, ah.return_username())==0)
			break;
	}
	fobj.sync();
	fobj.seekp(pos);
	ah.change_status_N();
	fobj.sync();
	fobj.write((char *)&ah, sizeof(ah));
	fobj.seekg(0);
	fobj.seekp(0, ios::end);
	fobj.close();
	cout << "\nAccount closed.";
}

void reopen_account()
{
	char temp_username[100], temp_password[100], temp_answer[100];
	int flag=0, pos;
	cout << "\nEnter your username: ";
	cin.sync();
	cin.getline(temp_username, 100);
	cout << "\nEnter your password: ";
	cin.sync();
	strcpy(temp_password, crypt_pass());
	account_holder ah;
	fstream fobj("account_holder.dat", ios::in|ios::out);
	while(!fobj.eof())
	{
		pos=fobj.tellg();
		fobj.read((char *)&ah, sizeof(ah));
		if ((strcmp(ah.return_username(), temp_username)==0)&&(strcmp(ah.return_password(), temp_password)==0))
		{
			flag=1;
			break;
		}
	}
	if (flag==0)
	{
		cout << "\nNo such account exists with us. Create a new one.";
	}
	if (flag==1)
	{
		if (ah.return_status()=='N')
		{
			cout << "\nSecurity Question: " << endl;
			cout << ah.return_question();
			cout << "\nEnter your answer to your question: " << endl;
			cin.sync();
			cin.getline(temp_answer, 100);
			if (strcmp(ah.return_answer(), temp_answer)==0)
			{
				ah.change_status_Y();
				fobj.sync();
				fobj.seekp(pos);
				fobj.write((char *)&ah, sizeof(ah));
				cout << "\nYour account has been reopened.";
				fobj.seekp(0, ios::end);
				fobj.sync();
				fobj.seekg(0);
				fobj.close();
			}
			else 
			{
				cout << "\nWrong answer. Try again!";
			}
		}
		else
		{
			cout << "\nYour account is already opened.";
		}
	}
}

class OPERATIONS
{
	int money, choose;
	double temp_accno;
	public:
		void operations_menu(char temp_username[])
		{
			lb:
			cout << "\nOperations Menu: "
				 << "\n1. Withdrawl Money."
				 << "\n2. Deposit Money."
				 << "\n3. Transfer Money."
				 << "\n4. Goto previous menu."
				 << "\nEnter correct option: ";
			cin >> choose;
			switch(choose)
			{
				case 1:
				{
					account_creation_view acv;
					fstream fobj("account_details.dat", ios::in|ios::out);
					fobj.read((char *)&acv, sizeof(acv));
					cout << "\nEnter withdrawl amount: Rs. ";
					cin >> money;
					if (acv.return_balance()-money>=0)
					{
						cout << "\nConfirm the transaction (Y/N): ";
						char ch;
						cin >> ch;
						if (ch=='Y'||ch=='y')
						{
							acv.enter_balance(acv.return_balance()-money);
							format_transaction();
							cout << "\nTransaction Successfull."
								 << "\nCurrent balance: Rs. " << acv.return_balance();
							fobj.seekp(0);
							fobj.write((char *)&acv, sizeof(acv));
						}	
					}
					else
						cout << "\nYou don't have enough balance to perform this transaction.";
					fobj.close();
					goto lb;
				}
				case 2:
				{
					account_creation_view acv;
					fstream fobj("account_details.dat", ios::in|ios::out);
					fobj.read((char *)&acv, sizeof(acv));
					cout << "\nEnter deposit amount: Rs. ";
					cin >> money;
					cout << "\nConfirm the transaction (Y/N): ";
					char ch;
					cin >> ch;
					if (ch=='Y'||ch=='y')
					{
						acv.enter_balance(acv.return_balance()+money);
						format_transaction();
						cout << "\nTransaction Successfull."
							 << "\nCurrent balance: Rs. " << acv.return_balance();
						fobj.seekp(0);
						fobj.write((char *)&acv, sizeof(acv));
					}
					fobj.close();
					goto lb;
				}
				case 3:
				{
					account_creation_view acv;
					fstream fobj("account_details.dat", ios::in|ios::out);
					fobj.read((char *)&acv, sizeof(acv));
					cout << "\nEnter the amount you want to transfer: Rs. ";
					cin >> money;
					if (acv.return_balance()-money>=0)
					{
						cout << "\nEnter the receiver's account number ";
						cin >> temp_accno;
						char ch;
						cout << "\nConfirm the transaction (Y/N) : ";
						cin >> ch;
						if (ch=='Y'||ch=='y')
						{
							chdir("..\\");
							fstream fin("account_holder.dat", ios::in);
							account_holder ah1;
							int flag=0;
							while(!fin.eof())
							{
								fin.read((char *)&ah1, sizeof(ah1));
								if(temp_accno==ah1.return_accno())
								{
									flag=1;
									break;
								}
							}
							if (flag==1)
							{
								chdir(ah1.return_username());
								fstream fobj1("account_details.dat", ios::in|ios::out);
								account_creation_view acv1;
								fobj1.read((char *)&acv1, sizeof(acv1));
								acv1.enter_balance(acv1.return_balance()+money);
								fobj1.seekp(0);
								fobj1.write((char *)&acv1, sizeof(acv1));
								fobj1.close();
								chdir("..\\");
								chdir(temp_username);
								acv.enter_balance(acv.return_balance()-money);
								fobj.seekp(0);
								fobj.write((char *)&acv, sizeof(acv));
								format_transaction();
								cout << "\nCurrent balance: Rs. " << acv.return_balance();
								cout << "\nTransaction successfull.";
							}
							else if(flag==0)
							{
								cout << "\nThere is no such user exists with the given account number.";
								cout << "\nTransaction failed.";
							}
							fin.close();
						}
						else
						{
							cout << "\nTransaction oborted by user.";
							chdir(temp_username);
						}
					}
					else
						cout << "\nYou don't have enough balance to perform this transaction.";
				}
			}	
		}
};

void login_menu(char username[])
{
	int choose;
	lb: 
	cout << "\nWelcome " << username << " : "
		 << "\n1. View personal details."
		 << "\n2. Edit personal details."
		 << "\n3. Operations."
		 << "\n4. Close your account."
		 << "\n5. Logout."
		 << "\nEnter correct choice: ";
	cin >> choose;
	switch (choose)
	{
		case 1: 
		{
			account_creation_view acv;
			fstream fin("account_details.dat", ios::in);
			fin.read((char *)&acv, sizeof(acv));
			acv.view();
			fin.close();
			goto lb;
		}
		case 2:		
		{
			account_creation_view acv;
			fstream fin("account_details.dat", ios::in);
			fin.read((char *)&acv, sizeof(acv));
			fin.close();
			fstream fout("account_details.dat", ios::out);
			acv.edit();
			fout.seekg(0);
			fout.write((char *)&acv, sizeof(acv));
			fout.close();
			goto lb;	
		}
		case 3:
			OPERATIONS o;
			o.operations_menu(username);
			goto lb;
		case 4: 
		{
			char choice;
			cout << "\nAre you sure you want to close your account (Y/N): ";
			cin >> choice;
			if (choice=='Y'||choice=='y')
			{
				chdir("..\\");
				close_account(username);
				break;
			}
			else
				goto lb;
		}
		case 5: cout << "\nLogging out ...";
				break;
		default: cout << "\nWrong choice entered. Try again.";
				 goto lb;
	}
}

void login()
{
	//Function for login using username and password
	int flag=0;
	account_holder ach;
	char temp_username[100], temp_password[100];
	cout << "\nEnter your username: ";
	cin.sync();
	cin.getline(temp_username, 100);
	cout << "\nEnter your password: ";
	cin.sync();
	strcpy(temp_password, crypt_pass());
	fstream fin("account_holder.dat", ios::in);
	while(!fin.eof())
	{
		fin.read((char *)&ach, sizeof(ach));
		if((strcmp(ach.return_username(), temp_username)==0)&&(strcmp(ach.return_password(), temp_password)==0))
		{
			flag=1;
			break;
		}		
	}
	fin.seekg(0);
	fin.close();
	if (flag==1)
	{
		if (ach.return_status()=='Y')
			{
				chdir(ach.return_username());
				cout << "\nLogin Successfull.";
				login_menu(temp_username);
				chdir("..\\");
			}
		else if (ach.return_status()=='N')
			{
				cout << "\nAccount has been closed by you or by the bank.";
			}
	}
	else
		cout << "\nNo account has been created with us. Please create a new account.";
}

int account_write()
{
	//Function to write username and password into a file and account details into another file
	int sf;
	account_holder obj1;
	account_creation_view obj;
	obj.creation();
	sf=obj1.creation_2();
	if (sf==1)
	{
		obj.creation_part();
		obj.enter_accno(obj1.return_accno());
		obj.enter_acv_bcode(obj1.return_bank_code());
		fstream fout("account_holder.dat", ios::out|ios::app);
		fout.write((char *)&obj1, sizeof(obj1));
		fout.close();
		mkdir(obj1.return_username());
		chdir(obj1.return_username());
		fstream fout1("account_details.dat", ios::out);
		fstream fout2("transaction_details.dat", ios::in);
		fout1.write((char *)&obj, sizeof(obj));
		fout1.close();
		chdir("..\\");
		return sf;
	}
	else
		return sf;
}

class ADMINISTRATOR_MENU
{
	char temp_username[100];
	int choose;
	public:
		void admin_menu()
		{
			lb:
			cout << "\nAdministrator Menu: "
				 << "\n1. View all users."
				 << "\n2. Delete a user account."
				 << "\n3. Create a new user account."
				 << "\n4. Close or reopen a user's account."
				 << "\n5. Edit a user's account."
				 << "\n6. Create a bank branch."
				 << "\n7. Reset program."
				 << "\n8. Goto home."
				 << "\nEnter correct option: ";
			cin >> choose;
			switch(choose)
			{
				case 1:
				{
					account_holder ach;
					fstream fin("account_holder.dat", ios::in);
					if(fin)
					{
						fin.read((char *)&ach, sizeof(ach));
						while(!fin.eof())
						{
							cout << "\nUSERNAME "<< "\t\t"<<"PASSWORD " << endl;
							cout << ach.return_username() <<"\t\t\t" << ach.return_password() << endl;
							fin.read((char *)&ach, sizeof(ach));
						}
						fin.close();
					}
					else
						cout << "\nNo account exists.";
					goto lb;
				}
				case 2:
				{
					int flag=0;
					account_holder ah;
					cout << "\nEnter the username : ";
					cin.sync();
					cin.getline(temp_username, 100);
					fstream fin("account_holder.dat", ios::in);
					fstream fout("temp_account_holder.dat", ios::out);
					while(!fin.eof())
					{
						fin.read((char *)&ah, sizeof(ah));
						if (strcmp(temp_username, ah.return_username())!=0)
							fout.write((char *)&ah, sizeof(ah));
						else
						{
							flag=1;
							continue;	
						}	
					}
					fout.close();
					fin.close();
					if (flag==0)
						cout << "\nAccount doesn't exist.";
					else
					{
						remove("account_holder.dat");
						rename("temp_account_holder.dat", "account_holder.dat");
						chdir(temp_username);
						remove("account_details.dat");
						remove("transaction_details.dat");
						chdir("..\\");
						rmdir(temp_username);
						cout << "\nAccount deleted.";
					}
					goto lb;
				}
				case 3:
				{
					account_write();
					goto lb;
				}
				case 4:
				{
					account_holder ah;
					char temp_username[100];
					int choose, pos;
					cin.sync();
					cout << "\nEnter the username: ";
					cin.getline(temp_username, 100);
					cout << "\n Press 1 to reopen an account or press 2 to close an account: ";
					cin >> choose;
					fstream fobj("account_holder.dat", ios::in|ios::out);
					while (!fobj.eof())
					{
						pos=fobj.tellg();
						fobj.read((char *)&ah, sizeof(ah));
						if (strcmp(temp_username, ah.return_username())==0)
							break;
					}
					if (choose==1)
					{
						if(ah.return_status()=='N')
						{
							ah.change_status_Y();
							cout << "\nAccount reopened successfully.";
						}
						else
							cout << "\nThe account has already been reopened.";
					}
					else if (choose==2)
					{
						if(ah.return_status()=='Y')
						{
							ah.change_status_N();
							cout << "\nAccount closed successfully";
						}
						else
							cout << "\nThe account has already been closed.";
					}
					fobj.seekp(pos);
					fobj.write((char *)&ah, sizeof(ah));
					fobj.sync();
					fobj.seekg(0);
					fobj.sync();
					fobj.seekp(0, ios::end);
					fobj.close();
					goto lb;
				}
				case 6:
				{
					fstream fout("bank_branch.dat", ios::out|ios::app);
					BANK_BRANCH bb;
					bb.create_branch();
					fout.write((char *)&bb, sizeof(bb));
					fout.close();
					goto lb;
				}
				case 7:
				{
					char temp_username[100];
					fstream fin("account_holder.dat", ios::in);
					account_holder ah;
					while(!fin.eof())
					{
						fin.read((char *)&ah, sizeof(ah));
						strcpy(temp_username, ah.return_username());
						chdir(temp_username);
						remove("account_details.dat");
						remove("transaction_details.dat");
						chdir("..\\");
						rmdir(temp_username);
					}
					fin.close();
					remove("account_holder.dat");
					remove("bank_branch.dat");
					Sleep (500);
					cout << "\nReset in progress ";
					for (int i=0; i<=5; i++)
					{
						Sleep (400);
						cout << ".";
					}
					cout << "\nProgram has been reset.";
					goto lb;
				}
				case 8:
					break;	
			}
		}
};

class BANKING_MENU
{
	int no;
	public :
		BANKING_MENU()
		{
			lb:
			cout << "\nBANKING MENU: "
			     << "\n1. Login to your account."
			     << "\n2. Create a new account."
			     << "\n3. Reopen your closed account."
			     << "\n4. Goto home."
			     << "\nEnter your choice: ";
			cin >> no;
			switch (no)
			{
				case 1: 
					login();
					goto lb;
				case 2: 
				{
					int sf;
					sf=account_write();
					if (sf==0)
						cout << "\nAccount creation failed.";
					goto lb;
				}	
				case 3:
					reopen_account();
					goto lb;	
				
				case 4: break;
					
				default: 
					cout << "\nWrong choice! Try again.";
					goto lb;
			}
		}
};

void about()
{
	//Function to see the about section of the program
	fstream about_out("bms_about.txt", ios::in);
	char about_str[500];
	cout << "\n\n==========================================================================================\n\n";
	while (!about_out.eof())
	{
		about_out.getline(about_str, 500);
		cout << about_str << endl;
	}
	cout << "\n==========================================================================================\n";
	about_out.close();
}

int main()
{
	system("COLOR 8F");
	time_t t = time(0);
	tm* now = localtime(&t);
	cout <<"\n                                   **** BANK MANAGEMENT SOFTWARE ****                                   " << now->tm_mday << '-' 
    																													<< (now->tm_mon + 1) << '-'
    																													<< (now->tm_year + 1900) << endl;
	lb:
	cout << "\nEnter program password: ";
    char program_password[100];
    strcpy(program_password, crypt_pass());
	if ((strcmp(program_password, "project")==0)||(strcmp(program_password, "admin")==0))
		{
			while(1)
			{
				cout << "\a";
				int choice;
				cout << "\nMAIN MENU"
					 << "\n1. Banking."
					 << "\n2. Administrator Menu."
					 << "\n3. About"
					 << "\n4. Exit Program."
					 << "\nENTER YOUR CHOICE: ";
				cin >> choice;
				switch(choice)
				{
					case 1: 
						BANKING_MENU();
						break;
						
					case 2:
					{
						char admin_pass[100];
						cout << "\nEnter administrator password: ";
						strcpy(admin_pass, crypt_pass());
						if (strcmp(admin_pass, "admin")==0)
						{
							ADMINISTRATOR_MENU am;
							am.admin_menu();
						}
						else
							cout << "\nWrong password. Try again!";
						break;
					}
					case 3:
						about();
						break;
					case 4: 
						Sleep (500);
						cout << "\n\nExiting ";
						for (int i=0; i<=4; i++)
						{
							Sleep (500);
							cout << ".";
						}
						exit(0);
						break;
					
					default:
						cout << "\nYou have entered a wrong choice. Try again.";
				}
			}	 	
		}
	else
		cout << "\nYou have entered a wrong password. Try again.";
		goto lb;
}
