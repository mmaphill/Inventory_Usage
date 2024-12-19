/* Developer: Phill Nunez
   Date: 12/15/2024
   Project: Corner Grocer/ Item Tracker Application 
   Description: Create an application that analyzes the text records generated throughout the day. */

#include "CORNER_GROCER_H.h"
#include <string> // include the string library
#include <iostream> // include the input output stream library

int main() {
	string fileToLoad = "CS210_Project_Three_Input_File.txt"; // variable to set the file to be loaded 
	FileManager newFile; // create a FileManager object to get the data and save a backup file.
	ItemTracker app; // create an ItemTracker obect named app to run the application functions

	newFile.setFileToLoad(fileToLoad); // set the file to load
	newFile.loadFile(); // load the file and save a backup 

	cout << endl << endl; // enter blank lines for aesthetic

	app.menuLoop(); // run through the menu loop

	return 0; // exit the program
}