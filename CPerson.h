#pragma once
#include<iostream>
#include"CManagementBooks.h"
using namespace std;
class CPerson
{
protected:
	string m_id;
	string m_name;
	string m_gender;
	string m_department;
public:
	CPerson();
    virtual	void borrowBookFromLibrary(COperationManagement& mb)= 0;
	void setId(string id);
	void setName(string name);
	void setGender(string Gender);
	void setDepartment(string department);
    virtual void showInfo()=0;
	virtual ~CPerson();
	void returnBook(COperationManagement& mb);
	string getId();
	string getName();
	string getGender();
	string getDepartment();
	friend std::ostream& operator << (std::ostream& os, const CPerson* person);
	friend std::istream& operator >> (std::istream& is, CPerson* user);
};
