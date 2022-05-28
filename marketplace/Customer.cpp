#include "Customer.h"
int Customer::id_count = 0;
Customer::Customer() { //we can Fto_object() here instead with a parameter string a
	id = id_count + 1;
	address = "";
	email = "";
	name = "";
	phone_num = "";
	password = "";
	id_count++;
}
Customer::Customer(string address_, string email_, string name_, string phone_num_, string password_) {
	id = id_count + 1;
	address = address_;
	email = email_;
	name = name_;
	phone_num = phone_num_;
	password = password_;
	id_count++;
}

Customer::~Customer() {

}

Customer Customer::Fto_object(string a) {
	Customer c;
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
	c.name = temp.front();
	temp.pop();
	c.email = temp.front();
	temp.pop();
	c.address = temp.front();
	temp.pop();
	c.phone_num = temp.front();
	temp.pop();
	c.password = temp.front();
	return c;
}
string Customer::Fto_string() {
	string a = "";
	a += name + '/'; //name/
	a += email + '/'; //name/email/
	a += address + '/'; //name/email/address/
	a += phone_num + '/';
	a += password + '/';
	return a; // goes to database.h
}

