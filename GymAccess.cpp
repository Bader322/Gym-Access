#include <iostream>
#include <occi.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
using namespace oracle::occi;

// Read Oracle password to establish connection
string readPassword()
{
  struct termios settings;
  tcgetattr( STDIN_FILENO, &settings );
  settings.c_lflag =  (settings.c_lflag & ~(ECHO));
  tcsetattr( STDIN_FILENO, TCSANOW, &settings );

  string password = "";
  getline(cin, password);

  settings.c_lflag = (settings.c_lflag |   ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &settings );
  return password;
}

// Give each prepared statement a name
struct STMT {
  string name;
  Statement *stmt;
};

// Prepare the statements that would be used repeatedly
// in this program
int initStatements(Connection *conn, STMT * & statements)
{
  int size = 6;
  statements = new STMT[size];
  string queryStr;

  // Given the mid, show the member if he/she is registered in a class  
  statements[0].name = "Inclass";
  queryStr = "select m.name,m.mid, w.name from members m, workoutclasses w where m.mid = w.mid and m.mid =  :1";
  statements[0].stmt = conn->createStatement(queryStr);

  // Show the members with expired membership
  statements[1].name = "expired_membership";
  queryStr = "select name,mid,expireDate from members where sysdate > expireDate"; 
  statements[1].stmt = conn->createStatement(queryStr);
  
  // Given a Trainer level, show the name, and 
  statements[2].name = "Show_Level";
  queryStr = "select name from trainers where Tlevel = :1"; 
  statements[2].stmt = conn->createStatement(queryStr);

  // Add a member
  statements[3].name = "Add_member";
  queryStr = " insert into Members values(:1,:2,:3,sysdate,to_date(:4,'yyyy/mm/dd'))"; 
  statements[3].stmt = conn->createStatement(queryStr);

   // Update membership
  statements[4].name = "UpdateMembership";
  queryStr =  "update members set expireDate = to_date(:1,'yyyy/mm/dd') where members.mid = :2";
  statements[4].stmt = conn->createStatement(queryStr);
  // Check for availabe rooms
  statements[5].name = "OpenRoom";
  queryStr =  "select rno from rooms where tid is null";
  statements[5].stmt = conn->createStatement(queryStr);
 
  return size;
}

// Given the name, find the corresponding prepared sql statement
Statement * findStatement(string name, STMT *statements, int size)
{
  for(int i = 0; i < size; i++) {
    if (statements[i].name == name)
      return statements[i].stmt;
  }
  return 0;
}
// Terminate all the prepared statements
void terminateStatements(Connection *conn, STMT *statements, int size)
{
    for(int i = 0; i < size; i++) {
        conn->terminateStatement(statements[i].stmt);
    }
}


// check the existence of the member id
// return 1 if exists otherwise 0
bool Mid_Check(Statement *stmt,int mid) {   
	 
    stmt->setInt(1,mid);
    ResultSet *rs = stmt->executeQuery();
    bool exists = rs->next();
    
    
    stmt->closeResultSet(rs);
    return exists;
}

void ShowMembers(STMT *statements,int size) {
    cout << "In show members\n";
    Statement *stmt = findStatement("Inclass", statements,size);
    int mid;
	 cout << "Enter the member id : ";
	 cin >> mid;
	 cin.clear();
	// if(!isdigit(mid)) {
	 
	   if(!Mid_Check(stmt,mid)) {
    	cout << "This Member is not registered for any class\n";
    	return;
    }
    ResultSet *rs = stmt->executeQuery();
    while(rs->next()) {
      cout << "=================\n";
      string a = rs->getString(1);
      string b = rs->getString(2);
      string c = rs->getString(3);
      cout << "Name: "<< a << endl;
      cout << "Mid: "<< b << endl;
      cout << "Registered In: " << c << endl;
    }
	 
	 
	 
	 stmt->closeResultSet(rs);
	// } 
	// else {
	 //cin.clear();
	// cout << "Value entered is not a valid id\n";
	 //exit(0);
	// }
	 
} 
	// show memebrs who have expired membership
void ShowExpired(STMT *statements,int size) {
    
    Statement *stmt = findStatement("expired_membership", statements,size);
    
    ResultSet *rs = stmt->executeQuery();
     cout << "In show Expired\n";
     while(rs->next()) {
     cout << "=================\n";
     string a = rs->getString(1);
     string b = rs->getString(2);
     string c = rs->getString(3);
     cout <<"Name: "<< a << endl;
     cout <<"Member ID: "<< b << endl;
     cout <<"Date Expired: "<< c << endl;
    }
}  
    
bool CheckLevelStatement(Statement *stmt,int level) {
	if(level > 5 || level < 1) {
	 cout << "Level entered is not valid\n";
	 return false;
	
	}

	return true;
}

     // show name of trainer with level specified
void ShowLevelSpecified(STMT *statements,int size) {
    Statement *stmt = findStatement("Show_Level", statements,size);
    int level;
    cout << "In ShowLevelSpecified\n";
    cout << "Enter the Level: ";
	 cin >> level;
	 cin.clear();
      
		// if user enters an invalid data 
	if(CheckLevelStatement(stmt,level) == 0) {
		cout << "Level "<< level << " doesn't exist, Returning to main menu" << endl;
		return;
	}    
		
		stmt->setInt(1,level);
		ResultSet *rs = stmt->executeQuery();
		
      
      while(rs->next()) {
     		cout << "=================\n";
    		string a = rs->getString(1);
     		//string b = rs->getString(1);
     //string c = rs->getString(3);
     		cout << "Name: " <<  a  << endl;
     		cout << "=================\n";
     	//	cout << b << endl;
   //    cout << c << endl;
     }
    
    stmt->closeResultSet(rs);
}
    // add mid, name, phone #, joindate by sysdate, expdate
void addmember(STMT *statements,int size, Connection *conn) {
	Statement *stmt = findStatement("Add_member", statements,size);
	string mid;
	string phone_number;
	string name;
	string expdate;
	cin.ignore();
	cout << "In add members\n";
	cout << "Enter the mid: ";
	getline(cin,mid);
	cout << "Enter the name: ";
	getline(cin,name);
	cout << "Enter the phone number: ";
	getline(cin,phone_number);
	cout << "Enter the expiry date of the membership. Format (yyyy/mm/dd): ";
	
	getline(cin,expdate);
	stmt->setInt(1,atoi(mid.c_str()));
	stmt->setString(2,name);
	stmt->setString(3,phone_number);
	stmt->setString(4,expdate);
	
	
	
	// error check inputs
	stmt->executeUpdate();
	conn->commit();
	cout << "*************************New Member Inserted*************************\n";
	
	
	
	
}
// Check if the mid exists int the database
bool Mid_Exists(int mid) {



}

// Update the membership date
void UpdateMembership(STMT *statements,int size, Connection *conn) {
	Statement *stmt = findStatement("UpdateMembership", statements,size);
   string mid,expdate;
   cout << "Enter the mid: ";
   cin >> mid;
   cout << "Enter the extension date of the membership. Format (yyyy/mm/dd): ";
   cin >> expdate;
  // if(!Mid_Exists) {
   // cout << "Value entered is not in the database\n";
    //return;
   //}
   stmt->setInt(2,atoi(mid.c_str()));
   stmt->setString(1,expdate);
   stmt->executeUpdate();
   conn->commit();
   cout << "*************************Update Successful*************************\n";

}
// List open rooms
void OpenRoom(STMT *statements,int size) {
	Statement *stmt = findStatement("OpenRoom", statements,size);
	string rno;
	ResultSet *rs = stmt->executeQuery();
   cout << "In Open Room\n";
   while(rs->next()) {
     cout << "=================\n";
     string rno = rs->getString(1);
     cout <<"Room: "<< rno << endl;
     cout << "=================\n";
    }
    
    stmt->closeResultSet(rs);

}
int main()
{
    string userName = "alsalehb";
    string password = "BadeR322";
    const string connectString = "sunfire.csci.viu.ca";

    // Establish connection using userName and password
     //cout << "Your user name:\n ";
    //getline(cin, userName);

    cout << "Your password: \n";
    //password = readPassword();

     Environment *env = Environment::createEnvironment();
     Connection *conn = env->createConnection
                          (userName, password, connectString);

     STMT *statements;
     int size = initStatements(conn, statements);

     Statement *stmt;
     string option;
 
   do{
   	cout << "Choose an option: A Letter 'Either lower case or upper case'\n";
   	cout << "########################\n";
   	cout << "========================\n";
      cout << "'L' Show name,mid,class name given the member id \n";
      cout << "'C' List rooms not scheduled for classes\n";
      cout << "'E' Show members who have their membership expired\n";
      cout << "'T' List Trainers of Level Specified\n";
      cout << "'Y' Add a new member\n";
      cout << "'U' Update Membership\n";
      cout << "'Q' To quit program\n";
      cout << "========================\n";
      cout << "*************************\n";
      cout << "Option: ";
      cin >> option;
      cin.clear();
		// check option selected and invoke the specified function accordingly
		
		
		
		 
		if(option.compare("L") == 0 || option.compare("l") == 0) {
			cout << "I'm here\n";
			ShowMembers(statements,size);
		
		
		// return 0;
		} //Show members who have their membership expired
		else if (option.compare("E") == 0 || option.compare("e") == 0) {
			cout << "choice E\n";
			ShowExpired(statements,size);	
		}
		else if (option.compare("T") == 0 || option.compare("t") == 0) {
			cout << "choice T\n";
			ShowLevelSpecified(statements,size);
		}
		// add a new memeber
		else if (option.compare("Y") == 0 || option.compare("y") == 0) {
			cout << "choice Y\n";
			addmember(statements,size,conn);
		}
		//Update Membership
		else if (option.compare("U") == 0 || option.compare("u") == 0) {
			cout << "choice U\n";
			UpdateMembership(statements,size,conn);
		}
		else if (option.compare("C") == 0 || option.compare("c") == 0) {
		   cout << "Choice C\n";
		   OpenRoom(statements,size);
		
		}


		


      
    } while (option.compare("q") != 0 && option.compare("Q") != 0);

	 

 
    // clean up environment before terminating
    terminateStatements(conn, statements, size);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return 0;
}


