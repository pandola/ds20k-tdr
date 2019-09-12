#ifndef BIBPARSER_H
#define BIBPARSER_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


/**
 * @brief Sets author case to true or false. If true it will process authors. 
 * @param b - boolean variable to set authors to
 */
void setAuthorCase(bool b);


/**
 * @brief Is called when processFiles encounters an '@' symbol indicating a 
 * reference. Input and output streams are passed into this function to
 * process the Reference as a delegate module. 
 * @param inp - input stream of the bibfile
 * @param out - output stream to the trimmed bib file
 * @param line - temporary line
 */
void processRef(fstream &inp, fstream &out, string &line);

/**
 * @brief Processes each bib file
 * @param filenm - path to bib file
 */
void processFile(string filenm);

/**
 * @brief For all the bib files
 */
void processFiles();

/**
 * @brief Appends vector<string> bibfiles
 * @param filenm - path of bib file
 */
void appendFileList(string filenm);

/**
 * @brief Appends vector<string> delfields 
 * @param delnm - individual fields to be trimmed
 */
void appendDelList(string delnm);

#endif