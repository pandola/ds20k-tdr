#include "Util.h"
#include "bibparser.h"

vector<string> delfields;
vector<string> bibfiles;
vector<string> TempRef; // author at index 1

bool authorCase = false;

void setAuthorCase(bool b){
	authorCase = b;
}

/**
 * @brief To-Do, work in progress to account for Author case
 * @param ref
 */
void AuthorCase(vector<string> &ref){
	int authorIndex = -1, affiliationIndex = -1;
	
	for (unsigned int i = 0; i < ref.size(); ++i){
		string Field = stripField(ref[i]);
		if (Field.compare("author") == 0) {
			//We could just assume author is the first field
			authorIndex = i;
		} else if (Field.compare("affiliation") == 0) {
			affiliationIndex = i;
		}
		if (authorIndex != -1 && affiliationIndex != -1){
			break;
		}
	}
	
	//cout << authorIndex << endl << affiliationIndex << endl;
	if (authorIndex == -1 || affiliationIndex == -1){
		return;
	}
	
	//Found
	string authorContents = stripContents(ref[authorIndex]);
	string affiliationContents = stripContents(ref[affiliationIndex]);
	
	//cout << authorContents << "\n" << affiliationContents << endl;
	
	if (authorContents.find(affiliationContents) != string::npos){
		ref[authorIndex] = "author = {" + affiliationContents + "},\n";
	}
	
}


/**
 * @brief Processes each reference
 * @param inp
 * @param out
 * @param line
 */
void processRef(fstream &inp, fstream &out, string &line){
	string field, contents;
	getline(inp, line);
	while (line.compare("}") != 0) { //While not end of reference
		field = stripField(line);
		if (binSearchStrVector(delfields, field) == -1){
			//Line is something we want at this point
			
			//contents = stripContents(line);
			//cout << line << endl;
			
			TempRef.push_back(line);
		}
		getline(inp, line);
	}
	TempRef.push_back(line);
	
	if (authorCase){
		AuthorCase(TempRef);
	}
	
	//Flush Contents
	for (unsigned int i = 0; i<TempRef.size(); ++i){
		//cout << TempRef[i] << endl;
		out << TempRef[i] << endl;
	}
	
	TempRef.clear(); //clear TempRef
}

/**
 * @brief Processes file
 * @param filenm
 */
void processFile(string filenm){
	cout << "Processing: " << filenm << endl;
	string line;
	fstream bibfile;
	
	bibfile.open(filenm.c_str(), ios::in);
	if (bibfile.is_open()) {
		fstream outputfile;
		outputfile.open(filenm.append(".trim").c_str(), ios::out);
		
		while (getline(bibfile, line)){
			if (line.front() == '@'){
				TempRef.push_back(line);
				processRef(bibfile, outputfile, line);
			} else {
				outputfile << line << endl;
			}
		}
		
		outputfile.close();
	} else {
		cout << "\t|->Unable to open file: " << filenm << endl;
	}
	bibfile.close();
}

/**
 * @brief Process files
 */
void processFiles(){
	sortStringVector(delfields);
	
	for (unsigned int i = 0; i < bibfiles.size(); ++i){
		processFile(bibfiles[i]);
	}
}

/**
 * @brief Appends to file list
 * @param filenm
 */
void appendFileList(string filenm){
	bibfiles.push_back(filenm);
}

/**
 * @brief Appends to del list
 * @param delnm
 */
void appendDelList(string delnm){
	delfields.push_back(delnm);
}

