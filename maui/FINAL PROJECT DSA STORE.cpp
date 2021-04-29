#include <iomanip> 
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


public class VideoNodeLList{
	public:
		fstream file;
		int count_id = 0;
		VideoNodeLList();
		~VideoNodeLList();
		void addVideo(string& title, string& genre, string& production, int& numberOfCopies);																				
		void searchVideo(int& id);
		void isAvailVideo(int& id);
		void listVideo();
		void load();
	protected:
		struct VideoNode{
		protected:
			int videoID;
			string videoTitle;
			string videoGenre;
			string videoProduction;
			int videoCopies;
			bool videoisAvailable;
			struct VideoNode *next;
			struct VideoNode *prev;
			friend class VideoNodeLList;
			friend class VideoRentedbyCustomerList;
	};
		VideoNode* head;
		VideoNode* tail;
		
	private:
		void add(VideoNode* v,string& title, string& genre, string& production, int& numberOfCopies);
		void remove(VideoNode* v);
		
};
VideoNodeLList::VideoNodeLList(){
	head = new VideoNode;
	tail = new VideoNode;
	head->next = tail;
	tail->prev = head;
	load();
}
VideoNodeLList::~VideoNodeLList(){
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}

string ToString(char* a){
    string s = a;
    return s;
}
void VideoNodeLList::load(){
	VideoNode* ptr = head->next;
    char id[3], title[50],genre[15], production[15], copies[3], isAvail[2];
	ifstream in_file("VideoNodeLList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  
			VideoNode* Video = new VideoNode;
         	char ca[str.size() + 1];
         	strcpy(ca, str.c_str());
			strcpy(id, strtok(ca , "-"));
			Video->videoID = atoi(id);
    		strcpy(title, strtok(NULL, "-"));
			Video->videoTitle = ToString(title);
    		strcpy(genre , strtok(NULL, "-"));
			Video->videoGenre = ToString(genre);
    		strcpy(production , strtok(NULL, "-"));
			Video->videoProduction = ToString(production);
    		strcpy(copies, strtok(NULL, "-"));
			Video->videoCopies = atoi(copies);
			strcpy(isAvail, strtok(NULL, "-"));
			Video->videoisAvailable = atoi(isAvail);
			count_id++;
			Video->next = ptr;					
			Video->prev = ptr->prev;				
			ptr->prev->next = ptr->prev = Video;			
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void VideoNodeLList::add(VideoNode* v,string& title, string& genre, string& production, int& numberOfCopies){
	VideoNode *Video = new VideoNode;
	int id  = count_id;
	Video->videoID = ++id;
	Video->videoTitle = title;
	Video->videoGenre = genre;
	Video->videoProduction = production;
	Video->videoCopies = numberOfCopies;
	Video->videoisAvailable = Video->videoCopies != 0 ? true:false;
	
	Video->next = v;				
	Video->prev = v->prev;			
	v->prev->next = v->prev = Video; 
	
	file.open("VideoNodeLList.txt", ios::out | ios::app);
	file << "\n" << Video->videoID 		<< "-" 
		 << Video->videoTitle			<< "-"
		 << Video->videoGenre			<< "-"
		 << Video->videoProduction		<< "-"
		 << Video->videoCopies			<< "-"
		 << Video->videoisAvailable		<< "\n";
	file.close();
}
void VideoNodeLList::searchVideo(int& id){
	VideoNode* ptr = head->next;
	while(ptr != tail && id != ptr->videoID){
		ptr = ptr->next;
	}
	cout << "Video ID: "  		 << ptr->videoID 			<< "\n"
		 << "Title: " 	 	 	 << ptr->videoTitle			<< "\n"
		 << "Genre: " 	 	 	 << ptr->videoGenre			<< "\n"
		 << "Production: "		 << ptr->videoProduction		<< "\n"
		 << "Number of Copies: " << ptr->videoCopies	<< "\n";
	cout << "\n";
}
void VideoNodeLList::addVideo(string& title, string& genre, string& production, int& numberOfCopies){
	add(tail, title, genre, production, numberOfCopies);
}
void VideoNodeLList::remove(VideoNode* v){
	VideoNode* Video = v->prev;
	VideoNode* w = v->next;
	Video->next = w;
	w->prev = Video;
	delete v;
}
void VideoNodeLList::isAvailVideo(int& id){
	VideoNode* ptr = head->next;
	while(ptr != tail && id != ptr->videoID){
		ptr = ptr->next;
	}

	cout << "Video ID: "  		 << ptr->videoID 			<< "\n"
		 << "Title: " 	 	 	 << ptr->videoTitle			<< "\n"
		 << "Genre: " 	 	 	 << ptr->videoGenre			<< "\n"
		 << "Production: "		 << ptr->videoProduction		<< "\n"
		 << "Number of Copies: " << ptr->videoCopies	<< "\n"
		 << "Availability: "	 << (ptr->videoisAvailable ? "Available":"Not Available")	<< "\n";
	cout << "\n";
}
void VideoNodeLList::listVideo(){
	VideoNode* ptr = head->next;
	int id;
	cout << "Video ID"	 	<< setw(25) 
		 << "Title"  		<< setw(20) 
	     << "Genre" 		<< setw(30) 
		 << "Production" 	<< "\n";
	while(ptr != tail){
		cout << setw(3)
			 << ptr->videoID 		 	<< setw(30) 
		 	 << ptr->videoTitle			<< setw(20) 
		 	 << ptr->videoGenre			<< setw(30) 
		 	 << ptr->videoProduction		<< "\n";

		ptr = ptr->next;
	}
	cout << "\n";
}


class CustomerNodeLList{
	public:
		fstream file;
		int count_id = 0;
		CustomerNodeLList();
		~CustomerNodeLList();
		void addCustomer(string& name, string& address);
		void searchCustomer(const int& id);
		void listCustomer();
		void load();
	protected:
		struct CustomerNode{
		protected:
			int customer_id = 0;
			string customer_name;
			string customer_address;
			CustomerNode *next;
			CustomerNode *prev;
			friend class CustomerNodeLList;
			friend class VideoRentedbyCustomerList;
		};
		CustomerNode* head;
		CustomerNode* tail;
	protected:
		void remove(CustomerNode* c);
};
CustomerNodeLList::CustomerNodeLList(){
	head = new CustomerNode;
	tail = new CustomerNode;
	head->next = tail;
	tail->prev = head;
	load();
}
CustomerNodeLList::~CustomerNodeLList(){
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}
void CustomerNodeLList::addCustomer(string& name, string& address){
	CustomerNode* ptr = head->next;
	CustomerNode *Customer = new CustomerNode;
	int id  = count_id;
	Customer->customer_id = ++id;
	Customer->customer_name = name;
	Customer->customer_address = address;
	Customer->next = ptr;					
	Customer->prev = ptr->prev;				
	ptr->prev->next = ptr->prev = Customer; 	
	file.open("CustomerNodeLList.txt", ios::out | ios::app);
	file << "\n" <<	Customer->customer_id 	<< "-" 
		 << Customer->customer_name		<< "-"
		 << Customer->customer_address		<< "\n";
	file.close();
}

void CustomerNodeLList::remove(CustomerNode* v){
	CustomerNode* Customer = v->prev;
	CustomerNode* w = v->next;
	Customer->next = w;
	w->prev = Customer;
	delete v;
}
void CustomerNodeLList::load(){
	CustomerNode* ptr = head->next;
    char id[3], name[50],address[50];
	ifstream in_file("CustomerNodeLList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  
			CustomerNode* Customer = new CustomerNode;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(id, strtok(temp , "-"));
    		strcpy(name, strtok(NULL, "-"));
    		strcpy(address , strtok(NULL, "-"));
			Customer->customer_id = atoi(id);
			Customer->customer_name = ToString(name);
			Customer->customer_address = ToString(address);
			count_id++;
			Customer->next = ptr;				
			Customer->prev = ptr->prev;				
			ptr->prev->next = ptr->prev = Customer;			
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void CustomerNodeLList::searchCustomer(const int& id){
	CustomerNode* ptr = head->next;
	while(ptr != tail && id != ptr->customer_id){
		ptr = ptr->next;
	}
	cout << "Customer ID: "  	 << ptr->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << ptr->customer_name			<< "\n"
		 << "Genre: " 	 	 	 << ptr->customer_address		<< "\n";
	cout << "\n";
}
void CustomerNodeLList::listCustomer(){
	
	CustomerNode* ptr = head->next;
	int id;
	cout << "Customer ID"	 	<< setw(20) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	while(ptr != tail){
		cout << setw(3)
			 << ptr->customer_id 		 		<< setw(30) 
		 	 << ptr->customer_name			<< setw(40) 
		 	 << ptr->customer_address			<< "\n";
		ptr = ptr->next;
	}
	cout << "\n";
}

struct VideoRentedbyCustomer{
	private:
		int customer_id;
		vector<int> videoID;
		int n = 0;
		VideoRentedbyCustomer* next;
		VideoRentedbyCustomer* prev;
		friend class VideoRentedbyCustomerList;
};

class VideoRentedbyCustomerList: public VideoNodeLList,public CustomerNodeLList{
	public:
		fstream file;
		VideoRentedbyCustomerList();
		~VideoRentedbyCustomerList();
		void rentVideo(int& customerid);
		void returnVideo(int& customerid);
		void load();
		void listCustomerRented();
	private:
		VideoRentedbyCustomer* head;
		VideoRentedbyCustomer* tail;
	protected:
		void remove(VideoRentedbyCustomer* RentedNode);
		void rent(VideoRentedbyCustomer* RentedNode, int& customerid);
		void returnV(VideoRentedbyCustomer* RentedNode, int& customerid);
};
VideoRentedbyCustomerList::VideoRentedbyCustomerList(){
	head = new VideoRentedbyCustomer;
	tail = new VideoRentedbyCustomer;
	head->next = tail;
	tail->prev = head;

	load();
}
VideoRentedbyCustomerList::~VideoRentedbyCustomerList(){
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}
void VideoRentedbyCustomerList::remove(VideoRentedbyCustomer* RentedNode){
	VideoRentedbyCustomer* right = RentedNode->prev;
	VideoRentedbyCustomer* left = RentedNode->next;
	left->next = right;
	right->prev = left;
	delete RentedNode;
}

void VideoRentedbyCustomerList::returnV(VideoRentedbyCustomer* RentedNode, int& customerid){
	if(head->next == tail){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
		
	VideoRentedbyCustomer* u = head->next;
	CustomerNode* ptr = CustomerNodeLList::head->next;
	VideoNode* V = VideoNodeLList::head->next;
	while(u != tail && customerid != u->customer_id){
		u = u->next;
		ptr = ptr->next;
	}
	cout << "Customer ID: "  	 << u->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << ptr->customer_name		<< "\n"
		 << "Address: " 	 	 << ptr->customer_address		<< "\n";
	cout << "\n";
	
	for (vector<int>::iterator it = u->videoID.begin(); it != u->videoID.end(); ++it) {
		while(V != VideoNodeLList::tail && *it != V->videoID) V = V->next;
			cout << "Video ID: "  	<< V->videoID 	<< "\n";
			V->videoCopies++;
			u->n--;
	}
	remove(u);

}

void VideoRentedbyCustomerList::rent(VideoRentedbyCustomer* RentedNode, int& customerid){
	char choice;
	VideoRentedbyCustomer *u = new VideoRentedbyCustomer;
	CustomerNode* p = CustomerNodeLList::head->next;
	while(p != CustomerNodeLList::tail && customerid != p->customer_id){
		p = p->next;
	}
	cout << "Customer ID: "  	 << p->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << p->customer_name		<< "\n"
		 << "Address: " 	 	 << p->customer_address		<< "\n";
	cout << "\n";
	u->customer_id = p->customer_id;
	VideoNode* ptr = VideoNodeLList::head->next;
	int videoID;
	while(choice != 'N'){
		cout << "Video to rent: ";	
		cin >> videoID;
		while(cin.fail()){
			cin.clear();
			cin.sync();
			cout << "Wrong Input! Must be a number: ";
			cin >> videoID;
		}
		while(ptr != VideoNodeLList::tail && videoID != ptr->videoID){
			ptr = ptr->next;
		}
		if(ptr->videoCopies == 0){
			cout << "VIDEO is NOT AVAILABLE" << "\n";
		}
	cout << "Video ID: "  		 << ptr->videoID 		<< "\n"
		 << "Title: " 	 	 	 << ptr->videoTitle		<< "\n"
		 << "Number of Copies: " << ptr->videoCopies	<< "\n";
	cout << "\n";
	ptr->videoCopies--;
	ptr->videoCopies != 0 ? ptr->videoisAvailable = true : ptr->videoisAvailable = false;
	u->videoID.push_back(ptr->videoID);
	u->n++;
	cout << "Rent another Video: (Y/N)";
	cin >> choice;
	}
	
	u->next = RentedNode;					
	u->prev = RentedNode->prev;			
	RentedNode->prev->next = RentedNode->prev = u; 
 	system("pause"); 
	file.open("VideoRentedbyCustomerList.txt", ios::out | ios::app);
	file << "\n" << u->customer_id << "-" 
		 		 << u->n 		   << "-";
	  for (std::vector<int>::iterator it = u->videoID.begin(); it != u->videoID.end(); ++it) {
        	file << *it << "-";
    	}
	file.close();
	
}
void VideoRentedbyCustomerList::returnVideo(int& customerid){
	returnV(tail, customerid);
}
void VideoRentedbyCustomerList::rentVideo(int& customerid){
	rent(tail, customerid);
}
void VideoRentedbyCustomerList::load(){
	VideoRentedbyCustomer* RentedNode = head->next;
    char cid[3], vid[3],nn[3];
	ifstream in_file("VideoRentedbyCustomerList.txt", ios::in); 
    if (in_file.is_open())
	{   
		string str;
		while(getline(in_file, str)){  
			VideoRentedbyCustomer* u = new VideoRentedbyCustomer;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(cid, strtok(temp , "-"));
			u->customer_id = atoi(cid);
    		strcpy(nn, strtok(NULL, "-"));
			u->n = atoi(nn);
			 for (int i = 0; i < u->n; i++) {
				strcpy(vid , strtok(NULL, "-"));
				u->videoID.push_back(atoi(vid));
			}
			u->next = RentedNode;					
			u->prev = RentedNode->prev;			
			RentedNode->prev->next = RentedNode->prev = u;			
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void VideoRentedbyCustomerList::listCustomerRented(){
	VideoRentedbyCustomer* RentedNode = head->next;
	CustomerNode* P = CustomerNodeLList::head->next;
	VideoNode* V = VideoNodeLList::head->next;
	cout << "Customer ID"	 	<< setw(20) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	while(RentedNode != tail && P != CustomerNodeLList::tail){
		cout << setw(3)
			 << RentedNode->customer_id 		 		<< setw(30) 
		 	 << P->customer_name				<< setw(40) 
		 	 << P->customer_address				<< "\n\n";
		cout << "Video ID"	 	<< setw(20) 
		 	 << "Movie Title"  	<< "\n";
		for (vector<int>::iterator it = RentedNode->videoID.begin(); it != RentedNode->videoID.end(); ++it) {
		 	while(V != VideoNodeLList::tail && *it != V->videoID) V = V->next;
				cout << *it << setw(25) << V->videoTitle << "\n";
			}
		P = P->next;
		RentedNode = RentedNode->next;
	}
	cout << "\n";
}


int main(){
	VideoNodeLList V;
	CustomerNodeLList C;
	VideoRentedbyCustomerList RentedNode;
	int choice;
	string title;
	string genre;
	string name;
	string address;
	string production;
	int numberOfCopies;
	int id;
	do{
		system("CLS");
		cout << "\t \t \t \t Video Rental Store \n" << endl;
		cout << "\t(1) New Video" << endl
		     << "\t(2) Rent a Video" << endl
		     << "\t(3) Return a Video" << endl
		     << "\t(4) Show Video Details" << endl
		     << "\t(5) Display all Videos	" << endl
			 << "\t(6) Check Video Availability" << endl
			 << "\t(7) Customer Maintenance" << endl
		     << "\t(8) Exit Program" << endl;
		     cout << "\n \tChoose: ";
		     cin >> choice;
		     switch(choice){
			 	case 1:
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
					break;
				case 2:
					system("CLS");
					cout << "Enter Customer ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Wrong Input! Must be a number: ";
						cin >> id;
					}
					RentedNode.rentVideo(id);
					break;	
				case 3:
					system("CLS");
					cout << "Enter Customer ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Wrong Input! Must be a number: ";
						cin >> id;
					}
					RentedNode.returnVideo(id);
					system("pause");
					break;
				case 4:
					system("CLS");
					cout << "Enter Video ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Wrong Input! Must be a number: ";
						cin >> id;
					}
					V.searchVideo(id);
					system("pause"); 
					break;
				case 5:
					system("CLS");
 					V.listVideo();
 					system("pause"); 
					break;
				case 6:
					system("CLS");
					cout << "Enter Video ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Wrong Input! Must be a number: ";
						cin >> id;
					}
					V.isAvailVideo(id);
					system("pause"); 
					break;
				case 7:
					int c;
					cout << "\t(1) Add New Customer" << endl
		     			 << "\t(2) Show Customer Details" << endl
		     			 << "\t(3) List of Videos Rented by a Customer" << endl;
		     			 cout << "\n \tChoose: ";
		     			 cin >> c;
					switch(c){
						case 1:	
			 				cin.clear();
							cin.sync();						
							system("CLS");
							cout << "Enter Customer Name: ";
							getline(cin, name);
							cout << "Enter Customer Address: ";
							getline(cin, address);
							C.addCustomer(name,address);
							system("pause");
							break;
						case 2:
							system("CLS");
							cout << "Enter Customer ID: ";
							cin >> id;
							while(cin.fail()){
								cin.clear();
								cin.sync();
								cout << "Wrong Input! Must be a number: ";
								cin >> id;
							}
							C.searchCustomer(id);
							system("pause"); 	
							break;
						case 3:
							system("CLS");
 							RentedNode.listCustomerRented();
 							system("pause"); 
							break;
					}
					break;
				case 8:
					V.~VideoNodeLList();
					C.~CustomerNodeLList();
					RentedNode.~VideoRentedbyCustomerList();
					exit(0);
					break;
				default:
					cout << "Invalid Choice" << "\n";
					break;
			 }
			 
	}while(choice != 8);
}



