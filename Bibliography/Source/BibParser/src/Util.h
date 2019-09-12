#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief This function returns the field name of a line read from 
 * reference. 
 * @param line - line of a reference in the form of "field = {content}"
 * @return returns fieldname of line
 */
string stripField(string line);

/**
 * @brief This function returns the contents of a line red from 
 * reference
 * @param line - line of a reference in the form of "field = {content}"
 * @return returns contents
 */
string stripContents(string line);

/**
 * @brief This function swaps elements of a string vector at positions
 * i and j. Make sure i and j are within x : 0 <= x < vector.size()
 * @param vs reference to the vector<string>
 * @param i - index to swap with index j
 * @param j - index to swap with index i
 */
void swapStrVector(vector<string> &vs, int i, int j);

/**
 * @brief Used by QuickSortStrVector function. You don't really call this
 * directly. Call sortStringVector(vs);
 * @param vs - reference to vector<string> you want to sort
 * @param start - start of where you want to partition in resepct to pivot
 * @param end - end of where you want to partition in respect to pivot
 * @return an index corresponding to a value in its correctly placed position.
 */
int partitionStrVector(vector<string> &vs, int start, int end);

/**
 * @brief Quicksort implementation used to sort a vector<string> from
 * indexes start to end. You don't really call this function to sort,
 * call sortStringVector(vs) instead. 
 * @param vs - reference to vector<string> you want to sort
 * @param start - beginning of where you want values to be sorted
 * @param end - end of where you want values to be sorted
 */
void quickSortStrVector(vector<string> &vs, int start, int end);

/**
 * @brief This function sorts strings in a vector<string> in lexicographic 
 * order, that is in alphabetical order with respect to UNICODE orderings. 
 * @param vs - reference to the vector<string> you want to sort.
 */
void sortStringVector(vector<string> &vs);


/**
 * @brief Binary Search implementation which searches for string ln inside
 * of a search space vector<string> vs. 
 * @param vs - reference to SORTED vector<string> you want to look in
 * @param ln - string to look for inside vs
 * @return returns index of ln in vs, -1 if not found. 
 */
int binSearchStrVector(vector<string> &vs, string ln);
#endif