#pragma once
#include <string>
using namespace std;
class CBook
{
private:
	string m_name;
	string m_isbn;
	string m_pressInfo;
	double m_price;
	int m_page;
	string m_author;
	int m_num;
public:
	CBook();
	void setNum(int num);
	int getNum();
	void setName(string name);
	string getName();
	void setIsbn(string isbn);
	string getIsbn();
	void setPressInfo(string perssInfo);
	string getPressInfo();
	void setPrice(double price);
	double getPrice();
	void setPage(int page);
	int getPage();
	void setAuthor(string author);
	string getAuthor();
	void checkIsnb();
	bool isBorrowed();
	void showInfo();
	friend std::ostream& operator <<(std::ostream& os, const CBook& book);
	friend std::istream& operator >>(std::istream& is, CBook& book);
};
