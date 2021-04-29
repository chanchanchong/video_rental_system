#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip> 
#include <vector>
#include <sstream>
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
		bool empty() const;
		void preprocessrentedvideos();
		void displayRentedVideo();
		void remove(RentedVideo* r);
	protected:
		Video *vhead;
		Video *vtail;
		Customer *chead;
		Customer *ctail;		
		RentedVideo *rhead;
		RentedVideo *rtail;
		void modifyVideo();
		void modifyRentedVideo();
		//void listRentedVideos();
		//void preprocessrentedvideos();
	private:
		int currentVideo = 0;
		int currentCustomer = 0;
		int currentRented = 0;
};
