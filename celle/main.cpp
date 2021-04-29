#include "data.h"
#include "implementation.cpp"
using namespace std;
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

