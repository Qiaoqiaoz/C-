#include "COperationManagement.h"
void COperationManagement::login(CPerson* user, int t)
{
	ifstream readFile;
	ifstream readFile1;
	if (t == 1)
	{
		readFile.open("teacherLogin.txt");
		readFile1.open("teacher.txt");
	}
	else
	{
		readFile1.open("student.txt");
		readFile.open("studentLogin.txt");
	}
	if (!readFile.is_open())
	{
		cout << "登录数据读取错误" << endl;
	}
	if (!readFile1.is_open())
	{
		cout << "用户数据读取错误" << endl;
	}
	cout << "请输入您的学工号:" << endl;
	string account, password;
	cin >> account;
	int flag = 0;
	while (!readFile.eof())
	{
		string act;
		readFile >> act;
		if (act == account)
		{
			cout << "请输入密码:" << endl;
			cin >> password;
			string pwd;
			readFile >> pwd;
			if (pwd == password)
			{
				cout << "登录成功" << endl;
				flag = 1;
				
				while (!readFile1.eof())
				{
					
					readFile1 >> user;
			
					if(user->getId() == act)
					{
						break;
					}
				}
				break;
			}
			else
			{
				cout << "密码错误，请重新登录" << endl;
				login(user, t);
			}
		}

	}
	if (!flag)
	{
		cout << "学工号错误，请重输入" << endl;
		login(user, t);
	}
	readFile.close();
	readFile1.close();
}

void COperationManagement::Register(CPerson* user, int t)
{
	ofstream writeFile;
	ofstream writeFile1;
	if (t == 1)
	{
		writeFile1.open("teacher.txt", ios::app);
		writeFile.open("teacherLogin.txt",ios::app);
	}
	else
	{
		writeFile1.open("student.txt", ios::app);
		writeFile.open("studentLogin.txt",ios::app);
	}
	string pwd, act;
	cout << "请输入您的学工号作为注册账号:" << endl;
	cin >> act;
	cout << "请输入您的注册密码:" << endl;
	cin >> pwd;
	writeFile << endl << act << " " << pwd;
	cout << "请完善您的相应信息:" << endl;
	string  name, department, gender;
	cout << "您的姓名:" << endl;
	cin >> name;
	cout << "您的性别:" << endl;
	cin >> gender;
	cout << "您所在的院系:" << endl;
	cin >> department;
	writeFile1 <<endl << act << " " << name << " " << gender << " " << department;//这里不能用user,因为在登录时才用，并且并没有初始化
	writeFile.close();
	writeFile1.close();
	cout << "注册成功！ 赶紧登录进入图书管吧!" << endl;
	login(user, t);
}

void COperationManagement::userOperation(CPerson* user, CManagementBooks mb)
{
	while (1)
	{
		cout << "请选择您的操作 1.借书 2.查看自己当前借书情况 3.还书 4.退出" << endl;
		int t;
		cin >> t;
		if (t == 1)
		{
			cout << "当前图书馆情况如下：" << endl;
			mb.showCurrentAllBook();
			cout << "是否有您想要借阅的图书(y/n)" << endl;
			string s;
			cin >> s;
			if (s == "y")
			{
				user->borrowBookFromLibrary(mb);
			}
		}
		else if (t == 2)
		{
			mb.checkBorrowedBook(user->getId());
		}
		else if (t == 3)
		{
			user->returnBook(mb);
		}
		else if (t == 4)
		{
			cout << "退出成功" << endl;
			break;
		}
		else
		{
			cout << "暂无此操作，请按提示操作" << endl;
		}
	}
}

void COperationManagement::adminLogin(CAdministrator& admin)
{
	ifstream readFile("adminLogin.txt");
	ifstream readFile1("admin.txt");
	cout << "请输入您的工号:" << endl;
	string account, password;
	cin >> account;
	int flag = 0;
	while (!readFile.eof())
	{
		string act;
		readFile >> act;
		if (act == account)
		{
			cout << "请输入密码:" << endl;
			cin >> password;
			string pwd;
			readFile >> pwd;
			if (pwd == password)
			{
				cout << "登录成功,欢迎您" << endl;
				flag = 1;

				while (!readFile1.eof())
				{
					
					readFile1 >> admin;
					if(admin.getId() == act)
					{
						break;
					}
				}
				break;
			}
			else
			{
				cout << "密码错误，请重新登录" << endl;
				adminLogin(admin);
			}
		}

	}
	if (!flag)
	{
		cout << "学工号错误，请重输入" << endl;
		adminLogin(admin);
	}
	readFile.close();
	readFile1.close();

}

void COperationManagement::init(CManagementBooks& mb)
{
	mb.initBooks();
	mb.initOutBook();
}

void COperationManagement::adminOperation(CAdministrator admin, CManagementBooks mb)
{
	while (1)
	{
		cout << "请选择您的操作 1.增加书 2.查看当前借阅情况 3.查看当前所有图书信息情况 4.查看借阅人详细信息 5.退出" << endl;
		int t;
		cin >> t;
		if (t == 1)
		{
			admin.addBook(mb);
		}
		else if (t == 2)
		{
			mb.checekOutBook();
		}
		else if (t == 3)
		{
			mb.showAllBooksInfo();
		}
		else if (t == 4)
		{
			string id;
			cout << "请输入您要查看借阅人的学工号:" << endl;
			cin >> id;
			mb.viewBorrowerDetails(id);
		}
		else if (t == 5)
		{
			cout << "退出成功" << endl;
			break;
		}
		else
		{
			cout << "暂无此操作，请按提示操作" << endl;
		}
	}
}


