#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

	// Validate that user input is an integer otherwise give user an option to enter 1,2,3, or 4
	void validateInput(int& userInput) {

		while (!(cin >> userInput)) {
			cin.clear();
			cin.ignore(123, '\n');
			cout << "---------------------------------------------------------------------------" << endl;
			cout << "\t\t\t" << "Invalid entry!!! PLEASE TRY AGAIN." << endl;
			cout << "\t\t" << "Please select an option from the menu: 1, 2, 3, or 4" << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			CallProcedure("displayMenu");
			cout << endl;

		}

	}

	// Get user input to run the functions 
	void getUserInput(int& userInput) {

		cout << "\t\t\t" << "WELCOME TO THE CORNER GROCER" << endl;
		CallProcedure("displayMenu");
		cout << endl;
		
		validateInput(userInput);
		while (userInput <= 0 && userInput > 4) { // this while statement will bring the user back to the main menu until s/he does not enter a valid entry
			getUserInput(userInput);
		}

	}

	// Get user input for item to search in the purchased items
	void userValue(string & userItem) {
		cout << "Enter an item to check the frequency it was purchased in a day:" << endl; // Ask user for for a specific item
		while (!(cin >> userItem)) {
			cin.clear();
			cin.ignore(123, '\n');
			cout << "Enter an item to check the frequency it was purchased in a day:" << endl;
		}

	}

	int main()
	{
		// declare variables 
		int userInput = 0;
		ifstream inFS;
		string item;
		int quantity;

		// While statement to execute the program until the user enters '4' to exit.
		while (userInput != 4) {

			getUserInput(userInput); // prints the welcome display to the user asking for user input to run the functions
			string specificItem;
			string userVal;
			if (userInput == 1) { // This will run if the user enters the number '1'
				CallProcedure("printItemsPurchased");// Calls python function to print the purchase amount of each product
			}

			else if (userInput == 2) { // This will run if the user enters the number '2'
				cout << endl;
				userValue(specificItem);
				cout << "Today there were sold " << callIntFunc("printSpecificItem", specificItem) << " " << specificItem << "." << endl;
				cout << endl;
			}
			else if (userInput == 3) { // This  statement will run if the user enters number '3'
				callIntFunc("newFile", "frequency.dat"); // Calls python function to read and write file
				inFS.open("frequency.dat"); //Opens the frequency.dat file
				if (!inFS.is_open()) { //Check if the file is open." << endl;
					break;
				}
				cout << endl;
				while (!inFS.eof()) { // Print the item and the quantities using a histogram '*'
					inFS >> item;
					inFS >> quantity;
					cout << item << ": ";
					for (int i = 0; i < quantity; ++i) { //For loop to increment the quantity using the histogram '*' for each item sold
						cout << "*";
					}
					cout << endl;
				}
				cout << endl;
				inFS.close(); // Close the file
			}

		}
	}