#include "Product.h"
#include<vector>
#include<unordered_map>

int Product::id_count = 0;
Product::Product() {
	id = id_count + 1;
	name = "";
	price = 0;
	category = 0;
	quantity = 0;
	seller_id = 0;
	Number_Customers = 0;
	Total_rate = 0;
	average_rate = 0;
	id_count++;
}

Product::Product(int category_, string name_, float price_, int quantity_, int seller_id_) {
	id = id_count + 1;
	category = category_;
	name = name_;
	price = price_;
	quantity = quantity_;
	seller_id = seller_id_;
	Number_Customers = 0;
	Total_rate = 0;
	average_rate = 0;
	id_count++;
}


Product* Product::Fto_object(string a) {
	Product *p=new Product; //pointer object because we will use the pointer objects in database.h
	queue<string> temp;
	string temp_st = "";
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '/') {
			temp.push(temp_st);
			temp_st = "";
		}
		else {
			temp_st += a[i];
		}
	}
	p->category = stoi(temp.front()); //string to integer
	temp.pop();
	p->name = temp.front();
	temp.pop();
	p->price = stoi(temp.front());
	temp.pop();
	p->quantity = stoi(temp.front());
	temp.pop();
	p->seller_id = stoi(temp.front());
	temp.pop();
	p->Number_Customers = stoi(temp.front());
	temp.pop();
	p->Total_rate = stoi(temp.front());
	temp.pop();
	p->average_rate = stof(temp.front()); //string to float
	return p;
}

string Product::Fto_string() {
	string a = "";
	a += to_string(category) + '/';
	a += name + '/';
	a += to_string(price) + '/';
	a += to_string(quantity) + '/';
	a += to_string(seller_id) + '/';
	a += to_string(Number_Customers) + '/';
	a += to_string(Total_rate) + '/';
	a += to_string(average_rate) + '/';
	return a;
}
void Product::print() {
	cout << category << "\t\t" << id << "\t" << name << "\t" << price << "\t" << quantity << "\t\t" << seller_id << endl;
}

void Product::print_head() {
	cout << "Category\t" << "ID\t" << "Name\t" << "Price\t" << "Quantity\t" << "Seller ID" << endl;
}

void Product::print_vector(vector<Product*> a) {
	print_head();
	for (int i = 0; i < a.size(); i++)
		a[i]->print();
	for (int i = 0; i < 40; i++)cout << "--";
	cout << endl;
}
void Product::print_vector(vector<Product*> a, vector<Product*> b) {
	print_head();
	for (int i = 0; i < a.size(); i++)
		a[i]->print();	
	for (int i = 0; i < b.size(); i++)
		b[i]->print();
	for (int i = 0; i < 40; i++)cout << "--";
	cout << endl;
}

Product::~Product()
{
}

