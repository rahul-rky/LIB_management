/*
    Dbms

    Books
    id -- Bookname -- NofCopies_Available.
    search : By book name

    BookDetails
    Issused Table

    Book_id Book_name strudent name 
    student details

    Fine calculation ..!
    Nnumber of books issused limit check. 

  ________________________________________________________________________

  -- for initial input in the database use file input Output as in CP.

  -- Use g++ fileName.cpp -l sqlite3 
  ________________________________________________________________________

*/

#include <bits/stdc++.h> 
#include <string> 
#include <sqlite3.h>
using namespace std;


/*
    DataBase initialization and filling initial deatils
    of Books and Student table in book.db named DataBase.
*/
class Create_DB{
  public:  
  
  /* Function to create database tabels */
  
    void Create_Table_init()
    {
      
        sqlite3* DB; 
        int exit = 0; 
        exit = sqlite3_open("book.db", &DB); 
        char* messaggeError;
        string sql="DROP TABLE BOOKS";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 
        sql="DROP TABLE BOOKS_ISSUED";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 
        sql="DROP TABLE STUDENT";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 
     //exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 

         sql = "CREATE TABLE BOOKS("
                          "ID          TEXT   PRIMARY KEY       NOT NULL, "
                          "BOOK_NAME           TEXT             NOT NULL, "
                          "AVAILABLE_COPIES    INT              NOT NULL )"; 
        
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 

        if (exit != SQLITE_OK) { 
            cerr << "Error Create Table" << std::endl; 
            sqlite3_free(messaggeError); 
        } 
        else{
            cout << "BOOKS Table created Successfully" << std::endl; 
        }
        sql = "CREATE TABLE BOOKS_ISSUED("
                "ID         TEXT       NOT NULL, "
                "BOOK_NAME        TEXT            NOT NULL, "
                "DATE_OF_ISSUE    TEXT            NOT NULL, "
                "STUDENT_NAME     TEXT            NOT NULL, "
                "STUDENT_ID       TEXT    NOT NULL )"; 
        int val = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

      if(val == SQLITE_OK){
          cout<<"BOOKS_ISSUED Table created"<<endl;
      }

      sql = "CREATE TABLE STUDENT("
              "ENROLLMENT_NUMBER  TEXT  PRIMARY KEY     NOT NULL, "
              "STUDENT_NAME         TEXT            NOT NULL, "
              "BRANCH         TEXT            NOT NULL, "
              "ADDRESS        TEXT               ,"
              "CONTACT_NUMBER     INT                )"; 

      val = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
      if(val == SQLITE_OK)
          cout<<"STUDENT Table created"<<endl;

      sql = "CREATE TABLE ADMIN("
                       "NAME            TEXT             NOT NULL, "
                       "USER_ID         TEXT             NOT NULL, "
                       "PASSWORD        TEXT             NOT NULL )"; 

      sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
      sqlite3_close(DB);
    }
  
  
    /* Function to insert data in table*/
    void Insert_DB_data()
    {
        sqlite3* DB; 
        int exit = 0; 
        exit = sqlite3_open("book.db", &DB); 
        char* messaggeError;
        string Books_Data("INSERT INTO BOOKS VALUES('iiitnLib01', 'War and Peace', 3);"
               "INSERT INTO BOOKS VALUES('iiitnLib02', 'Anna Karenina', 4);"

               "INSERT INTO BOOKS VALUES('iiitnLib03', 'The Great Gatsby', 4);"
               "INSERT INTO BOOKS VALUES('iiitnLib04', 'Turbulence And Triumph The Modi Years', 4);"
               "INSERT INTO BOOKS VALUES('iiitnLib05', 'Obama-The Call of History', 5);"
               "INSERT INTO BOOKS VALUES('iiitnLib06', 'Kashmiris Untold Story: Declassification', 8);"
               "INSERT INTO BOOKS VALUES('iiitnLib07', 'Savarkar: Echoes from a Forgotten Past', 1);"
               "INSERT INTO BOOKS VALUES('iiitnLib08', 'Sridevi: Girl Women Superstar', 0);"
               "INSERT INTO BOOKS VALUES('iiitnLib09', 'I Am Malala', 3);"
               "INSERT INTO BOOKS VALUES('iiitnLib10', 'Think and grow rich', 2);");
  
        exit = sqlite3_exec(DB, Books_Data.c_str(), NULL, 0, &messaggeError);

        string Issue_Data("INSERT INTO BOOKS_ISSUED VALUES('iiitnLib01', 'War and Peace','23:11:2020',  'Nagendra Patel', 'BT18CSE010');"
                  "INSERT INTO BOOKS_ISSUED VALUES('iiitnLib02', 'Anna Karenina','01:12:2020', 'Akash kumar', 'BT18CSE036');"
                  "INSERT INTO BOOKS_ISSUED VALUES('iiitnLib03', 'The Great Gatsby','19:11:2020', 'Ashwin Andey', 'BT18CSE005');"
                  );
  
      exit = sqlite3_exec(DB, Issue_Data.c_str(), NULL, 0, &messaggeError);

      string Student_data("INSERT INTO STUDENT VALUES('BT18CSE010', 'Nagendra Patel', 'CSE', 'bgddasgds','64546');"
                  "INSERT INTO STUDENT VALUES('BT18CSE036', 'Akash kumar','CSE','fbdh','45');"
                  "INSERT INTO STUDENT VALUES('BT18CSE040', 'Priya Singh','CSE','fbdh','45');"
                  "INSERT INTO STUDENT VALUES('BT18CSE005', 'Ashwin Andey','CSE','ajdba','7464');"
                );
      exit = sqlite3_exec(DB, Student_data.c_str(), NULL, 0, &messaggeError);
      if(exit == SQLITE_OK)
          cout<<"STUDENT data inserted"<<endl;
      else
        cout<<"Error"<<endl;
      
      sqlite3_close(DB);
    }    
  
};
/* 
   These CallBack Functions Help in Fetching the Results from the DataBase.  
*/
static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/* 
    -- For Multiple row value to return Use some kind of container if Required for 
    new callback Function.
*/

int RetModValue = 0;
static int Modcallback(void* data, int argc, char** argv, char** azColName) 
{ 
    for (int i = 0; i < argc; i++) {
       RetModValue = stoi(argv[i]);
    } 
   
    return -1; 
} 

string RetModValue1;
static int Mod1callback(void* data, int argc, char** argv, char** azColName) 
{ 
    for (int i = 0; i < argc; i++) {
       RetModValue1 = argv[i];
       
       // cout<<"Im going to return RetModValue: "<<RetModValue1<<endl;
    } 
   
    return -1; 
} 

int Show_var=0;

static int Show_callback(void *data, int argc, char **argv, char **azColName){
    int i;
    vector<string>v;
    vector<string>col;
    if(Show_var==0)
    {
        size_t fieldWidth = 10;
        cout<< setw(fieldWidth);
    }
    for(i = 0; i<argc; i++) {
        if(Show_var == 0)
        {
            size_t fieldWidth = 40;
            cout<< azColName[i];
            if(i!=argc-1)
                cout<< setw(fieldWidth);
        }
        v.push_back(argv[i]);
    }
    cout<<endl;
    cout<<endl;
    Show_var++;
    for(i = 0; i<argc; i++)
    {
        size_t fieldWidth = 40;
        cout<<v[i];
        if(i!=argc-1)
            cout<<setw(fieldWidth);
        
    }
    printf("\n");
    return 0;
}

class Admin {

private:
    string Name;
    string User_ID;
    string Password;

    bool validate_Password()
    {
        bool flag1, flag2, flag3, flag4;
        flag1 = flag2 = flag3 = flag4 = false;

        set<char> speacialChar, Capital, Small, integer;
        for(int i=0;i<256;i++)
        {
            if((i>= 65 && i<= 90))
                Capital.insert(i);
            else if((i >= 97 && i<= 122))
                Small.insert(i);
            else if((i >= 48 && i <= 58))
                integer.insert(i);
            else
                speacialChar.insert(i);

        }
        for(int i=0;Password[i];i++)
        {
            if(speacialChar.count(Password[i]))
                flag1 = true;
            else if(integer.count(Password[i]))
                flag2 = true;
            else if(Capital.count(Password[i]))
                flag3 = true;
            else 
                flag4 = true;
        }
        if(flag1 && flag2 && flag3 && flag4 && Password.length() >= 6)
            return true;
        return false;
    }

    void insertUser()
    {
        sqlite3* DB;  
        sqlite3_open("book.db", &DB);
        string query = "INSERT INTO ADMIN VALUES('"+Name+"', '"+User_ID+"', '"+Password+"');";
        sqlite3_exec(DB, query.c_str(), callback  , NULL, NULL);
        sqlite3_close(DB);
    }

public:

    void setDetails()
    {
        cout<<"Enter Name :: ";
        getline(cin,Name);
        getline(cin,Name);
        cout<<"Enter User_ID :: ";
        cin>>User_ID;

        while(1)
        {
            cout<<"************** NOTE :: Your Password should consist Lower, Upper, Number and specialcharactor ******"<<endl;
            cout<<"Enter Password :: ";
            cin>>Password;
            string temp; cout<<"Re-Enter password :: ";
            cin>>temp;
            if(Password == temp){
                if(validate_Password()){
                    insertUser();
                    cout<<"Registration Successful "<<endl;
                    break;
                }
                else
                    cout<<"Weak password"<<endl;
            }
            else
            {
                cout<<"Password Didn't Matches *** OOOPS"<<endl;
            }
            cout<<endl<<endl;
        }
    }
};

bool Is_User_Logged_In=false;
bool loginAdmin(string User_ID, string Password)
{
    sqlite3* DB;  
    sqlite3_open("book.db", &DB);
    string query ="select PASSWORD from ADMIN where USER_ID = '"+User_ID+"' ;";
    sqlite3_exec(DB, query.c_str(), Mod1callback  , NULL, NULL);
    if(RetModValue1 == Password)
    {
        cout<<"Do the Stuff :: "<<endl;
        Is_User_Logged_In = true;
        return true;
    }
    else
    {
        cout<<"***** Wrong Credential ******"<<endl;
        return false;
    }

    sqlite3_close(DB);
    return false;
}



class LibraryBook{
private:
    string BookId;
    string BookName;
    string Author;
    string Genre;
    float price;

public:

    void BookDetail()
    {
        // returns the name + author + Genere of Book.
    }    // Think few more Methods..!
};

class Student {
private:
    string Id,Name;
    string ContactNumber;
    string Address;

public:

    void getDetails()
    {
        string Branch = Id.substr(3,6);
        // Give the deatail of student as name + branch + contactNumber.
    }
};


class _Date
{
public:
    vector<int> date;

public:

    vector<int> getDate()
    {   
        time_t now = time(0);
        tm *ltm = localtime(&now);
        vector<int> day(3);
        day[2] = (1900 + ltm->tm_year);
        day[1] = (1 + ltm->tm_mon);
        day[0] = (ltm->tm_mday);
        return day;
    }
    int getDateDifference()
    {
        vector<int> presentDate = getDate();
        int ans = 0, span[3] = {1,30,365};
        for(int i=0;i<3;i++)
        {
            int Reqd = 0;
            if(i==0)
                Reqd = 30;
            else if(i==1)
                Reqd = 365;

            if(presentDate[i] - date[i] >= 0){
                ans += span[i]*(presentDate[i] - date[i]);
            }
            else
            {
                ans = ans + span[i]*(presentDate[i] - date[i] + Reqd);
                presentDate[i+1] -= 1;
            }
        }
        return ans;
    }
    void show_Date(){
        cout<<date[0]<<" : "<<date[1]<<" : "<<date[2]<<endl;
    }
};

/* 
    -- Convert the string date to vector day.
    -- It is for Calculation Purpose
*/

vector<int> stringToDate(string day)
{
    vector<int> v;
    string temp;
    for(int i=0;day[i];i++)
    {
        if(day[i] == ':'){
            v.push_back(stoi(temp));
            temp.clear();
        }
        else
            temp.push_back(day[i]);
    } 
    v.push_back(stoi(temp));
    return v;
}

/* 
    --It Returns the date vector to string,
    --This string is same as in our database Table
*/

string dateToString(vector<int> v)
{
    string temp = "";
    temp += to_string(v[0]);
    temp.push_back(':');
    temp += to_string(v[1]);
    temp.push_back(':');
    temp += to_string(v[2]);
    return temp;
}

// Inherits both libBook and student Think about this..! 
class Transaction {
private:

public:

    // -- Look into issused table and calculate the  Appropriate fine.
    bool Verify_Student(string EN)
    {
        sqlite3* DB;
        int exit = sqlite3_open("book.db", &DB);
        string query = "select count(ENROLLMENT_NUMBER) from STUDENT where ENROLLMENT_NUMBER = '"+EN+"';";
        sqlite3_exec(DB, query.c_str(), Modcallback, NULL, NULL);  
        sqlite3_close(DB);
        //cout<<"Im the returned value of search book: "<<RetModValue<<endl;
        return RetModValue;

    }
    void Issue_Book_To(string Student_Id,string Req_Book)
    {
      
        sqlite3* DB;  
        char* messaggeError;
        int exit = sqlite3_open("book.db", &DB);
        string query = "select STUDENT_NAME from STUDENT where ENROLLMENT_NUMBER = '"+Student_Id+"';";
        sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
        sqlite3_exec(DB, query.c_str(), Mod1callback, 0, &messaggeError);
        string Req_Student_name = RetModValue1;

        query = "select ID from BOOKS where BOOK_NAME = '"+Req_Book+"';";
        sqlite3_exec(DB, query.c_str(), Mod1callback, NULL, NULL);
        string Req_Book_Id = RetModValue1;

        _Date d;
        d.date = d.getDate();
        string Req_date = dateToString(d.date);
        query="INSERT INTO BOOKS_ISSUED VALUES('"+Req_Book_Id+"', '"+Req_Book+"', '"+Req_date+"' , '"+Req_Student_name+"', '"+Student_Id+"');";
        sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);  
        sqlite3_close(DB);

        cout<<"Book issued to :"<< Student_Id<<endl;
    }

    void Check_Limit(string Req_Id)
    {
        sqlite3* DB;  
        int exit = sqlite3_open("book.db", &DB);
        string query = "select count(STUDENT_ID) from BOOKS_ISSUED where STUDENT_ID = '"+Req_Id+"';";
        sqlite3_exec(DB, query.c_str(), Modcallback, NULL, NULL);  
        sqlite3_close(DB);
        cout<<Req_Id<<" has "<<RetModValue<<" books issued "<<endl;
    }

    void show_Db(string TN)
    {
        sqlite3* DB;  
        int exit = sqlite3_open("book.db", &DB);
        string query = "SELECT * from '"+TN+"';";
        sqlite3_exec(DB, query.c_str(), Show_callback  , NULL, NULL);
        sqlite3_close(DB);
    }

    void Update_No_Of_Copy(int val,string Req_Book)
    {
        sqlite3* DB;  
    //val=10;
        string str = to_string(val);
    
        int exit = sqlite3_open("book.db", &DB);
        string query = "UPDATE BOOKS SET AVAILABLE_COPIES = " + str + "  where BOOK_NAME = '"+Req_Book+"';";
    
        //cout<<query<<endl;
        //cout<<"Im calling from update: "<<endl;
        sqlite3_exec(DB, query.c_str(), callback , NULL, NULL);
    
        sqlite3_close(DB);

    }


    int Is_Avilable_DB(string Req_Book){
      
       sqlite3* DB;  
        int exit = sqlite3_open("book.db", &DB);
      //cout<<"J"<<endl;
        string query = "select AVAILABLE_COPIES from BOOKS where BOOK_NAME = '"+Req_Book+"';";
        sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
        sqlite3_exec(DB, query.c_str(), Modcallback, NULL, NULL);
        // cout<<val<<endl;
        //cout<<"Im in is_aviable: "<<RetModValue<<endl; 
        sqlite3_close(DB);
        return RetModValue;
    }

    bool Search_Book_DB(string Req_Book)
    {
         sqlite3* DB;
         int exit = sqlite3_open("book.db", &DB);
         // string query = "INSERT INTO "+table name+" ("+field1+") values ('"+myfinalstring+"')";
         string query = "select count(BOOK_NAME) from BOOKS where BOOK_NAME = '"+Req_Book+"';";
         sqlite3_exec(DB, query.c_str(), Modcallback, NULL, NULL);  
         sqlite3_close(DB);
         //cout<<"Im the returned value of search book: "<<RetModValue<<endl;
         return RetModValue;
    }

    void getIssuedBook(string Req_Book,string EN){
        cout<<endl;
        //cout<<Req_Book<<" book is ";
        if(Search_Book_DB(Req_Book))
        {
          cout<<"Okay ::"<<Req_Book<<" book is available"<<endl;
          if(Is_Avilable_DB(Req_Book) > 0)
          {
            int Book_count=Is_Avilable_DB(Req_Book);
            //cout<<"and can be issued"<<endl;
            string Issue_to=EN;
            Check_Limit(Issue_to);
            int Limit = RetModValue;
            if(Limit < 3)
            {
              
              Issue_Book_To(Issue_to,Req_Book);
              Update_No_Of_Copy(Book_count - 1,Req_Book);
            }
            else
            {
              cout<<"You already have 3 book issued"<<endl;
            }
            
          }
          else
            cout<<"but can't issue"<<endl;
        }
        else
          cout<<"Not in the lib"<<endl;
         
    } 
    int calculateFine(string dayOfIssue)
    {
        /*
            _Date d1,d2;
                d1.date.resize(3);
                d1.date[0] = 23, d1.date[1] = 11, d1.date[2] = 2020;
                d2.date = d2.getDate();
                d1.show_Date();
                d2.show_Date();

                cout<<d1.getDateDifference()<<endl;
        */

        _Date d1;
        d1.date = stringToDate(dayOfIssue);
        d1.show_Date();

        return (d1.getDateDifference() - 7) > 0 ? d1.getDateDifference() - 7 : 0;
    }


    void Add_Book(string BN)
    {
        if(Search_Book_DB(BN))
        {
            int Book_count=Is_Avilable_DB(BN);
            Update_No_Of_Copy(Book_count+1,BN);
        }
        else
        {
            sqlite3* DB;  
            int exit = sqlite3_open("book.db", &DB);
             char* messaggeError;
            string query = "SELECT count(*) from BOOKS;";
            sqlite3_exec(DB, query.c_str(), Modcallback, NULL, NULL); 

            string Req_Book_Id = "iiitnLib" + to_string(RetModValue+1);
            
            string No_of_copy = to_string(1);
            query="INSERT INTO BOOKS VALUES('"+Req_Book_Id+"', '"+BN+"', " + No_of_copy + ");";
            
            sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);  
            sqlite3_close(DB);
        }

        cout<<"******BOOK ADDED SUCCESSFUL*****"<<endl;
    }

    void returnBook(string enRollmentNumber, string bookName)
    {
        string query = "select DATE_OF_ISSUE from BOOKS_ISSUED where STUDENT_ID = '"+enRollmentNumber+"' and BOOK_NAME = '"+bookName+"';"; 
        sqlite3* DB;
        int exit = sqlite3_open("book.db", &DB);

        sqlite3_exec(DB, query.c_str(), Mod1callback, NULL, NULL);
        string dayOfIssue = RetModValue1;
        // cout<<dayOfIssue<<endl;
        int fine = calculateFine(dayOfIssue);

        cout<<"Your fine for the Book is: "<<fine<<endl;

        query = "DELETE from BOOKS_ISSUED where STUDENT_ID = '"+enRollmentNumber+"' and BOOK_NAME = '"+bookName+"'; ";

           /* Execute SQL statement */
        sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
        cout<<"You have successfully Returned the BOOK"<<endl;

        sqlite3_close(DB);
    }  
}; 



int main(int argc, char** argv) 
{ 
   //  /* Creating Database */
  
    // Create_DB table;
    // table.Create_Table_init();
    
    // // /* Fetching the data */
    // sqlite3* DB;
    // int exit = sqlite3_open("book.db", &DB);
  
    //  // Insertion in Table  
    //table.Insert_DB_data();
  
    // sqlite3_close(DB);
    
    
    // Transaction T;
    // sqlite3_exec(DB, query.c_str(), callback  , NULL, NULL);


    sqlite3* DB;  
    int exit = sqlite3_open("book.db", &DB);
    system("clear");
    cout<<"\t\t\t\t\t\t\t\t\t\t WELCOME TO IIITN LIBRARY"<<endl;
    cout<<"\t\tWhat do you want"<<endl;
    cout<<endl;
    cout<<"1. ISSUE BOOK"<<endl;
    cout<<"2. SHOW TABLE DETAIL"<<endl;
    cout<<"3. CHECK ISSUED BOOK"<<endl;
    cout<<"4. Return Book"<<endl;
    cout<<"5. ADD BOOK IN LIBERARY"<<endl;
    cout<<"6. Admin"<<endl;
    cout<<"7. Exit"<<endl;
    
    Transaction T;
    while(1)
    {
        int x;
        cin>>x;
        cout<<endl;
        cout<<endl;
        int flag=0;
        switch(x)
        {
            
            case 1:
            {  
                cout << "Choice is ISSUE BOOK"<<endl;
                cout<<"ENTER YOUR ENROLLMENT NUMBER"<<endl;
                string EN;
                cin>>EN;
                if(!T.Verify_Student(EN))
                {
                    cout<<"STUDENT IS NOT ENROLLED IN THE COLLEGE"<<endl;

                }
                else
                {
                    cout << "ENTER BOOK NAME :" << endl;  
                    string BN;
                    getline(cin,BN);
                    getline(cin,BN);
                    T.getIssuedBook(BN,EN);
                }
                
                break; 
            }
            case 2: 
            { 
                cout << "Choice is SHOW TABLE"<<endl;
                cout<<"WHICH TABLE YOU WANT TO SEE"<<endl;

                string TN;
                cin>>TN;
                T.show_Db(TN); 
                break; 
            }
            case 3:  
            {
                cout << "Choice is CHECK ISSUED BOOK"<<endl;
                cout<<"ENTER ENROLLMENT NUMBER"<<endl; 
                string EN;
                cin>>EN;
                T.Check_Limit(EN);
                break; 
            }
            case 4:
            {
                cout<<" Enter your ENROLLMENT_NUMBER and Book Name: "<<endl;
                string EN;cin>>EN;
                string BN;
                getline(cin,BN);
                getline(cin,BN);

                T.returnBook(EN,BN);
                break;
            }
            case 5:
            {
                if(Is_User_Logged_In == false)
                {
                    cout<<"*******YOU ARE NOT LOGGED IN******"<<endl;
                    cout<<"*******GO TO ADMIN AND LOGIN******"<<endl;
                }
                else
                {
                    string BN;
                    cout<<"*****ENTER THE BOOK TO ADD IN LIBERARY*****"<<endl;
                    getline(cin,BN);
                    getline(cin,BN);
                    T.Add_Book(BN);
                }

                break;
            }
            case 6:
            {
                cout<<" 1. Login"<<endl;
                cout<<" 2. SignUp"<<endl;
                int choice;cin>>choice;
                if(choice == 1)
                {
                    cout<<"Enter User_ID :: ";
                    string User_ID; cin>>User_ID;
                    cout<<"Enter Password :: ";
                    string Password; cin>>Password;

                    loginAdmin(User_ID, Password);
                }
                else if(choice == 2)
                {
                    Admin newUser;
                    newUser.setDetails();
                }
                break;
            }
            default: 
            { 
                cout << "Choice other than 1, 2 and 3"; 
                flag=1;
                break;
            }   
        }
         cout<<endl;
         cout<<endl;
         if(flag==1)
            break;
        cout<<"1. ISSUE BOOK"<<endl;
        cout<<"2. SHOW TABLE DETAIL"<<endl;
        cout<<"3. CHECK ISSUED BOOK"<<endl;
        cout<<"4. RETURN BOOK"<<endl;
        cout<<"5. ADD BOOK IN LIBERARY"<<endl;
        cout<<"6. Admin"<<endl;
        cout<<"7. Exit"<<endl;
        
    }
    sqlite3_close(DB);
    
    // cout<<"Here Im at the end"<<endl;
   // T.show_Db();
    return (0); 
} 
