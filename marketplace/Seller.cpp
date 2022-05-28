#include "Seller.h"
#include "Product.h"

int Seller::id_count = 0;

Seller::Seller() //we can Fto_object() here instead with a parameter string a
{
	id = id_count + 1;
	name = "";
	email = "";
	password = "";
	id_count++;
}

Seller::Seller(string email_, string name_, string password_) {
	id = id_count+1;
	name = name_;
	email = email_;
	password = password_;
	id_count++;
}

string Seller::Fto_string() {
	string a = "";
	a += name + '/';
	a += email + '/';
	a += password + '/';
	return a;
}

Seller Seller::Fto_object(string a) {
	Seller s;
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
	s.name = temp.front();
	temp.pop();
	s.email = temp.front();
	temp.pop();
	s.password = temp.front();
	return s;
}

Seller::~Seller()
{

}
