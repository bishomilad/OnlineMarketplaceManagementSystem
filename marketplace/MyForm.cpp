#include "MyForm.h"

Database db;
std::string email_seller;
std::string email_customer;

[STAThread]

String^ toSystemString(std::string a) {
	String^ str3 = gcnew String(a.data());
	return str3;
}
std::string toStandardString(System::String^ string)
{
	System::IntPtr pointer = Marshal::StringToHGlobalAnsi(string);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string returnString(charPointer, string->Length);
	Marshal::FreeHGlobal(pointer);

	return returnString;
}




void Project2::MyForm::Clear_all_data()
{
	//main page
	// email
	this->textBox1->Text = "";
	// password
	this->textBox2->Text = "";


	//main seller
	// quantity
	this->textBox18->Text = "";
	// category
	this->textBox17->Text = "";
	// price
	this->textBox16->Text = "";
	//name
	this->textBox15->Text = "";
	// seller products
	this->dataGridView3->Rows->Clear();
	this->dataGridView3->Refresh();
	// welcome
	this->label28->Text = "";


	//main customer
	// search name
	this->textBox11->Text = "";
	// search category
	this->textBox12->Text = "";
	// id to buy
	this->textBox13->Text = "";
	// rate to buy
	this->textBox14->Text = "";
	// price
	this->label14->Text = "";
	// main products
	this->dataGridView1->Rows->Clear();
	this->dataGridView1->Refresh();
	// cart 
	this->dataGridView2->Rows->Clear();
	this->dataGridView2->Refresh();
	// welcome
	this->label27->Text = "";



	// reg customer
	// Address
	this->textBox7->Text = "";
	// phone
	this->textBox6->Text = "";
	// name
	this->textBox5->Text = "";
	// password
	this->textBox4->Text = "";
	// email
	this->textBox3->Text = "";



	// reg seller
	// password
	this->textBox19->Text = "";
	// email
	this->textBox9->Text = "";
	// name
	this->textBox8->Text = "";

}

void Project2::MyForm::start_form()
{
	db.load_data();
}

void Project2::MyForm::end_form()
{
	db.save_data();

}

void Project2::MyForm::MainForm_Signin_seller_button() {
	// search email and password seller to login
	email_seller = toStandardString(this->textBox1->Text);
	index_seller = db.Search_Email_Seller(email_seller, toStandardString(this->textBox2->Text));
	if (email_seller.empty() || toStandardString(this->textBox2->Text).empty()) {
		MessageBox::Show("Please fill all the feilds", "Error", MessageBoxButtons::OK);
	}
	// if found
	else if (index_seller != -1) {
		panel5->Hide();
		panel4->Show();
		// show all seller's products
		Print_Seller_products(db.Search_Products_seller_id(index_seller ));
		// welcome
		this->label28->Text = toSystemString(db.sellers[email_seller].name);
	}
	else {
		MessageBox::Show("Invalid email or password", "Error!", MessageBoxButtons::OK);
		email_seller = "";
		index_seller = -1;
	}
}

void Project2::MyForm::MainForm_Signin_customer_button() {
	// search email and password customer to login
	email_customer = toStandardString(this->textBox1->Text);
	index_customer = db.Search_Email_Customer(email_customer, toStandardString(this->textBox2->Text));
	
	if (email_customer.empty() || toStandardString(this->textBox2->Text).empty()) {
		MessageBox::Show("Please fill all the feilds", "Error", MessageBoxButtons::OK);
	}
	// if found
	else if (index_customer != -1) {
		panel5->Hide();
		panel3->Show();
		// show all products to buy
		Print_Customer_Products(db.All_Products());
		// welcome
		this->label27->Text = toSystemString(db.customers[email_customer].name);
	}
	else {
		MessageBox::Show("Invalid email or password", "Error!", MessageBoxButtons::OK);
		email_customer = toStandardString(this->textBox1->Text);
		index_customer = db.Search_Email_Customer(email_customer, toStandardString(this->textBox2->Text));
	}
}

void Project2::MyForm::MainForm_Create_seller_button() {
	// show registration form (seller)
	panel5->Hide();
	panel2->Show();

}
void Project2::MyForm::MainForm_Create_customer_button() {
	// show registration form (customer)
	panel5->Hide();
	panel1->Show();
}

void Project2::MyForm::RegistrationFormSeller_Save_button() {

	string email = toStandardString(this->textBox9->Text);
	
	if (toStandardString(this->textBox8->Text).empty() || email.empty() || toStandardString(this->textBox19->Text).empty()) {
		MessageBox::Show("Please fill all the feilds", "Error", MessageBoxButtons::OK);
	}
	else if (email.find("@yahoo.com") == std::string::npos && email.find("@gmail.com") == std::string::npos && email.find("@cis.asu.edu.eg") == std::string::npos && email.find("@hotmail.com") == std::string::npos) {
			MessageBox::Show("Inalid email", "Error", MessageBoxButtons::OK); 
	}
	//if email not used 
	else if (db.Search_Email_Seller(email) == -1) {
		//(string email_, string name_, string password_) 

		// create Seller
		Seller s = Seller(email, toStandardString(this->textBox8->Text), toStandardString(this->textBox19->Text));
		// save seller in database (push in vector)
		db.add_Seller(s);
		MessageBox::Show("Your account is created", "Done!", MessageBoxButtons::OK);
		// return to main page
		RegistrationFormSeller_Back_button();
	}
	else {
		MessageBox::Show("Email is already used", "Amazon", MessageBoxButtons::OK, MessageBoxIcon::Question);
	}

}
void Project2::MyForm::RegistrationFormSeller_Back_button() {
	// return to main page
	panel2->Hide();
	panel5->Show();
	Clear_all_data();
}

void Project2::MyForm::RegistrationFormCustomer_Save_button() {

	string email = toStandardString(this->textBox3->Text);
	if (toStandardString(this->textBox5->Text).empty() || email.empty() || toStandardString(this->textBox4->Text).empty() || toStandardString(this->textBox6->Text).empty() || toStandardString(this->textBox7->Text).empty()) {
		MessageBox::Show("Please fill all the feilds", "Error", MessageBoxButtons::OK);
	}
	else if (email.find("@yahoo.com") == std::string::npos && email.find("@gmail.com") == std::string::npos && email.find("@cis.asu.edu.eg") == std::string::npos && email.find("@hotmail.com") == std::string::npos) {
			MessageBox::Show("Inalid email", "Error", MessageBoxButtons::OK);
	}
	//if email not used 
	else if (db.Search_Email_Customer(email) == -1) {
		//(string address_, string email_, string name_, string phone_num_, string password_)

		// create Customer
		Customer c = Customer(toStandardString(this->textBox7->Text), email, toStandardString(this->textBox5->Text), toStandardString(this->textBox6->Text), toStandardString(this->textBox4->Text));
		// save Customer in database (push in vector)
		db.add_Customer(c);
		MessageBox::Show("Your account is created", "Done!", MessageBoxButtons::OK);
		// return to main page
		RegistrationFormCustomer_Back_button();

	}
	else {
		MessageBox::Show("Email is already used", "Amazon", MessageBoxButtons::OK, MessageBoxIcon::Question);
	}


}
// return to main page
void Project2::MyForm::RegistrationFormCustomer_Back_button() {
	panel1->Hide();
	panel5->Show();
	Clear_all_data();
}



void Project2::MyForm::Customer_Search() {
	// 11 name 
	// 12 category
	if (this->textBox11->Text == "" && this->textBox12->Text == "") {
		Print_Customer_Products(db.All_Products());
	}
	else if (this->textBox11->Text != "" && this->textBox12->Text != "") {
		Print_Customer_Products(db.Search_Products(stoi(toStandardString(this->textBox12->Text))), db.Search_Products(toStandardString(this->textBox11->Text)));
	}
	else if (this->textBox12->Text != "") {
		Print_Customer_Products(db.Search_Products(stoi(toStandardString(this->textBox12->Text))));
	}
	else if (this->textBox11->Text != "") {
		Print_Customer_Products(db.Search_Products(toStandardString(this->textBox11->Text)));
	}
}


void Project2::MyForm::Customer_Add_to_cart() {

	db.customers[email_customer].cart.add_Product(db.products[stoi(toStandardString(this->textBox13->Text)) - 1], stoi(toStandardString(this->textBox14->Text)));
	// update Products in Cart (dataGridView)
	Print_Customer_Products_in_Cart(db.customers[email_customer].cart.list_Products);
	// update all Products (dataGridView)
	Print_Customer_Products(db.products);
	// update text (total price)
	this->label14->Text = toSystemString(to_string(db.customers[email_customer].cart.Total_price()));
}


void Project2::MyForm::Customer_Checkout() {
	// show total price
	MessageBox::Show("Total Price: " + toSystemString(to_string(db.customers[email_customer].cart.Total_price())), "Amazon", MessageBoxButtons::OK, MessageBoxIcon::Question);
	Customer_Signout();
}


void Project2::MyForm::Customer_Signout() {
	panel3->Hide();
	panel5->Show();
	// clear list of Products in cart (current customer)
	db.customers[email_customer].cart.list_Products.clear();
	// total_price = 0
	db.customers[email_customer].cart.total_price = 0;
	index_customer = -1;
	email_customer = "";
	Clear_all_data();
}

// print list of Products cart in table (dataGridView2)
void Project2::MyForm::Print_Customer_Products_in_Cart(vector<Product*> a) {

	//clear old data in table
	this->dataGridView2->Rows->Clear();
	this->dataGridView2->Refresh();

	// loop in vector to print
	for (int i = 0; i < a.size(); i++) {
		this->dataGridView2->Rows->Add(a[i]->id, toSystemString(a[i]->name), a[i]->price);
	}

}


void Project2::MyForm::Print_Customer_Products(vector<Product*> a) {

	//clear old data in table
	this->dataGridView1->Rows->Clear();
	this->dataGridView1->Refresh();

	// loop in vector to print
	for (int i = 0; i < a.size(); i++) {
		this->dataGridView1->Rows->Add(a[i]->id, toSystemString(a[i]->name), a[i]->price, a[i]->category, a[i]->quantity, a[i]->seller_id, a[i]->average_rate);
	}
}

void Project2::MyForm::Print_Customer_Products(vector<Product*> a, vector<Product*> b) {

	//clear old data in table
	this->dataGridView1->Rows->Clear();
	this->dataGridView1->Refresh();

	// loop in vector to print
	for (int i = 0; i < a.size(); i++) {
		this->dataGridView1->Rows->Add(a[i]->id, toSystemString(a[i]->name), a[i]->price, a[i]->category, a[i]->quantity, a[i]->seller_id, a[i]->average_rate);
	}
	for (int i = 0; i < b.size(); i++) {
		this->dataGridView1->Rows->Add(a[i]->id, toSystemString(b[i]->name), b[i]->price, b[i]->category, b[i]->quantity, b[i]->seller_id, b[i]->average_rate);
	}
}


void Project2::MyForm::Seller_Add_product() {
	//(int category_, string name_, float price_, int quantity_, int seller_id_)
	// create Product
	Product *p = new Product(stoi(toStandardString(this->textBox17->Text)), toStandardString(this->textBox15->Text), stof(toStandardString(this->textBox16->Text)), stoi(toStandardString(this->textBox18->Text)), index_seller);
	// save Product in database (push in vector)
	db.add_Product(p);
	// update Products seller in table (dataGridView)
	Print_Seller_products(db.Search_Products_seller_id(index_seller ));
}

void Project2::MyForm::Seller_Edit_product(){
	string what_change= toStandardString(this->comboBox1->Text);
	int id_to_change= stoi(toStandardString(this->textBox20->Text));
	string new_value= toStandardString(this->textBox10->Text);
	if (what_change == "price") {
		db.products[id_to_change - 1]->price = stof(new_value);
	}		
	else if (what_change == "quantity") {
		db.products[id_to_change - 1]->quantity = stoi(new_value);
	}
	Print_Seller_products(db.Search_Products_seller_id(index_seller));
}


void Project2::MyForm::Print_Seller_products(vector<Product*> a) {
	//clear old data in table
	this->dataGridView3->Rows->Clear();
	this->dataGridView3->Refresh();
	// loop in vector to print
	for (int i = 0; i < a.size(); i++) {
		this->dataGridView3->Rows->Add(a[i]->id, toSystemString(a[i]->name), a[i]->price, a[i]->category, a[i]->quantity, a[i]->seller_id, a[i]->average_rate);
	}
}


void Project2::MyForm::Seller_Signout() {
	panel4->Hide();
	panel5->Show();
	index_seller = -1;
	email_seller = "";
	Clear_all_data();
}
