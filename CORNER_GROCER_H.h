/* Developer: Phill Nunez
   Date: 12/15/2024
   Project: Corner Grocer/ Item Tracker Application
   Description: Create an application that analyzes the text records generated throughout the day. */

#pragma once
#include <string> // include the string library

using namespace std;

class FileManager {
public:
	// public functions
	void loadFile(); // function to load file
	void setFileToLoad(const string& fileToLoad); // function to set file to load

private:
	//private variables
	string fileToLoad; // private variable to store the file name
};

class ItemTracker {
public:
	void menuOptions(); // function to print the different menu options to the console
	void itemSearch(); // function to search for specific items
	void printAll(); // function to print the complete list of items with the count of times that item is in the list
	void printHistogram(); // function to print the complete list of items in a the form of a histogram
	void exitProgram(); // function to close the program and perform cleanup
	void menuLoop(); // function to loop through the menu options
	string toLower(const string& str); // function to change characters to lowercase
};

class InputValidator {
public:
	static int getValidateInt(); // function get int from the user and validate input
	static bool getValidateString(const string& input); // function to get a string from the user and validate input
};