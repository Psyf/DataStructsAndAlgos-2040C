#include <iostream>
#include <ctime> //for measuring running times ofc algorithms 
#include <cstdlib> //for random number generation
#define MAX_LEN 2000
using namespace std;


void randIntArray(int arr[], int lower, int upper, int len); 
void printArray(int arr[], int len); 

int main()
{
	int arr[MAX_LEN], lower, upper, len; 
	
	while (true)
	{
		//RANDOM MODE
		//Add file mode later 
		cout << "Enter [lower_bound] [upper_bound] [length] of your randomly generated array\n";
		cout << "Enter 0 0 0 to exit program:\n";
		cin >> lower >> upper >> len; 

		if (lower==0 && upper==0 && len==0) 
		{
			cout << "See you again!\n\n";
			break; 
		} 

		//Currently restricting length of randomly generated array 
		//Next version will experiement with std::vector and std::array 
		if (len>MAX_LEN) 
		{
			cout<< "ERROR: Max array length is 2000. Try again.\n\n"; 
			continue; 
		}

		randIntArray(arr, lower, upper, len); 
		//Add more algorithms later
		cout << "Enter number of sorting algoithm you'd like to try:\n";
		cout << "1 for Bubble Sort\n2 for Selection Sort\n3 for Insertion Sort\n";
		cout << "4 for Merge Sort\n5 for Quick Sort\n6 for Randomized Quick Sort\n7 for Count Sort\n";
		cout << "8 for Radix Sort\n9 for a test run of all the sorting algorithms.\n"; 
	}
	return 0; 
}

//Generates a list of integers of given length from lower to upper 
void randIntArray(int arr[], int lower, int upper, int len)
{
	double t=clock();
	srand(time(NULL)); 
	
	for (int i=0; i<len; i++)
		arr[i] = (rand() % (upper-lower+1)) + lower; 
	t = clock() - t; 
	t=t/CLOCKS_PER_SEC; 
	cout << "GENERATED an array of length " << len << " in the range " << lower << "-" << upper << " in " << t << " seconds.\n" ; 
	printArray(arr, len); 
}

void printArray(int arr[], int len)
{
	for (int i=0; i<len; i++)
		cout << arr[i] << " "; 
	cout << "\n";
}