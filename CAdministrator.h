#pragma once
#include<iostream>
#include<string>
#include "CManagementBooks.h"
#include"CBook.h"
using namespace std;
class CAdministrator
{
private:
	string m_id;
	string m_name;
	string m_gender;
	string m_department;
public:
	void addBook(CManagementBooks& mb);
	void setId(string id);
	void setName(string name);
	void setGender(string Gender);
	void setDepartment(string department);
	string getId();
	string getName();
	string getGender();
	string getDepartment();
	void showInfo();
	friend std::istream& operator >> (std::istream& is, CAdministrator& admin);
};