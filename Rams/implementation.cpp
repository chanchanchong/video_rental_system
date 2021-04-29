#include "data.h"

rentedLinkedList::rentedLinkedList(){
	head = new VideoRentedbyCustomer;
	tail = new VideoRentedbyCustomer;
	head->next = tail;
	tail->prev = head;

	prerun();
}
rentedLinkedList::~rentedLinkedList(){
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}
void rentedLinkedList::remove(VideoRentedbyCustomer* RentedNode){
	VideoRentedbyCustomer* right = RentedNode->prev;
	VideoRentedbyCustomer* left = RentedNode->next;
	left->next = right;
	right->prev = left;
	delete RentedNode;
}

void rentedLinkedList::returnV(VideoRentedbyCustomer* RentedNode, int& customerid){
	if(head->next == tail){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
		
	VideoRentedbyCustomer* u = head->next;
	CustomerNode* ptr = CustomerLinkedList::head->next;
	VideoNode* V = VideoLinkedList::head->next;
	while(u != tail && customerid != u->customer_id){
		u = u->next;
		ptr = ptr->next;
	}
	cout << "Customer ID: "  	 << u->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << ptr->customer_name		<< "\n"
		 << "Address: " 	 	 << ptr->customer_address		<< "\n";
	cout << "\n";
	
	for (vector<int>::iterator it = u->videoID.begin(); it != u->videoID.end(); ++it) {
		while(V != VideoLinkedList::tail && *it != V->videoID) V = V->next;
			cout << "Video ID: "  	<< V->videoID 	<< "\n";
			V->videoCopies++;
			u->n--;
	}
	remove(u);

}

void rentedLinkedList::rent(VideoRentedbyCustomer* RentedNode, int& customerid){
	char choice;
	VideoRentedbyCustomer *u = new VideoRentedbyCustomer;
	CustomerNode* p = CustomerLinkedList::head->next;
	while(p != CustomerLinkedList::tail && customerid != p->customer_id){
		p = p->next;
	}
	cout << "Customer ID: "  	 << p->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << p->customer_name		<< "\n"
		 << "Address: " 	 	 << p->customer_address		<< "\n";
	cout << "\n";
	u->customer_id = p->customer_id;
	VideoNode* ptr = VideoLinkedList::head->next;
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
		while(ptr != VideoLinkedList::tail && videoID != ptr->videoID){
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
	file.open("rentedLinkedList.txt", ios::out | ios::app);
	file  << u->customer_id << "*" 
		 		 << u->n	   << "*";
	  for (std::vector<int>::iterator it = u->videoID.begin(); it != u->videoID.end(); ++it) {
        	file << *it << "*";
    	}
	file.close();
	
}
void rentedLinkedList::returnVideo(int& customerid){
	returnV(tail, customerid);
}
void rentedLinkedList::rentVideo(int& customerid){
	rent(tail, customerid);
}
void rentedLinkedList::prerun(){
	VideoRentedbyCustomer* RentedNode = head->next;
    char cid[3], vid[3],nn[3];
	ifstream in_file("rentedLinkedList.txt", ios::in); 
    if (in_file.is_open())
	{   
		string str;
		while(getline(in_file, str)){  
			VideoRentedbyCustomer* u = new VideoRentedbyCustomer;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(cid, strtok(temp , "*"));
			u->customer_id = atoi(cid);
    		strcpy(nn, strtok(NULL, "*"));
			u->n = atoi(nn);
			 for (int i = 0; i < u->n; i++) {
				strcpy(vid , strtok(NULL, "*"));
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
void rentedLinkedList::listCustomerRented(){
	VideoRentedbyCustomer* RentedNode = head->next;
	CustomerNode* P = CustomerLinkedList::head->next;
	VideoNode* V = VideoLinkedList::head->next;
	cout << "Customer ID"	 	<< setw(22) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	while(RentedNode != tail && P != CustomerLinkedList::tail){
		cout << setw(3)
			 << RentedNode->customer_id 		<< setw(30) 
		 	 << P->customer_name				<< setw(40) 
		 	 << P->customer_address				<< "\n\n";
		cout << "Video ID"	 	<< setw(25) 
		 	 << "Movie Title"  	<< "\n";
		for (vector<int>::iterator it = RentedNode->videoID.begin(); it != RentedNode->videoID.end(); ++it) {
		 	while(V != VideoLinkedList::tail && *it != V->videoID) V = V->next;
				cout << *it << setw(32) << V->videoTitle << "\n";
			}
		P = P->next;
		RentedNode = RentedNode->next;
	}
	cout << "\n";
}

VideoLinkedList::VideoLinkedList(){
	head = new VideoNode;
	tail = new VideoNode;
	head->next = tail;
	tail->prev = head;
	prerun();
}
VideoLinkedList::~VideoLinkedList(){
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}

string ToString(char* a){
    string s = a;
    return s;
}
void VideoLinkedList::prerun(){
	VideoNode* ptr = head->next;
    char id[3], title[50],genre[15], production[15], copies[3], isAvail[2];
	file("VideoLinkedList.txt", ios::in); 
    if (file.is_open()){   
		string str;
		while(getline(file, str)){  
			VideoNode* Video = new VideoNode;
         	char ca[str.size() + 1];
         	strcpy(ca, str.c_str());
			strcpy(id, strtok(ca , "*"));
			Video->videoID = atoi(id);
    		strcpy(title, strtok(NULL, "*"));
			Video->videoTitle = ToString(title);
    		strcpy(genre , strtok(NULL, "*"));
			Video->videoGenre = ToString(genre);
    		strcpy(production , strtok(NULL, "*"));
			Video->videoProduction = ToString(production);
    		strcpy(copies, strtok(NULL, "*"));
			Video->videoCopies = atoi(copies);
			strcpy(isAvail, strtok(NULL, "*"));
			Video->videoisAvailable = atoi(isAvail);
			count_id++;
			Video->next = ptr;					
			Video->prev = ptr->prev;				
			ptr->prev->next = ptr->prev = Video;			
    	 }
    	 file.close();
    }
    else{
        cout << "cannot read file";
    }
       
}
void VideoLinkedList::add(VideoNode* v,string& title, string& genre, string& production, int& numberOfCopies){
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
	
	file.open("VideoLinkedList.txt", ios::out | ios::app);
	file << "\n" << Video->videoID 		<< "*" 
		 << Video->videoTitle			<< "*"
		 << Video->videoGenre			<< "*"
		 << Video->videoProduction		<< "*"
		 << Video->videoCopies			<< "*"
		 << Video->videoisAvailable;
	file.close();
}
void VideoLinkedList::search(int& id){
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
void VideoLinkedList::push(string& title, string& genre, string& production, int& numberOfCopies){
	add(tail, title, genre, production, numberOfCopies);
}
void VideoLinkedList::remove(VideoNode* v){
	VideoNode* Video = v->prev;
	VideoNode* w = v->next;
	Video->next = w;
	w->prev = Video;
	delete v;
}
void VideoLinkedList::isAvailable(int& id){
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
void VideoLinkedList::traverse(){
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

CustomerLinkedList::CustomerLinkedList(){
	head = new CustomerNode;
	tail = new CustomerNode;
	head->next = tail;
	tail->prev = head;
	prerun();
}
CustomerLinkedList::~CustomerLinkedList(){
	while(head->next != tail) remove(head->next);
	delete head;
	delete tail;
}
void CustomerLinkedList::addCustomer(string& name, string& address){
	CustomerNode* ptr = head->next;
	CustomerNode *Customer = new CustomerNode;
	int id  = count_id;
	Customer->customer_id = ++id;
	Customer->customer_name = name;
	Customer->customer_address = address;
	Customer->next = ptr;					
	Customer->prev = ptr->prev;				
	ptr->prev->next = ptr->prev = Customer; 
	count_id = Customer->customer_id;	
	file.open("CustomerLinkedList.txt", ios::out | ios::app);
	file << "\n" <<	Customer->customer_id 	<< "*" 
		 << Customer->customer_name		<< "*"
		 << Customer->customer_address;
	file.close();
}

void CustomerLinkedList::remove(CustomerNode* v){
	CustomerNode* Customer = v->prev;
	CustomerNode* w = v->next;
	Customer->next = w;
	w->prev = Customer;
	delete v;
}
void CustomerLinkedList::prerun(){
	CustomerNode* ptr = head->next;
    char id[3], name[50],address[50];
	ifstream in_file("CustomerLinkedList.txt", ios::in); 
    if (in_file.is_open()){   
		string str;
		while(getline(in_file, str)){  
			CustomerNode* Customer = new CustomerNode;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(id, strtok(temp , "*"));
    		strcpy(name, strtok(NULL, "*"));
    		strcpy(address , strtok(NULL, "*"));
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
void CustomerLinkedList::searchCustomer(const int& id){
	CustomerNode* ptr = head->next;
	while(ptr != tail && id != ptr->customer_id){
		ptr = ptr->next;
	}
	cout << "Customer ID: "  	 << ptr->customer_id 			<< "\n"
		 << "Title: " 	 	 	 << ptr->customer_name			<< "\n"
		 << "Genre: " 	 	 	 << ptr->customer_address		<< "\n";
	cout << "\n";
}
void CustomerLinkedList::listCustomer(){
	
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
