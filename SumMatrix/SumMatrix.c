/* 
 * C program to find the sum of an array using column and row methods.
 * It records the time taken to compute the sum in ms
 * then writes sum and time taken to a cvs file
 *
 * TODO
 * Fine tune the timer and make it compatible with other platforms aside from Windows
 * 	This means transitioning away from QPC for recording time
 * Make the Matrix dimensions customizable
 * Clean up .CSV output
 */

#include <stdio.h>
#include <windows.h>

void writeToFile(int rowSum, int colSum, double rowTime, double colTime) {
	/* Create .csv file */
	printf("Creating output file\n");
	FILE *fp;
	fp = fopen("output.csv", "w");
	if (fp == NULL) {
		printf("Error creating file\n");
		exit(1);
	}
	
	/* Write to file */
	fprintf(fp, "Sum by row: %d \n" 
	"Sum by column: %d\n"
	"Row calculation time: %f ms\n" 
	"Column calculation time: %f ms\n", 
	rowSum, colSum, rowTime, colTime);
	fclose(fp);
	
	/* Review Console */
	printf("File successfully created, press enter to escape\n");
	while(1) {
		if (getchar())
			break;
	}
}

int main() {
	/* Populate a series of 8 index arrays sequentially starting from 1-8 */
	static int rowSum = 0, colSum = 0;

	/* Time keeping */
	LARGE_INTEGER r1, r2;
	LARGE_INTEGER c1, c2;
	LARGE_INTEGER f1, f2;
	
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
	
	/* Sum the arrays by row and time it*/
	QueryPerformanceFrequency(&f1); 
	QueryPerformanceCounter(&r1);
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			rowSum += matrix[a][b];
		}
	}
	QueryPerformanceCounter(&r2);
	double rowTime = ((double)(r2.QuadPart - r1.QuadPart) / (double)f1.QuadPart) * 100000;
	printf("Row time: %f ms\n", rowTime);
	
	/* Sum the arrays by column and time it*/
	QueryPerformanceFrequency(&f2);
	QueryPerformanceCounter(&c1);
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			colSum += matrix[b][a];
		}
	}
	QueryPerformanceCounter(&c2);
	double colTime = ((double)(c2.QuadPart - c1.QuadPart) / (double)f2.QuadPart) * 100000;
	printf("Column time: %f ms\n", colTime);
	
	/* Make .CSV file */
	writeToFile(rowSum, colSum, rowTime, colTime);
	
	return 0;
}

