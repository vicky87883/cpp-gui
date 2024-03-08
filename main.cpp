#include <iostream>
#include<mysql.h> //These Libraries were added by including folders to projects options
#include<mysqld_error.h> //and this particularly, when pasting 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
char HOST[]="localhost";
char USER[]="root";
char PASS[]="root";

int main() {
	MYSQL* obj; //one to manage MYSQL session.
	int College_ID;
	char Name[20];
	char BirthDate[11]; //This is always 11: YYYY-MM-DD + 0 from every char array
	float Grade;
	bool ProgramIsOpened = true;
	int answer;    //These are to keep the program opened
	char* consult;
	char* sentence;
	string sentence_aux; //These are to add data to the table.
	
	//-------------------------------------------------------------------------------------------------------
	//connection
	if(!(obj=mysql_init(0)))
	{
		cout<<"ERROR: MYSQL object could not be created."<<endl;
	}
	else
	{
		if(!mysql_real_connect(obj,HOST,USER,PASS,"school",3306,NULL,0))
		{
			cout<<"ERROR: Some database info is wrong or do not exist."<<endl;
			cout<<mysql_error(obj)<<endl;
		}
		else
		{
			cout<<"Logged in."<<endl<<endl;
			while(ProgramIsOpened)
			{
				cout<<"College ID:";
				cin>>College_ID;
				cin.ignore(100,'\n');//Remember to clean your buffer after using cin for int, float and double.
				
				cout<<"Name: ";
				cin.getline(Name,20,'\n'); //We don't use :cin>>Name: Because it doesn't read spaces.
				
				cout<<"BirthDate: ";
				cin.getline(BirthDate,11,'\n');
				cout<<"Grade: ";
				cin>>Grade;
				cin.ignore(100,'\n');
				cout<<endl;
				
				//Setting our update.
				sentence_aux = "INSERT INTO student(College_ID,Name,BirthDate,Grade) VALUES('%d','%s','%s','%f')";
				sentence = new char[sentence_aux.length()+1];
				strcpy(sentence,sentence_aux.c_str()); //we copy our string statement into a *char
				consult = new char[strlen(sentence)+sizeof(int)+strlen(Name)+sizeof(float)];
				sprintf(consult,sentence,College_ID,Name,BirthDate,Grade);//Subsitutes %d.... for actual values.
				//Make out attempt.
				if(mysql_ping(obj))
				{
					cout<<"ERROR: Impossible to connect:"<<endl;
					cout<<mysql_error(obj)<<endl;
				}
				if(mysql_query(obj,consult))
				{
					cout<<"Error:"<<mysql_error(obj)<<endl;
					rewind(stdin);
					getchar();
				}
				else
				{
					cout<<"Info added correctly."<<endl;
				}
				mysql_store_result(obj);
				cout<<endl<<"Another?"<<endl;
				cout<<"[1]: Yes"<<endl;
				cout<<"[0]: No"<<endl;
				cout<<"Answer: ";
				cin>>answer;
				cin.ignore(100,'\n');
				if(answer==0)
				{
					ProgramIsOpened = false;
				}
				cout<<endl;
			}
		}
	}
	cout<<"BYE!!!!"<<endl;
	return 0;
}



































