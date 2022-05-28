#pragma once
#include<iostream>
#include<string>
#include"Cart.h"
#include"Product.h"
#include<queue>
using namespace std;
class Customer
{
public:
	int id;
	string name;
	string address;
	string email;
	string phone_num;
	string password;
	Cart cart;
	static int id_count;
	Customer();
	Customer(string address_, string email_, string name_, string phone_num_, string password_);

	string Fto_string();
	static Customer Fto_object(string a);
	~Customer();


};
