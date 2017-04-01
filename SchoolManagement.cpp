/*
 * SchoolManagement.cpp
 *
 *  Created on: Apr 1, 2017
 *      Author: dgunda1
 */

#include<bits/stdc++.h>
//clear screen for windows
#define ClearScreen() system("cls")
//Student filename
#define SFNAME "studentDetails.txt"
#define PrintLine(x) cout<<'\n'; for(int _=0;_<80;_++) cout<<x; cout<<'\n'
using namespace std;
bool strcmpis(pair <string, int> s1, pair <string,int> s2){
	return (strcasecmp(s1.first.c_str(),s2.first.c_str()))<0;
}
int scan(){
	string ch;
	int i,v;
	do{
		v=1;
		cin>>ch;
		for(i=0;i<ch.size();i++){
			if(!isdigit(ch[i])){
				v=0;
				break;
			}
		}
	}while(!v);
	return atoi(ch.c_str());
}

//Student class representing student record
class Student {

	char studentName[40];
	int rollNum;
	char fatherName[40];
	char motherName[40];
	char address[90];
	public:
	void getStudentDetails(void);
	void displyDetails(void){		//Printing the details of Student
		cout<<"Roll No.      : "<<rollNum<<endl;
		cout<<"Student Name. : "<<studentName<<endl;
		cout<<"Father's Name : "<<fatherName<<endl;
		cout<<"Mother's Name : "<<motherName<<endl;
		cout<<"Address       : "<<address<<endl;
	}

	//return strings based on char for easy access
	char * getString(char x){

		if(x=='N')
			return studentName;
		if(x=='F')
			return fatherName;
		if(x=='M')
			return motherName;
		if(x=='A')
			return address;
	}
	int getRollNo(){
			return rollNum;
		}
	void modifyDetail(char ch);
};

//getting student details from user
void Student::getStudentDetails(){

	cout<<"Enter Student Name    : ";
	do{
		gets(studentName);
	}while(strlen(studentName)==0);
	cout<<"Enter Roll No.        : ";
	do{
		rollNum=scan();
	}while(rollNum<1);
	cout<<"Enter Father Name     : ";
	do{
		gets(fatherName);
	}while(strlen(fatherName)==0);
	cout<<"Enter Mother Name     : ";
	do{
		gets(motherName);
	}while(strlen(motherName)==0);
	cout<<"Enter Address         : ";
	do{
		gets(address);
	}while(strlen(address)==0);

}


//change student data
void Student::modifyDetail(char ch){

	if(ch=='N'){
		cout<<"Enter Student Name    : ";
		do{
			gets(studentName);
		}while(strlen(studentName)==0);
	}
	else if(ch=='R'){
		int currntRollNum=rollNum;

		fstream fl(SFNAME,ios::in|ios::binary);
		Student obj;
		do{
			cout<<"Enter Roll No.        : ";
			rollNum = scan();
			fl.close();
			fl.open(SFNAME,ios::in|ios::binary);
			while(!fl.eof()){
				fl.read((char*)&obj, sizeof(obj));
				if(fl.eof())
					break;
				if(obj.getRollNo()==rollNum && currntRollNum!=rollNum){	//Checking roll num from file
					cout<<"\n Roll No: "<<rollNum<<". Already Exists !\n";
					rollNum = -1;
				}
			}
		}while(rollNum<1);//loop till new roll num
		fl.close();
	}
	else if(ch=='F'){
		cout<<"Enter Father Name     : ";
		do{
			gets(fatherName);
		}while(strlen(fatherName)==0);
	}
	else if(ch=='M'){
		cout<<"Enter Mother Name     : ";
		do{
			gets(motherName);
		}while(strlen(motherName)==0);
	}
	else{
		cout<<"Enter Address         : ";
		do{
			gets(address);
		}while(strlen(address)==0);
	}
}

//Insert Student Record into File
void insertStudentRecord(){
	Student obj,obj2;
	char ch;
	int v=0;
	cout<<"Please Enter Student details:\n";
	obj.getStudentDetails();
	fstream fl1(SFNAME, ios::in|ios::binary);
	ofstream fl2;
	//check for existing file/create new
	if(!fl1){
		fl2.open(SFNAME,ios::out|ios::binary);
		fl2.write((char*)&obj, sizeof(obj));
		fl2.close();
		cout<<"Student Record inserted successfully..\n";
		return;
	}
	while(!fl1.eof()){
		fl1.read((char*)&obj2,sizeof(obj));
		if(fl1.eof()){
			break;
		}
		if(obj.getRollNo()==obj2.getRollNo()){		//If record with same Roll No. exists, then stop insertion
			cout<<"Record with same Roll No. with following details already exists : \n";
			obj2.displyDetails();
			cout<<"Insertion Ended\n";
			return;
		}
		else if(strcmpi(obj.getString('N'),obj2.getString('N'))==0){
			if (!v)							//checking for existing name
				cout<<"Student with same name already exists with below details : \n";
			obj2.displyDetails();
			cout<<'\n';
			v=1;
		}
	}
	if(v){
		cout<<"Do you still want to insert the record (Y/N) ? ";//confirmation
		do{
			cin>>ch;
			ch = toupper(ch);
		}while(ch!= 'Y' && ch!='N');
		if(ch=='N'){
			cout<<"Insertion Ended\n";
			return;
		}
	}
	fl2.open(SFNAME,ios::out|ios::app|ios::binary);
	fl2.seekp(0,ios::end);
	fl2.write((char*)&obj, sizeof(obj));//write to file
	fl2.close();
	cout<<"Record Inserted successfully !\n";
}

//read the student file and disply all the records
int dispStudentRecord(){
	Student obj;
	int emptyFlag=0;
	fstream fl1(SFNAME, ios::in|ios::binary);
	//check if the student file exist
	if(!fl1){
		cout<<"No Records Exist\n";
		return 0;
	}
	//if yes then read the object
	while(!fl1.eof()){
		fl1.read((char*)&obj, sizeof(obj));
		if(fl1.eof())
			break;
		emptyFlag=1;
		obj.displyDetails();
		PrintLine('-');
	}
	fl1.close();
	if(!emptyFlag)
		cout<<"No Records Exist\n";
	return emptyFlag;
}

int searchRecordsWithID(const string str = "search"){
	fstream fl(SFNAME,ios::in|ios::ate|ios::binary);
	if((!fl)||fl.tellg()==0){
		cout<<" No Records Found !\n";
		return 0;
	}
	fl.close();
	fl.open(SFNAME,ios::in|ios::binary);
	char ch;
	char searchString[30];
	Student obj;
	int searchFlag = 0;
	cout<<"Enter Attribute to "<<str<<" :\n";
	cout<<" N for Name of Student.\n";
	cout<<" F for Father's Name.\n";
	cout<<" M for Mother's Name.\n";
	cout<<" A for Address.\n";
	cout<<"Enter your choice : ";
	do{
		cin>>ch;
		ch = toupper(ch);
	}while(ch!='T' && ch!='N' && ch!='F' && ch!='M' && ch!='A' && ch!='B');
	cout<<"Enter String : ";
	do{
		gets(searchString);
	}while(strlen(searchString)==0);
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		if((strcmpi(searchString,obj.getString(ch))==0)){
			if(!searchFlag)
				cout<<"\n Search Results are: \n\n";
			obj.displyDetails();
			PrintLine('-');
			searchFlag = 1;
		}
	}
	if(!searchFlag)
		cout<<"No Records Found \n";
	fl.close();
	return searchFlag;
}

//search by number
int searchWithRollNo( ){
	Student obj;
	int rnumber;
	int searchFlag=0;

		cout<<"Enter Roll No to search : ";
		cin>>rnumber;
		fstream fl(SFNAME,ios::in|ios::binary);
		if(!fl){					//No file exists
			cout<<"No Records Found\n";
			return 0;
		}
		while(!fl.eof()){
			fl.read((char*)&obj,sizeof(obj));
			if(fl.eof()){
				break;
			}
			if(rnumber==obj.getRollNo()){
				if(!searchFlag)
					cout<<"\nSearch Results are: \n\n";
				obj.displyDetails();
				PrintLine('-');
				searchFlag = 1;
			}
		}
		if(!searchFlag)
			cout<<"No Records Found \n";
		fl.close();
		return searchFlag;

}



void updateRecord(){				//Modify Student Records

		Student obj;
		if(!searchRecordsWithID("search for"))
			return;
		fstream fl1(SFNAME,ios::in|ios::binary);
		int rNum,pos;
		char ch;
		cout<<"Enter Roll No of Record to modify : ";
		do{
			cin>>rNum;
		}while(rNum<1);
		while(!fl1.eof()){
			pos=fl1.tellg();
			fl1.read((char*)&obj,sizeof(obj));
			if(fl1.eof())
				break;
			if(rNum==obj.getRollNo()){
				cout<<'\n';
				fl1.close();
				fl1.open(SFNAME,ios::out|ios::in|ios::binary);
				while(pos--) fl1.get();
				cout<<"Enter Attribute to modify :\n";
				cout<<" N for Name of Student.\n";
				cout<<" R for Roll No.\n";
				cout<<" F for Father's Name.\n";
				cout<<" M for Mother's Name.\n";
				cout<<" A for Address.\n";
				cout<<"Enter your option : ";
				do{
					cin>>ch;
					ch = toupper(ch);
				}while(ch!='T' && ch!='N' &&ch!='R' && ch!='F' && ch!='M' && ch!='A' && ch!='B');
				obj.modifyDetail(ch);
				obj.displyDetails();
				fl1.write((char*)&obj, sizeof(obj));//update file
				PrintLine('-');
				break;
			}
		}
}


//deleting record
void deleteStudent(){
	Student obj;
	int flag=0;
	if(!searchRecordsWithID("delete using"))
		return;
	cout<<"\n Enter Roll No to delete : ";
	int rNum;
	char ch;
	cin>>rNum;
	fstream fl(SFNAME, ios::in|ios::binary);
	fstream fo("temp.dat", ios::out|ios::binary);
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		if (rNum==obj.getRollNo()){
			cout<<"Record with below details will be deleted :\n\n";
			obj.displyDetails();
			cout<<"are you sure to continue ? (Y/N) : ";
			do{
				cin>>ch;
				ch = toupper(ch);
			}while(ch!='N' && ch!='Y');
			if(ch=='N'){
				cout<<"Deletion stopped\n";

				fl.close();
				fo.close();
				remove("temp.dat");
				return;
			}
			flag=1;
			continue;
		}
		fo.write((char*)&obj,sizeof(obj));
	}
	fl.close();
	fo.close();
	remove(SFNAME);//delte existing file
	rename("temp.dat",SFNAME); // rename temp file to current file
	if(flag)
		cout<<"Student Record Successfully Deleted \n";
	else
		cout<<"No Record found \n";
}

int main(){
	char ch;
	char ch1;
	int ch2;
	do{
		ClearScreen();
		PrintLine("*");
		cout<<"\t\t\t    Student Records";
		PrintLine("*");
		cout<<"\t Press 1 for Student Records.\n";
		cout<<"\t 0 for  Exit.\n\n";
		cout<<"Please Enter 1 or 0 : ";
		fflush(stdin);
		cin>>ch1;
		if(ch1=='1'){
			fflush(stdin);
			do{
				ClearScreen();
				PrintLine("*");
				cout<<"\t\t\t    Student Records";
				PrintLine("*");
				cout<<"\t\t\tStudent Records Database";
				PrintLine('-');
				cout<<"\t Press 1 for  Insert Student.\n";
				cout<<"\t2 for  Display all Records.\n";
				cout<<"\t3 for  Search using Roll No.\n";
				cout<<"\t4 for  Search using other Attributes.\n";
				cout<<"\t5 for  Modify a Student Info.\n";
				cout<<"\t6 for  Delete a Student Record.\n";
				cout<<"\t0 for  Exit.\n";
				cout<<"\nEnter your choice : ";
				ch2 = scan();
				switch(ch2){
					case 1:
						insertStudentRecord();
						break;
					case 2:
						dispStudentRecord();
						break;
					case 3:
						searchWithRollNo();
						break;
					case 4:
						searchRecordsWithID();
						break;
					case 5:
						updateRecord();
						break;
					case 6:
						deleteStudent();
						break;
				}
				fflush(stdin);
				if(ch2)
					cin>>ch;
			}while(ch2!=0);
		}

	}while(ch1!='0');
	ClearScreen();
	return 0;
}
