#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include"Product.h"
using namespace std;

class Cart
{ 

public:
	Cart();
	float total_price;
	vector<Product*> list_Products;

	void add_Product(Product * p, int rate);
	void checkout();
	float Total_price();

	~Cart();

};
