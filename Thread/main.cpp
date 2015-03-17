#include <iostream>
#include <iomanip>
#include <cmath>
#include <thread>
#include "Timer.h"

// InitValues - set array values.  Array items are
//   set to the sqrt of their index in the array.
//
// a - array in which to set values
// first - index of first array item to set
// count - number of items to set
void InitValues(double *a, int first, int count) {
	int limit = first + count;
	for (int i = first; i < limit; ++i) {
		a[i] = sqrt((double)i);
	}
}

// SumValues - sum array values.
//
// a - array to be summed
// sum - return value, the sum of all items in the range
// first - index of first array item to be summed
// count - number of items to sum
void SumValues(const double *a, double *sum, int first, int count) {
	double sumTmp = 0.0;
	int limit = first + count;
	for (int i = first; i < limit; ++i) {
		sumTmp += a[i];
	}
	*sum = sumTmp;
}

// ThreadedSum - initialize and sum a large array using
//   multiple threads.
//
// numThreads - number of threads to use
// arraySize - size of array to use
double ThreadedSum(int numThreads, size_t arraySize) {
	// Write your code here
	double MySum = 0.0;
	double* MyArray = new double[arraySize];
	InitValues(MyArray,0,arraySize);
	SumValues(MyArray, &MySum, 0, arraySize);
	return MySum;
}

int main(int argc, const char * argv[])
{
	// Use the number of hardware threads provided by the CPU(s).
	// If only one hardware thread, use two threads.
	int numThreads = std::thread::hardware_concurrency();
	if (numThreads < 2) numThreads = 2;  // use at least 2 threads

	// Create a Timer object
	Timer t;

	// Run for each power of 2 from 24 to 28 (You may want to start with 10-15 for testing)
	for (int power = 10; power < 15; power++)
	{
		t.StartTimer();
		double sum1 = ThreadedSum(1, 1 << power);
		t.EndTimer();
		std::cout << "Elapsed time: " << t.GetElapsedTime() << ", "
			<< "arraySize " << (1 << power) << ", numThreads = 1, sum = "
			<< std::setprecision(15) << sum1 << std::endl;

		/*t.StartTimer();
		double sumN = ThreadedSum(numThreads, 1 << power);
		t.EndTimer();
		std::cout << "Elapsed time: " << t.GetElapsedTime() << ", "
			<< "arraySize " << (1 << power) << ", numThreads = " << numThreads << ", sum = "
			<< std::setprecision(15) << sumN << std::endl;*/
	}
	system("pause");
	return 0;
}
