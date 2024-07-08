#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>

using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "your password";
const char* DB = "mydb";


class Flight{
	
	private:
		string Fnum, Dep, Des;
		int Seat;
		
	public:
		
		Flight(string fnum, string dep, string des, int seat){
			
			Fnum = fnum;
			Dep = dep;
			Des = des;
			Seat = seat;
		}
		
		string getFnum(){
			
			return Fnum;
		}
		string getDep(){
			
			return Dep;
		}
		string getDes(){
			
			return Des;
		}
		int getSeat(){
			
			return Seat;
		}
};

int main(){
	
	MYSQL* conn;
	conn = mysql_init(NULL);
	
	if(!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)){
		
		cout<<"Error : "<<mysql_error(conn)<<endl;
	}
	else{
		
		cout<<"Logged In Database!"<<endl;
	}
	Sleep(3000);
	
	Flight f1("Flight101", "UAE", "India", 50);
	Flight f2("Flight102", "UAE", "Japan", 40);
	Flight f3("Flight103", "UAE", "China", 30);
	
	int intS1 = f1.getSeat();
	int intS2 = f2.getSeat();
	int intS3 = f3.getSeat();
	
	
	stringstream ss1, ss2, ss3;
	
	ss1 << intS1;
	string strS1 = ss1.str();
	
	ss2 << intS2;
	string strS2 = ss2.str();
	
	ss3 << intS3;
	string strS3 = ss3.str();
	
	
	string insert1 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f1.getFnum()+"', '"+f1.getDep()+"', '"+f1.getDes()+"', '"+strS1+"' )";
	string insert2 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f2.getFnum()+"', '"+f2.getDep()+"', '"+f2.getDes()+"', '"+strS2+"' )";
	string insert3 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f3.getFnum()+"', '"+f3.getDep()+"', '"+f3.getDes()+"', '"+strS3+"' )";
	
	if(mysql_query(conn, insert1.c_str()) || mysql_query(conn, insert2.c_str()) || mysql_query(conn, insert3.c_str())){
		
		cout<<"Error : "<<mysql_error(conn)<<endl;
	}
	else{
		
		cout<<"Inserted Successfully!"<<endl;
	}
	Sleep(3000);
	
	bool exit = false;
	while(!exit){
		
		system("cls");
		
		cout<<endl;
		
		cout<<"Welcome to Airline Reservation System"<<endl;
		cout<<"*************************************"<<endl;
		cout<<"\t1) Reserve a seat in flight: "<<endl;
		cout<<"\t2) Exit: "<<endl;
		cout<<"\t3) Enter Your Choice: ";
		
		int val;
		cin >> val;
		
		if(val == 1){
			
			string flight;
			cout<<endl;
			
			cout<<"Enter Flight Number : ";
			cin >> flight;
			
			int total;
			
			string check = "SELECT Seat FROM Airline WHERE Fnumber = '"+flight+"'";
			
			if(mysql_query(conn, check.c_str())){
				
				cout<<"Error : "<<mysql_error(conn)<<endl;
			}
			else{
				
				MYSQL_RES* res;
				res = mysql_store_result(conn);
				
				if(res){
					
					MYSQL_ROW row = mysql_fetch_row(res);
					
					if(row){
						
					
					total = atoi(row[0]);
			        }
				}
			}
		
			if(total > 0){
				
				stringstream sst;
				total--;
				sst << total;
				string strT = sst.str();
				
				string update = "UPDATE Airline SET Seat = '"+strT+"' WHERE = '"+flight+"'";
				
				if(mysql_query(conn, update.c_str())){
				
				cout<<"Error : "<<mysql_error(conn)<<endl;
			    
			    }
			    else{
			    	
			    	cout<<"Seat is Reserved Successfully in : "<<flight<<endl;
				}
				if(total == 0){
					
					cout<<"Sorry! No seats available!"<<endl;
				}
			}
			Sleep(8000);
		}
	}
	
	    return 0;
    }
