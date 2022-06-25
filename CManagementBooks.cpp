#include "CManagementBooks.h"
using namespace std;

void CManagementBooks::showCurrentAllBook()
{
	for (int i = 0; i < m_allBookNum; i++)
	{
		cout << "书名:" << m_books[i].getName() <<" " << "剩余数量" << m_books[i].getNum() << endl;
	}
}

CManagementBooks::CManagementBooks()
{
	m_allBookNum = 0;
}

void CManagementBooks::addBook(CBook book)
{
	int flag = 0;
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == book.getName())
		{
			flag = 1;
			m_books[i].setNum(m_books[i].getNum() + book.getNum());
			ofstream writeFile("library.txt", ios::out);
			for (int i = 0; i < m_allBookNum; i++)
			{
				writeFile << m_books[i];
			}
			writeFile.close();
			break;
		}
	}
	if (!flag)
	{
		ofstream writeFile("library.txt", ios::app);
		m_books.push_back(book);
		m_allBookNum++;
		writeFile << book;
		writeFile.close();
	}
}



int CManagementBooks::getAllBookNum()
{
	return m_allBookNum;
}

void CManagementBooks::showAllBooksInfo()
{
	for (int i = 0; i < m_allBookNum; i++)
	{
		m_books[i].showInfo();
	}
}

bool CManagementBooks::borrow(string name)
{

	for (int i =0; i <m_allBookNum; i++)
	{
		if (m_books[i].getName() == name)
		{
			if (m_books[i].getNum() >= 1)
			{
				m_books[i].setNum(m_books[i].getNum() - 1);
				cout << "借书成功" << endl;
				ofstream writeFile("library.txt");
				for (int i = 0; i < m_allBookNum; i++)
				{
					writeFile << m_books[i];
				}
				writeFile.close();
				return true;
			}
			else
			{
				cout << "此书数量不足" << endl;
				return false;
			}
		}

	}
	cout << "很抱歉，暂无此书" << endl;
	return false;
}

void CManagementBooks::Return(string id,string bookName)
{
	CBook book;
	book.setName(bookName);
	addBook(book);
	ofstream writeFile("borrowedBook.txt",ios::out);
	for (auto iter =m_outBookMap.begin(); iter != m_outBookMap.end(); ++iter)
	{
		if (iter->first == id && iter->second == bookName)
		{
			m_outBookMap.erase(iter);
			break;
		}
	}
	for (auto map : m_outBookMap)
	{
		writeFile << endl << map.first << " " << map.second;
	}
	writeFile.close();
}

void CManagementBooks::initOutBook()
{
	ifstream readFile("borrowedBook.txt");
	if (!readFile.is_open())
	{
		cout << "查看全体借书情况数据读取出错" << endl;
	}
	else
	{
		while (!readFile.eof())
		{
			string studentId, bookName;
			readFile >> studentId >> bookName;
			m_outBookMap.insert(pair<string, string>(studentId, bookName));
		}
	}
	readFile.close();

}

void CManagementBooks::checekOutBook()
{
	for (auto map : m_outBookMap)
	{
		cout << "借阅人学工号:" << map.first<<" " << "借阅书名:" << map.second << endl;
	}
}

void CManagementBooks::initBooks()
{
	ifstream readFile;
	readFile.open("library.txt");
	if (!readFile.is_open())
	{
		cout << "图书数据读取错误" << endl;
		readFile.close();
		return;
	}
	while (!readFile.eof())
	{
		
		CBook book;
		readFile >> book;
		m_allBookNum++;
		m_books.push_back(book);
	}
	readFile.close();
}

int CManagementBooks::checkBorrowedBook(string userId)
{
	
	int flag = 0;
	for (auto map : m_outBookMap)
	{
		if (userId == map.first)
		{
			if (!flag)
			{
				cout << "您已经借的全部图书如下：" << endl;
				flag++;
			}
			else
			{
				flag++;
			}
			cout << map.second << " ";
		}
	}
	if (!flag)
	{
		cout << "您目前没有借书" << endl;
	}
	cout << "共：" << flag << "本";
	cout << endl;
	return flag;
}

void CManagementBooks::viewBorrowerDetails(string id)
{
	ifstream readFile("teacher.txt");
	ifstream readFile1("student.txt");
	int flag = 0;
	if (!readFile1.is_open()|| !readFile.is_open())
	{
		cout << "用户数据读取错误" << endl;
	}
	while (!readFile1.eof())
	{
		string act1, name, department, gender;
		readFile1 >> act1 >> name >> gender >> department;
		if (id == act1)
		{
			cout<<"用户类别:"<<"学生"<<" " << "用户姓名:" << name << " " << "用户性别:" << gender << " " << "用户所在部门:" << department << endl;
			flag = 1;
		}
	
	}
	if (!flag)
	{
		while (!readFile.eof())
		{
			string act1, name, department, gender;
			readFile >> act1 >> name >> gender >> department;
			if (id == act1)
			{
				flag = 1;
				cout << "用户类别:"<<"老师"<<" " << "用户姓名:" << name << " " << "用户性别:" << gender << " " << "用户所在部门:" << department << endl;
			}

		}
	}
	if (!flag)
	{
		cout << "无此用户！" << endl;
	}
	readFile.close();
	readFile1.close();
}

bool CManagementBooks::checkTrueBorrow(string id, string bookName)
{
	
	for (auto map : m_outBookMap)
	{
		if (map.first == id && map.second == bookName)
		{
			return true;
		}
	}
	return false;
}

void CManagementBooks::setMapValue(string userId,string bookName)
{
	m_outBookMap.insert(pair<string, string>(userId, bookName));
}



