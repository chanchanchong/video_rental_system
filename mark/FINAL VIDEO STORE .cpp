#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip> 
#include <string.h>
#include <cstdlib>
#include <fstream>
using namespace std;

class Video{
	protected:
		int video_id = 0;
		string video_title;
		string video_genre;
		string video_production;
		int video_numberOfCopies;
		bool video_isAvail;
		Video *next;
		Video *prev;
	friend class VideoList;
	friend class CustomerVideoRentList;
};
class VideoList{
	public:
		fstream file;
		int count_id = 0;
		VideoList();
		~VideoList();
		bool empty() const;
		void addVideo(string title, string genre, string production, int numberOfCopies);
		void searchVideo(const int& id);
		void isAvailVideo(const int& id);
		void listVideo();
		void storeVideo(Video* v);
		void load();
	protected:
		Video* header;
		Video* trailer;
		
	protected:
		void add(Video* v,string title, string genre, string production, int numberOfCopies);
		void remove(Video* v);
};
VideoList::VideoList(){
	header = new Video;
	trailer = new Video;
	header->next = trailer;
	trailer->prev = header;
	load();
}
VideoList::~VideoList(){
	while(!empty()) remove(header->next);
	delete header;
	delete trailer;
}
bool VideoList::empty() const { return (header->next == trailer); }
void VideoList::load(){
	storeVideo(header->next);
}
string convertString(char* c){
    string s = c;
    return s;
}
void VideoList::storeVideo(Video* v){
	
    char id[3], title[50],genre[15], production[15], copies[3], isAvail[2];
	ifstream in_file("VideoList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  
			Video* u = new Video;
         	char ca[str.size() + 1];
         	strcpy(ca, str.c_str());
			strcpy(id, strtok(ca , "|"));
    		strcpy(title, strtok(NULL, "|"));
    		strcpy(genre , strtok(NULL, "|"));
    		strcpy(production , strtok(NULL, "|"));
    		strcpy(copies, strtok(NULL, "|"));
			strcpy(isAvail, strtok(NULL, "|"));
			u->video_id = atoi(id);
			u->video_title = convertString(title);
			u->video_genre = convertString(genre);
			u->video_production = convertString(production);
			u->video_numberOfCopies = atoi(copies);
			u->video_isAvail = atoi(isAvail);
			count_id++;
			u->next = v;				
			u->prev = v->prev;			
			v->prev->next = v->prev = u;			
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void VideoList::add(Video* v,string title, string genre, string production, int numberOfCopies){
	Video *u = new Video;
	int id  = count_id;
	u->video_id = ++id;
	u->video_title = title;
	u->video_genre = genre;
	u->video_production = production;
	u->video_numberOfCopies = numberOfCopies;
	u->video_isAvail = u->video_numberOfCopies != 0 ? true:false;
	
	u->next = v;				
	u->prev = v->prev;				
	v->prev->next = v->prev = u; 	
	
	file.open("VideoList.txt", ios::out | ios::app);
	file << "\n" << u->video_id 	<< "|" 
		 << u->video_title			<< "|"
		 << u->video_genre			<< "|"
		 << u->video_production		<< "|"
		 << u->video_numberOfCopies	<< "|"
		 << u->video_isAvail		<< "\n";
	file.close();
}
void VideoList::searchVideo(const int& id){
	Video* p = header->next;
	while(p != trailer && id != p->video_id){
		p = p->next;
	}
	cout << "Video ID: "  		 << p->video_id 			<< "\n"
		 << "Title: " 	 	 	 << p->video_title			<< "\n"
		 << "Genre: " 	 	 	 << p->video_genre			<< "\n"
		 << "Production: "		 << p->video_production		<< "\n"
		 << "Number of Copies: " << p->video_numberOfCopies	<< "\n";
	cout << "\n";
}
void VideoList::addVideo(string title, string genre, string production, int numberOfCopies){
	add(trailer, title, genre, production, numberOfCopies);
}
void VideoList::remove(Video* v){
	Video* u = v->prev;
	Video* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

void VideoList::isAvailVideo(const int& id){
	Video* p = header->next;
	while(p != trailer && id != p->video_id){
		p = p->next;
	}

	cout << "Video ID: "  		 << p->video_id 			<< "\n"
		 << "Title: " 	 	 	 << p->video_title			<< "\n"
		 << "Genre: " 	 	 	 << p->video_genre			<< "\n"
		 << "Production: "		 << p->video_production		<< "\n"
		 << "Number of Copies: " << p->video_numberOfCopies	<< "\n"
		 << "Availability: "	 << (p->video_isAvail ? "Available":"Not Available")	<< "\n";
	cout << "\n";
}
void VideoList::listVideo(){
	Video* p = header->next;
	int id;
	cout << "Video ID"	 	<< setw(25) 
		 << "Title"  		<< setw(20) 
	     << "Genre" 		<< setw(30) 
		 << "Production" 	<< "\n";
	while(p != trailer){
		cout << setw(3)
			 << p->video_id 		 	<< setw(30) 
		 	 << p->video_title			<< setw(20) 
		 	 << p->video_genre			<< setw(30) 
		 	 << p->video_production		<< "\n";

		p = p->next;
	}
	cout << "\n";
}

class Customer{
	protected:
		int customer_id = 0;
		string customer_name;
		string customer_address;
		Customer *next;
		Customer *prev;
	friend class CustomerList;
	friend class CustomerVideoRentList;
};

class CustomerList{
	public:
		fstream file;
		int count_id = 0;
		CustomerList();
		~CustomerList();
		bool empty() const;
		void addCustomer(string name, string address);
		void searchCustomer(const int& id);
		void listCustomer();
		void load();
		void storeCustomer(Customer* C);
	protected:
		Customer* header;
		Customer* trailer;
	protected:
		void add(Customer* c, string name, string address);
		void remove(Customer* c);
};
CustomerList::CustomerList(){
	header = new Customer;
	trailer = new Customer;
	header->next = trailer;
	trailer->prev = header;
	load();
}

void CustomerList::load(){
	storeCustomer(header->next);
}
CustomerList::~CustomerList(){
	while(!empty()) remove(header->next);
	delete header;
	delete trailer;
}
bool CustomerList::empty() const { return (header->next == trailer); }
void CustomerList::add(Customer* c, string name, string address){
	Customer *u = new Customer;
	int id  = count_id;
	u->customer_id = ++id;
	u->customer_name = name;
	u->customer_address = address;
	u->next = c;					
	u->prev = c->prev;			
	c->prev->next = c->prev = u; 	
	count_id = u->customer_id;
	file.open("CustomerList.txt", ios::out | ios::app);
	file << "\n" <<	u->customer_id 	<< "|" 
		 << u->customer_name		<< "|"
		 << u->customer_address;
	file.close();
}
void CustomerList::addCustomer(string name, string address){
	add(trailer, name, address);
}
void CustomerList::remove(Customer* v){
	Customer* u = v->prev;
	Customer* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}
void CustomerList::storeCustomer(Customer* c){
    char id[3], name[50],address[50];
	ifstream in_file("CustomerList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  
			Customer* u = new Customer;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(id, strtok(temp , "|"));
    		strcpy(name, strtok(NULL, "|"));
    		strcpy(address , strtok(NULL, "|"));
			u->customer_id = atoi(id);
			u->customer_name = convertString(name);
			u->customer_address = convertString(address);
			count_id++;
			u->next = c;				
			u->prev = c->prev;			
			c->prev->next = c->prev = u;			
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void CustomerList::searchCustomer(const int& id){
	Customer* p = header->next;
	while(p != trailer && id != p->customer_id){
		p = p->next;
	}
	cout << "Customer ID: "  	 << p->customer_id 			<< "\n"
		 << "Name: " 	 	 	 << p->customer_name			<< "\n"
		 << "Address: " 	 	 	 << p->customer_address		<< "\n";
	cout << "\n";
}
void CustomerList::listCustomer(){
	Customer* p = header->next;
	int id;
	cout << "Customer ID"	 	<< setw(20) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	while(p != trailer){
		cout << setw(3)
			 << p->customer_id 		 		<< setw(30) 
		 	 << p->customer_name			<< setw(40) 
		 	 << p->customer_address			<< "\n";
		p = p->next;
	}
	cout << "\n";
}


class CustomerVideoRent: public Video, public Customer{
	private:
		int customer_id;
		vector<int> video_id;
		int n = 0;
		CustomerVideoRent* next;
		CustomerVideoRent* prev;
		friend class CustomerVideoRentList;
};

class CustomerVideoRentList: public VideoList,public CustomerList{
	public:
		fstream file;
		CustomerVideoRentList();
		~CustomerVideoRentList();
		void rentVideo(int& customerid);
		void returnVideo(int& customerid);
		void storeCustomerVideoRentList(CustomerVideoRent* CV);
		bool empty() const;
		void load();
		void listCustomerRented();
	private:
		CustomerVideoRent* header;
		CustomerVideoRent* trailer;
	protected:
		void remove(CustomerVideoRent* CV);
		void rent(CustomerVideoRent* CV, int& customerid);
		void returnV(CustomerVideoRent* CV, int& customerid);
};
CustomerVideoRentList::CustomerVideoRentList(){
	header = new CustomerVideoRent;
	trailer = new CustomerVideoRent;
	header->next = trailer;
	trailer->prev = header;
	load();
}

bool CustomerVideoRentList::empty() const { return (header->next == trailer); }

CustomerVideoRentList::~CustomerVideoRentList(){
	while(!empty()) remove(header->next);
	delete header;
	delete trailer;
}
void CustomerVideoRentList::remove(CustomerVideoRent* CV){
	CustomerVideoRent* u = CV->prev;
	CustomerVideoRent* w = CV->next;
	u->next = w;
	w->prev = u;
	delete CV;
}

void CustomerVideoRentList::returnV(CustomerVideoRent* CV, int& customerid){
	if(empty()){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
		
	CustomerVideoRent* u = header->next;
	Customer* p = CustomerList::header->next;
	Video* V = VideoList::header->next;
	while(u != trailer && customerid != u->customer_id){
		u = u->next;
		p = p->next;
	}
	cout << "Customer ID: "  	 << u->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << p->customer_name		<< "\n"
		 << "Address: " 	 	 << p->customer_address		<< "\n";
	cout << "\n";
	
	for (vector<int>::iterator it = u->video_id.begin(); it != u->video_id.end(); ++it) {
		while(V != trailer && *it != V->video_id) V = V->next;
			cout << "Video ID: "  	<< V->video_id 	<< "\n";
			V->video_numberOfCopies++;
			u->n--;
	}
	remove(u);
}

void CustomerVideoRentList::rent(CustomerVideoRent* CV, int& customerid){

	char choice;
	CustomerVideoRent *u = new CustomerVideoRent;
	Customer* p = CustomerList::header->next;
	while(p != CustomerList::trailer && customerid != p->customer_id){
		p = p->next;
	}
	cout << "Customer ID: "  	 << p->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << p->customer_name		<< "\n"
		 << "Address: " 	 	 << p->customer_address		<< "\n";
	cout << "\n";
	u->customer_id = p->customer_id;
	Video* ptr = VideoList::header->next;
	int videoid;
	while(choice != 'N'){
		cout << "Video to rent: ";
		cin >> videoid;
		while(ptr != VideoList::trailer && videoid != ptr->video_id){
			ptr = ptr->next;
		}
		if(ptr->video_numberOfCopies == 0){
			cout << "VIDEO is NOT AVAILABLE" << "\n";
		}
	cout << "Video ID: "  		 << ptr->video_id 				<< "\n"
		 << "Title: " 	 	 	 << ptr->video_title			<< "\n"
		 << "Number of Copies: " << ptr->video_numberOfCopies	<< "\n";
	cout << "\n";
	ptr->video_numberOfCopies--;
	ptr->video_numberOfCopies != 0 ? ptr->video_isAvail = true : ptr->video_isAvail = false;
	u->video_id.push_back(ptr->video_id);
	u->n++;
	cout << "Rent another Video: (Y/N)";
	cin >> choice;
	}
	
	u->next = CV;				
	u->prev = CV->prev;			
	CV->prev->next = CV->prev = u; 	
 	system("pause"); 
	file.open("CustomerVideoRentList.txt", ios::out | ios::app);
	file << "\n" << u->customer_id << "|" 
		 		 << u->n 		   << "|";
	  for (std::vector<int>::iterator it = u->video_id.begin(); it != u->video_id.end(); ++it) {
        	file << *it << "|";
    	}
	file.close();
	
}
void CustomerVideoRentList::returnVideo(int& customerid){
	returnV(trailer, customerid);
}
void CustomerVideoRentList::rentVideo(int& customerid){
	rent(trailer, customerid);
}
void CustomerVideoRentList::storeCustomerVideoRentList(CustomerVideoRent* CV){
    char cid[3], vid[3],nn[3];
	ifstream in_file("CustomerVideoRentList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  
			CustomerVideoRent* u = new CustomerVideoRent;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(cid, strtok(temp , "|"));
    		strcpy(nn, strtok(NULL, "|"));
			u->customer_id = atoi(cid);
			u->n = atoi(nn);
			 for (int i = 0; i < u->n; i++) {
				strcpy(vid , strtok(NULL, "|"));
				u->video_id.push_back(atoi(vid));
			}
			u->next = CV;			
			u->prev = CV->prev;			
			CV->prev->next = CV->prev = u;			
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void CustomerVideoRentList::load(){
	storeCustomerVideoRentList(header->next);
}
void CustomerVideoRentList::listCustomerRented(){
	CustomerVideoRent* CV = header->next;
	Customer* P = CustomerList::header->next;
	Video* V = VideoList::header->next;
	int id;
	cout << "Customer ID"	 	<< setw(20) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	while(CV != trailer && P != trailer){
		cout << setw(3)
			 << CV->customer_id 		 		<< setw(30) 
		 	 << P->customer_name				<< setw(40) 
		 	 << P->customer_address				<< "\n\n";
		cout << "Video ID"	 	<< setw(20) 
		 	 << "Movie Title"  	<< "\n";
		 	 for (vector<int>::iterator it = CV->video_id.begin(); it != CV->video_id.end(); ++it) {
		 	 	while(V != trailer && *it != V->video_id) V = V->next;
				cout << *it << setw(25)
					 << V->video_title << "\n";
			}
		P = P->next;
		CV = CV->next;
	}
	cout << "\n";
}

void inputlistCustomerRented(CustomerVideoRentList& CV){
	system("CLS");
 	CV.listCustomerRented();
 	system("pause"); 
}


void inputrentVideo(CustomerVideoRentList& CV){
	int customerid;
	char choice;
	system("CLS");
	cout << "Enter Customer ID: ";
	cin >> customerid;
	CV.rentVideo(customerid);
}

void inputreturnVideo(CustomerVideoRentList& CV){
	int customerid;
	char choice;
	system("CLS");
	cout << "Enter Customer ID: ";
	cin >> customerid;
	CV.returnVideo(customerid);
	system("pause"); 
}

void inputsearchVideo(VideoList& V){
		int id;
		system("CLS");
		cout << "Enter Video ID: ";
		cin >> id;
		V.searchVideo(id);
		system("pause"); 	
}

void inputisAvailVideo(VideoList& V){
		int id;
		system("CLS");
		cout << "Enter Video ID: ";
		cin >> id;
		V.isAvailVideo(id);
		system("pause"); 	
}

void inputaddVideo(VideoList& V){
		string title;
		string genre;
		string production;
		int numberOfCopies;
		cin.clear();
		cin.sync();
		
		system("CLS");
		cout << "Enter Video Title: ";
		getline(cin, title);
		cout << "Enter Video Genre: ";
		getline(cin, genre);	
		cout << "Enter Video Production: ";
		getline(cin, production);
		cout << "Enter number of copies: ";
		cin >> numberOfCopies;
		V.addVideo(title,genre,production,numberOfCopies);
		system("pause"); 
}

void inputlistVideo(VideoList& V){
	system("CLS");
 	V.listVideo();
 	system("pause"); 
}

void inputsearchCustomer(CustomerList& C){
		int id;
		system("CLS");
		cout << "Enter Customer ID: ";
		cin >> id;
		C.searchCustomer(id);
		system("pause"); 	
}

void inputaddCustomer(CustomerList& C){
		string name;
		string address;
		cin.clear();
		cin.sync();
		
		system("CLS");
		cout << "Enter Customer Name: ";
		getline(cin, name);
		cout << "Enter Customer Address: ";
		getline(cin, address);
		C.addCustomer(name,address);
		C.searchCustomer(C.count_id);
		system("pause"); 
}
void inputlistCustomer(CustomerList& C){
	system("CLS");
 	C.listCustomer();
 	system("pause"); 
}

int main(){
	VideoList V;
	CustomerList C;
	CustomerVideoRentList CV;
	int choice;
	do{
		system("CLS");
		cout << "\t-------------------------------------------------------------------------" << endl;
		cout << "\t \t \t \t Video Store \n" << endl;
		cout << "\t-------------------------------------------------------------------------" << endl;
		cout << "\t[1] New Video" << endl
		     << "\t[2] Rent a Video" << endl
		     << "\t[3] Return a Video" << endl
		     << "\t[4] Show Video Details" << endl
		     << "\t[5] Display all Videos	" << endl
			 << "\t[6] Check Video Availability" << endl
			 << "\t[7] Customer Maintenance" << endl
		     << "\t[8] Exit Program" << endl;
		     cout << "\n \tChoose: ";
		     cin >> choice;
		     switch(choice){
			 	case 1:
			 		inputaddVideo(V);
					break;
				case 2:
					inputrentVideo(CV);
					break;	
				case 3:
			 		inputreturnVideo(CV);
					break;
				case 4:
					inputsearchVideo(V);
					break;
				case 5:
					inputlistVideo(V);
					break;
				case 6:
					inputisAvailVideo(V);
					break;
				case 7:
					int c;
					cout << "\t[1] Add New Customer" << endl
		     			 << "\t[2] Show Customer Details" << endl
		     			 << "\t[3] List of Videos Rented by a Customer" << endl;
		     			 cout << "\n \tChoose: ";
		     			 cin >> c;
					switch(c){
						case 1:
							inputaddCustomer(C);
							break;
						case 2:
							inputsearchCustomer(C);
							break;
						case 3:
							inputlistCustomerRented(CV);
							break;
					}
					break;
				case 8:
					C.~CustomerList();
					CV.~CustomerVideoRentList();
					V.~VideoList();
					exit(0);
					break;
				default:
					
					break;
			 }
			 
	}while(choice != 8);
	
}



