#include "MyForm.h"
#include "Console_Application.h"


int main() {
	cout << "1. Console Application\n2. Windows Application\n";
	int a;
	cin >> a;
	if (a == 1) {
		Console_Application::Run_Console_Application();
	}
	else if (a == 2) {
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Project2::MyForm form;
		Application::Run(% form);

	}
}
/*
# Data Structures
"Online Marketplace Management System"
Team members :
	George Wagih
	Bishoy Milad
	Joseph Osama
	Jan Faragalla
	Ghaly Shaker
	John Reda
	Fady Sobhy
@ FCIS ASU
*/