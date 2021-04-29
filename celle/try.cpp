#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip> 
#include <vector>
#include <cstdlib>
using namespace std;
struct Video{
	int id;
	string title;
	string genre;
	string prod;
	int copy;
	bool avail;
	struct Video *next;
	struct Video *prev;
};
struct Customer{
	int id;
	string name;
	string address;
	struct Customer *next;
	struct Customer *prev;
};
struct RentedVideo{
	int customer_id;
	vector<int> video_id;
	int n_vid;
	struct RentedVideo* next;
	struct RentedVideo* prev;
};
class VideoStore{
	public:
		VideoStore();
		~VideoStore();
		fstream F;
		Video* searchV(int id);
		Customer* searchC(int id);
		void addVideo(string videoTitle, string videoGenre,string videoProd, int videoCopy);
		void rentVideo();
		void returnVideo();
		void displayVideo();
		void searchVideo(int id);
		void availVideo(int id);
		void preprocessvideo();
		
		//customer
		void enqueuecustomer(string &customerName, string &customerAddress);
		void displayCustomer();
		void preprocesscustomer();
		void searchCustomer(int id);
		
		void preprocessrentedvideos();
		void displayRentedVideo();
		RentedVideo* searchR(int id);

	protected:
		Video *vhead;
		Video *vtail;
		Customer *chead;
		Customer *ctail;		
		RentedVideo *rhead;
		RentedVideo *rtail;
		
		
		//void listRentedVideos();
		//void preprocessrentedvideos();
	private:
		int currentVideo = 0;
		int currentCustomer = 0;
		int currentRented = 0;
};

VideoStore::VideoStore(){
	vhead = new Video;
	vtail = new Video;
	vhead->next = vtail;
	vtail->prev = vhead;
	chead = new Customer;
	ctail = new Customer;
	chead->next = ctail;
	ctail->prev = chead;
	rhead = new RentedVideo;
	rtail = new RentedVideo;
	rhead->next = rtail;
	rtail->prev = rhead;
	
	//preprocess the context files and push it to the linkedlist
	preprocessvideo();
	preprocesscustomer();
	preprocessrentedvideos();
}
string converter(char* temp){
    string s(temp);
    return s;
}
VideoStore::~VideoStore(){
	
	Video *v = vhead->next;
	Customer *c = chead->next;
	RentedVideo *r = rhead->next;
	Video *vleft,*vright;
	Customer *cleft,*cright;
	RentedVideo *rleft,*rright;
	while(v != vtail && c != ctail && r != rhead->next){
		vleft = v->prev;
		vright = v->next;
		cleft = c->prev;
		cright = c->next;
		rleft = r->prev;
		rright = r->next;
		vleft->next = vright;
		vright->prev = vleft;
		cleft->next = cright;
		cright->prev = cleft;
		rleft->next = rright;
		rright->prev = rleft;
		delete v, c, r;
	}
	delete vhead, chead, rhead;
	delete vtail, ctail, rtail;
}
Video* VideoStore::searchV(int id){
	Video* v = vhead->next;
	while(v != vtail && id != v->id){
		v = v->next;
	}
	return v;
}
void VideoStore::searchVideo(int id){
	Video* v = searchV(id);
	cout << "Video ID: " << v->id  << "\n" << "Video Title: "  << v->title << "\n" << "Video Genre: " << v->genre << "\n"  << "Video Production: " << v->prod	<< "\n\n";
}
void VideoStore::searchCustomer(int id){
	Customer* c = searchC(id);
	cout << "Customer ID: " << c->id  << "\n" << "Customer Name: "  << c->name << "\n" << "Customer Address: " << c->address << "\n\n";
}
void VideoStore::availVideo(int id){
	Video* v = searchV(id);
	cout << "Video ID: " << v->id  << "\n" << "Video Title: "  << v->title << "\n" << "Video Genre: " << v->genre << "\n"  << "Video Production: " << v->prod	<< "\n" << "Video Copies: " << v->copy	<< "\n\n";
}
Customer* VideoStore::searchC(int id){
	Customer* c = chead->next;
	while(c != ctail && id != c->id){
		c = c->next;
	}
	return c;
}
RentedVideo* VideoStore::searchR(int id){
	RentedVideo* r = rhead->next;
	while(r != rtail && id != r->customer_id){
		r = r->next;
	}
	return r;
}
void VideoStore::displayRentedVideo(){
	if(rhead->next == rtail){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
	RentedVideo* r = rhead->next;
	Customer *c;
	Video *v;
	cout << "Customer ID"	 	<< setw(20) 
		 << "Name"  			<< setw(40) 
	     << "Address" 			<< "\n";
	
	while(r != rtail){
		c = searchC(r->customer_id);
		cout << r->customer_id 		<< setw(30) 
		 	 << c->name				<< setw(40) 
		 	 << c->address			<< "\n";
		cout << "Video ID"	 	<< setw(23) 
		 	 << "Movie Title"  	<< "\n";
		for (vector<int>::iterator it = r->video_id.begin(); it != r->video_id.end(); ++it) {
		 	 v = searchV(*it);
			cout << *it << setw(30) << v->title << "\n";
		}
		r = r->next;
		cout << "\n";
	}
	cout << "\n";
}
void VideoStore::displayVideo(){
	Video *v = vhead->next;
	if(!vhead->next){
		cout << "Empty" << "\n";
		system("pause");
		return;
	}
	cout  << "ID" << setw(13) << "Title" << setw(35) << "Genre" << setw(20) << "Production" << "\n";
	
	while(v != vtail){
		cout << left << setw(10) 
			 << v->id << setw(35) 
		 	 << v->title	<< setw(15) 
		 	 << v->genre << setw(30) 
		 	 << v->prod	<< "\n";
		v = v->next;
	}
}
void VideoStore::displayCustomer(){
	Customer *c = chead->next;
	if(!chead->next){
		cout << "Empty" << "\n";
		system("pause");
		return;
	}
	cout  << "ID" << setw(12) << "Name" << setw(38) << "Address" << "\n";
	
	while(c != ctail){
		cout << left << setw(10) 
			 << c->id << setw(35) 
		 	 << c->name	<< setw(15) 
		 	 << c->address  << "\n";
		c = c->next;
	}
}
void VideoStore::preprocessvideo(){
	Video* ptr = vhead->next;
    char store[30];
	ifstream ff("Videos.txt", ios::in); 
    if (ff.is_open()){   
		string str;
		while(getline(ff, str)){  
			Video* v = new Video;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(store, strtok(temp , "$"));
			v->id = atoi(store);
    		strcpy(store, strtok(NULL, "$"));
    		v->title = converter(store);
    		strcpy(store , strtok(NULL, "$"));
    		v->genre = converter(store);
    		strcpy(store , strtok(NULL, "$"));
    		v->prod = converter(store);
    		strcpy(store, strtok(NULL, "$"));
    		v->copy = atoi(store);
			strcpy(store, strtok(NULL, "$"));
			v->avail = atoi(store);
			currentVideo++;
			v->next = ptr;					
			v->prev = ptr->prev;				
			ptr->prev->next = ptr->prev = v;			
    	 }
    	 ff.close();
    }
    else{
        cout << "cannot read file";
        return;
    }
}
void VideoStore::preprocesscustomer(){
	Customer* ptr = chead->next;
    char store[30];
	ifstream ff("Customers.txt", ios::in); 
    if (ff.is_open()){   
		string str;
		while(getline(ff, str)){  
			Customer* c = new Customer;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(store, strtok(temp , "$"));
			c->id = atoi(store);
    		strcpy(store, strtok(NULL, "$"));
    		c->name = converter(store);
    		strcpy(store , strtok(NULL, "$"));
    		c->address = converter(store);
    		
			currentCustomer++;
			c->next = ptr;					
			c->prev = ptr->prev;				
			ptr->prev->next = ptr->prev = c;			
    	 }
    	 ff.close();
    }
    else{
        cout << "cannot read file";
        return;
    }
}
void VideoStore::preprocessrentedvideos(){
	RentedVideo* last = rhead->next;
    char store[30];
	ifstream ff("RentedVideo.txt", ios::in); 
    if (ff.is_open()){   
		string str;
		while(getline(ff, str)){  
			RentedVideo* r = new RentedVideo;
         	char temp[str.size() + 1];
         	strcpy(temp, str.c_str());
			strcpy(store, strtok(temp , "$"));
			r->customer_id = atoi(store);
			strcpy(store, strtok(NULL, "$"));
			r->n_vid = atoi(store);
			 for (int i = 0; i < r->n_vid; i++) {
				strcpy(store , strtok(NULL, "$"));
				r->video_id.push_back(atoi(store));
			}
			r->next = last;					
			r->prev = last->prev;				
			last->prev->next = last->prev = r;			
    	 }
    	 ff.close();
    }
    else{
        cout << "cannot read file";
        return;
    }
}
void VideoStore::addVideo(string videoTitle, string videoGenre,string videoProd, int videoCopy){
	
	
	Video *last = vtail;
	Video *v = new Video;
	v->id = ++currentVideo;
	v->title = videoTitle;
	v->genre = videoGenre;
	v->prod = videoProd;
	v->copy = videoCopy;
	v->avail = v->copy > 0 ? true:false;
	
	v->next = last;
	v->prev = last->prev;
	last->prev->next = last->prev = v;
	F.open("Videos.txt", ios::app | ios::out);
	F << v->id << "$" << v->title << "$" << v->genre << "$"	<< v->prod << "$" << v->copy << "$"	<< v->avail << "\n";
	F.close();
}
void VideoStore::enqueuecustomer(string &customerName, string &customerAddress){
	Customer *last = ctail;
	Customer *c = new Customer;

	c->id = ++currentCustomer;
	c->name = customerName;
	c->address = customerAddress;
	
	c->next = last;
	c->prev = last->prev;
	last->prev->next = last->prev = c;
		
	F.open("Customers.txt", ios::app | ios::out);
	F << c->id << "$" << c->name << "$" << c->address << "\n";
	F.close();
}
void VideoStore::rentVideo(){
	RentedVideo *last = rtail;
	RentedVideo *r = new RentedVideo;
	int id;
	char cc;	
	cout << "Customer ID: ";
	cin >> id;
	while(cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Please Try number: ";
		cin >> id;
	}
	Customer *c = searchC(id);
	cout << "Customer ID: " << c->id << "\n" << "Title: " << c->name << "\n" << "Address: " << c->address << "\n\n";
	r->customer_id = c->id;

	while(cc != 'N'){
		cout << "Video to rent: ";
		cin >> id;
		while(cin.fail()){
			cin.clear();
			cin.sync();
			cout << "Please Try Integer: ";
			cin >> id;
		}
		Video *v = searchV(id);
		//cout << "Video ID: " << v->id  << "\n" << "Video Title: "  << v->title << "\n" << "Video Genre: " << v->genre << "\n"  << "Video Production: " << v->prod	<< "\n" << "Video Copies: " << v->copy	<< "\n\n";
		if(v->avail == 0){
			cout << "VIDEO NOT AVAILABLE" << "\n"; continue;
		} 
		cout << "Video ID: " << v->id  << "\n" << "Video Title: "  << v->title << "\n" << "Video Genre: " << v->genre << "\n"  << "Video Production: " << v->prod	<< "\n" << "Video Copies: " << v->copy-- << "\n\n";
		v->avail = v->copy != 0 ? true : false;
		r->video_id.push_back(v->id);
		currentRented++;
		r->n_vid++;
		cout << "Rent another Video: (Y/N)";
		cin >> cc;
	}
	r->next = last;				
	r->prev = last->prev;			
	last->prev->next = last->prev = r; 	
	fstream file;
	file.open("RentedVideo.txt", ios::out | ios::app);
	file << r->customer_id << "$" << r->n_vid   << "$";
	for (std::vector<int>::iterator it = r->video_id.begin(); it != r->video_id.end(); ++it) {
        file << *it << "$";
    }
    file << "\n" ;
	file.close();
}
void VideoStore::returnVideo(){	
	RentedVideo* last = rtail;
	Video* v;
	if(chead->next == ctail){
		cout << "No Rented Videos" << "\n";
		system("pause");
		return;
	}
	int id;
	cout << "Enter Customer ID: ";
	cin >> id;
	while(cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Please Try Integer: ";
		cin >> id;
	}
	RentedVideo* r = searchR(id);
	Customer* c = searchC(id);
	if(r == rtail){
		cout << "Rented Video Not Found!" << "\n";
		return;
	}
	cout << "Customer ID: " << r->customer_id  << "\n" << "Title: " << c->name	<< "\n" << "Address: " << c->address << "\n\n";
	for (vector<int>::iterator it = r->video_id.begin(); it != r->video_id.end(); ++it) {
		v = searchV(*it);
		cout << "Video ID: "  	<< v->id 	<< "\n";
		v->copy++;
		r->n_vid--;
	}
	cout << "Video successfully return\n";
	RentedVideo* right = r->prev;
	RentedVideo* left = r->next;
	left->next = right;
	right->prev = left;
	delete r;
}


int main(){
	VideoStore V;
	int choice;
	string title;
	string genre;
	string name;
	string address;
	string production;
	int copy;
	int id;
	do{
		system ("cls");
		cout << "=======================================" << endl;
		cout << "   * WELCOME TO ALPHA MOVIE CENTER *" << endl;
		cout << "=======================================" << endl;
		cout << "\n --------------[ MENU ]---------------\n" << endl;
		cout << "\t[1]. Insert a New Video" << endl;
		cout << "\t[2]. Rent a Video" << endl;
		cout << "\t[3]. Return a Video" << endl;
		cout << "\t[4]. Show Video Details" << endl;
		cout << "\t[5]. Display All Videos" << endl; 
		cout << "\t[6]. Check Video Availability" << endl;
		cout << "\t[7]. Customer Maintenance" << endl;
		cout << "\t[8]. Exit the Program" << endl;
		cout << "\n --------------[ MENU ]---------------\n" << endl;
		cout << "\n\t Enter your choice: ";
		cin >> choice;
		     switch(choice){
			 	case 1:
			 		cin.clear();
					cin.sync();
					system("CLS");
					cout << "======================================" << endl;
					cout << "\t  *INSERT A NEW VIDEO*" << endl;
					cout << "======================================" << endl;	
					cout << "\n --[ ENTER THE FOLLOWING DETAIL/S ]--\n" << endl;
					cout << "Enter Video Title: ";
					getline(cin, title);
					cout << "Enter Video Genre: ";
					getline(cin, genre);	
					cout << "Enter Video Production: ";
					getline(cin, production);
					cout << "Enter number of copies: ";
					cin >> copy;
					V.addVideo(title,genre,production,copy);
					system("pause"); 
					break;
				case 2:
					system("CLS");
					cout << "======================================" << endl;
					cout << "\t  *RENT A NEW VIDEO*" << endl;
					cout << "======================================" << endl;	
					cout << "\n --[ ENTER THE FOLLOWING DETAIL/S ]--\n" << endl;
					V.rentVideo();
					system("pause");
					break;	
				case 3:
					system("CLS");
					cout << "======================================" << endl;
					cout << "\t  *RETURN A VIDEO*" << endl;
					cout << "======================================" << endl;				
					cout << "\n --[ ENTER THE FOLLOWING DETAIL/S ]--\n" << endl;
					V.returnVideo();
					system("pause");
					break;
				case 4:
					system("CLS");
					cout << "======================================" << endl;
					cout << "\t   *VIDEO DETAILS*" << endl;
					cout << "======================================" << endl;						
					cout << "\n --[ ENTER THE FOLLOWING DETAIL/S ]--\n" << endl;
					cout << "Enter Video ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Please Try Integer: ";
						cin >> id;
					}
					V.searchVideo(id);
					system("pause"); 
					break;
				case 5:
					system("CLS");
					cout << "======================================" << endl;
					cout << "\t   *LIST OF VIDEOS*" << endl;
					cout << "======================================\n" << endl;
 					V.displayVideo();
 					system("pause"); 
					break;
				case 6:
					system("CLS");
					cout << "======================================" << endl;
					cout << "\t   *VIDEO AVAILABILITY*" << endl;
					cout << "======================================" << endl;						
					cout << "\n --[ ENTER THE FOLLOWING DETAIL/S ]--\n" << endl;
					cout << "Enter Video ID: ";
					cin >> id;
					while(cin.fail()){
						cin.clear();
						cin.sync();
						cout << "Please Try Integer: ";
						cin >> id;
					}
					V.availVideo(id);
					system("pause"); 
					break;
				case 7:
					int c;
					cout << "======================================" << endl;
					cout << "\t   *CUSTOMER MAINTENACE*" << endl;
					cout << "======================================\n" << endl;	
					cout << "\n --------------[ MENU ]---------------\n" << endl;
					cout << "\t[1]. Add New Custpmer" << endl;
					cout << "\t[2]. Show Customer Details" << endl;
					cout << "\t[3]. List of Videos Rented by a Customer" << endl;
					cout << "\n --------------[ MENU ]---------------\n" << endl;
					cout << "\n\t Enter your choice: ";
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
							V.enqueuecustomer(name,address);
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
							V.searchCustomer(id);
							system("pause"); 	
							break;
						case 3:
							system("CLS");
 							V.displayRentedVideo();
 							system("pause"); 
							break;
						case 4:
							system("CLS");
 							V.displayCustomer();
 							system("pause"); 
							break;
					}
					break;
				case 8:
					V.~VideoStore();
					exit(0);
					break;
				default:
					cout << "Invalid Choice" << "\n";
					break;
			 }
			 
	}while(choice != 8);
}



