#pragma once    
#include "CPerson.h"
#include<fstream>
class CTeacher :
    public CPerson
{
public:
    CTeacher();
    void borrowBookFromLibrary(CManagementBooks& mb);
    void showInfo();
};
