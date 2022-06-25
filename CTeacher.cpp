#include "CTeacher.h"
#include<fstream>

CTeacher::CTeacher()
{
    m_name = "刘X";
}

void CTeacher::borrowBookFromLibrary(CManagementBooks& mb)
{
   
        int all = mb.checkBorrowedBook(m_id);
        if (all < 5)
        {
            string name;
            cout << "请输入您要借的书名:" << endl;
            cin >> name;
            if (mb.borrow(name))
            {
                ofstream writeFile("borrowedBook.txt", ios::app);
                mb.setMapValue(m_id, name);
                writeFile << endl << m_id << " " << name;
                writeFile.close();
            }
        }
        else
        {
            cout << "您已经超过了最大可借阅数" << endl;
        }
}
void CTeacher::showInfo()
{
    cout << "姓名:" << m_name<<" " << "学号:" << m_id<<" " << "性别:" << m_gender<<" " << "院系:" << m_department << endl;
}


