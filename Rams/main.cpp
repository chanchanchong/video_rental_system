#include "data.h"
#include "implementation.cpp"
using namespace std;
int main(){
	VideoLinkedList V;
	CustomerLinkedList C;
	rentedLinkedList RentedNode;
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
					V.push(title,genre,production,numberOfCopies);
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
					V.search(id);
					system("pause"); 
					break;
				case 5:
					system("CLS");
 					V.traverse();
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
					V.isAvailable(id);
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
					V.~VideoLinkedList();
					C.~CustomerLinkedList();
					RentedNode.~rentedLinkedList();
					exit(0);
					break;
				default:
					cout << "Invalid Choice" << "\n";
					break;
			 }
			 
	}while(choice != 8);
}



