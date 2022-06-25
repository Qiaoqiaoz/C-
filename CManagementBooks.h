#pragma once
#include<iostream>
#include"CBook.h"
#include<vector>
#include<unordered_map>
#include<fstream>
#include<string>
#include<fstream>
using namespace std;
class CManagementBooks
{
private:
	vector<CBook> m_books;
	int m_allBookNum;
	unordered_multimap<string, string>m_outBookMap;

public:
	void showCurrentAllBook();
	CManagementBooks();
	void addBook(CBook book);
	int getAllBookNum();
	void showAllBooksInfo();
	bool borrow(string name);
	void Return(string id,string bookName);
	void initOutBook();
	void checekOutBook();
	void initBooks();
	int checkBorrowedBook(string userId);
	void viewBorrowerDetails(string id);
	bool checkTrueBorrow(string id,string bookName);
	void setMapValue(string userId, string bookName);
};