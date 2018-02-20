/* 
 * C program to find the sum of an array using column and row methods.
 * It records the time taken to compute the sum in ms
 * then writes sum and time taken to a cvs file
 *
 * TODO
 * Fine tune the timer and make it compatible with other platforms aside from Windows
 * 	This means transitioning away from QPC for recording time
 * Make the Matrix dimensions customizable
 */

#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>

void writeToFile(int rowSum, int colSum) {
	/* Create .csv file */
	printf("Creating output file\n");
	FILE *fp;
	fp = fopen("output.csv", "w");
	if (fp == NULL) {
		printf("Error creating file\n");
		exit(1);
	}
	
	/* Write to file */
	fprintf(fp, "Sum by row: %d\n" 
		"Sum by column: %d\n", 
		rowSum, colSum);
	fclose(fp);
	
	/* Review Console */
	printf("File successfully created, press any key to escape\n");
	while(1) {
		if (getchar())
			break;
	}
}

int main() {
	/* Populate a series of 8 index arrays sequentially starting from 1-8 */
	static int rowSum = 0, colSum = 0;
	
	/* Make two dimensional array */
	static int matrix[8][8] = { 
	{1, 2, 3, 4, 5, 6, 7, 8} , 
	{9, 10, 11, 12, 13, 14, 15, 16} , 
	{17, 18, 19, 20, 21, 22, 23, 24} , 
	{25, 26, 27, 28, 29, 30, 31, 32} , 
	{33, 34, 35, 36, 37, 38, 39, 40} , 
	{41, 42, 43, 44, 45, 46, 47, 48} , 
	{49, 50, 51, 52, 53, 54, 55, 56} , 
	{57, 58, 59, 60, 61, 62, 63, 64} 
	};
	
	/* Sum the arrays by row */
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			rowSum += matrix[a][b];
		}
	}
		
	/* Sum the arrays by column */
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			colSum += matrix[b][a];
		}
	}
	
	/* Make .CSV file */
	writeToFile(rowSum, colSum);
	
	return 0;
}

