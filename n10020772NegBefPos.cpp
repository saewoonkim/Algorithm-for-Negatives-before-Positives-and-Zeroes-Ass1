// n10020772NegBefPos.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

#define SAMPLE 500

void basic_operation_test();
void execution_time_test();
void testing();

void NegBeforePos(int* A, int n);
void NegBeforePos_basicOperation(int* A, int n);
void NegBeforePos_executiontime(int* A, int n);
void show_arr(int A[], int size);

unsigned long long basic_operation = 0;

using namespace std;
using namespace std::chrono;

int main()
{
	testing();
	basic_operation_test();
	execution_time_test();
	printf("finished\n");

	return 0;
}

void testing() {
	int test1[] = { -10,0,5,1,4,-8,3,-2 };
	NegBeforePos(&*test1, 8);
	show_arr(test1, 8);

	int test2[] = { -1 };
	NegBeforePos(&*test2, 1);
	show_arr(test2, 1);

	int test3[] = { 0,-1 };
	NegBeforePos(&*test3, 2);
	show_arr(test3, 2);

	int test4[] = { -1,-1,-1 };
	NegBeforePos(&*test4, 3);
	show_arr(test4, 3);

	int test5[] = { -10,-9,-8,-7,-6,-5,-4,-3,-2,-1 };
	NegBeforePos(&*test5, 10);
	show_arr(test5, 10);

}

void show_arr(int A[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d, ", A[i]);
	printf("\n");
}

void NegBeforePos(int* A, int n) {
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		if (A[i] < 0)
			i++;
		else {
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			j--;
		}
	}
}

void NegBeforePos_executiontime(int* A, int n) {
	NegBeforePos(A, n);
}

void NegBeforePos_basicOperation(int* A, int n) {
	int i = 0;
	int j = n - 1;
	while (i <= j) {
		if (A[i] < 0)
			i++;
		else {
			basic_operation++;
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			j--;
		}
	}
}

void basic_operation_test() {
	/* initialize random seed: */
	srand((int)time(NULL));

	ofstream myfile;
	myfile.open("test1.txt");

	for (int size = 100; size < 5000; size += 100) {
		basic_operation = 0;
		for (int sample = 0; sample < SAMPLE; sample++) {
			int * test;

			test = (int*)malloc(sizeof(int) *(size + 1));
			for (int i = 0; i < size; i++) {
				test[i] = rand() % 60000 - 30000;
			}

			NegBeforePos_basicOperation(&*test, size);

			free(test);
		}
		printf("size %d finished!!\n", size);
		myfile << size << ";" << basic_operation / SAMPLE << "\n";
	}

	myfile.close();
}

void execution_time_test() {
	/* initialize random seed: */
	srand((int)time(NULL));

	ofstream myfile;
	myfile.open("test2.txt");

	for (int size = 100; size < 5000; size += 100) {

		duration<double> time_span = high_resolution_clock::now() - high_resolution_clock::now();
		for (int sample = 0; sample < SAMPLE; sample++) {
			int * test;

			test = (int*)malloc(sizeof(int) *(size + 1));
			for (int i = 0; i < size; i++) {
				test[i] = rand() % 60000 - 30000;
			}

			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			NegBeforePos_basicOperation(&*test, size);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			time_span += duration_cast<duration<double>>(t2 - t1);

			free(test);
		}
		printf("size %d finished!!\n", size);
		myfile << size << ";" << time_span.count() / SAMPLE << "\n";
	}

	myfile.close();
}

