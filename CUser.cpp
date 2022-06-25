#include "CUser.h"
#include<iostream>
#include<fstream>
#include"CManagementBooks.h"
using namespace std;




CUser::CUser()
{
    m_name = "陈1";
}

void CUser::setId(string id)
{
    m_id = id;
}

void CUser::setName(string name)
{
    m_name = name;
}

void CUser::setGender(string gender)
{
    m_gender = gender;
}



void CUser::setDepartment(string department)
{
    m_department = department;
}




CUser::~CUser()
{
}

void CUser::returnBook(CManagementBooks& mb)
{
    int all = mb.checkBorrowedBook(m_id);
    if (all == 0)
    {
        cout << "您暂未借书,无需归还" << endl;
    }
    else
    {
        cout << "请输入您要归还的书名:" << endl;
        string bookName;
        cin >> bookName;
        if (mb.checkTrueBorrow(m_id, bookName))
        {
            mb.Return(m_id, bookName);
            cout << "还书成功" << endl;
        }
        else
        {
            cout << "您并未借阅此书" << endl;
        }
    }
}

string CUser::getId()
{
    return m_id;
}

string CUser::getName()
{
    return m_name;
}

string CUser::getGender()
{
    return m_gender;
}


string CUser::getDepartment()
{
    return m_department;
}

std::ostream& operator<<(std::ostream& os, const CUser* user)
{
    os<< endl << user->m_id << " " << user->m_name << " " << user->m_gender << " " << user->m_department;
    return os;
}

std::istream& operator>>(std::istream& is, CUser* user)
{
   is >> user->m_id >> user->m_name >> user->m_gender >> user->m_department;
   return is;
}
