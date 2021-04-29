#pragma once
#include <iomanip> 
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



class VideoLinkedList{
	public:
		
		void push(string& title, string& genre, string& production, int& numberOfCopies);																				
		void search(int& id);
		void isAvailable(int& id);
		void traverse();
		void prerun();
		fstream file;
		int count_id = 0;
		VideoLinkedList();
		~VideoLinkedList();
	protected:
		struct VideoNode{
			int videoID;
			string videoTitle;
			string videoGenre;
			string videoProduction;
			int videoCopies;
			bool videoisAvailable;
			struct VideoNode *next;
			struct VideoNode *prev;
			friend class rentedLinkedList;
	};
		VideoNode* head;
		VideoNode* tail;
		
	private:
		void add(VideoNode* v,string& title, string& genre, string& production, int& numberOfCopies);
		void remove(VideoNode* v);
		
};

class CustomerLinkedList{
	public:
		fstream file;
		int count_id = 0;
		CustomerLinkedList();
		~CustomerLinkedList();
		void addCustomer(string& name, string& address);
		void searchCustomer(const int& id);
		void listCustomer();
		void prerun();
	protected:
		struct CustomerNode{
			int customer_id = 0;
			string customer_name;
			string customer_address;
			CustomerNode *next;
			CustomerNode *prev;
			friend class rentedLinkedList;
		};
		CustomerNode* head;
		CustomerNode* tail;
	protected:
		void remove(CustomerNode* c);
};


class rentedLinkedList: public VideoLinkedList,public CustomerLinkedList{
	public:
		fstream file;
		rentedLinkedList();
		~rentedLinkedList();
		void rentVideo(int& customerid);
		void returnVideo(int& customerid);
		void prerun();
		void listCustomerRented();
	private:
		struct VideoRentedbyCustomer{
		int customer_id;
		vector<int> videoID;
		int n = 0;
		VideoRentedbyCustomer* next;
		VideoRentedbyCustomer* prev;
		friend class rentedLinkedList;
};
		VideoRentedbyCustomer* head;
		VideoRentedbyCustomer* tail;
		
	protected:
		void remove(VideoRentedbyCustomer* RentedNode);
		void rent(VideoRentedbyCustomer* RentedNode, int& customerid);
		void returnV(VideoRentedbyCustomer* RentedNode, int& customerid);
};
