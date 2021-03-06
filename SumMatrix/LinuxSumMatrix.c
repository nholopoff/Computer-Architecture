/* 
 * C program to find the sum of an array using column and row methods.
 * It records the time taken to compute the sum in ms
 * then writes sum and time taken to a cvs file
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void makeFile(double rowTime, double colTime) 
{
	/* Create .csv file */
	printf("Creating output file\n");
	FILE *fp;
	fp = fopen("output.csv", "a");
	if (fp == NULL)
	{
		printf("Error creating file\n");
		exit(1);
	}
	fprintf(fp, "%f", rowTime);
	fprintf(fp, " , ");
	fprintf(fp, "%f\n", colTime);
	fclose(fp);
}

int main() 
{
	static int x = 0, y = 0, rowSum = 0, colSum = 0;
	int a, b, i, count = 0; 
	double rowTime, colTime;
	struct timespec start, end;
	clockid_t id = CLOCK_MONOTONIC;

	for (i = 0; i < 10; i++)
	{
	/* Make two dimensional array */
	printf("Specify 2D Matrix dimensions\n");
	scanf("%d %d", &x, &y);

	/* Make two dimensional array */
	int matrix[x][y];

	/* Fill array */
	for (a = 0; a < x; a++)
	{
		for (b = 0; b < y; b++)
		{
			count++;
			matrix[a][b] = count;
		}
	}
	
	/* Sum the arrays by row */
	rowSum = 0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for (a = 0; a < x; a++) 
	{
		for (b = 0; b < y; b++) 
		{
			rowSum += matrix[a][b];
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	rowTime = (double)((.000001) * ((end.tv_nsec - start.tv_nsec) + (end.tv_nsec - start.tv_nsec)));

	/* Sum the arrays by column */
	colSum = 0;
	clock_gettime(CLOCK_MONOTONIC, &start); 
	for (a = 0; a < x; a++) 
	{
		for (b = 0; b < y; b++) 
		{
			colSum += matrix[b][a];
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	colTime = (double)((.000001) * ((end.tv_nsec - start.tv_nsec) + (end.tv_nsec - start.tv_nsec)));

	makeFile(rowTime, colTime);
	}

	return 0;
}
