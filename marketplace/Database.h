#pragma once
#include<vector>
#include"Product.h"
#include "Seller.h"
#include"Customer.h"
#include"Cart.h"
#include<string>
#include <fstream>
#include <unordered_map>

using namespace std;

class Database
{
public:
    Database();
    unordered_map<string, Customer>::iterator it;
    unordered_map<string, Seller>::iterator it2;
    unordered_map<string, Customer>customers;
    unordered_map<string, Seller> sellers;

    vector<Product*> products;

    unordered_map<int, vector<Product *>> seller_id_products;
    unordered_map<string, vector<Product *>> name_products;
    unordered_map<int, vector<Product *>> category_products;

    int Search_Email_Seller(string target_email, string password);
    int Search_Email_Customer(string target_email, string password);
    int Search_Email_Seller(string target_email);
    int Search_Email_Customer(string target_email);

    vector<Product*> Search_Products(std::string name);
    vector<Product*> All_Products();
    vector<Product*> Search_Products(int category);
    vector<Product*> Search_Products_seller_id(int seller_id);

    void add_Product(Product *p);
    void add_Seller(Seller s);
    void add_Customer(Customer c);

    void load_data();
    void save_data();
    void CustomerFile_To_vector();
    void ProductFile_To_vector();
    void SellerFile_To_vector();
    void Customers_To_file();
    void Products_To_file();
    void Sellers_To_file();
    ~Database();

};

