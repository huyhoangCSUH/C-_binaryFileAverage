#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

float swap_endian(float);
 
int main(int argc, char** argv) {
	clock_t start = clock();
	// Reading the file
	char* fileLoc;
	if (argc < 2) {
		// fileLoc = (char*)"/tmp/out.bin";
		exit (EXIT_FAILURE);
	}
	else
		fileLoc = argv[1];
	cout << "File: " << fileLoc << endl;
	ifstream binfile;
	binfile.open(fileLoc, ios::in | ios::binary);
	if (!binfile.is_open()) {
		cout << "Error reading file!" << endl;
		binfile.close();
		exit (EXIT_FAILURE);
	}

	int totalRows = 10000000; // Number of rows (or records)
	const int totalCols = 4;
	int rowSize[totalCols] = {4, 4, 4, 4}; // layout of a row corresponding to the size of datatype
	float sum[totalCols] = {0, 0, 0, 0};
	unsigned long count[totalCols] = {0, 0, 0, 0};
	
	float tempVal;
	float swapped_val;
	for (int row = 0; row < totalRows; row++) {
		for (int i = 0; i < totalCols; i++) {
			binfile.read((char*)&tempVal, rowSize[i]);
			// float *convertedVal = static_cast<float*>(tempVal);
			swapped_val = swap_endian(tempVal);
			// cout << swapped_val << " "; 
			sum[i] += swapped_val;
			count[i]++;
		}
		// cout << endl;
	}
	clock_t end = clock();
	unsigned long timediff = end - start;
	printf("Time of exe: %lu\n", timediff);
	for (int i = 0; i < totalCols; i++) {
		printf("Avg: %f\n", sum[i]/count[i]);
		// printf("Count: %lu\n", );
	}
	cout << endl;

	return 0;
}

float swap_endian(float numToSwap) {
	union {
    	float numToSwap;
    	unsigned char b[4];
  	} dat1, dat2;

  dat1.numToSwap = numToSwap;
  dat2.b[0] = dat1.b[3];
  dat2.b[1] = dat1.b[2];
  dat2.b[2] = dat1.b[1];
  dat2.b[3] = dat1.b[0];
  return dat2.numToSwap;
}