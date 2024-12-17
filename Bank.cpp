#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip> 
using namespace std; 
struct sClient 
{ 
string AccountNumber; 
string Pincode; 
string Name; 
string Phone; 
string AccountBalance; 
bool MarkForDelete; 
}; 
vector<string>spiltstring(string s1 , string delim="#//#") 
{ 
string sWord; 
short pos =0; 
vector<string>vstring; 
while((pos=s1.find(delim))!=std::string::npos) 
{ 
sWord=s1.substr(0,pos); 
if(sWord!="") 
{ 
vstring.push_back(sWord); 
} 
s1.erase(0,pos+delim.length()); 
} 
if(s1!="") 
{ 
vstring.push_back(s1); 
} 
return vstring; 
} 
sClient ConvertFromLineToRecord(string s1) 
{ 
vector<string>vstring=spiltstring(s1); 
sClient Client; 
Client.AccountNumber=vstring[0]; 
Client.Pincode=vstring[1]; 
Client.Name=vstring[2]; 
Client.Phone=vstring[3]; 
Client.AccountBalance=vstring[4]; 
return Client; 
} 
vector<sClient>loadDataFromFile(string FileName) 
{
    vector<sClient>vClients; 
fstream MyFile; 
MyFile.open(FileName,ios::in);//read mode 
if(MyFile.is_open()) 
{ 
string line; 
while(getline(MyFile,line)) 
{ 
sClient Clients=ConvertFromLineToRecord(line); 
vClients.push_back(Clients); 
} 
MyFile.close(); 
} 
return vClients; 
} 
string ConvertFromRecordToLine(sClient Client , string delim="#//#") 
{ 
string s1 ; 
s1+=Client.AccountNumber+delim; 
s1+=Client.Pincode+delim; 
s1+=Client.Name+delim; 
s1+=Client.Phone+delim; 
s1+=Client.AccountBalance; 
return s1; 
} 
sClient ReadDataAboutAdd() 
{ 
sClient Client; 
cout<<"enter AccountNumber ? "; 
getline(cin,Client.AccountNumber); 
cout<<"enter Pincode ? "; 
getline(cin,Client.Pincode); 
cout<<"enter Name ? "; 
getline(cin,Client.Name); 
cout<<"enter Phone ?"; 
getline(cin,Client.Phone); 
cout<<" enter AccountBalance ?"; 
getline(cin,Client.AccountBalance); 
return Client; 
} 
string ReadAccountNumber() 
{ 
string AccountNumber; 
cout<<"enter AccountNumber ? "; 
cin>>AccountNumber; 
cin.ignore(); 
return AccountNumber;
} 
void addNewClientsToFile(sClient Client, string FileName) 
{ 
fstream MyFile; 
MyFile.open(FileName,ios::out|ios::app); 
if(MyFile.is_open()) 
{ 
MyFile<<ConvertFromRecordToLine(Client)<<endl; 
MyFile.close(); 
} 
} 
void addNewClients(string FileName) 
{ 
char readchoice='y'; 
cout<<"do you want to add new Client ?"; 
cin>>readchoice; 
do{ 
sClient Client = ReadDataAboutAdd() ; 
ConvertFromRecordToLine(Client); 
addNewClientsToFile(Client,FileName); 
}while(readchoice=='y'||readchoice=='Y'); 
} 
void addvectortofile(string FileName,vector<sClient>vClients) 
{ 
fstream MyFile; 
MyFile.open(FileName,ios::trunc); 
if(MyFile.is_open()) 
{ 
for(sClient &s : vClients) 
{ 
if(!s.MarkForDelete) 
{ 
string line = ConvertFromRecordToLine(s); 
MyFile<<line<<endl; 
} 
} 
MyFile.close(); 
} 
} 
void PrintCardOfData() 
{ 
 
cout << left << setw(20) << "AccountNumber" 
<< setw(20) << "Pincode" 
<< setw(25) << "Name" 
<< setw(20) << "Phone"
<< setw(20) << "AccountBalance" << endl; 
cout << "---------------------------------------------------------------" << endl; 
} 
void ShowAllClients(vector<sClient> vClients) 
{ 
PrintCardOfData(); 
for (sClient &s : vClients) 
{  
cout << left << setw(20) << s.AccountNumber 
<< setw(20) << s.Pincode 
<< setw(25) << s.Name 
<< setw(20) << s.Phone 
<< setw(20) << s.AccountBalance << endl; 
} 
} 
void PrintData(vector<sClient>& vClients) 
{ 
PrintCardOfData();  
for (const sClient& client : vClients) 
{  
cout << left << setw(20) << client.AccountNumber 
<< setw(20) << client.Pincode 
<< setw(25) << client.Name 
<< setw(20) << client.Phone 
<< setw(20) << client.AccountBalance << endl; 
} 
} 
sClient UpdateData() 
{ 
sClient Client; 
cout<<"enter Pincode ? "; 
getline(cin,Client.Pincode); 
cout<<"enter Name ? "; 
getline(cin,Client.Name); 
cout<<"enter Phone ?"; 
getline(cin,Client.Phone); 
cout<<" enter AccountBalance ?"; 
getline(cin,Client.AccountBalance); 
return Client; 
} 
bool SearchAccountandDelete(string FileName , vector<sClient>&vClients) 
{ 
bool found=false; 
char readchoice='y';
string accountNumber=ReadAccountNumber(); 
sClient Client; 
for(sClient &s :vClients) 
{ 
if(s.AccountNumber==accountNumber) 
{ 
PrintData(vClients); 
cout<<"do you want to Delete This Data about This Client ?"; 
cin>>readchoice; 
cin.ignore(); 
if(readchoice=='y'||readchoice=='Y') 
{ 
s.MarkForDelete=true; 
addvectortofile(FileName,vClients); 
cout<<"Data has been Deleted Successfully !!"; 
found= true; 
} 
} 
} 
if(!found) 
{ 
cout<<"AccountNumber Not Found !! "; 
found = false; 
} 
return found; 
} 
bool SearchAccountandUpdate(string FileName , vector<sClient>&vClients) 
{ 
bool found=false; 
char readchoice='y'; 
string accountNumber=ReadAccountNumber(); 
sClient Client; 
for(sClient &s :vClients) 
{ 
if(s.AccountNumber==accountNumber) 
{ 
PrintData(vClients); 
cout<<"do you want to Update This Data about This Client ?"; 
cin>>readchoice; 
cin.ignore(); 
if(readchoice=='y'||readchoice=='Y') 
{ 
sClient NewData = UpdateData(); 
s.Pincode=NewData.Pincode; 
s.Name=NewData.Name; 
s.Phone=NewData.Phone; 
s.AccountBalance=NewData.AccountBalance;
addvectortofile(FileName,vClients); 
cout<<"Data has been Upadted Successfully !!"; 
found= true; 
} 
} 
} 
if(!found) 
{ 
cout<<"AccountNumber Not Found !! "; 
found = false; 
} 
return found; 
} 
bool SearchAccountandPrintIt(string FileName , vector<sClient>&vClients) 
{ 
bool found=false; 
char readchoice='y'; 
string accountNumber=ReadAccountNumber(); 
sClient Client; 
for(sClient &s :vClients) 
{ 
if(s.AccountNumber==accountNumber) 
{ 
PrintCardOfData(); 
found= true; 
} 
} 
if(!found) 
{ 
cout<<"AccountNumber Not Found !! "; 
found = false; 
} 
return found; 
} 
void PrintHeadOfChoice() 
{ 
cout<<left<<"======================================="; 
cout<<setw(15)<<left<<" Main menu screen "; 
cout<<left<<"======================================="; 
cout<<setw(20)<<left<<"[1] Show Clients list "<<endl; 
cout<<setw(20)<<left<<"[2] Add New Clients "<<endl; 
cout<<setw(20)<<left<<"[3] Delete Clients "<<endl; 
cout<<setw(20)<<left<<"[4] Update Clients "<<endl; 
cout<<setw(20)<<left<<"[5] Find Clients "<<endl; 
cout<<setw(20)<<left<<"[6] Exit "<<endl;
} 
void ReadChoiceFromUser(vector<sClient> &vClients, string FileName) 
{ 
int readchoice; 
do 
{ 
PrintHeadOfChoice(); 
cout << "Enter your choice: "; 
cin >> readchoice; 
cin.ignore(); 
switch (readchoice) 
{ 
case 1: 
ShowAllClients(vClients); 
system("pause"); 
break; 
case 2: 
addNewClients(FileName); 
vClients = loadDataFromFile(FileName); 
system("pause"); 
break; 
case 3: 
SearchAccountandDelete(FileName, vClients); 
system("pause"); 
break; 
case 4: 
SearchAccountandUpdate(FileName, vClients); 
system("pause"); 
break; 
case 5: 
SearchAccountandPrintIt(FileName, vClients); 
system("pause"); 
break; 
case 6: 
cout << "Exiting program...\n"; 
break; 
default: 
cout << "Invalid choice. Try again.\n"; 
} 
} while (readchoice != 6); 
} 
int main() 
{ 
string FileName = "Clients2.txt"; 
vector<sClient>vClients=loadDataFromFile(FileName);
ReadChoiceFromUser(vClients,FileName); 
}