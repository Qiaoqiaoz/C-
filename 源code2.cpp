#include<bits/stdc++.h>
using namespace std;
class Date
{
    private:
        int year;
        int month;
        int day;
    public:
        Date(int x,int y,int z):year(x),month(y),day(z){}
        Date(){}
        int getYear(){return year;}
        int getMonth(){return month;}
        int getDay(){return day;}
        void setYear(int x){year=x;}
        void setMonth(int x){month=x;}
        void setDay(int x){day=x;}
        friend ostream & operator <<(ostream & output,Date & obj)
        {
            output<<obj.year<<" "<<obj.month<<" "<<obj.day;
            return output;
        }
        friend istream & operator >>(istream & input,Date & obj)
        {
            input>>obj.year>>obj.month>>obj.day;
            return input;
        }
        bool operator <(const Date & obj)const
        {
            return obj.year!=year?year<obj.year:obj.month!=month?month<obj.month:day<obj.day;
        }
};
class Record
{
    private:
        string bookName;
        int bookIndex;
        string stuName;
        string type;//操作类型
        int stuID;
        Date opTime;
        Date endTime;
        bool ifback;//是否归还
    public:
        Record(){ifback=0;}
        Record(string book,int b,string s1,int s2,string ty,Date o,Date end,bool f)
        {
            bookName=book;
            bookIndex=b;
            stuName=s1;
            stuID=s2;
            type=ty;
            opTime=o;
            endTime=end;
            ifback=f;
        }
        string getName(){return bookName;}
        int getIndex(){return bookIndex;}
        string getstuName(){return stuName;}
        int getID(){return stuID;}
        Date getopTime(){return opTime;}
        Date getendTime(){return endTime;}
        bool getifback(){return ifback;}
        string getType(){return type;}
        void setType(string x){type=x;}
        void setName(string x){bookName=x;}
        void setIndex(int x){bookIndex=x;}
        void setstuName(string x){stuName=x;}
        void setID(int x){stuID=x;}
        void setopTime(Date t){opTime=t;}
        void setendTime(Date x){endTime=x;}//修改还书时间
        void setifback(bool f){ifback=f;}
 
        friend ostream & operator <<(ostream & out,Record & obj);
        friend istream & operator >>(istream & in,Record & obj);
 
 
};
ostream & operator <<(ostream & out,Record & obj)
{
    out<<obj.bookIndex<<" ";
    out<<obj.bookName<<" ";
    out<<obj.stuName<<" ";
    out<<obj.stuID<<" ";
    out<<obj.type<<" ";
    out<<obj.opTime<<"   ";
    out<<obj.endTime<<"    ";
    out<<obj.ifback;
    return out;
}
istream & operator >>(istream & in,Record & obj)
{
    in>>obj.bookIndex>>obj.bookName>>obj.stuName>>obj.stuID>>obj.type>>
    obj.opTime>>obj.endTime>>obj.ifback;
 
    return in;
}
class Records
{
    protected:
        int RecordNum;
        vector <Record> v1;
        vector <Record> ::iterator vit1;
        multimap<bool,int>m2;
        multimap<bool,int>::iterator mit2;//是否归还bool
 
    public:
        Records(){RecordNum=0;}
        int getRecordNum(){return RecordNum;}
        vector <Record>  & getRecord(){return v1;}
        multimap<bool,int> & getM2(){return m2;}
 
        void setRecordNum(int x){RecordNum=x;}
        //无删除记录与增加记录Op，book类中和student类中这两个函数不同
        void disAllRecord();//所有记录
        void disAllRecord(int n);//所有记录
        void disNobackRecord();//显示未还书记录
 
 
};
 
void Records::disAllRecord()
{
    for(int i=0;i<v1.size();++i)cout<<v1[i]<<endl;
}
void Records::disNobackRecord()
{
    if(m2.find(0)!=m2.end())
        for(mit2=m2.lower_bound(0);mit2!=m2.upper_bound(0);++mit2)
            cout<<v1[mit2->second]<<endl;
    else cout<<"no records!"<<endl;
}
class Book:public Records
{
    private:
        string name;
        int index;
        int tot;//总数
        int shengyu;//剩余数量
        char ch;//辅助格式
        multimap<int,int>m1;
        multimap<int,int>::iterator mit1;//学号int
 
    public:
        Book(string n,int in,int tott,int shengyuu)
        {
            name=n;
            index=in;
            tot=tott;
            shengyu=shengyuu;
            ch='/';
        }
        Book()
        {
            ch='/';
        }
        multimap<int,int>& getM1(){return m1;}
        string getName(){return name;}
        int getIndex(){return index;}
        int getShengyu(){return shengyu;}
        int getTot(){return tot;}
        void setEndTime(int);//根据学号修改 op结束时间（续借）；
        void setTot(int x){tot=x;}
        void setShengyu(int x){shengyu=x;}
        void setName(string x){name=x;}
        void setIndex(int x){index=x;}
        void deleteRecord(int id,Date preTime)//还书时 标记 借书记录；
        {
            for(mit1=m1.lower_bound(id);mit1!=m1.upper_bound(id);++mit1)
            {
                if(v1[mit1->second].getifback()==0)
                {
                    v1[mit1->second].setifback(1);
                    v1[mit1->second].setendTime(preTime);
                }
            }
        }
        void addRecord(Record r)//增加一条记录
        {
            RecordNum++;
            v1.push_back(r);
            m2.insert(make_pair(r.getifback(),v1.size()-1));
            m1.insert(make_pair(r.getID(),v1.size()-1));
        }
 
        friend ostream & operator <<(ostream & output,Book & obj);
        friend istream & operator >>(istream & input,Book & obj);
        void disBase()
        {
            cout<<index<<" "<<name<<" "<<shengyu<<" "<<ch<<
        " "<<tot;
        }
 
 
};
void Book::setEndTime(int id)
{
    Date tt;
    for(mit1=m1.lower_bound(id);mit1!=m1.upper_bound(id);++mit1)
    {
        if(v1[mit1->second].getifback()==0)
        {
            tt=v1[mit1->second].getopTime();
            tt.setMonth(tt.getMonth()+2);
            v1[mit1->second].setendTime(tt);
        }
    }
}
ostream & operator <<(ostream & output,Book & obj)
{
    output<<obj.index<<" "<<obj.name<<" "<<obj.shengyu<<" "<<obj.ch<<
    " "<<obj.tot<<"    "<<obj.RecordNum<<endl;
 
    if(obj.getRecordNum())
    {
        vector <Record> vt;
        vt=obj.getRecord();
        for(int j=0;j<vt.size();++j)
            output<<vt[j]<<endl;
    }
    return output;
}
istream & operator >>(istream & input,Book & obj)
{
    input>>obj.index>>obj.name>>obj.shengyu>>obj.ch>>obj.tot>>obj.RecordNum;
    int p=obj.RecordNum;
    obj.setRecordNum(0);
    for(int i=1;i<=p;++i)
    {
 
        Record r;
        input>>r;
        obj.addRecord(r);
    }
    return input;
}
 
class Student:public Records
{
    private:
        string name;
        int ID;
        int num;//剩余借阅量
        multimap<int,int>m1;
        multimap<int,int>::iterator mit1;//书号int
    public:
        Student(string n,int id)
        {
            name=n;
            ID=id;
            num=10;
        }
        Student()
        {
            num=10;
        }
        multimap<int,int>& getM1(){return m1;}
        string getName(){return name;}
        int getID(){return ID;}
        int getNum(){return num;}
        void setName(string n){name=n;}
        void setID(int x){ID=x;}
        void setNum(int x){num=x;}
        void deleteRecord(int index,Date preTime)//和student类中的同名函数有差别
        {
            for(mit1=m1.lower_bound(index);mit1!=m1.upper_bound(index);++mit1)
            {
                if(v1[mit1->second].getifback()==0)
                {
                    v1[mit1->second].setifback(1);
                    v1[mit1->second].setendTime(preTime);
                }
            }
        }
        void setEndTime(int index)
        {
            Date tt;
            for(mit1=m1.lower_bound(index);mit1!=m1.upper_bound(index);++mit1)
            {
                if(v1[mit1->second].getifback()==0)
                {
                    tt=v1[mit1->second].getopTime();
                    tt.setMonth(tt.getMonth()+2);
                    v1[mit1->second].setendTime(tt);
                }
            }
        }
        void addRecord(Record r)//增加一条记录
        {
            RecordNum++;
            v1.push_back(r);
            m2.insert(make_pair(r.getifback(),v1.size()-1));
            m1.insert(make_pair(r.getIndex(),v1.size()-1));//和book类中的添加函数有多不同；
        }
 
        bool queryTLE(Date);
        void disBase()
        {
            cout<<name<<" ";
            cout<<ID<<" ";
            cout<<num;
        }
 
 
 
        friend ostream & operator <<(ostream  & output,Student & obj);
        friend istream & operator >>(istream & input,Student & obj);
 
};
istream & operator >>(istream & input,Student & obj)
{
 
    input>>obj.name>>obj.ID>>obj.num>>obj.RecordNum;
    int p=obj.getRecordNum();
    obj.setRecordNum(0);
    for(int i=1;i<=p;++i)
    {
        Record r;
        input>>r;
        obj.addRecord(r);
 
    }
    return input;
}
ostream & operator <<(ostream  & output,Student & obj)
{
    output<<obj.name<<" ";
    output<<obj.ID<<" ";
    output<<obj.num<<"  ";
    output<<obj.RecordNum<<endl;
    if(obj.getRecordNum())
    {
        vector<Record>vt;
        vt=obj.getRecord();
        for(int j=0;j<vt.size();++j)
            output<<vt[j]<<endl;
    }
    return output;
}
bool Student::queryTLE(Date tt)
{
    Date temp;
 
    for(mit2=m2.lower_bound(0);mit2!=m2.upper_bound(0);++mit2)
    {
 
        temp=v1[mit2->second].getendTime();
        if(temp<tt)return 1;
    }
    return 0;
}
class MangerOp
{
    private:
        int stuNum;//学生总数
        int bookNum;//书种数
        vector <Student> v1;
        vector <Student>::iterator vit1;
        map <int,int> m1;//学号,hu yi,so just use map
        map <int,int> ::iterator mit1;
 
        vector <Book> v2;
        vector <Book>::iterator vit2;
        map<int,int>m2;//书号
        map<int,int>::iterator mit2;
        map<string,int> m3;//书名
        map<string,int> ::iterator mit3;
 
 
    public:
        MangerOp()
        {
            stuNum=0;bookNum=0;v2.clear();m2.clear();m3.clear();
            load1();load2();
        }
        ~MangerOp()
        {
            save1();
            save2();
        }
        void load1();
        void load2();
        void save1();
        void save2();
 
        void addBook();
        void addStu();
        void deleteBook();
        void deleteStu();
 
        void queryStuAll();//查询某学生所有记录
        void queryStuNoback();//未还书记录
        void queryBookAllRecord();
        void queryBookNoback();
 
        void queryABook();//某本书信息
        void queryAStu();//某同学信息
 
};
void MangerOp::load1()
{
    ifstream infile("20171778book.txt",ios::in);
        if(!infile)return ;
    v2.clear();
    m2.clear();
    m3.clear();
    Book b;
    int i=0;
    while(infile>>b)
    {
        bookNum++;
        v2.push_back(b);
        m2.insert(make_pair(b.getIndex(),i));
        m3.insert(make_pair(b.getName(),i));
        i++;
        vector < Record > & vt=b.getRecord();//传引用法；此外考虑在book类中写一个小函数清空记录向量；
 
        multimap<bool,int> & m2=b.getM2();
        multimap<int,int>& m1=b.getM1();
        vt.clear();
        m1.clear();m2.clear();m3.clear();
    }
    bookNum=i;
    infile.close();
    cout<<"books load success!"<<endl;
}
void MangerOp::load2()
{
    ifstream infile("20171778stu.txt",ios::in);
        if(!infile)return ;
    v1.clear();
    m1.clear();
    Student s;
    int i=0;
    while(infile>>s)
    {
        v1.push_back(s);
        m1.insert(make_pair(s.getID(),i));
        i++;
        vector <Record> & vt=s.getRecord();//
        multimap <bool,int> & m2=s.getM2();
        multimap<int,int> & m1=s.getM1();
        vt.clear();
        m1.clear();
        m2.clear();
    }
    stuNum=i;
    infile.close();
    cout<<"students load success!"<<endl;
}
void MangerOp::save1()
{
    ofstream outfile("20171778book.txt",ios::out);
    if(!outfile)return ;
    for(int i=0;i<bookNum;++i)
    {
        outfile<<v2[i];
    }
    outfile.close();
}
void MangerOp::save2()
{
    ofstream outfile("20171778stu.txt",ios::out);
        if(!outfile)return ;
    for(int i=0;i<stuNum;++i)
    {
        outfile<<v1[i];
 
    }
    outfile.close();
}
void MangerOp::queryAStu()
{
    int id;
    cin>>id;
    mit1=m1.find(id);
    if(mit1!=m1.end())
    {
        cout<<v1[m1[id]];
    }
}
void MangerOp::queryABook()
{
    int index;
    cin>>index;
    mit2=m2.find(index);
    if(mit2!=m2.end())
        cout<<v2[m1[index]];
}
void MangerOp::addBook()
{
    string name;
    int index;
    int n;
    while(cin>>index&&index!=-1)
    {
        cin>>name>>n;//输入书号，书名，数量
        mit2=m2.find(index);
        if(mit2!=m2.end())
        {
            v2[mit2->second].setTot(v2[mit2->second].getTot()+n);
            v2[mit2->second].setShengyu(v2[mit2->second].getShengyu()+n);
 
        }
        else
        {
            v2.push_back(Book(name,index,n,n));
            m2.insert(make_pair(index,v2.size()-1));
            m3.insert(make_pair(name,v2.size()-1));
            bookNum++;
        }
    }
 
}
void MangerOp::addStu()
{
    int id;
    string name;
    while(cin>>id&&id!=-1)//输入id 姓名
    {
        cin>>name;
        mit1=m1.find(id);
        if(mit1==m1.end())
        {
            stuNum++;
            v1.push_back(Student(name,id));
            m1.insert(make_pair(id,v1.size()-1));
        }
    }
 
}
void MangerOp::deleteBook()
{
    int index,num;
    cin>>index>>num;
    mit2=m2.find(index);
    int i=mit2->second;
    if(mit2!=m2.end())
    {
        if(num==v2[i].getShengyu()&&num==v2[i].getTot())
        {
            bookNum--;
            v2.erase(v2.begin()+i);
            m2.erase(index);
            m3.erase(v2[i].getName());
        }
        else if(num<=v2[i].getShengyu())
        {
            v2[i].setShengyu(v2[i].getShengyu()-num);
            v2[i].setTot(v2[i].getTot()-num);
        }
    }
 
}
void MangerOp::deleteStu()
{
    int id;
    cin>>id;
    mit1=m1.find(id);
    if(mit1!=m1.end())
    {
        stuNum--;
        m1.erase(id);
        v1.erase(v1.begin()+(mit1->second));
    }
}
void MangerOp::queryBookAllRecord()
{
    int index;
    cin>>index;
    mit2=m2.find(index);
    if(mit2!=m2.end())
    {
        v2[mit2->second].disAllRecord();
    }
}
void MangerOp::queryBookNoback()
{
    int index;
    cin>>index;
    mit2=m2.find(index);
    if(mit2!=m2.end())
    {
        v2[mit2->second].disNobackRecord();
    }
}
void MangerOp::queryStuAll()
{
    int id;
    cin>>id;
    mit1=m1.find(id);
    if(mit1!=m1.end())
    {
        v1[mit1->second].disAllRecord();
    }
}
void MangerOp::queryStuNoback()
{
    int id;
    cin>>id;
    mit1=m1.find(id);
    if(mit1!=m1.end())
    {
        v1[mit1->second].disNobackRecord();
    }
}
 
class StuOp
{
    private:
        Student stu;
        int id;
        Date t1;
        vector <Book> v1;
        vector <Book> ::iterator vit1;
        map <int,int >m1;
        map <int,int >::iterator mit1;//shu hao
 
 
    public:
        StuOp(int ID,Date t):id(ID),t1(t)
        {
            load1();
            load2();
        }
        ~StuOp()
        {
            save1();
            save2();
        }
        void load1();//book
        void load2();//student
        void save1();
        void save2();
 
        void borrow();
        void back();
        void againBorrow();//续借
 
        void disAllRecord();//该生所有记录
        void disNobackRecord();//未还书记录
 
        void queryABook();
        void disAllBook();
 
};
void StuOp::load1()
{
 
    ifstream infile("20171778book.txt",ios::in);
        if(!infile)return ;
    v1.clear();
    Book b;
    int k=0;
    while(infile>>b)
    {
        v1.push_back(b);
        m1.insert(make_pair(b.getIndex(),k));
        k++;
        vector <Record> & vt=b.getRecord();
 
        multimap<bool,int> & m2=b.getM2();
        multimap<int,int>& m1=b.getM1();
        vt.clear();
        m1.clear();m2.clear();m1.clear();
    }
    infile.close();
    cout<<"books load success!"<<endl;
 
}
void StuOp::load2()
{
 
    bool flag=0;
    ifstream infile("20171778stu.txt",ios::in);
        if(!infile)return ;
    Student s;
    while(infile>>s)
    {
 
        if(s.getID()==id)
        {
            stu=s;stu.disBase();
            cout<<"... ...landing success!"<<endl;
            flag=1;
            break;
        }
        vector<Record> & vt=s.getRecord();
        multimap <bool,int> & m2=s.getM2();
        multimap<int,int> & m1=s.getM1();
        vt.clear();
        m1.clear();
        m2.clear();
    }
    if(!flag)cout<<"id wrong!"<<endl;
 
 
 
}
void StuOp::save1()
{
    ofstream outfile("20171778book.txt",ios::out);
        if(!outfile)return ;
    for(int i=0;i<v1.size();++i)
    {
        outfile<<v1[i];
 
    }
    outfile.close();
}
void StuOp::save2()
{
 
    ifstream infile("20171778stu.txt",ios::in);
        if(!infile)return ;
    vector <Student> v3;
    vector <Student>::iterator vit3;
    int k=0;
    Student s;
    while(infile>>s)
    {
        v3.push_back(s);
        k++;
        vector <Record> & vt=s.getRecord();
        multimap <bool,int> & m2=s.getM2();
        multimap<int,int> & m1=s.getM1();
        vt.clear();
        m1.clear();
        m2.clear();
    }
    infile.close();
 
 
    ofstream outfile("20171778stu.txt",ios::out);
        if(!outfile)return ;
    for(int i=0;i<v3.size();++i)
    {
        if(v3[i].getID()==stu.getID())
        {
            outfile<<stu;
        }
        else
        {
            outfile<<v3[i];
        }
 
    }
    outfile.close();
 
 
 
}
void StuOp::disAllBook()
{
    cout<<"disAllBook  ："<<endl;
    for(mit1=m1.begin();mit1!=m1.end();++mit1)
    {
        v1[mit1->second].disBase();
        cout<<endl;
    }
}
void StuOp::queryABook()
{
    int index;
    cin>>index;
    mit1=m1.find(index);
    if(mit1!=m1.end())
        cout<<v1[m1[index]];
}
void StuOp::disAllRecord()
{
    stu.disAllRecord();
}
void StuOp::disNobackRecord()
{
    stu.disNobackRecord();
}
void StuOp::borrow()
{
    int index;
    cin>>index;
    mit1=m1.find(index);
    if(mit1==m1.end())cout<<"book fail!"<<endl;
    else
    {
        Date t2;
        t2=t1;
        t2.setMonth(t1.getMonth()+1);
        if(stu.getNum()<1||v1[m1[index]].getShengyu()<1)cout<<"num fail!"<<endl;
 
        if(stu.queryTLE(t1))cout<<"TlE fail!"<<endl;
        else
        {
 
            Record rr(v1[m1[index]].getName(),index,stu.getName(),stu.getID(),"jieshu",t1,t2,0);
            stu.addRecord(rr);
            v1[m1[index]].addRecord(rr);
 
            v1[mit1->second].setShengyu(v1[m1[index]].getShengyu()-1);
            stu.setNum(stu.getNum()-1);
 
            cout<<"borrow success!"<<endl;
 
        }
    }
 
}
void  StuOp::back()
{
    int index;
    cin>>index;
    mit1=m1.find(index);
    if(mit1!=m1.end())
    {
        Record r(v1[m1[index]].getName(),index,stu.getName(),stu.getID(),"huanshu",t1,t1,1);
        stu.addRecord(r);
        v1[mit1->second].addRecord(r);
 
        stu.setNum(stu.getNum()+1);
        v1[mit1->second].setShengyu(v1[mit1->second].getShengyu()+1);
 
        stu.deleteRecord(index,t1);
        v1[mit1->second].deleteRecord(stu.getID(),t1);
        cout<<"back success!"<<endl;
    }
    else cout<<"query fail!"<<endl;
}
void StuOp::againBorrow()
{
    int index;
    cin>>index;
    mit1=m1.find(index);
    if(mit1!=m1.end())
    {
        Record r(v1[m1[index]].getName(),index,stu.getName(),stu.getID(),"xvjie",t1,t1,1);
        v1[mit1->second].addRecord(r);
        stu.addRecord(r);
        stu.setEndTime(index);
        v1[mit1->second].setEndTime(stu.getID());
        cout<<"againBorrow success!"<<endl;
    }
}
int main()
{
    //MangerOp man;  man.deleteBook();
    //man.deleteStu();
     //   /*
    int id;
    Date t;
    cin>>id>>t;
    StuOp stu(id,t);
    stu.disAllBook();//显示所有书；
    stu.borrow();
 
    //stu.back();
    //stu.againBorrow();
    //*/
    return 0;
}