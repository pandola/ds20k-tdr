#include "Util.h"


/**
 * @brief Binary seraches a string vector for a field
 * @param vs - sorted string vector
 * @param ln - string to be searched for in vs
 * @return index of ln in vs or -1 if not found
 */
int binSearchStrVector(vector<string> &vs, string ln) {
	int lo = 0;
	int hi = vs.size()-1;
	int mid = (lo + hi) / 2;
	
	//
	while (mid != lo && mid != hi) {
		
		if (ln.compare(vs[mid])==0) { //==
			return mid;
		} else if (ln.compare(vs[mid]) < 0) { //before
			hi = mid - 1;
		} else { // compare > 0
			lo = mid + 1;
		}
		mid = (lo + hi)/2;
	}

	if (ln.compare(vs[lo]) == 0) {
		return lo;
	} else if (ln.compare(vs[hi]) == 0) {
		return hi;
	}

	return -1;
}

/**
 * @brief Takes line from reference and returns field name
 * @param ln - line read inside reference
 * @return field name
 */
string stripField(string ln) {
	//cout << "FieldStrip:\t" << ln;
	string s = ln.substr(0, ln.find(" = "));
	/*
	if (s.compare("},")==0){
		cout << ln << ']' << endl;
		cout << s << endl;
	}
	 * */
	return s;
}

/**
 * @brief Takes line from reference and returns field contents
 * @param ln - line read inside reference
 * @return field contents
 */
string stripContents(string ln) {
	int start = ln.find("{") + 1;
	int end = ln.find("},\n");
	return ln.substr(start, end - start);
}

/**
 * @brief Swaps string elements in vector vs at positions i and j
 * @param vs - string vector
 * @param i - index for swap element 1
 * @param j - index for swap element 2
 */
void swapStrVector(vector<string> &vs, int i, int j) {
	string temp = vs[i];
	vs[i] = vs[j];
	vs[j] = temp;
}

/*
 * For QuickSort, partitions vector at start -> end
 * */
int partitionStrVector(vector<string> &vs, int start, int end) {
	string pivot = vs[end];
	int pindex = start;
	
	for (int i = start; i<end; ++i){
		if (vs[i].compare(pivot) <= 0){
			swapStrVector(vs, i, pindex);
			pindex++;
		}
	}
	swapStrVector(vs, pindex, end);
	return pindex;
}

/*
 * For QuickSort, recursive partition sort
 * */
void quickSortStrVector(vector<string> &vs, int start, int end) {
	if (start < end){
		int pIndex = partitionStrVector(vs, start, end);
		quickSortStrVector(vs, start, pIndex-1);
		quickSortStrVector(vs, pIndex+1, end);
	}
}

/**
 * @brief Sorts string vectors using quicksort
 * @param vs - string vector
 */
void sortStringVector(vector<string> &vs) { 
	quickSortStrVector(vs, 0, vs.size() - 1);
}
