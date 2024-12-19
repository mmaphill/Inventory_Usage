/* Developer: Phill Nunez
   Date: 12/15/2024
   Project: Corner Grocer/ Item Tracker Application
   Description: Create an application that analyzes the text records generated throughout the day. */

#include "CORNER_GROCER_H.h" // include the header file for the corner grocer
#include <iostream> // include the input output stream library
#include <fstream> // include the file stream library
#include <string> // include the string library
#include <sstream> // include string stream library
#include <map> // include the map library
#include <stdlib.h> // include the standard library header
#include <chrono> // include the chrono library
#include <thread> // include the thread library

using namespace std;

string nCharString(size_t n, char c) { return string(n, c); } // function to print a specific character a specified number of times

/* Function to set the file to be loaded at the start up of the program */
void FileManager::setFileToLoad(const string& file) { 
	fileToLoad = file;
}
 /* Function to load the file to be read for the user */
void FileManager::loadFile() { // function to load the file of data to be read
	ifstream inputFile(fileToLoad); // open file to read in data
	string line; // variable for each line in the file
	map<string, int> freqList; // variable to store a map of items and item_counts

	if (inputFile.is_open()) { // check to make sure the file has been opened
		cout << "Successfully opened file." << endl; // let the user know that the file opening was successful
		
		while (getline(inputFile, line)) { // get the lines from the file
			stringstream ss(line); // set a variable for the string stream lirary
			string item; // set a variable to hold the name of each item
			while (ss >> item) {
				freqList[item]++; // count the frequency of each item listed
			}
		}
		inputFile.close(); // close the file after opening it.
		
		ofstream outputFile("frequency.dat"); // open file for writing
		if (outputFile.is_open()) { // check to make sure the outputFile has been opened
			for (const auto& pair : freqList) {
				outputFile << pair.first << " " << pair.second << endl; // save the freqList into the outputFile
			}
			this_thread::sleep_for(chrono::seconds(3)); // Simulate progress with a delay
			cout.flush();
		}
		outputFile.close(); // close the backup file 
		cout << "Backup file successfully saved." << endl; // let the user know that the backup file has been created and saved
	}
	else {
		cerr << "Error: Could not open file." << endl; // let the user know that the file could not be opened.
	}
}

/* Function to display the menu options to the user*/
void ItemTracker::menuOptions() {
	/* Display a menu for the user, get input, return input */
	int width = 50; // width of the display screen for the menu
	int menu_input; // variable for user selection from the menu
	/* title strings for the menu */
	string title = "Welcome to the Corner Grocer"; // variable for title
	string option1 = "1. Item Search"; // variable for option 1 in the menu
	string option2 = "2. Print List"; // variable for option 2 in the menu
	string option3 = "3. Print Histogram"; // variable for option 3 in the menu
	string option4 = "4. Exit Program"; // variable for option 4 in the menu
	int needed_spaces = (width - title.size()) / 2 - 1; // number of spaces needed to place the title in the middle of the display screen

	this_thread::sleep_for(chrono::milliseconds(500)); // Simulate progress with delay

	/* Display the title */
	cout << nCharString(width, '*') << endl; // print a line of * to the console
	cout << nCharString(needed_spaces, '*') << " " << title << " " << nCharString(needed_spaces, '*') << endl; // print the title in the middle of the display screen
	cout << nCharString(width, '*') << endl; // print a line of * to the console

	cout << endl << nCharString(width, '*') << endl; // give to empty lines then print a line of * to the console
	needed_spaces = width - 2; // set needed_spaces to the size needed for blank lines with an * on the outside
	for (int i = 0; i < 2; i++) { // run through this loop 2 times
		cout << "*" << nCharString(needed_spaces, ' ') << "*" << endl; // print a line of * to the console
	}
	needed_spaces = (width - option1.size()) / 2; // set needed_spaces to the size needed for menu option 1 to be in the middle of the screen
	cout << "*" << nCharString(needed_spaces, ' ') << option1 << nCharString(needed_spaces - 2, ' ') << "*" << endl; // print option 1 to the center of the display screen
	needed_spaces = (width - option2.size()) / 2 - 1; // set needed_spaces to the size needed for menu option 2 to be in the middle of the screen
	cout << "*" << nCharString(needed_spaces, ' ') << option2 << nCharString(needed_spaces + 1, ' ') << "*" << endl; // print option 2 to the center of the display screen
	needed_spaces = (width - option3.size()) / 2; // set needed_spaces to the size needed for menu option 3 to be in the middle of the screen
	cout << "*" << nCharString(needed_spaces, ' ') << option3 << nCharString(needed_spaces - 2, ' ') << "*" << endl; // print option 3 to the center of the display screen
	needed_spaces = (width - option4.size()) / 2 - 1; // set needed_spaces to the size needed for menu option 4 to be in the middle of th screen
	cout << "*" << nCharString(needed_spaces, ' ') << option4 << nCharString(needed_spaces + 1, ' ') << "*" << endl; // print option 4 to the center of the display screen
	needed_spaces = width - 2; // set needed_spaces to the size needed for blank lines with an * on the outside
	for (int i = 0; i < 2; i++) { // run through this loop 2 times
		cout << "*" << nCharString(needed_spaces, ' ') << "*" << endl; // print a line of * to the console
	}
	cout << nCharString(width, '*') << endl; // give to empty lines then print a line of * to the console

	cout << endl << endl; // put in a couple blank lines 
	cout << "Please enter your menu choice (1, 2, 3, or 4): "; // request user input for the menu selection
}

/* Function to get input from the user for an item search */
void ItemTracker::itemSearch() {
	map<string, int> freqList; // variable to hold the items and counts in one area
	string item, searchItem, singularFormat; // variables to hold the item name and the user input
	int itemCount; // variable to hold the item count

	ifstream file("frequency.dat"); // open the backup file
	if (!file.is_open()) { // check to make sure that the file is open
		cout << "Error opening file." << endl; // let the user know that the file could not be opened
		return;
	}

	while (file >> item >> itemCount) { // while there are still items to in the file, set the item, set the itemCount
		freqList[toLower(item)] = itemCount; // set the item to lower case and make that location for that item in the map equal to it's item count
	}
	file.close(); // close the file after getting the freqList created
	
	do { // do until the while portion of code is met
		cout <<endl <<  "Please enter the item you are searching for: "; // request input from the user
		cin >> searchItem;

		// validate the input is only alpha characters
		if (!InputValidator::getValidateString(searchItem)) {
			cout << endl << "Invalid input. Please try again." << endl; // if it is not valid, let the user know
		}

	} while (!InputValidator::getValidateString(searchItem)); // continue to do this until the input is valid

	if (freqList.find(searchItem) != freqList.end()) { // check to see if the user input item is in the freqList
		if (freqList[searchItem] > 1) {
			cout << endl << "There were " << freqList[searchItem] << " " << searchItem << " found." << endl << endl; // print the name of the item in plural form and its respective count
		}
		else {
			int wordSize = searchItem.size() - 1;
			for (int i = 0; i < wordSize; i++) {
				singularFormat.push_back(searchItem.at(i));
			}
			cout << endl << "There was " << freqList[searchItem] << " " << singularFormat << " found." << endl << endl; // print the name of the item in singular form and its respective count
		}
	}
	else {
		cout << "Item not found." << endl << endl; // if the item is not found, let the user know
	}
	this_thread::sleep_for(chrono::seconds(2)); // Simulate progress with delay
}

/* Function to print all items with their respective count */
void ItemTracker::printAll() {
	string line; // variable to hold the data from the file
	ifstream file("frequency.dat"); // open the backup file

	if (!file.is_open()) { // check to make sure the file is open
		cout << "Error opening file" << endl; // if it is not open, let the user know
	}
	cout << endl; // enter a blank line for aesthetics
	while (getline(file, line)) { // get the next line of data from the file
		cout << line << endl; // print the line of data to the console
	}
	this_thread::sleep_for(chrono::seconds(4)); // Simulate progress with delay
	cout << endl; // enter a blank line for aesthetics
	
	file.close(); // close the file
}

/* Function to print all the items as a histogram chart */
void ItemTracker::printHistogram() {
	map<string, int> freqList; // variable to store the item and the item count in a map of locations
	string item; // variable to hold the item from the file
	string white = "\033[37m"; // variable to set the color of the text on the console to white
	string red = "\033[31m"; // variable to set the color of the text on the console to red
	string yellow = "\033[33m"; // variable to set the color of the text on the console to yellow
	string green = "\033[32m"; // variable to set the color of the text on the console to green
	string blue = "\033[34m"; // variable to set the color of the text on the console to blue
	int itemCount; // variable to hold the itemCount from the file
	unsigned int i; // variable for looping for loops
	ifstream file("frequency.dat"); // open the file "frequency.dat"

	if (!file.is_open()) { // check to make sure the file is open
		cout << "Error opening file." << endl; // let the user know if the file did not open
		return;
	}

	while (file >> item >> itemCount) { // while there is still data on the file, set the item and set the itemCount
		if (itemCount >= 10) { // if the item has a quantity of 10 or more, use the following color code for the histogram
			cout << white << item << " "; // print the item to console
			for (i = 0; i < 3; i++) { // print the first 3 *'s as red
				cout << red << "*";
			}
			for (i = 0; i < 3; i++) { // print the 4 - 6 *'s as yellow
				cout << yellow << "*";
			}
			for (i = 0; i < 3; i++) { // print the 7 - 9 *'s as green 
				cout << green << "*";
			}
			for (i = 9; i < itemCount; i++) { // print the rest of the *'s as blue
				cout << blue << "*";
			}
		}
		else if (itemCount > 6) { // if the item has a quantity of 7 to 9, use the following color code for the histogram
			cout << white << item << " ";
			for (i = 0; i < 3; i++) { // print the first 3 *'s as red
				cout << red << "*";
			}
			for (i = 0; i < 3; i++) { // print the 4 - 6 *'s as yellow
				cout << yellow << "*";
			}
			for (i = 6; i < itemCount; i++) { // print the 7 - 9 *'s as green
				cout << green << "*";
			}
		}
		else if (itemCount > 3) { // if the item has a quantity of 4 to 6, use the following color code for the histogram
			cout << white << item << " ";
			for (i = 0; i < 3; i++) { // print the first 3 *'s as red
				cout << red << "*";
			}
			for (i = 3; i < itemCount; i++) { // print the 4 - 6 *'s as yellow
				cout << yellow << "*";
			}
		}
		else { // if the item has a quantity of 3 or less, use the following color code for the histogram
			cout << white << item << " ";
			for (i = 0; i < itemCount; i++) { // print the *'s as red
				cout << red << "*";
			}
		}
		cout << endl; 
	}
	this_thread::sleep_for(chrono::seconds(4)); // Simulate progress with delay
	cout << white; // set the for printing to the console back to white
	file.close(); // close the file

	cout << endl; // enter a blank line for aesthetics
}

/* Function to exit the program */
void ItemTracker::exitProgram() {
	exit(0); // exit the program and perform cleanup
}

/* Function to set the menu loop for the application */
void ItemTracker::menuLoop() {
	int menuChoice; /// variable to hold the user's choice for the menu

	do { // do the following steps until the while is met
		menuOptions(); // show the menu options
		menuChoice = InputValidator::getValidateInt(); // get user input and validate that it is a number between 1 to 4
		switch (menuChoice) { // set the switch case for the menu choice 
		case 1: // case 1 runs the itemSearch
			itemSearch();
			break;
		case 2: // case 2 runs the printAll
			printAll();
			break;
		case 3: // case 3 runs the printHistogram
			printHistogram();
			break;
		case 4: // case 4 exits the program
			exitProgram();
			break;
		default: // no other choices are valid
			cout << "Invalid choice. Please select a valid option." << endl << endl;
		}
	} while (menuChoice != 4); // continue to do this until the menuChoice is 4
}

/* Function to set the characters of a string to lowercase */
string ItemTracker::toLower(const string& str) {
	string lowerStr = str; // make a copy of the original string
	for (auto& ch : lowerStr) { // go through each character in the string
		ch = tolower(ch); // convert the character to a lower case
	}

	return lowerStr; // return the lowercase string
}

/* function to validate int inputs from the user */
int InputValidator::getValidateInt() {
	int input_num;// variable to hold the number input by the user

	while (true) {
		cin >> input_num; // get the user input

		try { // try the following code
			if (cin.fail() || input_num < 0) { // check to see if the input was an integer and is greater than 0
				throw runtime_error("Invalid input. Input must be a positive integer"); // if the input is invalid, throw this runtime error
			}
			break; 
		}
		catch (const exception& e) { // catch the error and clear the data
			cerr << "Error: " << e.what() << endl; // let the user know that there was an error
			cin.clear(); // clear the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ingore the input that was received
		}
	}
	return input_num; // return the number input by the user
}

/* Function to validate string inputs from the user */
bool InputValidator::getValidateString(const string& input) {
	for (char ch : input) { // run through each character in the string input
		if (!isalpha(ch)) { // check to see if the string is alphabet characters only
			return false; // if not, return false
		}
	}
	return true; // if so, return true
}