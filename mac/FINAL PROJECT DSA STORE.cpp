#include <iomanip> 
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class CustomerNode{
	protected:
		int customer_id = 0;
		string customer_name;
		string customer_address;
		CustomerNode *next;
		CustomerNode *prev;
	friend class CustomerNodeLList;
	friend class VideoNodeLList;
	friend class VideoRentedbyCustomerList;
};
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
		CustomerNode* searchreturnCustomer(const int& id);
		CustomerNode* head;
		CustomerNode* tail;
	protected:
		void remove(CustomerNode* c);
};
string ToString(char* s){									//primitively converts character array to string
    string w(s);
    return w;
}
CustomerNodeLList::CustomerNodeLList(){					//constructor | automatically runs after creating the object
	head = new CustomerNode;
	tail = new CustomerNode;
	head->next = tail;									
	tail->prev = head;									
	load();												//loads the needed in the text files
}
CustomerNodeLList::~CustomerNodeLList(){				//destructor | autafter deleting the objects
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}
void CustomerNodeLList::addCustomer(string& name, string& address){	//creates a new object
	CustomerNode* ptr = head->next;
	CustomerNode *Customer = new CustomerNode;
	int id  = count_id;
	Customer->customer_id = ++id;
	Customer->customer_name = name;
	Customer->customer_address = address;
	Customer->next = ptr;					//points out the arrows of the newly created object
	Customer->prev = ptr->prev;						
	ptr->prev->next = ptr->prev = Customer; 	
	count_id = Customer->customer_id;
	file.open("CustomerNodeLList.txt", ios::out | ios::app);
	file <<	Customer->customer_id 	<< "||" 
		 << Customer->customer_name		<< "||"
		 << Customer->customer_address  << "\n" ;
	file.close();
}
void CustomerNodeLList::remove(CustomerNode* v){			//removes the bindings of the customer node before deleting it
	CustomerNode* Customer = v->prev;
	CustomerNode* w = v->next;
	Customer->next = w;
	w->prev = Customer;
	delete v;
}
void CustomerNodeLList::load(){					//preprocess the text files after creating the List object
	CustomerNode* ptr = head->next;
    char id[3], name[50],address[50];
	ifstream in_file("CustomerNodeLList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  				//catch per line
			CustomerNode* Customer = new CustomerNode;		//then creates a customer node
         	char temp[str.size() + 1];				
         	strcpy(temp, str.c_str());					//catches the line by temp
			strcpy(id, strtok(temp , "||"));
    		strcpy(name, strtok(NULL, "||"));
    		strcpy(address , strtok(NULL, "||"));
			Customer->customer_id = atoi(id);			//converts char array to int
			Customer->customer_name = ToString(name);
			Customer->customer_address = ToString(address);
			Customer->next = ptr;						//points last customer node to newly created customer node
			Customer->prev = ptr->prev;				
			ptr->prev->next = ptr->prev = Customer;	
			count_id++;									//catches the number of ids
    	 }
    	 in_file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void CustomerNodeLList::searchCustomer(const int& id){
	CustomerNode* ptr = searchreturnCustomer(id);			//traverse for the customerid
		ptr = ptr->next;
	cout << "Customer ID: "  	 << ptr->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << ptr->customer_name			<< "\n"
		 << "Genre: " 	 	 	 << ptr->customer_address		<< "\n";
	cout << "\n";
}
CustomerNode* CustomerNodeLList::searchreturnCustomer(const int& id){		//returns the customer id
	CustomerNode* ptr = head->next;
	while(ptr != tail && id != ptr->customer_id){
		ptr = ptr->next;
	}
	return ptr;		
}
void CustomerNodeLList::listCustomer(){							//list customer
	
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

class VideoNode{
	protected:
		int videoID;
		string videoTitle;
		string videoGenre;
		string videoProduction;
		int videoCopies;
		bool videoisAvailable;
		VideoNode *next;
		VideoNode *prev;
	friend class VideoNodeLList;
	friend class VideoRentedbyCustomerList;
};
class VideoNodeLList{
	public:
		ofstream file;
		int count_id = 0;
		VideoNodeLList();
		~VideoNodeLList();
		void addVideo(string& title, string& genre, string& production, int& numberOfCopies);																				
		void searchVideo(int& id);
		void isAvailVideo(int& id);
		void listVideo();
		void load();
		VideoNode* searchreturn(int& id);
	protected:
		VideoNode* head;
		VideoNode* tail;
		
};


VideoNodeLList::VideoNodeLList(){
	head = new VideoNode;
	tail = new VideoNode;
	head->next = tail;
	tail->prev = head;
}
VideoNodeLList::~VideoNodeLList(){
	VideoNode* p = head->next;
	while(p != tail){
		VideoNode* c = p->prev;
		VideoNode* w = p->next;
		c->next = w;
		w->prev = c;
		delete p;
	}
	delete head;
	delete tail;
}
void VideoNodeLList::load(){							//preloads the file
	VideoNode* ptr = head->next;
    char id[3], title[50],genre[15], production[15], copies[3], isAvail[2];			//serves as temps to store 
	ifstream in_file("VideoNodeLList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		string s;
		while(getline(in_file, str)){  
			VideoNode* Video = new VideoNode;
         	char ca[str.size() + 1];
         	strcpy(ca, str.c_str());
			strcpy(id, strtok(ca , "||"));
			Video->videoID = atoi(id);
    		strcpy(title, strtok(NULL, "||"));
			Video->videoTitle = ToString(title);
    		strcpy(genre , strtok(NULL, "||"));
			Video->videoGenre = ToString(genre);
    		strcpy(production , strtok(NULL, "||"));
			Video->videoProduction = ToString(production);
    		strcpy(copies, strtok(NULL, "||"));
			Video->videoCopies = atoi(copies);
			strcpy(isAvail, strtok(NULL, "||"));
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
void VideoNodeLList::addVideo(string& title, string& genre, string& production, int& numberOfCopies){
	VideoNode* v = tail;
	VideoNode *Video = new VideoNode;
	int id  = count_id;
	Video->videoID = ++id;
	Video->videoTitle = title;
	Video->videoGenre = genre;
	Video->videoProduction = production;
	Video->videoCopies = numberOfCopies;
	Video->videoisAvailable = Video->videoCopies != 0 ? true:false;
	count_id = Video->videoID;
	Video->next = v;				
	Video->prev = v->prev;				
	v->prev->next = v->prev = Video; 	
	
	file.open("VideoNodeLList.txt", ios::out | ios::app);
	file << Video->videoID 				<< "||" 
		 << Video->videoTitle			<< "||"
		 << Video->videoGenre			<< "||"
		 << Video->videoProduction		<< "||"
		 << Video->videoCopies			<< "||"
		 << Video->videoisAvailable		<< "\n" ;
	file.close();
}
void VideoNodeLList::searchVideo(int& id){
	VideoNode* ptr = searchreturn(id);
	cout << "Video ID: "  		 << ptr->videoID 			<< "\n"
		 << "Title: " 	 	 	 << ptr->videoTitle			<< "\n"
		 << "Genre: " 	 	 	 << ptr->videoGenre			<< "\n"
		 << "Production: "		 << ptr->videoProduction	<< "\n"
		 << "Number of Copies: " << ptr->videoCopies	<< "\n";
	cout << "\n";
}
VideoNode* VideoNodeLList::searchreturn(int& id){
	VideoNode* ptr = head->next;
	while(ptr != tail && id != ptr->videoID){
		ptr = ptr->next;
	}
	return ptr;
}
void VideoNodeLList::isAvailVideo(int& id){
	VideoNode* ptr = searchreturn(id);

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
		 	 << ptr->videoProduction	<< setw(30)	
			 << ptr->videoCopies << "\n";

		ptr = ptr->next;
	}
	cout << "\n";
}
class VideoRentedbyCustomer: public VideoNode, public CustomerNode{
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
		void rentVideo(CustomerNodeLList& C, VideoNodeLList& V);
		void returnVideo(CustomerNodeLList& C, VideoNodeLList&V);
		void loadRented();
		void listCustomerRented(CustomerNodeLList& C, VideoNodeLList&V);
	private:
		VideoRentedbyCustomer* head;
		VideoRentedbyCustomer* tail;
	protected:
		void remove(VideoRentedbyCustomer* RentedNode);
};
VideoRentedbyCustomerList::VideoRentedbyCustomerList(){
	head = new VideoRentedbyCustomer;
	tail = new VideoRentedbyCustomer;
	head->next = tail;
	tail->prev = head;
	loadRented();
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

void VideoRentedbyCustomerList::returnVideo(CustomerNodeLList& C, VideoNodeLList& V){
	VideoRentedbyCustomer* RentedNode = tail;
	VideoNode* ptr;
	if(head->next == tail){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
	int cid;
	cout << "Enter Customer ID: ";
	cin >> cid;
	while(cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Please Try Integer: ";
		cin >> cid;
	}
	VideoRentedbyCustomer* u = head->next;
	CustomerNode* p = C.searchreturnCustomer(cid);
	while(u != tail && cid != u->customer_id){
		u = u->next;
	}
	if(u == tail){
		cout << "Customer Not Found!" << "\n";
		return;
	}
	cout << "Customer ID: "  	 << u->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << p->customer_name		<< "\n"
		 << "Address: " 	 	 << p->customer_address		<< "\n";
	cout << "\n";
	
	for (vector<int>::iterator it = u->videoID.begin(); it != u->videoID.end(); ++it) {
			ptr = V.searchreturn(*it);
			cout << "Video ID: "  	<< ptr->videoID 	<< "\n";
			ptr->videoCopies++;
			u->n--;
	}
	remove(u);

}

void VideoRentedbyCustomerList::rentVideo(CustomerNodeLList& C, VideoNodeLList& V){
	char choice;
	VideoRentedbyCustomer* RentedNode = tail;
	VideoRentedbyCustomer *u = new VideoRentedbyCustomer;
	VideoNode* ptr;
	int cid;
	cout << "Enter Customer ID: ";
	cin >> cid;
	while(cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Please Try Integer: ";
		cin >> cid;
	}
	//if customer id exist in the rented videos insert the videos id 
	CustomerNode* p = C.searchreturnCustomer(cid);
	cout << "Customer ID: "  	 << p->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << p->customer_name		<< "\n"
		 << "Address: " 	 	 << p->customer_address		<< "\n";
	cout << "\n";
	u->customer_id = p->customer_id;
	int videoID;
	while(choice != 'N'){
		cout << "Video to rent: ";
		cin >> videoID;
		while(cin.fail()){
			cin.clear();
			cin.sync();
			cout << "Please Try Integer: ";
			cin >> videoID;
		}
		ptr = V.searchreturn(videoID);
		
		if(ptr->videoCopies == 0){
			cout << "VIDEO is NOT AVAILABLE" << "\n";
			continue;
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
	file << u->customer_id << "||" 
		 		 << u->n   << "||";
	  for (std::vector<int>::iterator it = u->videoID.begin(); it != u->videoID.end(); ++it) {
        	file << *it << "||";
    	}
    	file << "\n" ;
	file.close();
	
}
void VideoRentedbyCustomerList::loadRented(){
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
			strcpy(cid, strtok(temp , "||"));
			u->customer_id = atoi(cid);
    		strcpy(nn, strtok(NULL, "||"));
			u->n = atoi(nn);
			 for (int i = 0; i < u->n; i++) {
				strcpy(vid , strtok(NULL, "||"));
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
void VideoRentedbyCustomerList::listCustomerRented(CustomerNodeLList& C, VideoNodeLList& V){
	if(head->next == tail){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
	VideoRentedbyCustomer* RentedNode = head->next;
	CustomerNode* P;
	VideoNode* ptr;
	cout << "Customer ID"	 	<< setw(20) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	
	while(RentedNode != tail && P != tail){
		P = C.searchreturnCustomer(RentedNode->customer_id);
		cout 
			 << RentedNode->customer_id 		<< setw(30) 
		 	 << P->customer_name				<< setw(40) 
		 	 << P->customer_address				<< "\n";
		cout << "Video ID"	 	<< setw(23) 
		 	 << "Movie Title"  	<< "\n";
		for (vector<int>::iterator it = RentedNode->videoID.begin(); it != RentedNode->videoID.end(); ++it) {
		 	ptr = V.searchreturn(*it);
				cout << *it << setw(30) << ptr->videoTitle << "\n";
			}
		P = P->next;
		RentedNode = RentedNode->next;
		cout << "\n";
	}
	cout << "\n";
}


int main(){
	VideoNodeLList V;
	CustomerNodeLList C;
	VideoRentedbyCustomerList RentedNode;
	V.load();
	C.load();
	RentedNode.loadRented();
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
		cout << "\t \t \t \t Video Store \n\n\n" << endl;
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
					/*
					New Video
					Step 1: creates a new video and assigns its title, genre etc.
					Step 2: the last video will point out the newly created video as the next to it.
					vice versa, the newly created video will point out the last video as the previous to it.
					Step 3: the tail pointer will point the newly created video as the last video.
					*/
					V.addVideo(title,genre,production,numberOfCopies);
					system("pause"); 
					break;
				case 2:
					system("CLS");
					/*
					Rent video
					Step 1: while traversing the customer linked list till the customerid
					is found, if found it will store in the CustomerVideoRent Node
					Step 2: while traversing the video linked list till the video id 
					is found, if found it will store in the Customer VideoRent Node and 
					subtracts the number of copies with one. 
					Step 3: if the number of copies have reach zero, the isAvail will turn into false
					Step 4: the last rentedvideo will point out the newly created rentvideo as the next to it.
					vice versa, the newly created rentedvideo will point out the last video as the previous to it.
					Step 5: opens the text file by ios::out(we will write into the text file)
					*/
					RentedNode.rentVideo(C,V);
					break;	
				case 3:
					system("CLS");
					/*
					Step 1: checks the rentedvideo if empty return
					Step 2: while traversing the customer linked list till the customerid
					is found
					Step 3: while traversing the video linked list till the video id 
					is found, if found it will store in the Customer VideoRent Node and 
					adds the number of copies by one. 
					Step 4: prints the rented videos 
					Step 5: deleting the pointers of VideoRent Node
					*/
					RentedNode.returnVideo(C,V);
					system("pause");
					break;
				case 4:
					system("CLS");
					cout << "Enter Video ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Please Try Integer: ";
						cin >> id;
					}
					/*
					Show Video Details
					Step 1: checks the video if empty return
					Step 2: while traversing the video linked list till the video id
					is found, if found prints
					*/
					V.searchVideo(id);
					system("pause"); 
					break;
				case 5:
					system("CLS");
					/*	
					Display Videos
					Step 1: checks the video if empty return
					Step 2: traversing the video linked list while printing it
					*/
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
						cout << "Please Try Integer: ";
						cin >> id;
					}
					/*
					Show Video is available or not
					Step 1: checks the video if empty return
					Step 2: while traversing the video linked list till the video id
					is found, if found prints
					*/
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
							/*Add a new Customer
							Step 1: creates a new Customer and assigns its name and address
							Step 2: the last Customer will point out the newly created Customer as the next to it.
							vice versa, the newly created Customer will point out the last Customer as the previous to it.
							Step 3: the tail pointer will point the newly created Customer as the last Customer 
							*/
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
								cout << "Please Try Integer: ";
								cin >> id;
							}
							/*
							Show Customer details
							Step 1: checks the Customer if empty return
							Step 2: while traversing the Customer linked list till the video id
							is found, if found prints
							*/
							C.searchCustomer(id);
							system("pause"); 	
							break;
						case 3:
							system("CLS");
							/*
							
							Show rented video Details
							Step 1: checks the video if empty return
							Step 2: while traversing the rentedvideo linked list till the customer id
							is found, if found prints its video_ids of the rented videos
							*/
 							RentedNode.listCustomerRented(C,V);
 							system("pause"); 
							break;
						case 4:
							system("CLS");
 							C.listCustomer();
 							system("pause"); 
							break;
					}
					break;
				case 8:
					RentedNode.~VideoRentedbyCustomerList();
					V.~VideoNodeLList();
					C.~CustomerNodeLList();
					exit(0);
					break;
				default:
					cout << "Invalid Choice" << "\n";
					break;
			 }
			 
	}while(choice != 8);
}



