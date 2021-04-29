#include "data.h"

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

void VideoStore::remove(RentedVideo* r){
	r = rhead->next;
	RentedVideo* u = r->prev;
	RentedVideo* w = r->next;
	u->next = w;
	w->prev = u;
	delete r;
}
string converter(char* temp){
    string s(temp);
    return s;
}
bool VideoStore::empty() const
{ return (rhead->next == rtail); }

void VideoStore::modifyVideo(){
	//linkedlist rewrites every line in text file
	Video *v = vhead->next;
	F.open("Videos.txt", ios::out);
	F.seekp(0, F.beg);
	while(v != vtail){
		F << v->id << "$" << v->title << "$" << v->genre << "$"	<< v->prod << "$" << v->copy << "$"	<< v->avail << "\n";
		v = v->next;
    }
    F.close();
}

void VideoStore::modifyRentedVideo(){
	RentedVideo *r = rhead->next;
	F.open("RentedVideo.txt", ios::out);
	F.seekp(0, F.beg);
	while(r != rtail){
		F << r->customer_id << "$" << r->n_vid   << "$";
		for (std::vector<int>::iterator it = r->video_id.begin(); it != r->video_id.end(); ++it) {
        	F << *it << "$";
    	}
    	F << "\n";
    	r = r->next;
    }
    F.close();
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
void VideoStore::displayRentedVideo(){
	RentedVideo* r = rhead->next;
	if(r == rtail || empty()){
		cout << "No Rented Videos" << "\n";
		return;
	}
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
		 	 << "Video Title"  	<< "\n";
		for (vector<int>::iterator it = r->video_id.begin(); it != r->video_id.end(); ++it) {
			v = searchV(*it);
			cout << v->id << setw(30) << v->title << "\n";
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
		v->avail = v->copy > 0 ? true : false;
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
	modifyVideo();
}
void VideoStore::returnVideo(){	
RentedVideo* r = rhead->next;
	Video* v;
	if(rhead->next == rtail || empty()){
		cout << "No Rented Videos" << "\n";
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
	
	while(r != rtail && id != r->customer_id){
		r = r->next;
	}
	if(id != r->customer_id){
		cout << "Customer Not Found!\n";
		return; 
	}
	if(r->n_vid == 0){
		cout << "No Rented Videos" << "\n";
		remove(r);
		return;
	}
	if(r == rtail){
		cout << "Rented Video Not Found!" << "\n";
		return;
	}
	Customer* c = searchC(id);
	cout << "Customer ID: " << r->customer_id  << "\n" << "Title: " << c->name	<< "\n" << "Address: " << c->address << "\n\n";
	for (vector<int>::iterator it = r->video_id.begin(); it != r->video_id.end(); ++it) {
		v = searchV(*it);
		cout << "Video ID: "  	<< v->id 	<< "\n";
		v->copy++;
	}
	cout << "Video successfully return\n";
	modifyVideo();
	modifyRentedVideo();
	remove(r);
}

