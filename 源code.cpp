#include<iostream>
#include"CBook.h"
#include"CStudent.h"
#include"CManagementBooks.h"
#include"CTeacher.h"
#include<fstream>
#include"CAdministrator.h"
#include"COperationManagement.h"
using namespace std;
int main()
{
	CManagementBooks mb;
	CPerson* user = nullptr;
	COperationManagement om;
	om.init(mb);
	cout << "***** 欢迎来到图书馆 *****" << endl;
	cout << "注意事项" << endl;
	cout << "1.学生最多共可借三本书,老师最多共可借五本"<<endl<<endl;
	cout << "请选择您的登录方式 1:老师 2:学生 3:管理员" << endl;
	int t;
	cin >> t;
	if (t == 1)
	{
		user = new CTeacher;
	}
	else if(t == 2)
	{
		user = new CStudent;
	}
	else if(t == 3)
	{
		CAdministrator admin;
		om.adminLogin(admin);
		admin.showInfo();
		om.adminOperation(admin, mb);
		return 0;
	}
	cout << "您是否已有账号？(y/n):" << endl;
	string c;
	cin >> c;
	if (c == "y")
	{
		cout << "请登录:" << endl;
		om.login(user,t);
		user->showInfo();
	}
	else
	{
		cout << "来注册一个吧!" << endl;
		om.Register(user,t);
	}
	om.userOperation(user, mb);
	delete user;
	return 0;
}
