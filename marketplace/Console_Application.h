#pragma once
#include<iostream>
#include<string>
#include"Product.h"
#include "Seller.h"
#include"Customer.h"
#include"Cart.h"
#include "database.h"
using namespace std;
class Console_Application
{
public:
	void static Run_Console_Application();
	Console_Application();
	~Console_Application();
};
Console_Application::Console_Application() {

}
Console_Application::~Console_Application() {

}
void Console_Application::Run_Console_Application() {
	short int choice;
	Database db;
	int IndexCustomer = 1;
	int IndexSeller = -1;
	//Cart cart;
	string email, password, name;

	/* retrieving the database from previous executions */
	db.load_data();
	bool goback = false; //flag to go back to the first of the loop starting the program
	do //to go back to loop after creating accounts
	{
		choice = 0;
		goback = false;
		cout << "Welcome! \n1: Customer\n2: Seller\n3: Exit" << endl;
		cin >> choice;
		if (choice == 1) //customer
		{
			cout << "1: Sign in \n2: Create an account" << endl;
			cin >> choice;
			if (choice == 1) //sign in customer
			{
				cout << "Write your Email:" << endl;
				cin >> email;
				cout << "Write your password:" << endl;
				cin >> password;
				IndexCustomer = db.Search_Email_Customer(email, password);
				if (IndexCustomer != -1) //if email and password match the db
				{
					int cat = 0, sllr = 0;
					string prodname;
					bool searchagain = true;
					do
					{
						cout << "1: Show all products \n2: Search products by name \n3: Search by name and category \n4: Search by category \n5: Search by seller's ID \n6: Proceed to buy a product" << endl;
						cin >> choice;
						if (choice == 1)
						{
							Product::print_vector(db.All_Products());
						}
						else if (choice == 2)
						{
							cout << "Insert name:\n";
							cin >> prodname;
							Product::print_vector(db.Search_Products(prodname));

						}
						else if (choice == 3)
						{
							cout << "Insert name:\n";
							cin >> prodname;
							cout << "Insert category: (1: Medicines and Health 2:Food 3:Electronics 4:Toys 5:Digital Codes 6: Others)\n";
							cin >> cat;
							Product::print_vector(db.Search_Products(prodname), db.Search_Products(cat));
						}
						else if (choice == 4)
						{
							cout << "Insert category: (1: Medicines and Health 2:Food 3:Electronics 4:Toys 5:Digital Codes 6: Others)\n";
							cin >> cat;
							Product::print_vector(db.Search_Products(cat));
						}
						else if (choice == 5)
						{
							cout << "Insert seller's ID:\n";
							cin >> sllr;
							Product::print_vector(db.Search_Products_seller_id(sllr));
						}
						else if (choice == 6)
						{
							searchagain = false;
						}
					} while (searchagain == true);

					bool exitf = false;
					while (!exitf) //repeats asking about buying or checking out or exiting
					{
						exitf = false;
						cout << "a: Buy a product\nb: Checkout\nc: Exit\n";
						char order;
						int prdid, rating = 0;
						cin >> order;
						switch (order)
						{
						case 'a':
							cout << "Write the product ID and rate it:\n";
							cin >> prdid >> rating;
							if (db.products[prdid - 1]->quantity > 0) {
								db.customers[email].cart.add_Product(db.products[prdid - 1], rating);//4oof lw hn3ml el rating fe func lw7dha
								cout << "Product " << db.products[prdid - 1]->name << "has been added to your cart.\n";
							}
							else {
								cout << "Not enough quantity of this product is available\n";
							}
							break;
						case 'b':
							db.customers[email].cart.checkout();
							break;
						case'c':
							exitf = true;
							break;
						default:
							cout << "Wrong order, try again.\n";
						}
					} if (exitf) goback = false; //to terminate if user chooses c

				}
				else
				{
					cout << "Email and password don't match." << endl;
					goback = true;
				}
			}
			else if (choice == 2) //create an acc customer
			{
				string phonen, addrs;
				bool emaildup = false;  //flag to return back to the loop if email was a duplicate
				do //this do while to check the email
				{
					emaildup = false;
					cout << "Write your email:\n";
					cin >> email;

					if (email.find("@yahoo.com") == std::string::npos && email.find("@gmail.com") == std::string::npos && email.find("@cis.asu.edu.eg") == std::string::npos && email.find("@hotmail.com") == std::string::npos) { //checking for '@' and '.' in an email address
						cout << "Please write a valid email. \n";
						emaildup = true;
					}

					if (db.Search_Email_Customer(email) != -1) {
						cout << "This email is already taken.\n";
						emaildup = true;
					}
				} while (emaildup == true); //if the email already exists in database return to loop
				cout << "Write your password: \n";
				cin >> password;
				cout << "Write your name: \n";
				cin >> name;
				cout << "Write your phone number: \n";
				cin >> phonen;
				cout << "Write your address: \n";
				cin >> addrs;
				Customer cstmr(addrs, email, name, phonen, password);
				db.add_Customer(cstmr); //adding the new customer to the database
				cout << "Account created successfully. " << endl;
				goback = true;
			}
			else { cout << "Wrong option."; goback = true; }
		}
		else if (choice == 2) //seller
		{
			cout << "1: Sign in \n2: Create an account" << endl;
			cin >> choice;
			if (choice == 1) //sign in seller
			{
				cout << "Write your Email:" << endl;
				cin >> email;
				cout << "Write your password:" << endl;
				cin >> password;
				IndexSeller = db.Search_Email_Seller(email, password);
				if (IndexSeller != -1) //if email and password match the db
				{
					string prodname;
					int cat, quantity;
					float price;
					bool sellagain = true;
					do
					{
						sellagain = true;
						cout << "1: View my products \n2: Sell a new product \n3: Edit product\n4: Exit" << endl;
						cin >> choice;
						if (choice == 1) {
							Product::print_vector(db.Search_Products_seller_id(IndexSeller));
						}
						else if (choice == 2) {
							cout << "Write your new product's name:\n";
							cin >> prodname;
							cout << "Write your new product's price:\n";
							cin >> price;
							cout << "Write your new product's category: (1: Medicines and Health 2:Food 3:Electronics 4:Toys 5:Digital Codes 6: Others)\n";
							cin >> cat;
							cout << "How many products will you sell from this kind? \n";
							cin >> quantity;
							Product* prdct = new Product(cat, prodname, price, quantity, db.sellers[email].id);
							db.add_Product(prdct);
							cout << "Product " << prodname << " is available in the market now." << endl;
						}
						else if (choice == 3) {
							cout << "Enter the id of the product you want to modify\n";
							int id_to_modify;
							cin >> id_to_modify;
							id_to_modify -= 1; //to be an index for products vector
							cout << "1: Edit the product price \n2: Edit the product quantity " << endl;
							cin >> choice;

							if (choice == 1) {
								cout << "Enter the new price:\n";
								float new_price;
								cin >> new_price;
								db.products[id_to_modify]->price = new_price;
							}
							else if (choice == 2) {
								cout << "Enter the new quantity:\n";
								int new_quantity;
								cin >> new_quantity;
								db.products[id_to_modify]->quantity = new_quantity;
							}
							else {
								cout << "Wrong order, try again.\n";
							}
						}
						else if (choice == 4) {
							sellagain = false;
							goback = true;
						}
						else
						{
							cout << "Wrong order, try again.\n";
						}

					} while (sellagain == true);

				}
				else
				{
					cout << "Email and password don't match." << endl;
					goback = true;
				}
			}
			else if (choice == 2) //create an acc seller
			{
				bool emaildup = false;  //flag to return back to the loop if email was a duplicate
				do //this do while to check the email
				{
					emaildup = false;
					cout << "Write your email:\n";
					cin >> email;

					if (email.find("@yahoo.com") == std::string::npos && email.find("@gmail.com") == std::string::npos && email.find("@cis.asu.edu.eg") == std::string::npos && email.find("@hotmail.com") == std::string::npos) { //checking for '@' and '.' in an email address
						cout << "Please write a valid email. \n";
						emaildup = true;
					}

					if (db.Search_Email_Seller(email) != -1) {
						cout << "This email is already taken.\n";
						emaildup = true;
					}
				} while (emaildup == true); //if the email already exists in database return to loop
				cout << "Write your password:\n";
				cin >> password;
				cout << "Write your name please:\n";
				cin >> name;
				Seller newseller(email, name, password);
				db.add_Seller(newseller); //adding the new seller to the database
				cout << "Account created successfully." << endl;
				goback = true;
			}
			else { cout << "Wrong option"; goback = true; }
		}
		else {
			goback = false;
		}
	} while (goback == true); //to start the program again after creating accounts

	/* saving all the database in the filesystem for further executions */
	db.save_data();

}