#include "Cart.h"
#include "Product.h"
Cart::Cart() {
	total_price = 0;
}
void Cart::add_Product(Product * p, int rate) {
	if (p->quantity > 0) {
		p->Total_rate += rate;
		p->Number_Customers++;
		p->average_rate = (float)(p->Total_rate) / (p->Number_Customers);
		list_Products.push_back(p);
		total_price += p->price;
		p->quantity--; 
	}

}
float Cart::Total_price() { 
	return total_price;
}
void Cart::checkout() {
	Product::print_vector(list_Products);
	cout << "Total Price: " << Total_price() << endl;
	total_price = 0;
	list_Products.clear();
}
Cart::~Cart() {

}
