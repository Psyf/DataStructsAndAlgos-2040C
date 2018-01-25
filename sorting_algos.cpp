#include <iostream>
#include <ctime> //for measuring running times ofc algorithms 
#include <cstdlib> //for random number generation
#include <vector>
#define MAX_LEN 50000
using namespace std;


void randIntArray(int arr[], int lower, int upper, int len); 
void printArray(int arr[], int len); 
void swap(int arr[], int a, int b) ; 
void selection_sort(int arr[], int len); 
void bubble_sort(int arr[], int len); 
void insertion_sort(int arr[], int len); 
void merge(int arr[], int low, int mid, int high); 
void merge_sort(int arr[], int low, int high); 

int main()
{
	int lower, upper, len; 
	
	while (true)
	{
		//RANDOM MODE
		//Add file mode later 
		//Add manual input mode later
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

		int arr[MAX_LEN];
		randIntArray(arr, lower, upper, len); 

		/*
		//Add more algorithms later
		//Add specific comparison mode later 
		//Add graphing functionality later 
		cout << "Enter number of sorting algoithm you'd like to try:\n";
		cout << "1 for selection Sort\n2 for Selection Sort\n3 for Insertion Sort\n";
		cout << "4 for Merge Sort\n5 for Quick Sort\n6 for Randomized Quick Sort\n7 for Count Sort\n";
		cout << "8 for Radix Sort\n9 for a test run of all the sorting algorithms.:\n"; 
		*/

		double t; 

		//FOR SELECTION SORT
		t=clock(); 
		selection_sort(arr, len);
		t = clock()-t; 
		t /= CLOCKS_PER_SEC;  
		cout << "Sorting using SELECTION Sort. "; 
		//printArray(arr, len); 
		cout << "Time taken: " << t << " seconds.\n\n";
		

		//FOR BUBBLE SORT
		t=clock(); 
		bubble_sort(arr, len);
		t = clock()-t; 
		t /= CLOCKS_PER_SEC;  
		cout << "Sorting using Enhanced Bubble Sort. "; 
		//printArray(arr, len); 
		cout << "Time taken: " << t << " seconds.\n\n";


		//FOR INSERTION SORT
		t=clock(); 
		insertion_sort(arr, len);
		t = clock()-t; 
		t /= CLOCKS_PER_SEC;  
		cout << "Sorting using INSERTION Sort. "; 
		//printArray(arr, len); 
		cout << "Time taken: " << t << " seconds.\n\n";



		//FOR MERGE SORT
		t=clock(); 
		merge_sort(arr, 0, 4);
		t = clock()-t; 
		t /= CLOCKS_PER_SEC;  
		cout << "Sorting using MERGE Sort. "; 
		//printArray(arr, len); 
		cout << "Time taken: " << t << " seconds.\n\n";
	}

	return 0; 
}

//Generates a list of integers of given length from lower to upper 
//NOTE: Generate a graph later to see how random this random is
void randIntArray(int arr[], int lower, int upper, int len)
{
	double t=clock();
	srand(time(NULL)); 
	
	for (int i=0; i<len; i++)
		arr[i] = (rand() % (upper-lower+1)) + lower; 
	t = clock() - t; 
	t=t/CLOCKS_PER_SEC; 
	
	//MODIFY BY: uncommenting the lines below
	//cout << "GENERATED an array of length " << len << " in the range " << lower << "-" << upper << " in " << t << " seconds.\n" ; 
	//printArray(arr, len); 
}

//Prints the array for you
void printArray(int arr[], int len)
{
	for (int i=0; i<len; i++)
		cout << arr[i] << " "; 
	cout << "\n";
}

void swap(int arr[], int a, int b) 
{
	int temp = arr[a]; 
	arr[a] = arr[b]; 
	arr[b] = temp; 
}

void selection_sort(int arr[], int len)
{
	int smallestIdx, smallestInt; 
	bool swapped; 

	for (int i=0; i<len-1; i++)
	{
		smallestInt = arr[i]; 
		smallestIdx = i; 
		swapped = false; 
		for (int j=i+1; j<len; j++)
		{
			if (arr[j] < smallestInt)
			{
				smallestIdx = j; 
				smallestInt = arr[j]; 
				swapped = true; 
			} 
		} 
		if (swapped == false) break; 
		swap(arr, i, smallestIdx);
	}
}

void bubble_sort(int arr[], int len)
{
	bool swapped; 
	int sorted=0; 
	do {
		swapped = false; 
		for (int i=0; i<len-sorted-1; i++)
		{
			if (arr[i] > arr[i+1])
			{
				swapped = true; 
				swap(arr, i, i+1); 
			}
		}
	} while (swapped); 
}

void insertion_sort(int arr[], int len)
{
	int setIndex; 
	int temp; 
	for (int i=1; i<len; i++)
	{
		setIndex=i; 
		//figuring out where to insert
		for (int j=i-1; j>=0; j--)
			if (arr[i] < arr[j]) setIndex = j; 
		temp = arr[i]; 
		//shifting everything to the right and inserting
		for(int k=i; k>setIndex; k--)
			arr[k] = arr[k-1]; 
		arr[setIndex] = temp; 
	}
}

void merge_sort(int arr[], int low, int high)
{
	int mid=(low+high)/2; 
	if (low<high)
	{
		merge_sort(arr, low, mid); 
		merge_sort(arr, mid+1, high); 
		merge(arr, low, mid, high); 
	}
}

//uses std::vector for merging during mergesort
void merge(int arr[], int low, int mid, int high)
{
	int len = high-low+1; 
	vector <int> tempArr;
	tempArr.reserve(len); 
	int left=low, right = mid+1; 

	while(left<=mid && right<=high)
	{
		if (arr[left] < arr[right])
			tempArr.push_back(arr[left++]); 
		else 
			tempArr.push_back(arr[right++]); 
	}

	for (int i=left; i<=mid; i++)
		tempArr.push_back(arr[i]); 
	for (int j=right; j<=high; j++)
		tempArr.push_back(arr[j]); 
	for (int k=0; k<len; k++)
		arr[low++] = tempArr[k];  
}
