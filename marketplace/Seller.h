#pragma once
#include<iostream>
using namespace std;

class Seller
{
public:
	int id;
	string name;
	string email;
	string password;
	static int id_count;
	Seller();
	Seller(string email_, string name_,string password_);
	string Fto_string();
	static  Seller Fto_object(string a);
	~Seller();

};

