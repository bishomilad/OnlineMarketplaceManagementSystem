#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include <unordered_map>
using namespace std;
class Product
{
public:
	int id;
	string name;
	float price;
	int category;
	int quantity; //the number of products in the database now
	int seller_id; // id from seller.h
	int Number_Customers;
	int Total_rate;
	float average_rate;
	static int id_count;

	Product();
	Product(int category_, string name_, float price_, int quantity_, int seller_id_);
	string Fto_string();
	static  Product* Fto_object(string a);
	void print();
	static  void print_vector(vector<Product*>);
	static  void print_vector(vector<Product*>, vector<Product*>);
	static void print_head();
	~Product();

};


