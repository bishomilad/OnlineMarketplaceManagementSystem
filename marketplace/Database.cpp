#include "Database.h"

Database::Database() {

}



int Database::Search_Email_Customer(string target_email, string password) { //for signing in
	it = customers.find(target_email);
	if (it == customers.end()) { return -1; }
	if (it->second.password == password) {
		return it->second.id;
	}
	else return -1;
}


int Database::Search_Email_Customer(string target_email) { //preventing duplicate emails
	it = customers.find(target_email);
	if (it == customers.end()) {
		return -1;
	}
	else {
		return it->second.id;
	}
}


int Database::Search_Email_Seller(string target_email, string password) { //for signing in
	it2 = sellers.find(target_email);
	if (it2 == sellers.end()) { return -1; }
	if (it2->second.password == password) {
		return it2->second.id;
	}
	else return -1;
}


int Database::Search_Email_Seller(string target_email) { //preventing duplicate emails

	it2 = sellers.find(target_email);
	if (it2 == sellers.end()) {
		return -1;
	}
	else {
		return it2->second.id;
	}
}

vector<Product*> Database::Search_Products(string name) {
	return name_products[name];
}
vector<Product*> Database::All_Products() {
	return products;
}
vector<Product*> Database::Search_Products(int category) { 
	return category_products[category];
}
vector<Product*> Database::Search_Products_seller_id(int seller_id) {
	return seller_id_products[seller_id];
}



void Database::add_Product(Product *p) {
	products.push_back(p);
	seller_id_products[p->seller_id].push_back(p);
	name_products[p->name].push_back(p);
	category_products[p->category].push_back(p);
}

void  Database::add_Seller(Seller s) {
	sellers.insert(make_pair(s.email, s));
}

void Database::add_Customer(Customer c) {
	customers.insert(make_pair(c.email, c));
}

void Database::load_data() {
	CustomerFile_To_vector();
	ProductFile_To_vector();
	SellerFile_To_vector();
}

void Database::save_data() {
	Customers_To_file();
	Products_To_file();
	Sellers_To_file();
}

void  Database::CustomerFile_To_vector() {
	ifstream Customer_file;
	Customer_file.open("Customer.txt");
	string a;
	while (getline(Customer_file, a)) {
		Customer c = Customer::Fto_object(a);
		add_Customer(c);
	}
	Customer_file.close();
}

void  Database::ProductFile_To_vector() {
	ifstream Product_file;
	Product_file.open("Product.txt");
	string a;
	while (getline(Product_file, a)) {
		Product*p = Product::Fto_object(a);
		add_Product(p);
	}
	Product_file.close();
}

void  Database::SellerFile_To_vector() {
	ifstream Seller_file;
	Seller_file.open("Seller.txt");
	string a;
	while (getline(Seller_file, a)) {
		Seller s= Seller::Fto_object(a);
		add_Seller(s);
	}
	Seller_file.close();
}

void  Database::Customers_To_file() {
	ofstream Customer_f_out = ofstream("Customer.txt");
	for (it = customers.begin(); it != customers.end(); it++) {
		Customer_f_out << it->second.Fto_string() << endl;
	}
	Customer_f_out.close();
}

void Database::Products_To_file() {
	ofstream Product_f_out = ofstream("Product.txt");
	for (int i = 0; i < products.size(); i++) {
		Product_f_out << products[i]->Fto_string() << endl;
	}
	Product_f_out.close();
}

void Database::Sellers_To_file() {
	ofstream Seller_f_out = ofstream("Seller.txt");
	for (it2 = sellers.begin(); it2 != sellers.end(); it2++) {
		Seller_f_out << it2->second.Fto_string() << endl;
	}
	Seller_f_out.close();
}

Database::~Database() {

}