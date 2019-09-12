
#include "Util.h"
#include "bibparser.h"
#include <cstring>

int main(int argc, char **argv)
{
	//For debugging arguments
	
	/*
	for (int i = 1; i<argc; ++i)
		cout << argv[i] << endl;
	*/
	
	
	//If no arguments are present
	//if (argc < 2) {
	//	cout << "Type " << argv[0] << " -h for proper usage." << endl;
	//	return 1;
	//}
	
	//For Help Screen
	// To-Do: Make help screen more descriptive
	//if (strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0) {
	//	cout << "Usage: " << argv[0] << " <input filename> [-d | -delfile] <delfile path> [-a | --authorcase]  \n";
	//	cout << "Switches:\n";
	//	cout << "-d  -delfile     - used to specify path to file containing list of fields to\n";
	//	cout << "                   omit.\n";
	//	cout << "-a  --authorcase - toggle author collaboration processing. Program will \n";
	//	cout << "                   search inside.\n";
	//	cout << "                   author field contents of affiliation field. If found, it \n";
	//	cout << "                   will only put the collaboration name in the author field.\n";
		//cout << "\nProgram sources can be found at: \n";
		//cout << "<insert url here>\n\n";
		
	//	return 0;
	//}
	
	/*
	if (argc < 4) {
		cout << "Invalid number of arguments. Type " << argv[0] << " -h for proper usage." << endl; 
		return 1;
	}
	 * */

    //declare blank delfile name
	string delfilename; 
	for (int i = 1; i < argc; ++i) {
		//If argument is a switch
		if (argv[i][0] == '-') { 
			
			//If it is -d switch for specifying files
			if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-delfile") == 0) { 
				
				//check if there is no argument after the switch
				if ((i + 1) == argc){ 
					//Throw error
					cout << "Missing delfile. Type " << argv[0] << " -h for proper usage." << endl; 
					return 2;
				}
				
				//Else set delfilename to argument after the switch
				delfilename = argv[i + 1];
				
				//Increment i by 1
				i++; 
			 
			} else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--authorcase") == 0){
				
				setAuthorCase(true);
				
			} else { //Not a recognized switch
				cout << "Invalid switch type: " << argv[i] << endl;
				return 3;
			}
		
		//Assume if its not a switch, its a bibfile you want to process
		} else { 
			//Append bib file name to File list
			appendFileList(argv[i]); 
		}
	}
	
    delfilename = "ignore.txt";
    setAuthorCase(true);
    appendFileList(argv[1]);
    
	if (delfilename.empty()){
		cout << "No delfile specified.\n" << endl;
		return 2;
	}
	
	//declare filestream to read delfile
	fstream del; 
	
	//open delfile
	del.open(delfilename.c_str(), ios::in); 
	
	//check if delfile is opened(does it exist?)
	if (del.is_open()){ 
		
		//declare line variable
		string line; 
		
		//While there is something to read
		while (getline(del, line)) { 
			
			//if the line is not empty
			if (line.compare("")!=0) { 
				//Append to del list
				appendDelList(line);
			}
		}
		
	} else { //file unable to be open
		cout << "Unable to open delfile: " << delfilename << endl;
		return 4;
	}
	
	//Process Files
	processFiles();
	
	return 0;
}
