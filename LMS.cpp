#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

//PASSWORD.H
class Password
{
    string Pass;

public:
    Password()
    {
        
    }
    Password(string Pass)
    {
        this->Pass = Pass;
    }

    void setPassword(string Pass)
    {
        this->Pass = Pass;
    }

    string& setPassword()
    {return Pass;}
    string retPassword()
    {return Pass;}
    bool checkPassword(Password const Orignal);
};

bool Password::checkPassword(Password const Orignal)
{
    if (Orignal.Pass == this->Pass)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string getPass()
{
    string pass;
    char ch;
    int i = 0;
    while (i < 8)
    {
        ch = getch();
        i++;
        if (ch != '\n')
        {
            pass = pass + ch;
            cout << "*";
        }
    }
    return pass;
}

//Date.h
class Date
{
    int DD;
    int MM;
    int YYYY;

public:
    Date()
    {
        struct tm *currentDate;
        time_t rawTime;

        rawTime = time(NULL);
        currentDate = localtime(&rawTime);

        DD = currentDate->tm_mday;
        MM = 1 + currentDate->tm_mon;
        YYYY = 1900 + currentDate->tm_year;
    }
    Date(int DD, int MM, int YYYY)
    {
        this->DD = DD;
        this->MM = MM;
        this->YYYY = YYYY;
    }

    friend ostream &operator<<(ostream &, Date);
    int returnDD()
    {return DD;}
    int returnMM()
    {return MM;}
    int returnYYYY()
    {return YYYY;}
    Date operator+(int D);
};

ostream &operator<<(ostream &out, Date d)
{
    cout << d.DD << "-" << d.MM << "-" << d.YYYY;
    return out;
}

Date Date::operator+(int D)
{
    struct tm *currentDate;
    time_t rawTime;
    Date temp;
    rawTime = time(NULL) + (D*24*60*60);
    currentDate = localtime(&rawTime);

    temp.DD = currentDate->tm_mday;
    temp.MM = 1 + currentDate->tm_mon;
    temp.YYYY = 1900 + currentDate->tm_year;
    return temp;
}

// Member.h

// Record counting functions
int countStudentMembers();
int countFacultyMembers();

enum MemberType
{
    StudentType,
    FacultyType
};

class Member
{
protected:
    string MemberID;
    MemberType Type;
    short NoOfBooksIssued;
    const int maxBookLimit;
    string Name;
    string PhoneNumber;

public:
    Member(int maxLimit) : maxBookLimit(maxLimit)
    {
    }
    virtual void addDetails() = 0;
    virtual void showDetails() = 0;
    bool canIssueBook()
    {
        if (NoOfBooksIssued <= maxBookLimit)
        {
            return true;
        }
        return false;
    }
    void issueBook()
    {
        NoOfBooksIssued++;
    }
    bool hasBooksissued()
    {
        if (NoOfBooksIssued > 0)
        {
            return true;
        }
        return false;
    }
    void returnBook()
    {
        NoOfBooksIssued--;
    }
};

class Student : public Member
{
    int studentMemberCount;

public:
    Student(string Name, string PhoneNumber) : Member(3) // maximum book borrow limit 3
    {
        Type = StudentType;
        MemberID = "ST";
        NoOfBooksIssued = 0;
        this->Name = Name;
        this->PhoneNumber = PhoneNumber;
        this->studentMemberCount = 0;
        MemberID.append(to_string(studentMemberCount));
    }
    Student() : Member(3) // maximum book borrow limit 3
    {
        Type = StudentType;
        MemberID = "ST";
        NoOfBooksIssued = 0;
    }

    int retStudentMemberCount()
    {
        return studentMemberCount;
    }
    string retMemberID()
    {
        return MemberID;
    }
    void addDetails();
    void showDetails();
};

void Student::addDetails()
{
    system("cls");
    cout << "\nEnter the name of the student : ";
    getline(cin, Name);
    cout << "\nEnter the phone number : ";
    getline(cin, PhoneNumber);
    studentMemberCount = countStudentMembers() + 1;
    MemberID.append(to_string(studentMemberCount));
    showDetails();
}

void Student::showDetails()
{
    system("cls");
    cout << "Name         : " << Name << endl;
    cout << "Phone Number : " << PhoneNumber << endl;
    cout << "Member ID    : " << MemberID << endl;
    cout << "Books Issued : " << NoOfBooksIssued << endl;
}

void showStudent()
{
    fstream Show;
    Student F;
    Show.open("StudentList.dat", ios::in | ios::binary);
    if (!Show)
    {
        cout << "\nNo Records available";
        getch();
        return;
    }
    while (Show)
    {
        Show.read((char *)&F, sizeof(F));
        F.showDetails();
        getch();
    }
    Show.close();
}

class Faculty : public Member
{
    int facultyMemberCount;

public:
    Faculty(string Name, string PhoneNumber) : Member(5) // maximum book borrow limit 5
    {
        Type = FacultyType;
        NoOfBooksIssued = 0;
        MemberID = "FC";
        this->Name = Name;
        this->PhoneNumber = PhoneNumber;
        this->facultyMemberCount = 0;
        MemberID.append(to_string(facultyMemberCount));
    }
    Faculty() : Member(5) // maximum book borrow limit 5
    {
        Type = FacultyType;
        NoOfBooksIssued = 0;
        MemberID = "FC";
    }
    int retFacultyMemberCount()
    {
        return facultyMemberCount;
    }
    string retMemberID()
    {
        return MemberID;
    }
    void addDetails();
    void showDetails();
};

void Faculty::addDetails()
{
    system("cls");
    cout << "\nEnter the name of the faculty : ";
    getline(cin, Name);
    cout << "\nEnter the phone number : ";
    getline(cin, PhoneNumber);

    facultyMemberCount = countFacultyMembers() + 1;
    MemberID.append(to_string(facultyMemberCount));
    showDetails();
}

void Faculty::showDetails()
{
    system("cls");
    cout << "Name         : " << Name << endl;
    cout << "Phone Number : " << PhoneNumber << endl;
    cout << "Member ID    : " << MemberID << endl;
    cout << "Books Issued : " << NoOfBooksIssued << endl;
}

void showFaculty()
{
    fstream Show;
    Faculty F;
    Show.open("FacultyList.dat", ios::in | ios::binary);
    if (!Show)
    {
        cout << "\nNo Records available";
        getch();
        return;
    }
    while (Show)
    {
        Show.read((char *)&F, sizeof(F));
        F.showDetails();
        getch();
    }
    Show.close();
}

int countStudentMembers()
{
    fstream lastRecord;
    Student last;
    lastRecord.open("StudentList.dat", ios::in | ios::binary);
    lastRecord.seekg(0, ios::end);
    int temp = lastRecord.tellg() / sizeof(last);
    lastRecord.close();
    return temp;
}

int countFacultyMembers()
{
    fstream lastRecord;
    Faculty last;
    lastRecord.open("FacultyList.dat", ios::in | ios::binary);
    if(!lastRecord)
    {
        return 0;
    }
    lastRecord.seekg(0, ios::end);
    int temp = lastRecord.tellg() / sizeof(last);
    lastRecord.close();
    return temp;
}

//Book.H
//Functions to get count of books
int getLastRecordJournal();
int getLastRecordMagazine();
int getLastRecordStudyBooks();

//Book returning functions


enum BookType
{
    JournalType,
    MagazineType,
    StudyBookType
};

class Book
{
protected:
    string BookID;
    string Name;
    string Author;
    bool Status; //true - available for issue False- issued
    string edition;
    BookType Type;

public:
    virtual void DisplayBookDetails() = 0;
    virtual void setBookDetails() = 0;
    virtual void updateStatus() = 0;
    virtual bool retStatus() = 0;
    //virtual ~Book();
    string retBookID()
    {
        return BookID;
    }
};

class Journal : public Book
{
    int JournalCount;

public:
    Journal()
    {
        Type = JournalType;
        BookID = "JO";
    }
    void setBookDetails();
    void updateStatus();
    void DisplayBookDetails();
    bool retStatus();
    int retJournalCount()
    {
        return JournalCount;
    }
};

void Journal::setBookDetails()
{
    system("cls");
    cout << "\nEnter the book name : ";
    getline(cin, Name);
    cout << "\nEnter the author's name : ";
    getline(cin, Author);
    cout << "\nEnter the book's edition : ";
    getline(cin, edition);

    Status = true;
    JournalCount = getLastRecordJournal() + 1;
    BookID.append(to_string(JournalCount));
    DisplayBookDetails();
    cout << "\n Book added to the records!";
}

void Journal::updateStatus()
{
    if (Status)
    {
        Status = false;
    }
    else
    {
        Status = true;
    }
}

bool Journal::retStatus()
{
    return Status;
}

void Journal::DisplayBookDetails()
{
    system("cls");

    cout << "Name : " << Name << endl;
    cout << "Author : " << Author << endl;
    cout << "Book ID : " << BookID << endl;
    cout << "Edition : " << edition << endl;
    cout << "Book Type : Journal" << endl;
    if (Status)
    {
        cout << "Status : Available" << endl;
    }
    else
    {
        cout << "Status : Issued" << endl;
    }
}

void showJournals()
{
    fstream ShowBook;
    Journal book;
    ShowBook.open("JournalList.dat", ios::in | ios::binary);
    if (!ShowBook)
    {
        cout << "\nNo Books available";
        getch();
        return;
    }
    while (ShowBook)
    {
        ShowBook.read((char *)&book, sizeof(book));
        book.DisplayBookDetails();
        getch();
    }
    ShowBook.close();
}

class Magazine : public Book
{
    int MagazineCount;

public:
    Magazine()
    {
        Type = MagazineType;
        BookID = "MA";
    }
    void setBookDetails();
    void updateStatus();
    void DisplayBookDetails();
    bool retStatus();
    int retMagazineCount()
    {
        return MagazineCount;
    }
};

void Magazine::setBookDetails()
{
    system("cls");
    cout << "\nEnter the book name : ";
    getline(cin, Name);
    cout << "\nEnter the author's name : ";
    getline(cin, Author);
    cout << "\nEnter the book's edition : ";
    getline(cin, edition);

    Status = true;
    MagazineCount = getLastRecordMagazine() + 1;
    BookID.append(to_string(MagazineCount));
    DisplayBookDetails();
    cout << "\n Book added to the records!";
}

void Magazine::updateStatus()
{
    if (Status)
    {
        Status = false;
    }
    else
    {
        Status = true;
    }
}

bool Magazine::retStatus()
{
    return Status;
}

void Magazine::DisplayBookDetails()
{
    system("cls");

    cout << "Name : " << Name << endl;
    cout << "Author : " << Author << endl;
    cout << "Book ID : " << BookID << endl;
    cout << "Edition : " << edition << endl;
    cout << "Book Type : Magazine" << endl;
    if (Status)
    {
        cout << "Status : Available" << endl;
    }
    else
    {
        cout << "Status : Issued" << endl;
    }
}

void showMagazines()
{
    fstream ShowBook;
    Magazine book;
    ShowBook.open("MagazineList.dat", ios::in | ios::binary);
    if (!ShowBook)
    {
        cout << "\nNo Books available";
        getch();
        return;
    }
    while (ShowBook)
    {
        ShowBook.read((char *)&book, sizeof(book));
        book.DisplayBookDetails();
        getch();
    }
    ShowBook.close();
}

class StudyBooks : public Book
{
    int StudyBooksCount;

public:
    StudyBooks()
    {
        Type = StudyBookType;
        BookID = "SB";
        StudyBooksCount++;
    }
    void setBookDetails();
    void updateStatus();
    void DisplayBookDetails();
    bool retStatus();
    int retStudyBooksCount()
    {
        return StudyBooksCount;
    }
};

void StudyBooks::setBookDetails()
{
    system("cls");
    cout << "\nEnter the book name : ";
    getline(cin, Name);
    cout << "\nEnter the author's name : ";
    getline(cin, Author);
    cout << "\nEnter the book's edition : ";
    getline(cin, edition);

    Status = true;
    StudyBooksCount = getLastRecordStudyBooks() + 1;
    BookID.append(to_string(StudyBooksCount));
    DisplayBookDetails();
    cout << "\n Book added to the records!";
}

void StudyBooks::updateStatus()
{
    if (Status)
    {
        Status = false;
    }
    else
    {
        Status = true;
    }
}

bool StudyBooks::retStatus()
{
    return Status;
}

void StudyBooks::DisplayBookDetails()
{
    system("cls");

    cout << "Name : " << Name << endl;
    cout << "Author : " << Author << endl;
    cout << "Book ID : " << BookID << endl;
    cout << "Edition : " << edition << endl;
    cout << "Book Type : Study Books" << endl;
    if (Status)
    {
        cout << "Status : Available" << endl;
    }
    else
    {
        cout << "Status : Issued" << endl;
    }
}

void showStudyBooks()
{
    fstream ShowBook;
    StudyBooks book;
    ShowBook.open("StudyBooksList.dat", ios::in | ios::binary);
    if (!ShowBook)
    {
        cout << "\nNo Books available";
        _getch();
        return;
    }
    while (ShowBook)
    {
        ShowBook.read((char *)&book, sizeof(book));
        book.DisplayBookDetails();
        getch();
    }
    ShowBook.close();
}

int getLastRecordJournal()
{
    fstream lastRecord;
    Journal last;
    lastRecord.open("JournalList.dat", ios::in | ios::binary);
    if (!lastRecord)
    {
        return 0;
    }
    lastRecord.seekg(-sizeof(last), ios::end);
    // lastRecord.read((char *)&last, sizeof(last));
    // int temp = last.retJournalCount();
    lastRecord.seekg(0, ios::end);
    int temp = lastRecord.tellg() / sizeof(last);
    lastRecord.close();
    return temp;
}

int getLastRecordMagazine()
{
    fstream lastRecord;
    Magazine last;
    lastRecord.open("MagazineList.dat", ios::in | ios::binary);
    if (!lastRecord)
    {
        return 0;
    }
    lastRecord.seekg(-sizeof(last), ios::end);
    // lastRecord.read((char *)&last, sizeof(last));
    // int temp =last.retMagazineCount();
    lastRecord.seekg(0, ios::end);
    int temp = lastRecord.tellg() / sizeof(last);
    lastRecord.close();
    return temp;
}

int getLastRecordStudyBooks()
{
    fstream lastRecord;
    StudyBooks last;
    lastRecord.open("StudyBooksList.dat", ios::in | ios::binary);
    if (!lastRecord)
    {
        return 0;
    }
    lastRecord.seekg(-sizeof(last), ios::end);
    // lastRecord.read((char *)&last, sizeof(last));
    // int temp = last.retStudyBooksCount();
    lastRecord.seekg(0, ios::end);
    int temp = lastRecord.tellg() / sizeof(last);
    lastRecord.close();
    return temp;
}


// Bill.h

class Transaction
{
    string TransID;
    string MemberID;
    string BookID;
    Date dateOfIssue;
    Date dueDate;


    public:
    Transaction(string MemberID, string BookID, int days)
    {
        this->MemberID = MemberID;
        this->BookID = BookID;
        dueDate = dateOfIssue + days;
        TransID.push_back(MemberID[0]);
        TransID.push_back(BookID[0]);
        TransID.append(to_string(dateOfIssue.returnDD()));
    }

    void generateTransaction();

};

void Transaction:: generateTransaction()
{
    system("cls");
    cout << "\nTransaction ID: " << TransID << endl;
    cout << "Book ID: " << BookID << endl;
    cout << "Member ID: " << MemberID << endl;
    cout << "Date of issue: " << dateOfIssue << endl;
    cout << "Due Date: " << dueDate << endl;
    _getch();
    
}


//Library.cpp
bool checkBook(string *);

class Librarian
{
    string Name;
    Password Pass;

public:
    Librarian()
    {
    }
    string &setName()
    {
        return Name;
    }
    void setPassword(string password)
    {
        Pass.setPassword() = password;
    }
    Password retPass()
    {
        return Pass;
    }
    string retName()
    {
        return Name;
    }

    //Book related functions

    void showBook();
    void addBook();
    void issueBook();
    void returnBook();

    //Member related functions

    void addFaculty();
    void addFaculty(string, string); // Overloaded function for intializing files
    void addStudent();
    void addStudent(string, string); // Overloaded function for intializing files
};

void AddAdmin(string Name, string Password)
{
    fstream loginInfo;
    Librarian newAdmin;
    newAdmin.setName() = Name;
    newAdmin.setPassword(Password);
    loginInfo.open("loginInfo.dat", ios::app | ios::binary);
    loginInfo.write((char *)&newAdmin, sizeof(newAdmin));
    loginInfo.close();
}

void Librarian::addFaculty()
{
    Faculty newFaculty;
    fstream addMember;
    cin.ignore();
    newFaculty.addDetails();
    addMember.open("FacultyList.dat", ios::app | ios::binary);
    addMember.write((char *)&newFaculty, sizeof(Faculty));
    addMember.close();
    getch();
}

void Librarian::addFaculty(string Name, string Number) // Overloaded function for intializing files
{
    Faculty newFaculty(Name, Number);
    fstream addMember;
    addMember.open("FacultyList.dat", ios::app | ios::binary);
    addMember.write((char *)&newFaculty, sizeof(newFaculty));
    addMember.close();
}

void Librarian::addStudent()
{
    Student newStudent;
    fstream addMember;
    addMember.open("StudentList.dat", ios::app | ios::binary);

    if (!addMember)
    {
        cout << "\nError in opening the record!";
    }
    cin.ignore();
    newStudent.addDetails();
    addMember.write((char *)&newStudent, sizeof(newStudent));
    addMember.close();
    getch();
}

void Librarian::addStudent(string Name, string Number) // Overloaded function for intializing files
{
    Student newStudent(Name, Number);
    fstream addMember;
    addMember.open("StudentList.dat", ios::app | ios::binary);

    if (!addMember)
    {
        cout << "\nError in opening the record!";
    }
    addMember.write((char *)&newStudent, sizeof(newStudent));
    addMember.close();
}

void Librarian::addBook()
{
    int Type;
    fstream AddBook;
    //Book *newBook;
    Journal J;
    Magazine M;
    StudyBooks S;
    system("cls");
    cout << "\nEnter the type of book 0-Jounral 1-Magazine 2-Study Book: ";
    cin >> Type;
    cin.ignore();
    switch (Type)
    {
    case JournalType:
        //newBook = new Journal;
        J.setBookDetails();
        AddBook.open("JournalList.dat", ios::app | ios::binary);
        AddBook.write((char *)&J, sizeof(Journal));
        AddBook.close();
        break;
    case MagazineType:
        //newBook = new Magazine;
        M.setBookDetails();
        AddBook.open("MagazineList.dat", ios::app | ios::binary);
        AddBook.write((char *)&M, sizeof(Magazine));
        AddBook.close();

        break;
    case StudyBookType:
        //newBook = new StudyBooks;
        S.setBookDetails();
        AddBook.open("StudyBooksList.dat", ios::app | ios::binary);
        AddBook.write((char *)&S, sizeof(StudyBooks));
        AddBook.close();

        break;
    default:
        cout << "\nNot valid!";
    }
    getch();
    //delete newBook;
    return;
}

void Librarian::showBook()
{
    int Type;
    system("cls");
    cout << "\nEnter the type of book 0-Jounral 1-Magazine 2-Study Book: ";
    cin >> Type;

    switch (Type)
    {
    case JournalType:
        showJournals();
        break;
    case MagazineType:
        // book = new Magazine;
        // ShowBook.open("MagazineList.dat", ios::in);
        // if (!ShowBook)
        // {
        //     cout << "\nNo Books available";
        //     delete book;
        //     return;
        // }
        // while (ShowBook.read((char *)book, sizeof(Magazine)))
        // {
        //     //system("cls");
        //     book->DisplayBookDetails();
        //     _getch();
        // }
        // ShowBook.close();
        showMagazines();
        break;
    case StudyBookType:
        // book = new StudyBooks;
        // ShowBook.open("StudyBooksList.dat", ios::in);
        // if (!ShowBook)
        // {
        //     cout << "\nNo Books available";
        //     delete book;
        //     return;
        // }
        // while (ShowBook.read((char *)book, sizeof(StudyBooks)))
        // {
        //     //system("cls");
        //     book->DisplayBookDetails();
        //     _getch();
        // }
        // ShowBook.close();
        showStudyBooks();
        break;
    default:
        cout << "\nEnter a valid option!";
        break;
    }
    //delete book;
    return;
}

void Librarian::issueBook()
{
    fstream MemberFile;
    string MID, BID;
    bool flag = false;
    system("cls");
    cout << "\nEnter the Member ID: ";
    cin >> MID;
    if(MID[0] == 'S')
    {
        Student S;
        int pos = 0;
        MemberFile.open("StudentList.dat", ios::in| ios::ate | ios::binary);
        if(!MemberFile)
        {
            cout <<"\nNo Student Members Found!";
            return;
        }
        MemberFile.seekg(0, ios::beg);
        while(!MemberFile.eof())
        {
            pos = MemberFile.tellg();
            MemberFile.read((char *)&S, sizeof(S));
            if(S.retMemberID() == MID && S.canIssueBook())
            {
                flag = true;
                if(!checkBook(&BID))
                {
                    cout << "\nCan't issue the book!";
                    break;
                }
                S.issueBook();
                MemberFile.seekp(pos);
                MemberFile.write((char *)&S, sizeof(S));
                MemberFile.close();
                Transaction T(MID, BID, 7);
                T.generateTransaction();
                return;
            }

        }

        if(!flag)
        {
            cout <<"\nCan't Issue Book!";
        }

    }
    else if(MID[0] == 'F')
    {
        Faculty S;
        int pos = 0;
        MemberFile.open("FacultyList.dat", ios::in| ios::ate | ios::binary);
        if(!MemberFile)
        {
            cout <<"\nNo Faculty Members Found!";
            return;
        }
        MemberFile.seekg(0, ios::beg);
        while(!MemberFile.eof())
        {
            pos = MemberFile.tellp();
            MemberFile.read((char *)&S, sizeof(S));
            if(S.retMemberID() == MID && S.canIssueBook())
            {
                flag = true;
                if(!checkBook(&BID))
                {
                    cout << "\nCan't issue the book (1)!";
                    break;
                }
                S.issueBook();
                MemberFile.seekp(pos);
                MemberFile.write((char *)&S, sizeof(S));
                MemberFile.close();
                Transaction T(MID, BID, 14);
                T.generateTransaction();
                
                return;
            }

        }

        if(!flag)
        {
            cout <<"\nCan't Issue Book (2)!";
        }

    }
    else
    {
        cout <<"\nNo Such Member!";
    }
    getch();
}

bool checkBook(string *BID)
{
    system("cls");
    fstream BookFile;
    string BookID;
    int pos = 0;
    cout << "\nEnter the Book ID: ";
    cin >> BookID;
    if( BookID[0] == 'J')
    {
        Journal J;
        BookFile.open("JournalList.dat", ios::in|ios::ate|ios::binary);
        if(!BookFile)
        {
            cout << "\nNo Journals Found!";
            return false;
        }
        BookFile.seekg(0,ios::beg);
        while(!BookFile.eof())
        {
            pos = BookFile.tellg();
            BookFile.read((char *)&J, sizeof(J));
            if(J.retBookID() == BookID && J.retStatus())
            {
                *BID = BookID;
                J.updateStatus();
                BookFile.seekp(pos);
                BookFile.write((char *)&J, sizeof(J));
                BookFile.close();
                return true;
            }
        }
    }
    else if( BookID[0] == 'M')
    {
        Magazine J;
        BookFile.open("MagazineList.dat", ios::in|ios::ate|ios::binary);
        if(!BookFile)
        {
            cout << "\nNo Magazines Found!";
            return false;
        }
        BookFile.seekg(0,ios::beg);
        while(!BookFile.eof())
        {
            pos = BookFile.tellg();
            BookFile.read((char *)&J, sizeof(J));
            if(J.retBookID() == BookID && J.retStatus())
            {
                *BID = BookID;
                J.updateStatus();
                BookFile.seekp(pos);
                BookFile.write((char *)&J, sizeof(J));
                BookFile.close();
                return true;
            }
        }
    }
    else if( BookID[0] == 'S')
    {
        StudyBooks J;
        BookFile.open("StudyBooksList.dat", ios::in|ios::ate|ios::binary);
        if(!BookFile)
        {
            cout << "\nNo Study Book Found!";
            return false;
        }
        BookFile.seekg(0,ios::beg);
        while(!BookFile.eof())
        {
            pos = BookFile.tellg();
            BookFile.read((char *)&J, sizeof(J));
            if(J.retBookID() == BookID && J.retStatus())
            {
                *BID = BookID;
                J.updateStatus();
                BookFile.seekp(pos);
                BookFile.write((char *)&J, sizeof(J));
                BookFile.close();
                return true;
            }
        }
    }
    return false;
}

void Librarian::returnBook()
{

}

//Main.cpp

//Functions

void BookMenu(Librarian User);
void MemberMenu(Librarian User);
void AddLibrarian();
void LibrarianMenu(Librarian User);
void LoginPage();
void Login();


int main()
{
    //use following for intializing files
    //AddAdmin("Admin007", "Admin007");
    Login();
    // Librarian user;
    // user.issueBook();
    // user.addFaculty();
    // user.addFaculty();
    // user.addFaculty();
    // showFaculty();
    return 0;
}

//Funtion definations

void Login()
{
    
    char ch;
    do
    {
        system("cls");
        cout << "\t\t\t\t Library Management Portal" << endl;
        cout << "1. Login" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case '1':
            LoginPage();
            break;
        case '2':
            exit(0);
            break;
        default:
            cout << "\nEnter a valid choice !" << endl;
        }
    } while (ch != '2');
}

void LoginPage()
{
    system("cls");

    fstream LoginData;
    LoginData.open("loginInfo.dat", ios::in | ios::binary);
    Librarian check, validate;
    int flag = 0;
    cout << "\nEnter Username : ";
    cin >> check.setName();

    if (!LoginData)
    {
        exit(0);
    }
    while (LoginData.read((char *)&validate, sizeof(validate)))
    {
        //LoginData.read((char *)&validate, sizeof(validate));
        if (validate.retName() == check.retName())
        {
            flag = 1;
            string temp;
            cout << "\nEnter Password : ";
            temp = getPass();
            check.setPassword(temp);
            if (check.retPass().checkPassword(validate.retPass()))
            {
                LibrarianMenu(validate);
                return;
            }
            else
            {
                cout << "\nWrong Password! \nPress any key to continue";
                _getch();
            }
        }
    }
    if (flag == 0)
        cout << "\nNo user Found!";
    LoginData.close();
    _getch();
}

void LibrarianMenu(Librarian User)
{
    char userChoice;
    do
    {
        system("cls");
        cout << "\t\t\t Main Menu" << endl;
        cout << "1. Book Menu" << endl;
        cout << "2. Member Menu" << endl;
        cout << "3. Add Librarian" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice :";
        cin >> userChoice;

        switch (userChoice)
        {
        case '1':
            BookMenu(User);
            break;
        case '2':
            MemberMenu(User);
            break;
        case '3':
            AddLibrarian();
            break;
        case '4':
            return;
            break;
        default:
            cout << "\nEnter a valid choice";
        }

    } while (userChoice != '4');
}

void BookMenu(Librarian User)
{
    char userChoice;
    do
    {
        system("cls");
        cout << "\t\t\t Book Menu" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Show Book" << endl;
        cout << "3. Issue Book" << endl;
        // cout << "4. Return Book" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice :";
        cin >> userChoice;

        switch (userChoice)
        {
        case '1':
            User.addBook();
            break;
        case '2':
            User.showBook();
            break;
        case '3':
            User.issueBook();
            break;
        // case '4':
        //     User.returnBook();
        //     break;
        case '5':
            return;
            break;
        default:
            cout << "\nEnter a valid choice";
        }

    } while (userChoice != '5');
}

void MemberMenu(Librarian User)
{
    char userChoice;
    do
    {
        system("cls");
        cout << "\t\t\t Member Menu" << endl;
        cout << "1. Add Faculty" << endl;
        cout << "2. Add Student" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice :";
        cin >> userChoice;

        switch (userChoice)
        {
        case '1':
            User.addFaculty();
            break;
        case '2':
            User.addStudent();
            break;
        case '3':
            return;
            break;
        default:
            cout << "\nEnter a valid choice";
        }

    } while (userChoice != '3');
}

void AddLibrarian()
{
    system("cls");
    string UID, Pass;
    cout << "\nEnter User ID (no space/special character): ";
    cin >> UID;
    cout << "\nEnter Password (8 characters): ";
    cin >> Pass;
    AddAdmin(UID, Pass);
}
